import os
import logging

import numpy as np
import torch
import torch.nn as nn
import torch.nn.init as init

from torch.utils.data import Dataset, TensorDataset, ConcatDataset
from torchvision import datasets, transforms
import torchvision

logger = logging.getLogger(__name__)


#######################
# TensorBaord setting #
#######################
def launch_tensor_board(log_path, port, host):
    """Function for initiating TensorBoard.
    
    Args:
        log_path: Path where the log is stored.
        port: Port number used for launching TensorBoard.
        host: Address used for launching TensorBoard.
    """
    os.system(f"tensorboard --logdir={log_path} --port={port} --host={host}")
    return True


#########################
# Weight initialization #
#########################
def init_weights(model, init_type, init_gain):
    """Function for initializing network weights.
    
    Args:
        model: A torch.nn instance to be initialized.
        init_type: Name of an initialization method (normal | xavier | kaiming | orthogonal).
        init_gain: Scaling factor for (normal | xavier | orthogonal).
    
    Reference:
        https://github.com/DS3Lab/forest-prediction/blob/master/pix2pix/models/networks.py
    """

    def init_func(m):
        classname = m.__class__.__name__
        if hasattr(m, 'weight') and (classname.find('Conv') != -1 or classname.find('Linear') != -1):
            if init_type == 'normal':
                init.normal_(m.weight.data, 0.0, init_gain)
            elif init_type == 'xavier':
                init.xavier_normal_(m.weight.data, gain=init_gain)
            elif init_type == 'kaiming':
                init.kaiming_normal_(m.weight.data, a=0, mode='fan_in')
            else:
                raise NotImplementedError(f'[ERROR] ...initialization method [{init_type}] is not implemented!')
            if hasattr(m, 'bias') and m.bias is not None:
                init.constant_(m.bias.data, 0.0)

        elif classname.find('BatchNorm2d') != -1 or classname.find('InstanceNorm2d') != -1:
            init.normal_(m.weight.data, 1.0, init_gain)
            init.constant_(m.bias.data, 0.0)

    model.apply(init_func)


def init_net(model, init_type, init_gain, gpu_ids):
    """Function for initializing network weights.
    
    Args:
        model: A torch.nn.Module to be initialized
        init_type: Name of an initialization method (normal | xavier | kaiming | orthogonal)l
        init_gain: Scaling factor for (normal | xavier | orthogonal).
        gpu_ids: List or int indicating which GPU(s) the network runs on. (e.g., [0, 1, 2], 0)
    
    Returns:
        An initialized torch.nn.Module instance.
    """

    init_weights(model, init_type, init_gain)
    # torch.save(model.state_dict(), '/home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/globalModel.pt')
    # exit(0)
    return model


#################
# Dataset split #
#################
class CustomTensorDataset(Dataset):
    """TensorDataset with support of transforms."""

    def __init__(self, tensors, transform=None):
        assert all(tensors[0].size(0) == tensor.size(0) for tensor in tensors)
        self.tensors = tensors
        self.transform = transform

    def __getitem__(self, index):
        x = self.tensors[0][index]
        y = self.tensors[1][index]
        if self.transform:
            x = self.transform(x.numpy().astype(np.uint8))
        return x, y

    def __len__(self):
        return self.tensors[0].size(0)


def create_datasets(data_path,
                    dataset_name,
                    more_sample_quantity_per_client,
                    less_sample_quantity_per_client,
                    num_client_with_more_sample,
                    num_client_with_less_sample,
                    contained_num_class,
                    num_class):
    """Split the whole dataset in IID or non-IID manner for distributing to clients."""
    dataset_name = dataset_name.upper()
    # get dataset from torchvision.datasets if exists
    if hasattr(torchvision.datasets, dataset_name):
        # set transformation differently per dataset
        if dataset_name in ["CIFAR10"]:
            transform = torchvision.transforms.Compose(
                [
                    torchvision.transforms.ToTensor(),
                    torchvision.transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
                ]
            )
        elif dataset_name in ["MNIST"]:
            transform = torchvision.transforms.ToTensor()

        # prepare raw training & test datasets
        training_dataset = torchvision.datasets.__dict__[dataset_name](
            root=data_path,
            train=True,
            download=True,
            transform=transform
        )
        test_dataset = torchvision.datasets.__dict__[dataset_name](
            root=data_path,
            train=False,
            download=True,
            transform=transform
        )
    else:
        # dataset not found exception
        error_message = f"...dataset \"{dataset_name}\" is not supported or cannot be found in TorchVision Datasets!"
        raise AttributeError(error_message)

    # unsqueeze channel dimension for grayscale image datasets
    if training_dataset.data.ndim == 3:  # convert to NxHxW -> NxHxWx1
        training_dataset.data.unsqueeze_(3)
    num_categories = np.unique(training_dataset.targets).shape[0]

    if "ndarray" not in str(type(training_dataset.data)):
        training_dataset.data = np.asarray(training_dataset.data)
    if "list" not in str(type(training_dataset.targets)):
        training_dataset.targets = training_dataset.targets.tolist()

        # sort data by labels
    sorted_indices = torch.argsort(torch.Tensor(training_dataset.targets))

    training_inputs_re = training_dataset.data[sorted_indices]
    training_labels_re = torch.Tensor(training_dataset.targets)[sorted_indices]
    training_inputs = [[] for i in range(10)]
    training_labels = [[] for i in range(10)]
    for i in range(len(training_labels_re)):
        index = int(training_labels_re[i])
        training_inputs[index].append(training_inputs_re[i])
        training_labels[index].append(training_labels_re[i])

    more_num_sample_per_class = more_sample_quantity_per_client // contained_num_class
    less_num_sample_per_class = less_sample_quantity_per_client // contained_num_class
    class_category = [i for i in range(10)]

    more_client_data = [[] for i in range(num_client_with_more_sample)]
    more_client_label = [[] for i in range(num_client_with_more_sample)]
    for j in range(num_client_with_more_sample):
        select_class = np.random.choice(class_category, contained_num_class, replace=False)
        for i in range(len(select_class)):
            tmp = [i for i in range(len(training_inputs[select_class[i]]))]
            index = np.random.choice(tmp, more_num_sample_per_class, replace=False)
            for k in range(len(index)):
                more_client_data[j].append(training_inputs[select_class[i]][index[k]])
                more_client_label[j].append(training_labels[select_class[i]][index[k]])
    client_data = torch.Tensor(np.array(more_client_data))
    client_label = torch.Tensor(np.array(more_client_label))
    more_local_datasets = [
        CustomTensorDataset(
            (
                client_data[i], client_label[i].long()
            ),
            transform=transform
        )
        for i in range(num_client_with_more_sample)
    ]

    less_client_data = [[] for i in range(num_client_with_less_sample)]
    less_client_label = [[] for i in range(num_client_with_less_sample)]
    for j in range(num_client_with_less_sample):
        select_class = np.random.choice(class_category, contained_num_class, replace=False)
        for i in range(len(select_class)):
            tmp = [i for i in range(len(training_inputs[select_class[i]]))]
            index = np.random.choice(tmp, less_num_sample_per_class, replace=False)
            for k in range(len(index)):
                less_client_data[j].append(training_inputs[select_class[i]][index[k]])
                less_client_label[j].append(training_labels[select_class[i]][index[k]])

    client_data = torch.Tensor(np.array(less_client_data))
    client_label = torch.Tensor(np.array(less_client_label))
    less_local_datasets = [
        CustomTensorDataset(
            (
                client_data[i], client_label[i].long()
            ),
            transform=transform
        )
        for i in range(num_client_with_less_sample)
    ]

    local_datasets = more_local_datasets + less_local_datasets

    # for i in range(len(local_datasets)):
    #     count_class = [0 for i in range(10)]
    #     for j in range(len(local_datasets[i])):
    #         tmp_index = local_datasets[i][j][1].item()
    #         count_class[tmp_index] = count_class[tmp_index] + 1
    #     print('------------------- client ', i, '---------------------------')
    #     for k in range(len(count_class)):
    #         print('digits ', k, ' contains ', count_class[k], ' samples.')
    # exit(0)
    return local_datasets, test_dataset


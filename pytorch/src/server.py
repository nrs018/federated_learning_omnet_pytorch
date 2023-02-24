import copy
import gc
import logging


import torch
import torch.nn as nn

from multiprocessing import pool, cpu_count
from torch.utils.data import DataLoader
from tqdm.auto import tqdm
from collections import OrderedDict

from .models import *
from .utils import *
from .client import Client

logger = logging.getLogger(__name__)


class Server(object):
    """Class for implementing center server orchestrating the whole process of federated learning
    
    At first, center server distribute model skeleton to all participating clients with configurations.
    While proceeding federated learning rounds, the center server samples some fraction of clients,
    receives locally updated parameters, averages them as a global parameter (model), and apply them to global model.
    In the next round, newly selected clients will recevie the updated global model as its local model.  
    
    Attributes:
        clients: List containing Client instances participating a federated learning.
        __round: Int for indcating the current federated round.
        writer: SummaryWriter instance to track a metric and a loss of the global model.
        model: torch.nn instance for a global model.
        seed: Int for random seed.
        device: Training machine indicator (e.g. "cpu", "cuda").
        mp_flag: Boolean indicator of the usage of multiprocessing for "client_update" and "client_evaluate" methods.
        data_path: Path to read data.
        dataset_name: Name of the dataset.
        num_shards: Number of shards for simulating non-IID data split (valid only when 'iid = False").
        iid: Boolean Indicator of how to split dataset (IID or non-IID).
        init_config: kwargs for the initialization of the model.
        fraction: Ratio for the number of clients selected in each federated round.
        num_clients: Total number of participating clients.
        local_epochs: Epochs required for client model update.
        batch_size: Batch size for updating/evaluating a client/global model.
        criterion: torch.nn instance for calculating loss.
        optimizer: torch.optim instance for updating parameters.
        optim_config: Kwargs provided for optimizer.
    """
    def __init__(self, model_config={}, data_config={}, init_config={}, fed_config={}, optim_config={}):
        self.clients = None
        self._round = 0

        self.model = eval(model_config["name"])(**model_config)

        self.data_path                       = data_config["data_path"]
        self.dataset_name                    = data_config["dataset_name"]
        self.num_class = model_config["num_classes"]
        self.more_sample_quantity_per_client = data_config['more_sample_quantity_per_client']
        self.less_sample_quantity_per_client = data_config['less_sample_quantity_per_client']
        self.num_client_with_more_sample     = data_config['num_client_with_more_sample']
        self.num_client_with_less_sample     = data_config['num_client_with_less_sample']
        self.contained_num_class             = data_config["contained_num_class"]

        self.init_config = init_config

        self.num_clients = fed_config["K"]
        self.num_rounds = fed_config["R"]
        self.local_epochs = fed_config["E"]
        self.batch_size = fed_config["B"]

        self.criterion = fed_config["criterion"]
        self.optimizer = fed_config["optimizer"]
        self.optim_config = optim_config
        self.device = 'cpu'
        
    def load_model(self):
        self.model.load_state_dict(torch.load('/home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/globalModel.pt'))
        self.transmit_model()
        
    def setup(self, **init_kwargs):
        """Set up all configuration for federated learning."""
        print('server setup......')
        # valid only before the very first round
        assert self._round == 0

        # initialize weights of the model
        init_net(self.model, **self.init_config)

        # split local dataset for each client
        local_datasets, test_dataset = create_datasets(
            self.data_path,
            self.dataset_name,
            self.more_sample_quantity_per_client,
            self.less_sample_quantity_per_client,
            self.num_client_with_more_sample,
            self.num_client_with_less_sample,
            self.contained_num_class,
            self.num_class
        )
        
        # assign dataset to each client
        self.clients = self.create_clients(local_datasets)

        # prepare hold-out dataset for evaluation
        self.data = test_dataset
        self.dataloader = DataLoader(test_dataset, batch_size=self.batch_size, shuffle=False)
        
        # configure detailed settings for client upate and 
        self.setup_clients(
            batch_size=self.batch_size,
            criterion=self.criterion, num_local_epochs=self.local_epochs,
            optimizer=self.optimizer, optim_config=self.optim_config
            )
        
        # send the model skeleton to all clients
        self.transmit_model()
        
    def create_clients(self, local_datasets):
        """Initialize each Client instance."""
        print('create clients')
        clients = []
        for k, dataset in enumerate(local_datasets):
            client = Client(client_id=k, local_data=dataset, device=self.device)
            clients.append(client)
        return clients

    def setup_clients(self, **client_config):
        """Set up each client."""
        print('setup clients')
        for k, client in enumerate(self.clients):
            client.setup(**client_config)

    def transmit_model(self, sampled_client_indices=None):
        """Send the updated global model to selected/all clients."""
        if sampled_client_indices is None:
            # send the global model to all clients before the very first and after the last federated round
            assert (self._round == 0) or (self._round == self.num_rounds)

            for client in self.clients:
                client.model = copy.deepcopy(self.model)


        else:
            # send the global model to selected clients
            assert self._round != 0

            for idx in tqdm(sampled_client_indices, leave=False):
                self.clients[idx].model = copy.deepcopy(self.model)

    def random_selection(self):
        num_sampled_clients = np.random.choice([1, 3], p=[0.8, 0.2], replace=False)
        #selectedRation = [0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0, 0,
        #                  0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06,
        #                  0.06, 0.06, 0.06, 0.06, 0.06, 0, 0, 0]
        selectedRation = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0.055, 0.055, 0.055, 0.055, 0.055, 0.055, 0.055, 0.055, 0.055, 0.055,
                          0.055, 0.055, 0.055, 0.055, 0.055, 0.055, 0.055, 0.065]
        # num_sampled_clients = max(int(self.fraction * self.num_clients), 1)
        sampled_client_indices = sorted(np.random.choice(a=[i for i in range(self.num_clients)],
                                                         size=num_sampled_clients,
                                                         p=selectedRation,
                                                         replace=True).tolist())
        print('sampled_client_indices: ', sampled_client_indices)
        return sampled_client_indices          

    def sample_clients(self):
        """Select some fraction of all clients."""
        # sample clients randommly
        message = f"[Round: {str(self._round).zfill(4)}] Select clients...!"
        print(message); logging.info(message)
        del message; gc.collect()

        num_sampled_clients = max(int(self.fraction * self.num_clients), 1)
        sampled_client_indices = sorted(np.random.choice(a=[i for i in range(self.num_clients)], size=num_sampled_clients, replace=False).tolist())

        return sampled_client_indices
    
    def train_client(self, client_id):
        # print(client_id)
        self.clients[client_id].client_update()
        # save model as *.pt file
        torch.save(self.clients[client_id].model.state_dict(), 
                   '/home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/' + str(client_id) + '.pt')
        print(client_id, ' has updated the model.')
        
    def update_selected_clients(self, sampled_client_indices):
        """Call "client_update" function of each selected client."""
        # update selected clients
        # message = f"[Round: {str(self._round).zfill(4)}] Start updating selected {len(sampled_client_indices)} clients...!"
        # print(message); logging.info(message)
        # del message; gc.collect()

        selected_total_size = 0
        for idx in tqdm(sampled_client_indices, leave=False):
            self.clients[idx].client_update()
            selected_total_size += len(self.clients[idx])

        message = f"[Round: {str(self._round).zfill(4)}] ...{len(sampled_client_indices)} clients are selected and updated (with total sample size: {str(selected_total_size)})!"
        print(message); logging.info(message)
        del message; gc.collect()
        print(selected_total_size)
        return selected_total_size
    
    def mp_update_selected_clients(self, selected_index):
        """Multiprocessing-applied version of "update_selected_clients" method."""
        # update selected clients
        message = f"[Round: {str(self._round).zfill(4)}] Start updating selected client {str(self.clients[selected_index].id).zfill(4)}...!"
        print(message, flush=True); logging.info(message)
        del message; gc.collect()

        self.clients[selected_index].client_update()
        client_size = len(self.clients[selected_index])

        message = f"[Round: {str(self._round).zfill(4)}] ...client {str(self.clients[selected_index].id).zfill(4)} is selected and updated (with total sample size: {str(client_size)})!"
        print(message, flush=True); logging.info(message)
        del message; gc.collect()

        return client_size

    def average_selected_client_model(self):
        """Average the updated and transmitted parameters from each selected client."""

        client_weights = []
        averaged_weights = OrderedDict()
        path = '/home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/'
        file_list = os.listdir(path)
        count = 0
        fl = open('/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt', 'a')
        
        fl.write('selected client which successful upload their model ')
        for f in file_list:
            if not os.path.isdir(path + f):
                print(path + f)
                fl.write(f + ' ')
                self.model.load_state_dict(torch.load(path + f))
                client_weights.append(self.model.state_dict())
                count += 1
        
        w = 1.0 / count 
        for it in range(len(client_weights)):
            local_weights = client_weights[it]
            for key in local_weights.keys():
                if it == 0:
                    averaged_weights[key] = w * local_weights[key]
                else:
                    averaged_weights[key] += w * local_weights[key]
        self.model.load_state_dict(averaged_weights)
        test_loss, test_acc = self.evaluate_global_model()
        fl.write('\n' + 'After evaluate global model: ' + str(test_loss) + ' ' + str(test_acc) + '\n')
        fl.close()
        torch.save(self.model.state_dict(), path + 'globalModel.pt')


    def average_model(self, sampled_client_indices, coefficients):
        """Average the updated and transmitted parameters from each selected client."""
        message = f"[Round: {str(self._round).zfill(4)}] Aggregate updated weights of {len(sampled_client_indices)} clients...!"
        print(message); logging.info(message)
        del message; gc.collect()
        for i in range(len(coefficients)):
            coefficients[i] = 1.0 / len(coefficients)

        averaged_weights = OrderedDict()
        for it, idx in tqdm(enumerate(sampled_client_indices), leave=False):
            local_weights = self.clients[idx].model.state_dict()
            for key in self.model.state_dict().keys():
                if it == 0:
                    averaged_weights[key] = coefficients[it] * local_weights[key]
                else:
                    averaged_weights[key] += coefficients[it] * local_weights[key]
        self.model.load_state_dict(averaged_weights)

        # message = f"[Round: {str(self._round).zfill(4)}] ...updated weights of {len(sampled_client_indices)} clients are successfully averaged!"
        # print(message); logging.info(message)
        # del message; gc.collect()
    
    def evaluate_selected_models(self, sampled_client_indices):
        """Call "client_evaluate" function of each selected client."""
        # message = f"[Round: {str(self._round).zfill(4)}] Evaluate selected {str(len(sampled_client_indices))} clients' models...!"
        # print(message); logging.info(message)
        # del message; gc.collect()

        for idx in sampled_client_indices:
            self.clients[idx].client_evaluate()

        message = f"[Round: {str(self._round).zfill(4)}] ...finished evaluation of {str(len(sampled_client_indices))} selected clients!"
        print(message); logging.info(message)
        del message; gc.collect()

    def mp_evaluate_selected_models(self, selected_index):
        """Multiprocessing-applied version of "evaluate_selected_models" method."""
        self.clients[selected_index].client_evaluate()
        return True

    def train_federated_model(self):
        """Do federated training."""
        # select pre-defined fraction of clients randomly
        # sampled_client_indices = self.sample_clients()
        sampled_client_indices = self.random_selection()
        # send global model to the selected clients
        self.transmit_model(sampled_client_indices)

        # updated selected clients with local dataset
        # if self.mp_flag:
        #     with pool.ThreadPool(processes=cpu_count() - 1) as workhorse:
        #         selected_total_size = workhorse.map(self.mp_update_selected_clients, sampled_client_indices)
        #     selected_total_size = sum(selected_total_size)
        # else:
        selected_total_size = self.update_selected_clients(sampled_client_indices)

        # evaluate selected clients with local dataset (same as the one used for local update)
        # if self.mp_flag:
        #     message = f"[Round: {str(self._round).zfill(4)}] Evaluate selected {str(len(sampled_client_indices))} clients' models...!"
        #     print(message); logging.info(message)
        #     del message; gc.collect()
        #
        #     with pool.ThreadPool(processes=cpu_count() - 1) as workhorse:
        #         workhorse.map(self.mp_evaluate_selected_models, sampled_client_indices)
        # else:
        self.evaluate_selected_models(sampled_client_indices)

        # calculate averaging coefficient of weights
        mixing_coefficients = [len(self.clients[idx]) / selected_total_size for idx in sampled_client_indices]

        # average each updated model parameters of the selected clients and update the global model
        self.average_model(sampled_client_indices, mixing_coefficients)
    
    def evaluate_clients(self):

        client_loss = []
        for i in range(len(self.clients)):
            f = open('./client_loss.txt', 'a')
            f.write('===========  client ' + str(i) + '  ==================\n')
            f.close()

            cli_loss, cli_acc = self.clients[i].client_evaluate()
            client_loss.append([i, cli_loss])

        return client_loss
    
        
    def evaluate_global_model(self):
        """Evaluate the global model using the global holdout dataset (self.data)."""
        self.model.eval()
        self.model.to(self.device)

        test_loss, correct = 0, 0
        with torch.no_grad():
            for data, labels in self.dataloader:
                data, labels = data.float().to(self.device), labels.long().to(self.device)
                outputs = self.model(data)
                test_loss += eval(self.criterion)()(outputs, labels).item()
                
                predicted = outputs.argmax(dim=1, keepdim=True)
                correct += predicted.eq(labels.view_as(predicted)).sum().item()
                
                if self.device == "cuda": torch.cuda.empty_cache()
        self.model.to("cpu")

        test_loss = test_loss / len(self.dataloader)
        test_accuracy = correct / len(self.data)

        return test_loss, test_accuracy

    def fit(self):
        """Execute the whole process of the federated learning."""
        self.results = {"loss": [], "accuracy": []}
        for r in range(self.num_rounds):
            self._round = r + 1
            
            self.train_federated_model()
            test_loss, test_accuracy = self.evaluate_global_model()
            
            self.results['loss'].append(test_loss)
            self.results['accuracy'].append(test_accuracy)

            message = f"[Round: {str(self._round).zfill(4)}] Evaluate global model's performance...!\
                \n\t[Server] Loss: {test_loss:.4f}, Accuracy: {100. * test_accuracy:.2f}%\n"
            print(message); logging.info(message)
            del message; gc.collect()
        self.transmit_model()

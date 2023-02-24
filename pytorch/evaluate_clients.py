import os
import time
import datetime
import pickle
import yaml
import threading
import logging

import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter

from src.server import Server
from src.utils import launch_tensor_board
from src.client import *


if __name__ == "__main__":
    # read configuration file
    with open('/home/narisu/src/TFF/toyota_distributedFL/pytorch/config.yaml') as c:
        configs = list(yaml.load_all(c, Loader=yaml.FullLoader))
    data_config = configs[0]["data_config"]
    fed_config = configs[1]["fed_config"]
    optim_config = configs[2]["optim_config"]
    init_config = configs[3]["init_config"]
    model_config = configs[4]["model_config"]
   
    # os.system('cp /home/narisu/src/TFF/toyota_distributedFL/pytorch/back/globalModel.pt /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/')
    # initialize federated learning 
    central_server = Server(model_config, data_config, init_config, fed_config, optim_config)
    
    central_server.setup()
    # load gobal model from dictory, 
    # and then transmit to all client for preparing evaluate client.
    central_server.load_model()
    client_loss = central_server.evaluate_clients()

    if os.path.exists('/home/narisu/src/TFF/toyota_distributedFL/pytorch/client_loss.txt'):
        os.remove('/home/narisu/src/TFF/toyota_distributedFL/pytorch/client_loss.txt')
    f = open('/home/narisu/src/TFF/toyota_distributedFL/pytorch/client_loss.txt', 'a')
    f.write('id loss\n')
    for i in range(len(client_loss)):
        f.write(str(i) + ' ' + str(client_loss[i][1]) + '\n')
    f.close()
    exit(0)
    # do federated learning
    # central_server.fit()



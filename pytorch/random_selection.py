
import os
import time
import datetime
import pickle
import yaml
import threading
import logging
import torch
import torch.nn as nn
from torch.utils.tensorboard import SummaryWriter

from src.server import Server
from src.utils import launch_tensor_board


if __name__ == "__main__":
    # read configuration file
    with open('./config-random.yaml') as c:
        configs = list(yaml.load_all(c, Loader=yaml.FullLoader))
    global_config = configs[0]["global_config"]
    data_config = configs[1]["data_config"]
    fed_config = configs[2]["fed_config"]
    optim_config = configs[3]["optim_config"]
    init_config = configs[4]["init_config"]
    model_config = configs[5]["model_config"]
    log_config = configs[6]["log_config"]
   

    # initialize federated learning 
    central_server = Server(model_config, global_config, data_config, init_config, fed_config, optim_config)
    central_server.setup()

    # do federated learning
    central_server.fit()



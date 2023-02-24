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


if __name__ == "__main__":
    # read configuration file
    with open('/home/narisu/src/TFF/toyota_distributedFL/pytorch/config.yaml') as c:
        configs = list(yaml.load_all(c, Loader=yaml.FullLoader))
    data_config = configs[0]["data_config"]
    fed_config = configs[1]["fed_config"]
    optim_config = configs[2]["optim_config"]
    init_config = configs[3]["init_config"]
    model_config = configs[4]["model_config"]

    # initialize federated learning 
    central_server = Server(model_config, data_config, init_config, fed_config, optim_config)
    central_server.setup()
    # central_server.load_model()
    central_server.average_selected_client_model()
    





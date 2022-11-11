# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:44:05 2022

@author: Marco-PC
"""
import networkx as nx
import simulation as simx
import SirsModel as sirs

from utils import onShow

alpha = 0.999
beta = 0.999
gamma = 0.999

G = nx.gnp_random_graph(50, 0.1)

model = sirs.SirsModel(G, alpha, beta, gamma)
sim = simx.Simulator(model.initialState(),
                     model.transition(),
                     onShow)
sim.run(15, 5)

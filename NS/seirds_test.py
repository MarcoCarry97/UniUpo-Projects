# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:44:05 2022

@author: Marco-PC
"""
import networkx as nx
import simulation as simx
import SeirdsModel as seirds

from utils import onShow

alpha = 0.5
beta = 0.5
gamma = 0.5
delta = 0.5

G = nx.gnp_random_graph(50, 0.1)

model = seirds.SeirdsModel(G, alpha, beta, gamma, delta)
sim = simx.Simulator(model.initialState(),
                     model.transition(),
                     onShow)
sim.run(15, 7)

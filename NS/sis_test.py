# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:44:05 2022

@author: Marco-PC
"""
import networkx as nx
import simulation as simx
import SisModel as sis

from utils import onShow

alpha = 0.1
beta = 0.1

G = nx.gnp_random_graph(100, 0.1)

model = sis.SisModel(G, alpha, beta)
sim = simx.Simulator(model.initialState(),
                     model.transition(),
                     onShow)
sim.run(100,100)

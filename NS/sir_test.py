# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:44:05 2022

@author: Marco-PC
"""
import networkx as nx
import simulation as simx
import SirModel as sir

from utils import onShow

alpha=0.999
beta=0.999

G=nx.gnp_random_graph(20, 0.1)

model=sir.SirModel(G,alpha,beta)
sim=simx.Simulator(model.initialState(),
                   model.transition(),
                   onShow)
sim.run(1000,5)






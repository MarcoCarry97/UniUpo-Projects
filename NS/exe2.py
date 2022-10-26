# -*- coding: utf-8 -*-
"""
Created on Thu Oct 20 12:03:50 2022

@author: Marco-PC
"""

import networkx as nx
import matplotlib.pyplot as plt

G = nx.read_graphml('./datasets/openflights/openflights_usa.graphml.gz')

def exist_path_of_length(G,u,v,size):
    return nx.shortest_path_length(G,u,v)==size

def exist_direct_path(G,u,v):
    return exist_path_of_length(G, u, v, 1)
        
def shortest_path_from_to(G,u,v):
    return nx.shortest_path(G,u,v)

def is_connected_to_everything(G):
    return nx.is_strongly_connected(G)
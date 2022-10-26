# -*- coding: utf-8 -*-
"""
Created on Tue Oct 25 17:00:56 2022

@author: Marco-PC
"""

import networkx as nx

import numpy as np



G = nx.read_edgelist('datasets/ia-enron-only/ia-enron-only.edges', nodetype=int)
nx.draw(G)


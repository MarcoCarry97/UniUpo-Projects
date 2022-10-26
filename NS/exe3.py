# -*- coding: utf-8 -*-
"""
Created on Tue Oct 25 17:00:56 2022

@author: Marco-PC
"""

import networkx as nx

import numpy as np

import statistics as st


G = nx.read_edgelist('datasets/ia-enron-only/ia-enron-only.edges', nodetype=int)
nx.draw(G)

def find_hub(G,key=""):
    return max(G.nodes, key=key)

def find_hub_by_degree(G):
    return find_hub(G,key=G.degree)

def find_hub_by_betweeness(G):
    bet=nx.centrality.betweenness_centrality(G)
    return find_hub(G,key=bet)

def mean(G):
    degree_seq=[G.degree(n) for n in G.nodes]
    statistics.mean(degree_sequence))
    
def median():
    degree_seq=[G.degree(n) for n in G.nodes]
    statistics.median(degree_sequence))
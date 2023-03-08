# -*- coding: utf-8 -*-
"""
Created on Wed Nov  9 12:23:14 2022

@author: Marco-PC
"""

import networkx as nx
import matplotlib.pyplot as plt

def color(num,state):
    ret=None
    if(state=="S"):
        ret=["lightblue"]
    if(state=="E"):
        ret=["yellow"]
    if(state=="I"):
        ret=["red"]
    if(state=="R"):
        ret=["green"]
    if(state=="D"):
        ret=["gray"]
    return ret
    
def colors(states):
    ret=list()
    for s in states:
        ret+=color(*s)
    return ret

def onShow(G,state):
    colorList=colors(G.nodes(data="state"))
    nx.draw(G,with_labels=True,
            node_color=colorList)
    plt.show()
# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:44:05 2022

@author: Marco-PC
"""
import networkx as nx
import simulation as simx
import SirModel as sir
import SisModel as sis
import SirsModel as sirs
import SeirdsModel as seirds
import matplotlib.pyplot as plt

alpha=0.999
beta=0.999
gamma=0.999
delta=0.999

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

G=nx.gnp_random_graph(100, 0.23)

model=sir.SirModel(G,alpha,beta)
sim=simx.Simulator(model.initialState(),
                   model.transition(),
                   onShow)
sim.run(1000,5)






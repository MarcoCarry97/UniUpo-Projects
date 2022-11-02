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

alpha=0.5
beta=0.5
gamma=0.5
delta=0.5

def onShow(G,state):
    nx.draw(G)
    plt.show()

G=nx.gnp_random_graph(25, 0.23)

model=sir.SirModel(G,alpha,beta)
sim=simx.Simulator(model.initialState(),
                   model.transition(),
                   onShow)
sim.run(25,3)






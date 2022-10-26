# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 22:39:28 2022

@author: Marco-PC
"""

import networkx as nx
import random
import spreadingModel as sm

class SisModel(sm.SpreadingModel):
    
    def __init__(self,alpha,beta):
        super(self)
        self.alpha=alpha
        self.beta=beta
        
    def transition(self):
        def trans(G,current):
            nextState={}
            for node in self.G.nodes:
                if current[node]=="S":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<self.beta:
                                nextState="I"
                else:
                    if random.random()<self.alpha:
                        nextState[node]="S"
        return trans
                        
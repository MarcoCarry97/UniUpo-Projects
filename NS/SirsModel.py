# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 23:32:42 2022

@author: Marco-PC
"""

import networkx as nx
import random
import spreadingModel as sm

class SirsModel(sm.SpreadingModel):
    
    def __init__(self,alpha,beta,gamma):
        super(self)
        self.alpha=alpha
        self.beta=beta
        self.gamma=gamma
        
    def transition(self):
        def trans(G,current):
            nextState={}
            for node in self.G.nodes:
                if current[node]=="S":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<self.beta:
                                nextState="I"
                elif current[node]=="I":
                    if random.random()<self.alpha:
                        nextState[node]=="R"
                else:
                    if random.random()<self.gamma:
                        nextState[node]=="S"
        return trans
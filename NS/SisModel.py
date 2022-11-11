# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 22:39:28 2022

@author: Marco-PC
"""

import networkx as nx
import random
import spreadingModel as sm

class SisModel(sm.SpreadingModel):
    
    def __init__(self,G,alpha,beta):
        super().__init__(G)
        self.alpha=alpha #S-->I probability
        self.beta=beta #I-->S probability
        
    def transition(self): 
        def trans(G,current):
            nextState={}
            print(current)
            for node in self.G.nodes:
                nextState[node]=current[node]
                if current[node]=="S":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<self.beta:
                                nextState[node]="I"
                else:
                    if random.random()<self.alpha:
                        nextState[node]="S"
                return (G,nextState)
        return trans
                        
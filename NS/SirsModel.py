# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 23:32:42 2022

@author: Marco-PC
"""

import networkx as nx
import random
import spreadingModel as sm

class SirsModel(sm.SpreadingModel):
    
    def __init__(self,G,alpha,beta,gamma):
        super().__init__(G)
        self.alpha=alpha #S-->I probability
        self.beta=beta #I-->R probability
        self.gamma=gamma #R-->S probability
        
    def transition(self):
        def trans(G,current):
            nextState={}
            for node in self.G.nodes:
                nextState[node]=current[node]
                if current[node]=="S":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<1-self.alpha:
                                nextState[node]="I"
                elif current[node]=="I":
                    if random.random()<1-self.beta:
                        nextState[node]="R"
                else:
                    if random.random()<1-self.gamma:
                        nextState[node]="S"
            return (G,nextState)
        return trans
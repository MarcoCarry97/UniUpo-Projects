# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 23:37:43 2022

@author: Marco-PC
"""

import networkx as nx
import random
import spreadingModel as sm

class SeirdsModel(sm.SpreadingModel):
    
    def __init__(self,G,alpha,beta,gamma,delta):
        super().__init__(G)
        self.alpha=alpha #S-->E probability
        self.beta=beta #E-->I probability
        self.gamma=gamma #I-->R probability
        self.delta=delta #R-->S probability
        
    
    #NOTA: per gli esposti(E) ho riutilizzato il ragionamento
    # di S (vedi codice), un comportamento più realistico si potrebbe ottenere
    # togliendo il ciclo for nel caso E, "simulando" una sorta di quarantena
    def transition(self):
        def trans(G,current):
            nextState={}
            for node in self.G.nodes:
                nextState[node]=current[node]
                if current[node]=="S":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<1-self.alpha:
                                nextState[node]="E"
                elif current[node]=="E":
                    #for neighbor in G.neighbors(node):
                    #if current[neighbor]=="I":
                    if random.random()<1-self.beta:
                        nextState[node]="I"
                    else:
                        nextState[node]="S"
                elif current[node]=="I":
                    if random.random()<1-self.gamma:
                        nextState[node]="R"
                    else:
                        nextState[node]="D"
                elif current[node]=="R":
                    if random.random()<1-self.delta:
                        nextState[node]="S"
            return (G,nextState)
        return trans
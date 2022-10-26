# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 23:37:43 2022

@author: Marco-PC
"""

import networkx as nx
import random
import spreadingModel as sm

class SeirdsModel(sm.SpreadingModel):
    
    def __init__(self,alpha,beta,gamma,delta):
        super(self)
        self.alpha=alpha #S-->I probability
        self.beta=beta #I-->R probability
        self.gamma=gamma #R-->S probability
        self.delta=delta #E-->I probability
        
    
    #NOTA: per gli esposti(E) ho riutilizzato il ragionamento
    # di S (vedi codice), un comportamento più realistico si potrebbe ottenere
    # togliendo il ciclo for nel caso E, "simulando" una sorta di quarantena
    def transition(self):
        def trans(G,current):
            nextState={}
            for node in self.G.nodes:
                if current[node]=="S":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<self.beta:
                                nextState="E"
                elif current[node]=="E":
                    for neighbor in G.neighbors(node):
                        if current[neighbor]=="I":
                            if random.random()<self.delta:
                                nextState="E"
                elif current[node]=="I":
                    if random.random()<self.alpha:
                        nextState[node]=="R"
                    else:
                        nextState[node]=="D"
                elif current[node]=="R":
                    if random.random()<self.gamma:
                        nextState[node]=="S"
        return trans
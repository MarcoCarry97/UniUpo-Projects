# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 22:14:57 2022

@author: Marco-PC
"""

import networkx as nx
import random

class SpreadingModel: #abstract class implementing principal functions
    
    def __init__(self,graph):
        self.graph=graph
        self.state={}
        self.sim=None
        
    def initialState(self): #method defining the initial state
        def init():
            self.state={}
            for node in self.G.nodes:
                self.state[node]="S"
            patientZero=random.choice(list(self.G.nodes))
            self.state[patientZero]="I"
            return self.state
        return init
    
    def transition(self): #method defining the transition function
        pass
    
    def run(self,num=1,name="Sample"): #method that run the simulation
        self.sim=nx.Simulator(self.initialState(),
                           self.transition(),
                           name)
        self.sim.run(num)
    
    def draw(self): #method drawing the graph
        self.sim.draw(with_labels=True)
    
    def plot(self): #method plotting the results
        self.sim.plot()
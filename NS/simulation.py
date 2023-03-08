# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:32:11 2022

@author: Marco-PC
"""
import networkx as nx
import numpy as np
import pandas as pd

class Simulator:
    
    def __init__(self,onStart,onStep,onShow):
        self.onStart=onStart
        self.onStep=onStep
        self.onShow=onShow
        self.snapshots=dict()
        self.steps=0
      
    def assign(self,G,state):
        nx.set_node_attributes(G, state,"state")
      
    def count(self,state,key):
        c=0
        for k in state.values():
            if k==key:
                c+=1
        return c
      
    def keep(self,G,state):
        keys=set(state.values())
        for key in keys:
            num=self.count(state,key)
            if( key in self.snapshots):
                self.snapshots[key]+=[num]
            else:
                self.snapshots[key]=[num]
           
    def plot(self): #IDEA: creare un dataframe con Pandas e plottare con la sua funzione
        end=False
        while(not end):
            done=True
            for key in self.snapshots.keys():
                if len(self.snapshots[key]) < self.steps:
                    self.snapshots[key]+=[self.snapshots[key][-1]] 
                    done=False
            if done:
                end=True
        df=pd.DataFrame(self.snapshots)
        #df["time"]=np.array(range(1,self.steps+1))
        df.plot.line()
        
        
    def run(self,steps,intervals):
        self.steps=steps
        x=steps//intervals
        state=self.onStart()
        self.assign(*state)
        self.onShow(*state)
        for step in range(1,steps+1):
            state=self.onStep(*state)
            self.assign(*state)
            self.keep(*state)
            if(step%x==0):
                self.onShow(*state)
        self.onShow(*state)
        self.plot()
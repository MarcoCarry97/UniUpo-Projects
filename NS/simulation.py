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
        self.snapshots=[]
        self.steps=0
      
    def assign(self,G,state):
        nx.set_node_attributes(G, state,"state")
      
    def keep(self,G,state):
        snapshot={}
        for s in state.values():
            if s in snapshot:
                snapshot[s]+=1
            else:
                snapshot[s]=1
        self.snapshots+=[snapshot]
    
    def plot(self): #IDEA: creare un dataframe con Pandas e plottare con la sua funzione
        dictio=dict()
        s=self.snapshots[0]
        for key in s:
            dictio[key]=np.zeros(self.steps)
        for snap in self.snapshots:
            for key in snap.keys():
                if key in dictio:
                    dictio[key]+=[snap[key]]
                else:
                    dictio[key]=[snap[key]]
        for key in dictio.keys():
            print(len(dictio[key]))
        df=pd.DataFrame(dictio)
        df["time"]=np.array(1,self.steps+1)
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
        #self.plot()
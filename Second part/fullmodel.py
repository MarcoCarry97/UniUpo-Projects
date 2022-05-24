# -*- coding: utf-8 -*-
"""
Created on Wed May 25 00:23:14 2022

@author: Marco-PC
"""
import covidmodel as covid

class FullModel:
    def __init__(self):
        pass
        
    def getCombinations(self):
        pass
    
    def execute(self,alpha,gamma,mu,omicron,N):
        for comb in self.getCombinations():
            model=covid.Model(comb)
            model.execute(alpha,gamma,mu,omicron,N)
            
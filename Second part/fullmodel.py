# -*- coding: utf-8 -*-
"""
Created on Wed May 25 00:23:14 2022

@author: Marco-PC
"""
import covidmodel as covid

class FullFractionalDesign:
    def __init__(self):
        pass
        
    def getCombinations(self):
        betas=[0.42*15,0.02*40]
        recommends=[False,True]
        containedPercents=[0.35,0.83]
        res=[]
        for beta in betas:
            for recommend in recommends:
                for containedPercent in containedPercents:
                    res+=[{"beta":beta,
                           "recommandation":recommend,
                           "containedPercent":containedPercent
                           }]
        return res
               
    
    def execute(self,alpha,gamma,mu,omicron,N,steps):
        for comb in self.getCombinations():
            model=covid.Model(comb)
            model.execute(steps,alpha,gamma,mu,omicron,N)
            
                
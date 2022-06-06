# -*- coding: utf-8 -*-
"""
Created on Wed May 25 00:23:14 2022

@author: Marco-PC
"""
import covidmodel as covid

class FullFactorialDesign:
    def __init__(self):
        pass
        
    def getCombinations(self):
        #betas=[0.42*15,0.02*40]
        betas=[1.3,0.3]
        #betas=[0.42*15*0.1]
        recommends=[False,True]
        containedPercents=[0.5,0.0]
        res=[]
        for containedPercent in containedPercents:
            for recommend in recommends:    
                for beta in betas:
                    res+=[{"beta":beta,
                           "recommandation":recommend,
                           "containedPercent":containedPercent
                           }]
        return res
               
    
    def execute(self,alpha,gamma,mu,omicron,N,steps):
        combs=self.getCombinations()
        for i in range(0,len(combs)):
            comb=combs[i]
            model=covid.Model(comb)
            model.execute(steps,alpha,gamma,mu,omicron,N,i)
            
                
# -*- coding: utf-8 -*-
"""
Created on Sat May 21 11:03:17 2022

@author: Marco-PC
"""

class YatesAlgorithm:
    def __init__(self):
        pass
        
    def conputeEffects(self,response,n):
        step=response
        for i in range(0,n):
            out=[0]*len(step)
            couples=[]
            for i in range(1,len(step),2):
                couples+=[(step[i-1],step[i])]
            for c in range(0,len(couples)):
                couple=couples[c]
                i=c
                j=i+len(couples)
                x=couple[0]
                y=couple[1]
                out[i]=x+y
                out[j]=y-x
            step=out
        e=2**(n-1)
        effects=[0]*len(response)
        for i in range(0,len(effects)):
            effects[i]=step[i]/e
        effects[0]/=2
        return effects
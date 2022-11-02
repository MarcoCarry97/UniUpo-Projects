# -*- coding: utf-8 -*-
"""
Created on Wed Nov  2 15:32:11 2022

@author: Marco-PC
"""

class Simulator:
    
    def __init__(self,onStart,onStep,onShow):
        self.onStart=onStart
        self.onStep=onStep
        self.onShow=onShow
        
    def run(self,steps,intervals):
        x=steps//intervals
        state=self.onStart()
        self.onShow(*state)
        for step in range(1,steps+1):
            state=self.onStep(*state)
            if(step%x==0):
                print(step)
                self.onShow(*state)
        self.onShow(*state)
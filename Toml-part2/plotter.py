# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 10:02:51 2022

@author: Marco-PC
"""

from matplotlib import pyplot as plt
import numpy as np

class Plotter:
    def __init__(self,funx,funy):
        self.funx=funx
        self.funy=funy
        self.xlab="x"
        self.ylab="y"
        self.title="plot"
        self.size=10
        self.limitx=(None,None)
        self.limity=(None,None)
        
    def show(self,nmin,nmax,step):
        n=np.arange(nmin,nmax,step)
        x=self.funx(n)
        y=self.funy(n)
        plt.plot(x,y)
        plt.xlabel(self.xlab,fontSize=self.size)
        plt.ylabel(self.ylab,fontSize=self.size)
        plt.title(self.title, fontSize=self.size)
        
        plt.show()
        
    def labels(self,xlab,ylab):
        self.xlab=xlab
        self.ylab=ylab
        
    def fontSize(self,size):
        self.size=size
     
    def limits(self,xmin,xmax,ymin,ymax):
        self.limitx=(xmin,xmax)
        self.limity=(ymin,ymax)
        
        
# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 10:02:51 2022

@author: Marco-PC
"""

from matplotlib import pyplot as plt
import numpy as np
import os
import shutil as sh

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
        
    def show(self,nmin,nmax,step,delete=False):
        n=np.arange(nmin,nmax,step)
        x=self.funx(n)
        y=self.funy(n)
        fig=plt.figure()
        plt.plot(x,y)
        plt.xlabel(self.xlab,fontSize=self.size)
        plt.ylabel(self.ylab,fontSize=self.size)
        plt.title(self.title, fontSize=self.size)
        if(os.path.exists("./plots") and delete):
            sh.rmtree("./plots")
            os.mkdir("./plots")
        fig.savefig("./plots/"+self.title+".jpg")
        plt.show()
        
    def labels(self,xlab,ylab):
        self.xlab=xlab
        self.ylab=ylab
        
    def fontSize(self,size):
        self.size=size
     
    def limits(self,xmin,xmax,ymin,ymax):
        self.limitx=(xmin,xmax)
        self.limity=(ymin,ymax)
        
        
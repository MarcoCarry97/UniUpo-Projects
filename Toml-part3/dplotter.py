# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 10:02:51 2022

@author: Marco-PC
"""

from matplotlib import pyplot as plt
import numpy as np
import os
import shutil as sh
import pandas as pd
import seaborn as sb

#useful plots:
    #lineplot
    #pairplot
    #boxplot
    #scatterplot
    #barplot
    #heatmap
    #clustermap
    
    

class Plotter:
    def __init__(self):
        self.xlabel="x"
        self.ylabel="y"
        self.ptitle="plot"
        self.size=10
        sb.set_style("whitegrid")
    
    def labels(self,x,y):
        self.xlabel=x
        self.ylabel=y
    
    def title(self,t):
        self.ptitle=t
    
    def show(self,data,delete=False,save=False,hue=None,dkind=None,vmin=-1,vmax=1):
        fig=plt.figure(figsize=(10,9))
        plt.xlabel(self.xlabel,fontsize=self.size)
        plt.ylabel(self.xlabel,fontsize=self.size)
        plt.title(self.ptitle,fontsize=self.size)
        
        #plot here
        
        if(os.path.exists("./plot") and delete and save):
            sh.rmtree("./plot")
        if(delete and save):
            os.mkdir("./plot")
        plt.show()
        fig.savefig(self.ptitle+".jpg")
        
    
class LinePlotter(Plotter):
    def __init__(self):
        super().__init__()
    
    def show(self,data,delete=False,save=False,hue=None,dkind=None,vmin=-1,vmax=1):
        fig=plt.figure(figsize=(10,9))
        plt.xlabel(self.xlabel,fontsize=self.size)
        plt.ylabel(self.xlabel,fontsize=self.size)
        plt.title(self.ptitle,fontsize=self.size)
        
        sb.lineplot(data=data,x=self.xlabel,y=self.ylabel)
        
        if(os.path.exists("./plot") and delete and save):
            sh.rmtree("./plot")
        if(delete and save):
            os.mkdir("./plot")
        plt.show()
        fig.savefig(self.ptitle+".jpg")
        
class PairPlotter(Plotter):
    def __init__(self):
        super().__init__()
    
    def show(self,data,delete=False,save=False,hue=None,dkind=None,vmin=-1,vmax=1):
        fig=plt.figure(figsize=(10,9))
        plt.xlabel(self.xlabel,fontsize=self.size)
        plt.ylabel(self.xlabel,fontsize=self.size)
        plt.title(self.ptitle,fontsize=self.size)
        
        sb.pairplot(data=data)
        
        if(os.path.exists("./plot") and delete and save):
            sh.rmtree("./plot")
        if(delete and save):
            os.mkdir("./plot")
        plt.show()
        fig.savefig(self.ptitle+".jpg")
        
class BoxPlotter(Plotter):
    def __init__(self):
        super().__init__()
    
    def show(self,data,delete=False,save=False,hue=None,dkind=None,vmin=-1,vmax=1):
        fig=plt.figure(figsize=(10,9))
        plt.xlabel(self.xlabel,fontsize=self.size)
        plt.ylabel(self.xlabel,fontsize=self.size)
        plt.title(self.ptitle,fontsize=self.size)
        
        sb.boxplot(x=self.xlabel,y=self.ylabel,data=data)
        
        if(os.path.exists("./plot") and delete and save):
            sh.rmtree("./plot")
        if(delete and save):
            os.mkdir("./plot")
        #plt.show()
        fig.savefig(self.ptitle+".jpg")
        

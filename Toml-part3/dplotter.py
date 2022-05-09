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

def plotTypes():
    return [
            "bar",
            "count",
            "scatter",
            "pain",
            "line",
            "box",
            "strip",
            "violin",
            "heat"
        ]

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
    
    def show(self,plotType,data,x,y,delete=False,save=False,hue=None,dkind=None,vmin=-1,vmax=1):
        fig=plt.figure(figsize=(10,9))
        plt.xlabel(self.xlabel,fontsize=self.size)
        plt.ylabel(self.xlabel,fontsize=self.size)
        plt.title(self.ptitle,fontsize=self.size)
        if(plotType=="bar"):
            p=sb.barplot(x=x,y=y)
        elif(plotType=="count"):
            p=sb.countplot(x)
        elif(plotType=="scatter"):
            p=sb.scatterplot(x=x,y=y)
        elif(plotType=="pain"):
            p=sb.pairplot(data,hue=hue,diag_kind=dkind)
        elif(plotType=="line"):
            p=sb.lineplot(x=x, y=y)
        elif(plotType=="box"):
            p=sb.boxplot(data=x)
        elif(plotType=="strip"):
            p=sb.stripplot(data=x)
        elif(plotType=="violin"):
            p=sb.violinplot(data=x)
        elif(plotType=="heat"):
            p=sb.heatmap(x,annot=True,cmap="RdBu",vmin=vmin,vmax=vmax)
        plt.show()
        if(os.path.exists("./plot") and delete and save):
            sh.rmtree("./plot")
        if(delete and save):
            os.mkdir("./plot")
        plt.show()
        fig.savefig(self.ptitle+".jpg")
        
    
        
    def choosePlot(self,x=None,y=None,hue=None,dkind=None,vmin=-1,vmax=1):
        p=None
        plotType=self.plotType
        if(plotType=="bar"):
            p=sb.barplot(x=x,y=y)
        elif(plotType=="count"):
            p=sb.countplot(x=x,y=y)
        elif(plotType=="scatter"):
            p=sb.scatterplot(x=x,y=y)
        elif(plotType=="pain"):
            p=sb.pairplot(x,hue=hue,diag_kind=dkind)
        elif(plotType=="line"):
            p=sb.lineplot(x=x, y=y)
        elif(plotType=="box"):
            p=sb.boxplot(data=x)
        elif(plotType=="strip"):
            p=sb.stripplot(data=x)
        elif(plotType=="violin"):
            p=sb.violinplot(data=x)
        elif(plotType=="heat"):
            p=sb.heatmap(x,annot=True,cmap="RdBu",vmin=vmin,vmax=vmax)
            #eventual labels
        return p
    
        
        
        

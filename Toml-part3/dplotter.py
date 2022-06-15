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
from seaborn_qqplot import pplot
import statmodels.api as sm
import matplotlib.pyplot as plt

#useful plots:
    #lineplot
    #pairplot
    #boxplot
    #scatterplot
    
def getCorrelationMatrix(data):
    return data.corr()

class Plotter:
    def __init__(self):
        self.xlabel="x"
        self.ylabel="y"
        self.ptitle="plot"
        self.size=20
        sb.set_style("whitegrid")
    
    def labels(self,x,y):
        self.xlabel=x
        self.ylabel=y
    
    def title(self,t):
        self.ptitle=t
    
    def show(self,data,delete=False,save=False,hue=None,kind="line",vmin=-1,vmax=1):

        if(kind=="heatmap"):
            data.style.background_gradient(cmap ='viridis').set_properties(**{'font-size': '20px'})
        else:
            data.plot(x=self.xlabel,y=self.ylabel,kind=kind,title=self.ptitle)
        if(os.path.exists("./plot") and delete and save):
            sh.rmtree("./plot")
        if(delete and save):
            os.mkdir("./plot")
        
 
def boxplot(data,x,y,title,delete,save):
    p=Plotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,kind="box",delete=delete,save=save)
    
def scatterplot(data,x,y,title,delete,save):
    p=Plotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,kind="scatter",delete=delete,save=save)
    
def pairplot(data,x,y,title,delete,save):
    p=Plotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,kind="pair",delete=delete,save=save)
    
def lineplot(data,x,y,title,delete,save):
    p=Plotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,kind="line",delete=delete,save=save)
    
def heatmap(data,title,delete,save):
    corMatrix=data.corr()
    sb.heatmap(corMatrix,annot=True)
    
def qqplot(data,x,y,title,delete,save):
    fig=sm.qqplot(data)
    plt.show()
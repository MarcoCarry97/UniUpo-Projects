# -*- coding: utf-8 -*-
"""
Created on Sun May  8 10:29:36 2022

@author: Marco-PC
"""

import base as b
import dplotter as dp
import numpy as np
import pandas as pd
import seaborn as sb

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"
               #"PM10_Manlleu.csv"
               ]
    return b.prepareData(listfiles, ";")

def boxplot(data,x,y,title,delete,save):
    p=dp.BoxPlotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,delete=delete,save=save)
    
def scatterplot(data,x,y,title,delete,save):
    p=dp.ScatterPlotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,delete=delete,save=save)
    
def pairplot(data,x,y,title,delete,save):
    p=dp.PairPlotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,delete=delete,save=save)
    
def lineplot(data,x,y,title,delete,save):
    p=dp.LinePlotter()
    p.labels(x, y)
    p.title(title)
    p.show(data,delete=delete,save=save)
    
def heatmap(data,title,delete,save):
    p=dp.HeatMap()
    p.title(title)
    p.show(data,delete=delete,save=save)
    
data=sensorData()
refSt="RefSt"
o3="Sensor_O3"
time="time"

labels=["Temp",
        "RelHum",
        "Sensor_NO",
        "Sensor_SO2",
        "Sensor_NO2",
        #"Sensor_PM10"
        ]

delete=True
save=True

heatmap(data,"Correlation", delete, save)
delete=False

b.addTime(data)
b.addNormalizedData(data)

for label in labels:
    scatterplot(data,label,refSt,label+" - SensorO3",delete,save)
    scatterplot(data,label,o3,label+" - RefSt",delete,save)  

scatterplot(data,o3,refSt, o3+" - "+refSt, delete, save)
scatterplot(data,"normalizedO3","normalizedRefSt", "normalizedO3 - normalizedRefSt", delete, save)
   
lineplot(data,o3,time,o3+" on "+time,delete,save)
lineplot(data,refSt,time,refSt+" on "+time,delete,save)



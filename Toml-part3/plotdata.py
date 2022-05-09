# -*- coding: utf-8 -*-
"""
Created on Sun May  8 10:29:36 2022

@author: Marco-PC
"""

from base import prepareData
import dplotter as dp
import numpy as np

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "PM10_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"]
    return prepareData(listfiles, ";")

data=sensorData()
delete=False
plotTypes=["scatter","line","bar"]
for ptype in plotTypes:
    p=dp.Plotter()
    y=data["Sensor_O3"].values
    x=np.arange(0,len(y),1)
    p.labels("time","O3")
    p.title("O3 - "+ptype)
    for key in data.keys():
        if(key!="date" and key!="Sensor_O3"):
               data.plot.pie(startangle=90)
            delete=False
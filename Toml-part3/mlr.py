# -*- coding: utf-8 -*-
"""
Created on Sat May 14 00:10:56 2022

@author: Marco-PC
"""

import base as b
import linear as lm

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"
               #"PM10_Manlleu.csv"
               ]
    return b.prepareData(listfiles, ";")


data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,"Sensor_O3")

model=linearRegr.makeModel()
res=model.predict()
res.printRes()
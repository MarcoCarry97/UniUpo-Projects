# -*- coding: utf-8 -*-
"""
Created on Wed May 18 18:00:47 2022

@author: Marco-PC
"""

import base as b
import svr as svr


def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"
               #"PM10_Manlleu.csv"
               ]
    return b.prepareData(listfiles, ";")


predLabel="RefSt"
otherLabel="Sensor_O3"

first=["Sensor_O3","Temp","Sensor_SO2"] #best positives
second=["RelHum","Sensor_NO2","Sensor_NO"] #best negatives
third=["Sensor_O3","Temp","RelHum"] #best squares

features=[first,second,third]

kernel="rbf"

for feature in features:
    print("\n\n\nSUPPORT VECTOR REGRESSION WITH RBF KERNEL\n\n\n")
    data=sensorData()
    data=data.drop(["date"],axis=1)
    svRegr=svr.SupportVectorRegression(data,0.7,predLabel,alpha=1)
    svRegr.noRegularization()
    model=svRegr.makeModel(kernel,labels=feature)
    model.tune()
    res=model.predict()
    res.printRes()
    model.plot()
# -*- coding: utf-8 -*-
"""
Created on Wed May 18 16:51:34 2022

@author: Marco-PC
"""

import base as b
import randomforest as rf


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

numEst=5

first=["Sensor_O3","Temp","Sensor_SO2"] #best positives
second=["RelHum","Sensor_NO2","Sensor_NO"] #best negatives
third=["Sensor_O3","Temp","RelHum"] #best squares

features=[first,second,third]

for feature in features:
    print("\n\n\nRANDOM FOREST REGRESSION WITH "+str(numEst)+" ESTIMATORS\n\n\n")
    data=sensorData()
    data=data.drop(["date"],axis=1)
    rfRegr=rf.RandForestRegression(data,0.7,predLabel,alpha=1)
    rfRegr.noRegularization()
    model=rfRegr.makeModel(numEst,labels=feature)
    res=model.predict()
    res.printRes()
    model.plot()
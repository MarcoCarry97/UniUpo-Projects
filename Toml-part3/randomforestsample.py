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


estValues=[1,2,3,4,5]

for val in estValues:
    print("\n\n\nRANDOM FOREST REGRESSION WITH "+str(val)+" ESTIMATORS\n\n\n")
    data=sensorData()
    data=data.drop(["date"],axis=1)
    rfRegr=rf.RandForestRegression(data,0.7,predLabel,alpha=1)
    rfRegr.noRegularization()
    model=rfRegr.makeModel(val)
    res=model.predict()
    res.printRes()
    model.plot()
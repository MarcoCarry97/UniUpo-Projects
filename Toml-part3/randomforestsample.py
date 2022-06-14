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

data=sensorData()
data=data.drop(["date"],axis=1)
rfRegr=rf.RandForestRegression(data,0.7,predLabel,alpha=1,numEst=numEst)
rfRegr.noRegularization()
subset=rfRegr.forwardSelection()
print(subset)
model=rfRegr.makeModel(features=subset)
#model.tune()
res=model.predict()
res.printRes()
model.plot()
# -*- coding: utf-8 -*-
"""
Created on Wed May 18 16:04:06 2022

@author: Marco-PC
"""

import base as b
import knn as knn


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

k=5

print("\n\n\nKNN REGRESSION WITH K="+str(k)+"\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
knnRegr=knn.KnnRegression(data,0.7,predLabel,alpha=1)
knnRegr.noRegularization()
subset=knnRegr.forwardSelection()
print(subset)
model=knnRegr.makeModel(features=subset)
model.tune()
res=model.predict()

res.printRes()
model.plot(0,50)

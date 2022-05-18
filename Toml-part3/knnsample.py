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


print("\n\n\KNN REGRESSION WITH K=1\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
knnRegr=knn.KnnRegression(data,0.7,predLabel,alpha=1)
knnRegr.noRegularization()
model=knnRegr.makeModel(1)
res=model.predict()
res.printRes()
model.plot()

print("\n\n\KNN REGRESSION WITH K=5\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
knnRegr=knn.KnnRegression(data,0.7,predLabel,alpha=1)
knnRegr.noRegularization()
model=knnRegr.makeModel(5)
res=model.predict()
res.printRes()
model.plot()

print("\n\n\KNN REGRESSION WITH K=10\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
knnRegr=knn.KnnRegression(data,0.7,predLabel,alpha=1)
knnRegr.noRegularization()
model=knnRegr.makeModel(10)
res=model.predict()
res.printRes()
model.plot()

print("\n\n\KNN REGRESSION WITH K=20\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
knnRegr=knn.KnnRegression(data,0.7,predLabel,alpha=1)
knnRegr.noRegularization()
model=knnRegr.makeModel(1)
res=model.predict()
res.printRes()
model.plot()
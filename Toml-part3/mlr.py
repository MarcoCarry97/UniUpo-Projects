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





print("\n\n\nLINEAR REGRESSION WITHOUT REGULARIZATION\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,"Sensor_O3")
linearRegr.noRegularization()
model=linearRegr.makeModel()
res=model.predict()
res.printRes()
print(model.trainingSet)

print("\n\n\nLINEAR REGRESSION WITH LASSO\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,"Sensor_O3")
linearRegr.useLasso()
model=linearRegr.makeModel()
res=model.predict()
res.printRes()
print(model.trainingSet)

print("\n\n\nLINEAR REGRESSION WITH RIDGE REGRESSION\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,"Sensor_O3")
linearRegr.useRidgeRegression()
model=linearRegr.makeModel()
res=model.predict()
res.printRes()
print(model.trainingSet)
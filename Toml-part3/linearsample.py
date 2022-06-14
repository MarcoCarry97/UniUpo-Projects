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


predLabel="RefSt"
otherLabel="Sensor_O3"

print("\n\n\nLINEAR REGRESSION WITHOUT REGULARIZATION\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,predLabel,alpha=1)
linearRegr.noRegularization()
model=linearRegr.makeModel()
#model.tune()
res=model.predict()
res.printRes()
model.plot()

print("\n\n\nLINEAR REGRESSION WITH LASSO\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,predLabel,alpha=1)
linearRegr.useLasso()
subset=linearRegr.forwardSelection()
print(subset)
model=linearRegr.makeModel(features=subset)
model.tune()
res=model.predict()
res.printRes()
model.plot()

print("\n\n\nLINEAR REGRESSION WITH RIDGE REGRESSION\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
linearRegr=lm.LinearRegression(data,0.7,predLabel,alpha=1)
linearRegr.useRidgeRegression()
subset=linearRegr.forwardSelection()
print(subset)
model=linearRegr.makeModel(features=subset)
model.tune()
res=model.predict()
res.printRes()
model.plot()
# -*- coding: utf-8 -*-
"""
Created on Wed May 18 00:48:10 2022

@author: Marco-PC
"""

from kernel import KernelRegression, KernelModel
import base as b

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"
               #"PM10_Manlleu.csv"
               ]
    return b.prepareData(listfiles, ";")


predictLabel="RefSt"

print("\n\n\nLINEAR KERNEL RIDGE REGRESSION\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
kernelRegr=KernelRegression(data,0.7,predictLabel)
model=kernelRegr.makeModel("linear")
res=model.predict()
res.printRes()
model.plot()

print("\n\n\nRADIAL BASE FUNCTION KERNEL\n\n\n")
data=sensorData()
data=data.drop(["date"],axis=1)
kernelRegr=KernelRegression(data,0.7,predictLabel)
model=kernelRegr.makeModel("RBF")
res=model.predict()
res.printRes()
model.plot()
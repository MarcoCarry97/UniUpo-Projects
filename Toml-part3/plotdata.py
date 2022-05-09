# -*- coding: utf-8 -*-
"""
Created on Sun May  8 10:29:36 2022

@author: Marco-PC
"""

from base import prepareData
import dplotter as dp
import numpy as np
import pandas as pd

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "PM10_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"]
    return prepareData(listfiles, ";")

data=sensorData()
delete=True
o3="Sensor_O3"
p=dp.BoxPlotter()
p.labels("time",o3)
p.show(data,delete=delete,save=True)
delete=False
   
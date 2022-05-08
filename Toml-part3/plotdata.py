# -*- coding: utf-8 -*-
"""
Created on Sun May  8 10:29:36 2022

@author: Marco-PC
"""

from base import prepareData
from dplotter import BoxPlotter
import numpy as np
from dplotter import Plotter

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "PM10_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"]
    return prepareData(listfiles, ";")

data=sensorData()
#print(data)
#pd.set_option("display.max.columns", None)
delete=True
#print(data)
bp=BoxPlotter(data)
bp.show()



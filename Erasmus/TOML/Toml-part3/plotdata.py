# -*- coding: utf-8 -*-
"""
Created on Sun May  8 10:29:36 2022

@author: Marco-PC
"""

import base as b
import dplotter as dp

def sensorData():
    listfiles=["captor17013-sensor1.csv",
               "NO_Manlleu.csv",
               "SO2_Manlleu.csv",
               "NO2_Manlleu.csv"
               #"PM10_Manlleu.csv"
               ]
    return b.prepareData(listfiles, ";")
    


    
data=sensorData()
refSt="RefSt"
o3="Sensor_O3"
time="time"

labels=["Temp",
        "RelHum",
        "Sensor_NO",
        "Sensor_SO2",
        "Sensor_NO2",
        #"Sensor_PM10"
        ]

delete=True
save=True

dp.heatmap(data,"Correlation", delete, save)
delete=False

b.addTime(data)
b.addNormalizedData(data)

for label in labels:
    #dp.scatterplot(data,label,[refSt,o3],label+" - SensorO3",delete,save)
    dp.scatterplot(data,label,refSt,label+" - "+refSt,delete,save)
    dp.scatterplot(data,label,o3,label+" - "+o3,delete,save)  

dp.scatterplot(data,o3,refSt, o3+" - "+refSt, delete, save)
dp.scatterplot(data,"normalizedO3","normalizedRefSt", "normalizedO3 - normalizedRefSt", delete, save)
   
dp.lineplot(data,time,o3,o3+" on "+time,delete,save)
dp.lineplot(data,time,refSt,refSt+" on "+time,delete,save)
dp.lineplot(data.iloc[0:500],time,[o3,refSt],o3+", "+refSt+" on "+time,delete,save)


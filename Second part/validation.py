# -*- coding: utf-8 -*-
"""
Created on Thu Jun  2 22:14:22 2022

@author: Marco-PC
"""

# -*- coding: utf-8 -*-
"""
Interpretation:
    0 -> ---
    1 -> --+
    2 -> -+-
    3 -> -++
    4 -> +--
    5 -> +-+
    6 -> ++-
    7 -> +++
"""

import pandas as pd
import numpy as np


dataList=[]

for i in range(0,8): #read csv files
    dataList+=[pd.read_csv("covidsim-"+str(i)+".csv")]
    
avgData=pd.DataFrame()

labels=list(dataList[0].columns)

#labels.remove("time")
#labels.remove("Unnamed: 0")

num=len(dataList[0]["S"])

for label in reversed(labels):
    values=[]
    for i in range(0,num):
        val=0
        for data in dataList:
            val+=data[label][i]
        values+=[val]
        
    avgData.insert(0,label,np.array(values))   

avgData.plot(x="time",y=["S","E","I","R","D","L","C"])
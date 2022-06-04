# -*- coding: utf-8 -*-
"""
Created on Fri Jun  3 11:03:24 2022

@author: Marco-PC
"""

import pandas as pd
import numpy as np

from yates import YatesAlgorithm

dataList=[]
yatesAlg=YatesAlgorithm()

for i in range(0,8): #read csv files
    dataList+=[pd.read_csv("covidsim-"+str(i)+".csv")]
    
avgData=pd.DataFrame()

#labels=list(dataList[0].columns)
labels=["I","L"]

#labels.remove("time")
#labels.remove("Unnamed: 0")

num=len(dataList[0]["S"])

for label in labels:
    values=[]
    for data in dataList:
        labVal=data[label]
        values+=[labVal.max()]
        #i+=1
    print("max",values,"\n")
    avgData.insert(0,"max "+label,np.array(values))
    res=yatesAlg.conputeEffects(values, 3)
    avgData.insert(0,"effects "+label,np.array(res))


avgData.to_excel("./yatesRes.xlsx")
avgData.to_csv("./yatesRes.csv")
#avgData.insert(0,"time",np.arange(0,len(dataList[0]["S"]),1))  
#avgData.plot(x="time",y=["S","E","I","R","D","L","C"])
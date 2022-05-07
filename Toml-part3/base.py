import pandas as pd
import numpy as np
import tensorflow as tf
import sklearn as sk

def readData(filename,separator):
    data=pd.read_csv(filename,delimiter=separator)
    data.isnull().values.any()
    data=data.dropna()
    data.head()
    return data;

def mergeData(data,other,how,left,right):
    return pd.merge(data,other,how=how,left_on=left,right_on=right)

def printShape(features,data):
    print(features,data.shape)

def prepareData(listFileNames,separator):
    listdata=[]
    for filename in listFileNames: #Loading and preprocessing
        listdata+=[readData(filename,separator)]
    data=listdata[0]
    for i in range(1,len(listdata)):
        data=mergeData(data,listdata[i],)
    

class Algorithm:
    def __init__(self,filename,percentual):
        data=pd.read_csv(filename)
        print(type(data))

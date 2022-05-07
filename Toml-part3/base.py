import pandas as pd
import numpy as np
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
    for i in range(1,len(listdata)): #Merging
        data=mergeData(data,listdata[i],"inner","date","date")
        data.head()
    return data
    

class Algorithm:
    def __init__(self,data,percentual):
        self.trainingSet=data[0:len(data)*percentual]
        self.testSet=data[len(data)*percentual+1,len(data)]

    def makeModel():
        pass


class Model:
    def __init__(self,trainingSet,testSet,labels):
        self.trainingSet=trainingSet
        self.testSet=testSet
        self.labels=labels
        self.ridge=False
        self.lasso=False
        self.none=True
        
    def getCoefficients(self):
        return self.model.coef_
    
    def predict(self):
        pass
    
    def useRidgeRegression(self):
        self.ridge=True
        self.lasso=False
        self.none=False
        
    def useLasso(self):
        self.lasso=True
        self.ridge=False
        self.none=False
        
    def noRegularization(self):
        self.none=True
        self.ridge=False
        self.lasso=False

class Results:
    def __init__(self,prediction,prob,score,rsquare,rmse,mae):
        self.prediction=prediction;
        self.probability=prob
        self.score=score
        self.rsquare=rsquare
        self.rmse=rmse
        self.mae=mae
    
    def __str__(self):
        return 
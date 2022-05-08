import pandas as pd
import numpy as np
import sklearn as sk
import sklearn.metrics as skm
import math

def readData(filename,separator):
    data=pd.read_csv(filename,delimiter=separator)
    data.isnull().values.any()
    data=data.dropna()
    if("date" in data.keys()):
        data["date"]=pd.to_datetime(data["date"]).dt.strftime('%Y-%m-%dT%H:%M')
    if("Sensor_O3" in data.keys()):
        nums=[]
        for n in data["Sensor_O3"]:
            if n.count(".")>1:
                n=n.replace(".","",1)
            nums+=[np.float64(n)]
        data["Sensor_O3"]=np.array(nums)
                
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
    def __init__(self,data,percentual,predictLabels,alpha):
        self.trainingSet=data[0:len(data)*percentual]
        self.testSet=data[len(data)*percentual+1,len(data)]
        self.predictLabels=predictLabels
        self.modelType="Normal"
        self.alpha=alpha

    def makeModel():
        pass
    
    def useRidgeRegression(self):
        self.modelType="Ridge"
        
    def useLasso(self):
        self.modelType="Lasso"
        
    def noRegularization(self):
        self.modelType="Normal"



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
        prediction=self.model.predict(self.testSet)
        truevalue=self.testSet[self.labels]
        score=self.model.score(self.testSet,self.labels)
        rsquare=skm.r2_score(truevalue, prediction)
        rmse=math.sqrt(skm.mean_squared_error(truevalue,prediction))
        mae=skm.mean_absolute_error(truevalue,prediction)
        prob=self.model.predict_proba(self.testSet)
        return Results(prediction,prob,score,rsquare,rmse,mae)
    
class Results:
    def __init__(self,prediction,prob,score,rsquare,rmse,mae):
        self.prediction=prediction;
        self.probability=prob
        self.score=score
        self.rsquare=rsquare
        self.rmse=rmse
        self.mae=mae
    
 
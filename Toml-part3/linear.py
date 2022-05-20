# -*- coding: utf-8 -*-
"""
Created on Sat May  7 23:52:55 2022

@author: Marco-PC
"""

import sklearn.linear_model as lm
from sklearn.feature_selection import SelectFromModel as forwardSelection
import numpy as np
import pandas as pd

#import sklearn.metrics as skm
#import math

from base import Algorithm, Model

class LinearRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,scale=False):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        
    def makeModel(self):
        return LinearModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,modelType=self.modelType,alpha=self.alpha)
        
class LinearModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha)
        self.model=None
        if(modelType=="Normal"):
            self.model=lm.LinearRegression()
            select=forwardSelection(self.model)
            select.fit(trainingSet,trainingLabels)
            self.featuresSelected=np.array(self.trainingSet.columns[select.get_support()])
            self.trainingSet=self.makeDataset(self.featuresSelected,select.transform(self.trainingSet).T)
            self.testSet=self.makeDataset(self.featuresSelected,select.transform(self.testSet).T)
        elif(modelType=="Lasso"):
            self.model=lm.Lasso(alpha=alpha)
        else:
            self.model=lm.Ridge(alpha=alpha)
        
        self.model.fit(self.trainingSet,self.trainingLabels)
        
        #self.features=self.model.transform(self.trainingSet)
    def makeDataset(self,labels,arrays):
        dictio={}
        for i in range(0,len(labels)):
            dictio[labels[i]]=arrays[i]
        return pd.DataFrame(dictio)

    def params(self):
        return {
                "alpha": [0.5,1,2,5,10,25,50,100,250,500,1000]
            }
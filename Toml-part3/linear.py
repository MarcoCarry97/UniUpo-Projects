# -*- coding: utf-8 -*-
"""
Created on Sat May  7 23:52:55 2022

@author: Marco-PC
"""

import sklearn.linear_model as lm
#import sklearn.metrics as skm
#import math

from base import Algorithm, Model

class LinearRegression(Algorithm):
    def __init__(data,percentual):
        super().__init__(data, percentual)
        
    def makeModel(self):
        labels=self.trainingSet.keys()
        return LinearModel(self.trainingSet,self.testSet,labels,self.modelType,self.alpha)
        
class LinearModel(Model):
    def __init__(self, trainingSet, testSet, labels,modelType,alpha):
        super.__init__(self,trainingSet,testSet,labels)
        self.model=None
        if(modelType=="Normal"):
            self.model=lm.LinearRegression(normalize=True)
        elif(modelType=="Lasso"):
            self.model=lm.Lasso(alpha=alpha,normalize=True)
        else:
            self.model=lm.Ridge(alpha=alpha,normalize=True)
        self.model.fit(trainingSet.values,labels.values)
    
    


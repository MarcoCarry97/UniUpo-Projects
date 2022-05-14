# -*- coding: utf-8 -*-
"""
Created on Sat May  7 23:52:55 2022

@author: Marco-PC
"""

import sklearn.linear_model as lm
from sklearn.feature_selection import SelectFromModel as forwardSelection

#import sklearn.metrics as skm
#import math

from base import Algorithm, Model

class LinearRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,scale=False):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        
    def makeModel(self):
        return LinearModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,self.alpha)
        
class LinearModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha)
        self.model=None
        if(modelType=="Normal"):
            self.model=lm.LinearRegression()
        elif(modelType=="Lasso"):
            self.model=lm.Lasso(alpha=alpha)
        else:
            self.model=lm.Ridge(alpha=alpha)
        #self.model=forwardSelection(self.model)
        self.model.fit(trainingSet,trainingLabels)
        #self.features=self.model.trainsform(self.trainingSet)
    


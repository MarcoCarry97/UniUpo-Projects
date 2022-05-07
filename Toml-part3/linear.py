# -*- coding: utf-8 -*-
"""
Created on Sat May  7 23:52:55 2022

@author: Marco-PC
"""

import sklearn.linear_model as lm
import sklearn.metrics as skm
import math

from base import Algorithm, Model, Result

class LinearRegression(Algorithm):
    def __init__(data,percentual):
        super().__init__(data, percentual)
        
    def makeModel(self):
        labels=self.trainingSet.keys()
        return LinearModel(self.trainingSet,self.testSet,labels)
        
class LinearModel(Model):
    def __init__(self, trainingSet, testSet, labels):
        super.__init__(self,trainingSet,testSet,labels)
        self.model=lm.LinearRegression(normalize=True)
        self.model.fit(trainingSet.values,labels.values)
    
    def predict(self):
        prediction=self.model.predict(self.testSet)
        score=self.model.score(self.testSet,self.labels)
        rsquare=skm.r2_score(truevalue, prediction)
        rmse=math.sqrt(skm.mean_squared_error(truevalue,prediction))
        mae=skm.mean_absolute_error(truevalue,prediction)
        prob=self.model.predict_proba(self.testSet)
        return Result(prediciton,score)


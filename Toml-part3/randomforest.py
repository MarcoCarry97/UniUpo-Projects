# -*- coding: utf-8 -*-
"""
Created on Wed May 18 16:30:20 2022

@author: Marco-PC
"""

import sklearn as sk
import sklearn.ensemble as ens
import pandas as pd
import numpy as np

from base import Algorithm, Model

class RandForestRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        
    def makeModel(self,numEst):
        return RandForestModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,modelType=self.modelType,alpha=self.alpha,numEst=numEst)
      
class RandForestModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,kernelType="linear",numEst=1):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha)
        self.kernelType=kernelType
        self.model=None
        self.numEst=numEst
        self.model=ens.RandomForestRegressor(n_estimators=self.numEst)
       
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select=forwardSelection(self.model)
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select.fit(trainingSet,trainingLabels)
        #self.featuresSelected=np.array(self.trainingSet.columns[select.get_support()])
        #self.trainingSet=self.makeDataset(self.featuresSelected,select.transform(self.trainingSet).T)
        #self.testSet=self.makeDataset(self.featuresSelected,select.transform(self.testSet).T)
        
        
        self.model.fit(self.trainingSet,self.trainingLabels)
        
        #self.features=self.model.transform(self.trainingSet)

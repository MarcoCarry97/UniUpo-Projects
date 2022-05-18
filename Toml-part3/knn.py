# -*- coding: utf-8 -*-
"""
Created on Wed May 18 15:44:32 2022

@author: Marco-PC
"""

# -*- coding: utf-8 -*-
"""
Created on Tue May 17 23:40:57 2022

@author: Marco-PC
"""

import sklearn as sk
import sklearn.neighbors as knn
from sklearn.feature_selection import SelectFromModel as forwardSelection
import pandas as pd
import numpy as np

from base import Algorithm, Model

class KnnRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        
    def makeModel(self,k):
        return KnnModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,modelType=self.modelType,alpha=self.alpha,k=k)
      
class KnnModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,kernelType="linear",k=1):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha)
        self.kernelType=kernelType
        self.model=None
        self.k=k
        self.model=knn.KNeighborsRegressor(self.k)
       
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select=forwardSelection(self.model)
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select.fit(trainingSet,trainingLabels)
        #self.featuresSelected=np.array(self.trainingSet.columns[select.get_support()])
        #self.trainingSet=self.makeDataset(self.featuresSelected,select.transform(self.trainingSet).T)
        #self.testSet=self.makeDataset(self.featuresSelected,select.transform(self.testSet).T)
        
        
        self.model.fit(self.trainingSet,self.trainingLabels)
        
        #self.features=self.model.transform(self.trainingSet)


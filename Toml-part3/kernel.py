# -*- coding: utf-8 -*-
"""
Created on Tue May 17 23:40:57 2022

@author: Marco-PC
"""

import sklearn as sk
import sklearn.kernel_ridge as kr
import sklearn.gaussian_process.kernels as kernels
import sklearn.gaussian_process as gp
from sklearn.feature_selection import SelectFromModel as forwardSelection
import pandas as pd
import numpy as np

from base import Algorithm, Model

class KernelRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        self.gamma=gamma
        
    def makeModel(self,kernelType):
        return KernelModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,kernelType=kernelType,modelType=self.modelType,alpha=self.alpha)
      
class KernelModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,kernelType="linear"):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha)
        self.kernelType=kernelType
        self.model=None
        
        self.model=kr.KernelRidge(alpha=self.alpha,kernel=self.kernelType)
       
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select=forwardSelection(self.model)
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select.fit(trainingSet,trainingLabels)
        #self.featuresSelected=np.array(self.trainingSet.columns[select.get_support()])
        #self.trainingSet=self.makeDataset(self.featuresSelected,select.transform(self.trainingSet).T)
        #self.testSet=self.makeDataset(self.featuresSelected,select.transform(self.testSet).T)
        
        
        self.model.fit(self.trainingSet,self.trainingLabels)
        
        #self.features=self.model.transform(self.trainingSet)


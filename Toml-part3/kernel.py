# -*- coding: utf-8 -*-
"""
Created on Tue May 17 23:40:57 2022

@author: Marco-PC
"""

import sklearn.kernel_ridge as kr

from base import Algorithm, Model

class KernelRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        self.gamma=gamma
        
    def makeModel(self,kernelType,labels):
        return KernelModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,kernelType=kernelType,modelType=self.modelType,alpha=self.alpha,selectedLabels=labels)
      
class KernelModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,kernelType="linear",selectedLabels=[]):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha,selectedLabels=selectedLabels)
        self.kernelType=kernelType
        self.model=None
        
        self.model=kr.KernelRidge(alpha=self.alpha,kernel=self.kernelType)
        self.redefineSets()
       
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select=forwardSelection(self.model)
        #self.model.fit(self.trainingSet,self.trainingLabels)
        #select.fit(trainingSet,trainingLabels)
        #self.featuresSelected=np.array(self.trainingSet.columns[select.get_support()])
        #self.trainingSet=self.makeDataset(self.featuresSelected,select.transform(self.trainingSet).T)
        #self.testSet=self.makeDataset(self.featuresSelected,select.transform(self.testSet).T)
        
        
        self.model.fit(self.trainingSet,self.trainingLabels)
        
        #self.features=self.model.transform(self.trainingSet)


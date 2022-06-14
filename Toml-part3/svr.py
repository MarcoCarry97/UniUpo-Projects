# -*- coding: utf-8 -*-
"""
Created on Wed May 18 17:51:58 2022

@author: Marco-PC
"""

import sklearn.svm as skv


from base import Algorithm, Model

class SupportVectorRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False,kernel="rbf"):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        self.kernel=kernel
        
    def makeModel(self,features=[]):
        return SvrModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,modelType=self.modelType,alpha=self.alpha,kernelType=self.kernel,labels=features)
      
class SvrModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,kernelType="rbf",labels=[]):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha,selectedLabels=labels)
        self.kernelType=kernelType
        self.model=None
        self.kernelType=kernelType
        self.model=skv.SVR(kernel=self.kernelType)
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
    def params(self):
        return {
            "gamma":["scale","auto",1,2,3,4,5],
            "C":[0.001,0.01,0.1,1,10,100,200,300,400,500,600,700,800,900,1000],
            "kernel":["rbf"],
            "degree":[1,2,3,4,5]
            }
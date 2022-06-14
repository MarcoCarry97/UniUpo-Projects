# -*- coding: utf-8 -*-
"""
Created on Wed May 18 16:30:20 2022

@author: Marco-PC
"""

import sklearn.ensemble as ens

from base import Algorithm, Model

class RandForestRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False,numEst=1):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        self.numEst=1
        
    def makeModel(self,features=[]):
        return RandForestModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,modelType=self.modelType,alpha=self.alpha,numEst=self.numEst,selectedLabels=features)
      
class RandForestModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,numEst=1,selectedLabels=[]):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha,selectedLabels=selectedLabels)
        
        self.model=None
        self.numEst=numEst
        self.model=ens.RandomForestRegressor(n_estimators=self.numEst)
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
            "n_estimators":[1,10,20,30,40,50,60,70,80,90,100],
            "criterion":["squared_error"],
            "max_depth":[None,1,10,20,30,40,50,60,70,80,90100],
            "min_samples_split":[1,2,5],
            "min_samples_leaf":[2,5,10],
            "max_features":["auto"],
            "max_leaf_nodes":[None,1,2,5],
            "max_samples":[None,1,5,0.7,0.3]
            }
    
    
        
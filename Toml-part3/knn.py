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

import sklearn.neighbors as knn


from base import Algorithm, Model

class KnnRegression(Algorithm):
    def __init__(self,data,percentual,predictLabel,alpha=1,gamma=None,scale=False,k=1):
        super().__init__(data, percentual,predictLabel,alpha=alpha,scale=scale)
        self.k=k
        
    def makeModel(self,features=[]):
        return KnnModel(self.trainingSet,self.trainingLabels,self.testSet,self.testLabels,modelType=self.modelType,alpha=self.alpha,k=self.k,labels=features)
      
class KnnModel(Model):
    def __init__(self, trainingSet, trainingLabels, testSet, testLabels,modelType="Normal", alpha=1,k=1,labels=[]):
        super().__init__(trainingSet, trainingLabels, testSet, testLabels,modelType=modelType, alpha=alpha,selectedLabels=labels)
        self.model=None
        self.k=k
        self.model=knn.KNeighborsRegressor(self.k)
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
            "n_neighbors":[1]+list(range(10,110,10)),
            "weights":["uniform","distance"],
            "leaf_size":[10,20,30,40,50,60,70,80,90,100],
            "p":[1,2,3,4,5,6,7,8,9,10]
            
            }

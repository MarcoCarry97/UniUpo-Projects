# -*- coding: utf-8 -*-
"""
Created on Wed Jun  8 21:27:13 2022

@author: Marco-PC
"""

import numpy as np
import pandas as pd


def sigmoid(xx):
    return(1/(1+np.exp(-xx)))

def safe_log(xx):
    yy=np.zeros(shape=(len(xx),1))
    for ii in range(len(xx)):
        if xx[ii] < 1e-10 :
            yy[ii]=np.log(1e-10)
        else:
            yy[ii]=np.log(xx[ii])
    return(yy)

def safe_inv(xx):
    yy=np.zeros(shape=(len(xx),1))
    for ii in range(len(xx)):
        if np.abs(xx[ii]) < 1e-10 :
            yy[ii]=1e+10
        else:
            yy[ii]=1.0/xx[ii]
    return(yy)

def ReLU(num):
    return np.maximum(num,0)

def randomNum(a,b):
    return np.random.randn(a,b)

def computeLoss(trueValue,prediction):
    a=trueValue*safe_log(prediction)
    b=(1-trueValue)*safe_log(1-prediction)
    return -a-b

def computeInvert(trueValue,prediction):
    a=trueValue*safe_inv(prediction)
    b=(1-trueValue)*safe_inv(1-prediction)
    return -a+b

def backpropagation(self,trueValue,prediction,aa,za):
    weights=self.weights
    i=len(za)-1
    gradPred=computeInvert(trueValue,prediction)
    sig=sigmoid(za[i])
    gradZ=gradPred*sig*(1-sig)
    gradW=aa[i-1].T.dot(gradZ)
    gradWeights=[gradW]
    for i in range(len(aa)-2,-1,-1):
        gradA=gradZ.dot(weights[i])
        gradZ=gradA.copy()
        gradZ[za[i]<0]=0
        gradW=aa[i-1].dot(weights[i])
        gradWeights+=[gradW]
    return gradWeights   
    

class NeuralNetwork:
    def __init__(self,inputs=1,hiddens=20,outputs=3,batchSize=640,learningRate=1e-4):
        self.numInput=inputs
        self.numHidden=hiddens
        self.numOutput=outputs
        self.batchSize=batchSize
        self.weights=[randomNum(inputs,hiddens)]
        for i in range(0,hiddens):
            self.weights+=[randomNum(hiddens,hiddens)]
        self.weights=[randomNum(inputs,outputs)]
        self.learningRate=learningRate
        
    
    def forward(x,weights):
        a=x
        z=ReLU(a)
        aa=[a]
        za=[z]
        for i in range(1,len(weights)):
            aa+=[a]
            w=weights[i]
            z=a.dot(w)
            a=ReLU(z)
            za=[z]
        return sigmoid(z),aa,za
    
    def updateWeights(self,alpha,gradWeights,t):
        for i in range(0,len(self.weights)):
            value=0
            if(t==0):
                value=self.gradWeights[i]
            else:
                value=alpha*value+(1-alpha)*self.gradWeights[i]
                self.weights[i]-=value*self.learningRate
            
        
    def compute(self,trainingSet,testSet,numIterations=2000):
        losses=np.zeros(shape=(numIterations,2))
        prediction=0
        for t in range(0,numIterations):
            #training
            prediction,aa,za=self.forward(self.weights)
            trueValue=0
            loss=computeLoss(trueValue, prediction)
            losses[t,0]=loss.mean()
            #testing
            testPrediction=self.forward(self.weights)
            testValue=0
            loss=computeLoss(testValue, testPrediction)
            losses[t,1]=loss.mean()
            #updating
            gradWeights=backpropagation(trueValue, prediction, aa, za)
            self.updateWeights(0.7,gradWeights, t)
        return prediction 
            
            
    
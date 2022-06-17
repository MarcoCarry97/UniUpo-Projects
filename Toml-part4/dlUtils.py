# -*- coding: utf-8 -*-
"""
Created on Wed Jun  8 21:27:13 2022

@author: Marco-PC
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score
from sklearn.metrics import mean_squared_error

def sigmoid(xx):
    return(1/(1+np.exp(-xx)))

def safe_log(xx):
    yy=np.zeros(shape=(len(xx),1))
    for ii in range(len(xx)):
        if(xx[ii] < 1e-10):
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

def randomNum(size):
    return np.random.randn(size)

def randomNum2(a,b):
    return np.random.randn(a,b)

def computeLoss(trueValue,prediction):
    a=trueValue*safe_log(prediction)
    b=(1-trueValue)*safe_log(1-prediction)
    return (-a-b).mean()

def computeInvert(trueValue,prediction):
    a=trueValue*safe_inv(prediction)
    b=(1-trueValue)*safe_inv(1-prediction)
    return -a+b

def backpropagation(w,trueValue,a3,z3,a2,z2,a1,z1,x):
    gradA3=computeInvert(trueValue,a3)
    sig=sigmoid(z3)
    gradZ3=gradA3*sig*(1-sig)
    gradW3=a2.T.dot(gradZ3)
    gradA2=gradZ3.dot(w[2].T)
    gradZ2=gradA2.copy()
    gradZ2[z2<0]=0
    gradW2=a1.T.dot(gradZ2)
    gradA1=gradZ2.dot(w[1].T)
    gradZ1=gradA1.copy()
    gradZ1[z1<0]=0
    gradW1=x.T.dot(gradZ1)
    return [gradW1,gradW2,gradW3]

def module(xx):
    return(np.sqrt(xx.dot(xx)))

def generateSet(shape,noise,radius):
    size=shape[0]
    x=np.zeros(shape=shape)
    y=np.zeros(shape=(size,1))
    x[:,0]=randomNum(size)
    x[:,1]=randomNum(size)
    x[:,2]=1
    for i in range(0,size):
        mod=module(x[i,0:2])
        n1=randomNum(1)
        n2=randomNum(1)
        if((mod+noise*n1)<radius[0] or (mod+noise*n2)>radius[1]):
            y[i]=0
        else:
            y[i]=1
    return [x,y]
          

def generateDataSet(x,y,noise,radius):
    trainingSet=generateSet((x,y),noise,radius)
    testSet=generateSet((x,y),noise,radius)
    return trainingSet,testSet

def forward(x,w):
    z1=x.dot(w[0])
    a1=ReLU(z1)
    z2=a1.dot(w[1])
    a2=ReLU(z2)
    z3=a2.dot(w[2])
    a3=sigmoid(z3)
    return a3,z3,a2,z2,a1,z1

class NeuralNetwork:
    def __init__(self,data,inputs,hiddens,outputs,batchSize,radius,learningRate=1e-4,noise=0):
        self.inputs=inputs
        self.hiddens=hiddens
        self.outputs=outputs
        self.weights=[randomNum2(inputs,hiddens),
                      randomNum2(hiddens,hiddens),
                      randomNum2(hiddens,outputs)]
        self.learningRate=learningRate
        self.batchSize=batchSize
        self.trainingSet,self.testSet=data[0],data[1]
        self.noise=noise
        self.radius=radius
        self.v1,self.v2,self.v3=0,0,0
        self.losses=None
        
    def updateWeights(self,gradW,alpha,t):
        v1=self.v1
        v2=self.v2
        v3=self.v3
        if(t==0):
            v1=gradW[0]
            v2=gradW[1]
            v3=gradW[2]
        v1=alpha*v1+(1-alpha)*gradW[0]
        v2=alpha*v2+(1-alpha)*gradW[1]
        v3=alpha*v3+(1-alpha)*gradW[2]
        self.weights[0]-=self.learningRate*v1
        self.weights[1]-=self.learningRate*v2
        self.weights[2]-=self.learningRate*v3
        self.v1=v1
        self.v2=v2
        self.v3=v3
        #self.losses=0
        
        
    def plotLogLoss(self,losses):
        time=np.arange(1,len(losses)+1,1)
        lossFrame=pd.DataFrame({
                "training loss":np.log(losses[:,0]),
                "test loss":np.log(losses[:,1]),
                "time":time
            })
        lossFrame.plot(x="time",y=["training loss","test loss"])
        
    def compute(self,numIter=2000,alpha=0.7,plot=False):
        losses=np.zeros(shape=(numIter,2))
        predSample=0
        trueSample=0
        for t in range(0,numIter):
            #training
            a3,z3,a2,z2,a1,z1=forward(self.trainingSet[0],self.weights)
            prediction=a3
            trueValue=self.trainingSet[1]
            trainLoss=computeLoss(trueValue, prediction)
            losses[t,0]=trainLoss
            #test
            predTest,_,_,_,_,_=forward(self.testSet[0],self.weights)
            predSample=predTest
            testValue=self.testSet[1]
            trueSample=testValue
            testLoss=computeLoss(testValue, predTest)
            losses[t,1]=testLoss
            #backpropagation
            gradW=backpropagation(self.weights, trueValue, a3, z3, a2, z2, a1, z1, self.trainingSet[0])
            self.updateWeights(gradW,alpha,t)
        if(plot):
            self.plotLogLoss(losses)
        r2=r2_score(trueSample,predSample)
        rmse=np.sqrt(mean_squared_error(trueSample, predSample))/len(trueSample)
        return r2, rmse
        
        
        

        
    
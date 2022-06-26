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
import random as rnd

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
    #return np.ones(shape=(a,b))
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
    print([gradW1,gradW2,gradW3])
    #print([gradA3,gradA2,gradA1],[gradZ3,gradZ2,gradZ1],[gradW1,gradW2,gradW3])
    return [gradW1,gradW2,gradW3]

def module(xx):
    return(np.sqrt(xx.dot(xx)))

def generateTrainingSet(shape,noise,radius):
    size=shape[0]
    x=np.zeros(shape=shape)
    y=np.zeros(shape=(size,1))
    x[:,0]=np.random.randn(size)
    x[:,1]=np.random.randn(size)
    x[:,2]=1
    print("radius",radius)
    for i in range(0,size):
        mod=module(x[i,0:2])
        n1=np.random.randn()
        n2=np.random.randn()
        if(mod+noise*np.random.randn()<radius[0]) or (mod+noise*np.random.randn()>radius[1]):
            y[i]=0
        else:
            y[i]=1
    return [x,y]
          
def generateTestSet(shape,noise,radius):
    size=shape[0]
    x=np.ones(shape=shape)
    y=np.zeros(shape=(size,1))
    x[:,0]=np.random.randn(size)
    x[:,1]=np.random.randn(size)
    x[:,2]=1
    print("radius",radius)
    for i in range(0,size):
        mod=module(x[i,0:2])
        n1=np.random.randn()
        n2=np.random.randn()
        if(mod+noise*np.random.randn()<radius[0]) or (mod+noise*np.random.randn()>radius[1]):
            y[i]=0
        else:
            y[i]=1
    return [x,y]
          

def generateDataSet(x,y,noise,radius):
    trainingSet=generateTrainingSet((x,y),noise,radius)
    testSet=generateTestSet((x,y),noise,radius)
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
        self.trainingLoss=None
        self.testLoss=None
        
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
        
    def fit(self,trainingSet,numIter=2000,alpha=0.7):
        self.trainingLoss=np.zeros(shape=(numIter,2))
        prediction=0
        truevalue=0
        for t in range(0,numIter):
            a3,z3,a2,z2,a1,z1=forward(trainingSet[0],self.weights)
            trueValue=trainingSet[1]
            prediction=a3
            self.trainingLoss[t]=computeLoss(trueValue,prediction)
            gradW=backpropagation(self.weights, trueValue, a3, z3, a2, z2, a1, z1, self.trainingSet[0])
            self.updateWeights(gradW, alpha, t)
        return self.testSet
            
    def randomFit(self,trainingSet,size,numIter=2000,alpha=0.7):
        self.trainingLoss=np.zeros(shape=(numIter,2))
        prediction=0
        truevalue=0
        trainingSet,testSet=self.chooseRandomly(size)
        for t in range(0,numIter):
            a3,z3,a2,z2,a1,z1=forward(trainingSet[0],self.weights)
            trueValue=trainingSet[1]
            prediction=a3
            self.trainingLoss[t]=computeLoss(trueValue,prediction)
            gradW=backpropagation(self.weights, trueValue, a3, z3, a2, z2, a1, z1,trainingSet[0])
            self.updateWeights(gradW, alpha, t)
        return testSet
    
    def predict(self, testSet):
        trueValue=testSet[0]
        prediction,_,_,_,_,_=forward(testSet[0],self.weights)
        self.testLoss=computeLoss(trueValue, prediction)
        return self.computeAccuracy(trueValue, prediction)
        
    def compute(self,numIter=2000,alpha=0.7,plot=False):
        losses=np.zeros(shape=(numIter,2))
        predSample=0
        trueSample=0
        if(plot):
            self.pointPlot(self.trainingSet)
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
            gradW=backpropagation(self.weights, trueValue, a3, z3, a2, z2, a1, z1,
                                  self.trainingSet[0])
            self.updateWeights(gradW,alpha,t)
            if(plot and t%200==0):
                self.gridPlot(self.testSet)
        if(plot):
            self.gridPlot(self.testSet)
            self.plotLogLoss(losses)
        diff=((losses[numIter-1,0]-losses[numIter-1,1])**2)**(1/2)
        return self.computeAccuracy(testValue,predTest),diff
    
    def chooseRandomly(self,size):
        trSet=np.zeros(shape=(size,self.inputs))
        trLabels=np.zeros(shape=(size,1))
        teSet=np.zeros(shape=(size,self.inputs))
        teLabels=np.zeros(shape=(size,1))
        takens=[]
        for i in range(0,size):
            j=rnd.randrange(0,self.batchSize,1)
           # while j not in takens:
           #     j=rnd.randrange(0,self.batchSize,1)
            takens+=[j]
            trSet[i]=self.trainingSet[0][j]
            trLabels[i]=self.trainingSet[1][j]
            teSet[i]=self.testSet[0][j]
            teLabels[i]=self.testSet[1][j]
        return (trSet,trLabels),(teSet,teLabels)
        
    
    def computeStohastic(self,size,numIter=2000,alpha=0.7,plot=False):
        losses=np.zeros(shape=(numIter,2))
        predSample=0
        trueSample=0
        if(plot):
            self.pointPlot(self.trainingSet)
        for t in range(0,numIter):
            trainingSet,testSet=self.chooseRandomly(size)
            #training
            a3,z3,a2,z2,a1,z1=forward(trainingSet[0],self.weights)
            prediction=a3
            trueValue=trainingSet[1]
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
            gradW=backpropagation(self.weights, trueValue, a3, z3, a2, z2, a1, z1, trainingSet[0])
            self.updateWeights(gradW,alpha,t)
            if(plot and t%20==0):
                self.gridPlot(self.testSet)
        if(plot):
            self.gridPlot(self.testSet)
            self.plotLogLoss(losses)
        diff=((losses[numIter-1,0]-losses[numIter-1,1])**2)**(1/2)
        return self.computeAccuracy(testValue,predTest),diff
    
    def computeAccuracy(self,trueValues,predTest):
        tp,tn,fp,fn=0,0,0,0
        for i in range(0,len(trueValues)):
            if(predTest[i]<=0.5):
                predTest[i]=0
            else:
                predTest[i]=1
            if(trueValues[i]==1 and predTest[i]==1):
                tp+=1
            elif(trueValues[i]==0 and predTest[i]==0):
                tn+=1
            elif(trueValues[i]==0 and predTest[i]==1):
                fp+=1
            else:
                fn+=1
        return (tp+tn)/(tp+tn+fp+fn)
        
    def gridPlot(self,testSet):
        plt.figure(figsize=(10,10))
        plt.xlim(-2,2) 
        plt.ylim(-2,2) 

        plt.title("Classification areas, orange: class 0, green: class 1. Also shows testing set")
        plt.xlabel("x0")
        plt.ylabel("x1")

        GRID=100
        grid=np.zeros(shape=(2*GRID,3))
        for height in range(-GRID,GRID):  
            for i in range(0,2*GRID):
                grid[i,0]= 2*(i-GRID)/GRID
                grid[i,1]= 2*height/GRID
                grid[i,2]=1

            pred_grid,_,_,_,_,_=forward(grid,self.weights)
            #print("pred grid",pred_grid)
            idgrid_1 = np.where(pred_grid > 0.5)[0]
            idgrid_0 = np.where(pred_grid <= 0.5)[0]
        
            if len(idgrid_0)>0:
                plt.plot(grid[idgrid_0,0],grid[idgrid_0,1],"+",c="orange")
            if len(idgrid_1)>0:
                plt.plot(grid[idgrid_1,0],grid[idgrid_1,1],"+",c="green")
        ytest=testSet[1]
        idtest_1 = np.where(ytest > 0.5)[0]
        idtest_0 = np.where(ytest <= 0.5)[0]

        xtest=testSet[0]
        plt.plot(xtest[idtest_0,0],xtest[idtest_0,1],"d",c="red")
        plt.plot(xtest[idtest_1,0],xtest[idtest_1,1],"d",c="blue")
        plt.show()
        return()
        
    def pointPlot(self,trainingSet):
        y=trainingSet[1]
        x=trainingSet[0]
        
        id_1 = np.where(y == 1)[0]
        id_0 = np.where(y == 0)[0]


        plt.figure(figsize=(10,10))
        plt.xlim(-2,2) 
        plt.ylim(-2,2) 

        plt.title("Training set, red: class 0, blue: class 1")
        plt.xlabel("x0")
        plt.ylabel("x1")

        plt.plot(x[id_0,0],x[id_0,1],"d",c="red")
        plt.plot(x[id_1,0],x[id_1,1],"d",c="blue")
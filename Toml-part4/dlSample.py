# -*- coding: utf-8 -*-
"""
Created on Sat Jun 11 01:01:14 2022

@author: Marco-PC
"""

import dlUtils as dl
import numpy as np

inputs=3
outputs=1

def perform(H,T):
    radius=[1.5,1]
    noise=1
    data=dl.generateDataSet(T,inputs, noise, radius)
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5])
    nn.computeStohastic(T//4,plot=True)
    #r2,rmse,loss=nn.computeStohastic(nn.batchSize//4,plot=True)
    
    
def tune(data,H,T,learningRate,alpha,plot=False):
    radius=[1.5,1]
    noise=1
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5],learningRate=learningRate)
    accuracy,diff=nn.computeStohastic(T//4,numIter=2000,alpha=alpha,plot=plot)
    return accuracy,diff,nn

def underfitting(): #exercise 2
    print("UNDERFITTING")
    hiddens=1
    batchSize=640
    perform(hiddens,batchSize)
    hiddens=2
    perform(hiddens,batchSize)
    hiddens=5
    perform(hiddens,batchSize)

def overfitting(): #exercise 3
    print("OVERFITTING")
    hiddens=20
    batchSize=1
    perform(hiddens,batchSize)
    batchSize=5
    perform(hiddens,batchSize)
    batchSize=10
    perform(hiddens,batchSize)
    batchSize=20
    perform(hiddens,batchSize)
    
def rightValue(): #exercise 4
    print("RIGHT VALUES")
    batchSize=640
    alphas=np.array([0.2,0.3,0.4])
    Hs=np.array([8,9,10,11])
    learningRates=np.array([1e-6,1e-5,1e-4])
    bestCombination=None
    best=0
    first=True
    radius=[1.5,1]
    noise=1
    bestData=None
    bestModel=None
    bestDiff=0
    data=dl.generateDataSet(batchSize,inputs, noise, radius)
    for H in Hs:
        for alpha in alphas:
            for lr in learningRates:
                accuracy,diff,model=tune(data,H,batchSize,lr,alpha)
                print(accuracy,best,bestCombination)
                if(first):
                    best=accuracy
                    bestCombination=(H,lr,alpha)
                    bestData=data
                    bestModel=model
                    first=False
                if(best<accuracy):
                    best=accuracy
                    bestCombination=(H,lr,alpha)
                    bestData=data
                    bestModel=model
                    bestDiff=diff

                #print(H,lr,alpha,R2,rmse)
    print("bestCombination",bestCombination)
    H,lr,alpha=bestCombination
    res=bestModel.compute(alpha=alpha,plot=True)
    print("result for (H, lr, alpha)",bestCombination,":",res)
                
    
    
    
def problems(): #exercise 5
    print("PROBLEMS")
    batchSize=640
    hiddens=100
    perform(hiddens,batchSize)
    hiddens=320
    perform(hiddens,batchSize)
    hiddens=640
    perform(hiddens,batchSize)
    hiddens=1280
    perform(hiddens,batchSize)

#underfitting()
#overfitting()
rightValue()
#problems()
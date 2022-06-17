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
    data=dl.generateDataSet(H,inputs, noise, radius)
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5])
    r2,rmse,loss=nn.compute(plot=True)
    print(r2,rmse)
    
def tune(data,H,T,learningRate,alpha,plot=False):
    radius=[1.5,1]
    noise=1
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5],learningRate=learningRate)
    accuracy,diff=nn.compute(numIter=2000,alpha=alpha,plot=plot)
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
    alphas=np.array([0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1])
    Hs=np.array([5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20])
    learningRates=np.array([1e-6,1e-5,1e-4,1e-3,1e-2,1e-1,1])
    bestCombination=None
    best=0
    first=True
    radius=[1.5,1]
    noise=1
    bestData=None
    bestModel=None
    bestDiff=0
    for H in Hs:
        data=dl.generateDataSet(H,inputs, noise, radius)
        for alpha in alphas:
            for lr in learningRates:
                accuracy,diff,model=tune(data,H,batchSize,lr,alpha)
                #print(accuracy,best,bestCombination)
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
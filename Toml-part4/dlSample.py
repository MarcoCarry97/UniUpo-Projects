# -*- coding: utf-8 -*-
"""
Created on Sat Jun 11 01:01:14 2022

@author: Marco-PC
"""

import dlUtils as dl
import numpy as np

inputs=3
outputs=1

def perform(H,T,alpha=0.7,lr=1e-4):
    radius=[1,1.5]
    noise=0
    data=dl.generateDataSet(T,inputs, noise, radius)
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5],learningRate=lr)
    accuracy,_=nn.compute(alpha=alpha,plot=True)
    print("accuracy",H,T,accuracy)
    #r2,rmse,loss=nn.computeStohastic(nn.batchSize//4,plot=True)
    
    
def tune(data,H,T,learningRate,alpha,plot=False):
    radius=[1,1.5]
    noise=0
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5],learningRate=learningRate)
    accuracy,diff=nn.compute(numIter=2000,alpha=alpha,plot=plot)
    return accuracy,diff,nn

def sample():
    perform(20,640,alpha=0.5,lr=1e-4)

def underfitting(): #exercise 2
    print("UNDERFITTING")
    hiddens=1
    batchSize=640
    perform(hiddens,batchSize)
    hiddens=3
    perform(hiddens,batchSize)
    hiddens=5
    perform(hiddens,batchSize)
    hiddens=7
    perform(hiddens,batchSize)
    hiddens=9
    perform(hiddens,batchSize)

def overfitting(): #exercise 3
    print("OVERFITTING")
    hiddens=20
    batchSize=10
    perform(hiddens,batchSize)
    batchSize=20
    perform(hiddens,batchSize)
    batchSize=50
    perform(hiddens,batchSize)
    batchSize=100
    perform(hiddens,batchSize)
    batchSize=200
    perform(hiddens,batchSize)
    
def rightValue(): #exercise 4
    print("RIGHT VALUES")
    batchSize=640
    alphas=np.array([0.5,0.6,0.7])
    Hs=np.array([13,15,17,19,21,23,25])
    learningRates=np.array([1e-4])
    bestCombination=None
    best=0
    first=True
    radius=[1,1.5]
    noise=0
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
    res=tune(data,H,batchSize,lr,alpha,plot=True)
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

#sample()
underfitting()
#overfitting()
#rightValue()
#problems()
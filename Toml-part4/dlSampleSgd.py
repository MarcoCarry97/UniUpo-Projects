# -*- coding: utf-8 -*-
"""
Created on Sat Jun 11 01:01:14 2022

@author: Marco-PC
"""

import dlUtils as dl
import numpy as np

inputs=3
outputs=1

def perform(H,T,B):
    radius=[1.5,1]
    noise=1
    data=dl.generateDataSet(T,inputs, noise, radius)
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5])
    nn.computeStohastic(size=B,plot=True)
    #r2,rmse,loss=nn.computeStohastic(nn.batchSize//4,plot=True)
    
    
def tune(data,H,T,B,learningRate,alpha,plot=False):
    radius=[1.5,1]
    noise=1
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5],learningRate=learningRate)
    accuracy,diff=nn.computeStohastic(size=B,numIter=2000,alpha=alpha,plot=plot)
    return accuracy,diff,nn

def underfitting(): #exercise 2
    print("UNDERFITTING")
    hiddens=[1,2,5]
    batchSize=640
    B=batchSize//4
    for H in hiddens:
        perform(H,batchSize,B)
    

def overfitting(): #exercise 3
    print("OVERFITTING")
    hiddens=20
    batchSizes=[10,20,100,200]
    for T in batchSizes:
        perform(hiddens,T,T//4)
    
    
def rightValue(): #exercise 4
    print("RIGHT VALUES")
    batchSize=640
    alphas=np.array([0.2,0.3,0.4])
    Hs=np.array([5,6,7,8,9,10,11])
    learningRates=np.array([1e-6,1e-5,1e-4])
    dividers=[4,8,16,32]
    bestCombination=None
    best=0
    first=True
    radius=[1.5,1]
    noise=1
    bestData=None
    bestModel=None
    bestDiff=0
    d=8
    data=dl.generateDataSet(batchSize,inputs, noise, radius)
    for H in Hs:
        for alpha in alphas:
            for lr in learningRates:
                accuracy,diff,model=tune(data,H,batchSize,batchSize//d,lr,alpha)
                
                if(first):
                    best=accuracy
                    bestCombination=(H,lr,alpha)
                    bestData=data
                    bestModel=model
                    bestDiff=diff
                    first=False
               # if(best==accuracy and bestDiff>diff):
               #     best=accuracy
               #     bestCombination=(H,lr,alpha)
               #     bestModel=model
               #     bestDiff=diff
                elif(best<accuracy):
                    best=accuracy
                    bestCombination=(H,lr,alpha)
                    bestData=data
                    bestModel=model
                    bestDiff=diff
                print(accuracy,best,bestCombination)

                #print(H,lr,alpha,R2,rmse)
    print("bestCombination",bestCombination)
    H,lr,alpha=bestCombination
    res=bestModel.computeStohastic(batchSize//d,alpha=alpha,plot=True)
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
# -*- coding: utf-8 -*-
"""
Created on Sat Jun 11 01:01:14 2022

@author: Marco-PC
"""

import dlUtils as dl
import numpy as np
from threading import Thread, Lock

inputs=3
outputs=1

def perform(H,T):
    radius=[1.5,1]
    noise=1
    data=dl.generateDataSet(H,inputs, noise, radius)
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5])
    nn.compute()
    
def tune(data,H,T,learningRate,alpha):
    radius=[1.5,1]
    noise=1
    nn=dl.NeuralNetwork(data,inputs,H,outputs,T,[1,1.5],learningRate=learningRate)
    return nn.compute(numIter=2000,alpha=alpha)

def underfitting(): #exercise 2
    hiddens=1
    batchSize=640
    perform(hiddens,batchSize)
    hiddens=2
    perform(hiddens,batchSize)
    hiddens=5
    perform(hiddens,batchSize)

def overfitting(): #exercise 3
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
    batchSize=640
    alphas=np.array([0.1,0.25,0.5,0.75,0.9])
    Hs=np.array([10,12,14,16,18,20])
    learningRates=np.array([1e-6,1e-5,1e-4,1e-3,1e-2])
    bestCombination=None
    bestR2=0
    bestRmse=0
    first=True
    mutex=Lock()
    threads=[]
    radius=[1.5,1]
    noise=1
    for H in Hs:
        data=dl.generateDataSet(H,inputs, noise, radius)
        for alpha in alphas:
            for lr in learningRates:
                R2, rmse=tune(data,H,batchSize,lr,alpha)
                if(first):
                    bestR2=R2
                    bestRmse=rmse
                    bestCombination=(H,lr,alpha)
                    first=False
                if(bestR2<R2 and bestRmse>rmse):
                    bestR2=R2
                    bestRmse=rmse
                    bestCombination=(H,lr,alpha)
                print(H,lr,alpha,R2,rmse)
    print("bestCombination",bestCombination)
                
    
    
    
def problems(): #exercise 5
    hiddens=20
    batchSize=640
    perform(hiddens,batchSize)
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
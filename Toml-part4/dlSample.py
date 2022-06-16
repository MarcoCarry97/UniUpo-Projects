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
    nn=dl.NeuralNetwork(inputs,H,outputs,T,[1,1.5])
    nn.compute()
    
def tune(H,T,learningRate,alpha):
    nn=dl.NeuralNetwork(inputs,H,outputs,T,[1,1.5],learningRate=learningRate)
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
    alphas=np.array([0.35,0.7])
    Hs=np.array([10,20,50,100])
    learningRates=np.array([1e-6,1e-2])
    bestCombination=None
    bestR2=0
    i=0
    mutex=Lock()
    threads=[]
    for alpha in alphas:
        for H in Hs:
            for lr in learningRates:
                def fun():
                    R2=tune(H,batchSize,lr,alpha)
                    mutex.acquire()
                    if(bestR2<R2):
                        bestR2=R2
                        bestCombination=(H,lr,alpha)
                    mutex.release()
                t=Thread(target=fun)
                t.start()
                threads+=[t]
                #fun()
    print(len(threads))
    for t in threads:
     #   print(t)
       t.join()
      #  print("finished")
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
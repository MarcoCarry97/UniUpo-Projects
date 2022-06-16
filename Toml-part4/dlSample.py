# -*- coding: utf-8 -*-
"""
Created on Sat Jun 11 01:01:14 2022

@author: Marco-PC
"""

import dlUtils as dl

inputs=3
outputs=1

def perform(H,T):
    nn=dl.NeuralNetwork(inputs,H,outputs,T,[1,1.5])
    nn.compute()

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
    hiddens=20
    batchSize=640
    perform(hiddens,batchSize)
    
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
    
underfitting()
overfitting()
rightValue()
problems()
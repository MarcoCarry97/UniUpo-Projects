# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 11:22:53 2022

@author: Marco-PC
"""

from supply import Optimizer,Latency,Time
from plotter import Plotter
from numpy import log

def preparation():     #prepare the optimizer, it has a method to compute the coefficient a and b
    lat=Latency(5000,4,9,9,5)
    time=Time(0.95,15*0.62,2.6,500,100)
    payload=32
    radiorate=31.25
    numRings=8
    numNeighbors=5
    maxEnergy=1
    sampleFreq=1/(60*30*1000)
    opt=Optimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,sampleFreq)
    return opt

def plot(e,l,xlab,ylab,opt):
    p=Plotter(e,l)
    p.labels(xlab,ylab)
    p.fontSize(10)
    p.show(opt.time.wmin,opt.time.wmax,1)
    
opt=preparation()

a,b=opt.getCoefficients()    
    
energy=lambda x:a[0]/x+a[1]*x+a[2] #functions to calc energy and latency
latency=lambda x:b[0]*x+b[1]

Ew=energy(opt.time.wmin) #worst cases
Lw=latency(opt.time.wmax)

balance=lambda x:log(Ew-energy(x))+log(Lw-latency(x)) #function to maximize

plot(energy,latency,"Energy(Tw)","Latency(Tw)",opt)
plot(lambda x:x,energy,"Tw","Energy(Tw)",opt)
plot(lambda x:x,latency,"Tw","Latency(Tw)",opt)
plot(lambda x:x,balance,"Tw","Balance(Tw)",opt)
print("ok")
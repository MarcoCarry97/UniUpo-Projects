# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 11:22:53 2022

@author: Marco-PC
"""

from supply import Optimizer,Latency,Time
from plotter import Plotter
from numpy import log

def preparation(Fs):     #prepare the optimizer, it has a method to compute the coefficient a and b
    lat=Latency(5000,4,9,9,5)
    time=Time(0.95,15*0.62,2.6,500,100)
    payload=32
    radiorate=31.25
    numRings=8
    numNeighbors=5
    maxEnergy=1
    sampleFreq=Fs#1/(60*30*1000)
    opt=Optimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,sampleFreq)
    return opt

def plot(e,l,xlab,ylab,title,opt,delete=False):
    p=Plotter(e,l)
    p.labels(xlab,ylab)
    p.fontSize(10)
    p.title=title
    p.show(opt.time.wmin,opt.time.wmax,1,delete)
    
sampleFreqs=[1,2,5,10]
    
delete=True
for i in range (0,len(sampleFreqs)):
    Fs=sampleFreqs[i]/(30*60*1000)
    opt=preparation(Fs)
    a,b=opt.getCoefficients()         
    energy=lambda x:a[0]/x+a[1]*x+a[2] #functions to calc energy and latency
    latency=lambda x:b[0]*x+b[1]
    Ew=energy(opt.time.wmin) #worst cases
    Lw=latency(opt.time.wmax)
    measureString="(Fs - "+str(Fs)+" Hz)"
    balance=lambda x:log(Ew-energy(x))+log(Lw-latency(x)) #function to maximize
    plot(energy,latency,"Energy(Tw)","Latency(Tw)","Energy-Latency "+measureString,opt,delete)
    delete=False
    plot(lambda x:x,energy,"Tw","Energy(Tw)","Energy "+measureString,opt)
    if( i==0):
        plot(lambda x:x,latency,"Tw","Latency(Tw)","Latency "+measureString,opt)
    plot(lambda x:x,balance,"Tw","Balance(Tw)","Balance "+measureString,opt)
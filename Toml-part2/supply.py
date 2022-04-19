
import gpkit as gp
import numpy as np
import cvxpy as cp
from gpUtils import GeoIneq,GeoProblem
from scipyUtils import Inequality
import scipyUtils as sp
from cvxUtils import CvxIneq, CvxProblem

#CLASS CONTAINING ALL THE LATENCIES

class Latency:
    def __init__(self,maximum,pbl,hdr,ack,ps):
        self.max=maximum
        self.pbl=pbl
        self.hdr=hdr+pbl
        self.ack=ack+pbl
        self.ps=ps+pbl

#CLASS CONTAINING ALL THE TIMES

class Time:
    def __init__(self,al,cw,cs,wmax,wmin):
        self.al=al
        self.cw=cw
        self.cs=cs
        self.wmax=wmax
        self.wmin=wmin
        self.hdr=None
        self.ack=None
        self.ps=None
        self.data=None

#ABSTRACT CLASS FOR OPTIMIZATION

class Optimizer:
    def __init__(self,payload,radiorate,numRings,numNeighbors,maxEnergy,latencies,times,samplingFreq):
        self.payload=payload
        self.radiorate=radiorate
        self.numRings=numRings
        self.numNeighbors=numNeighbors
        self.maxEnergy=maxEnergy
        self.latency=latencies
        self.time=times
        self.samplingFreq=samplingFreq
        times.hdr=latencies.hdr/radiorate
        times.ack=latencies.ack/radiorate
        times.ps=latencies.ps/radiorate
        times.data=times.hdr+payload/radiorate+times.ack

    def numNodes(self):
        return self.numNeighbors*((self.numRings)**2)

    def solve(self):
        fzero=self.makeFzero()
        cons=self.makeConstraints()
        problem=GeoProblem(fzero)
        for c in cons:
            problem.addIneq(c)
        Tw=gp.Variable("Tw")
        #problem.addVar(Tw)
        res=problem.solve(Tw)
        return res

    def makeFzero(self): pass

    def makeConstraints(self): pass

    def outFrequency(self,Fs,d):
        D=self.numRings
        if(d==D):
            return Fs
        else:
            return ((D**2-d**2+2*d-1)/(2*d-1))*Fs

    def inFrequency(self,Fs,d):
        D=self.numRings
        C=self.numNeighbors
        if(d==0):
            return (C*D**2)*Fs
        else:
            return ((D**2-d**2)/(2*d-1))*Fs

    def numBiasNodes(self,d):
        return self.numNeighbors*d

    def numInputs(self,d):
        if(d==self.numRings):
            return 0
        elif(d==0):
            return self.numNeighbors
        else:
            return ((2*d+1)/(2*d-1))

    def calcAlpha(self,d):
        Tcs=self.time.cs
        Tal=self.time.al
        Tps=self.time.ps
        Tack=self.time.ack
        Tdata=self.time.data
        B=self.numBiasNodes(d)
        Fout=self.outFrequency(self.samplingFreq,d)
        Fin=self.inFrequency(self.samplingFreq,d)
        Fb=B*Fout
        a1=Tcs+Tal+(3/2)*Tps*((Tps+Tal)/2+Tack+Tdata)*Fb
        a3=((Tps+Tal)/2+Tcs+Tal+Tack+Tdata)*Fout +((3/2)*Tps+Tack+Tdata)*Fin+(3/4)*Tps*Fb
        a2=Fout/2
        return [a1,a2,a3]

    def calcBeta(self,d):
        Tcw=self.time.cw
        Tdata=self.time.data
        b1=d/2
        b2=(Tcw/2+Tdata)*d
        return [b1,b2]

    def getCoefficients(self):
        a=self.calcAlpha(1)
        b=self.calcBeta(self.numRings)
        return a,b

    def bottleneck(self):
        I=self.numInputs(0)
        return GeoIneq(lambda Tw: I*self.calcEnergy(Tw,1),lambda x:1/4)

    def calcEnergy(self,Tw,d):
        Tack=self.time.ack
        Tdata=self.time.data
        Tcs=self.time.cs
        Tal=self.time.al
        numInput=self.numInputs(d-1)
        Fout=self.outFrequency(self.samplingFreq,d)
        Ttx=Tack+Tdata+Tw/2
        return (Tcs+Tal+Ttx)*Fout

#PROBLEM 1: OPTIMIZING ENERGY

class EnergyOptimizer(Optimizer):
    def __init__(self, payload, radiorate, numRings, numNeighbors, maxEnergy, latencies, times, samplingFreq):
        super().__init__(payload, radiorate, numRings, numNeighbors, maxEnergy, latencies, times, samplingFreq)

    def makeFzero(self):
        a,b=self.getCoefficients()
        return lambda Tw:(a[0]/Tw)+a[1]*Tw+a[2]

    def makeConstraints(self):
        bot=self.bottleneck()
        a,b=self.getCoefficients()
        ineq1=GeoIneq(lambda Tw:self.time.wmin,lambda Tw:Tw)
        ineq0=GeoIneq(lambda Tw:Tw,lambda Tw: self.time.wmax)
        ineq2=GeoIneq(lambda Tw:b[0]*Tw+b[1],lambda Tw:self.latency.max)
        return [ineq1,ineq2,ineq0,bot]

#PROBLEM 2: OPTIMIZING LATENCY

class LatencyOptimizer(Optimizer):
    def __init__(self, payload, radiorate, numRings, numNeighbors, maxEnergy, latencies, times, samplingFreq):
        super().__init__(payload, radiorate, numRings, numNeighbors, maxEnergy, latencies, times, samplingFreq)

    def makeFzero(self):
        a,b=self.getCoefficients()
        return lambda Tw:b[0]*Tw+b[1]

    def makeConstraints(self):
        a,b=self.getCoefficients()
        bot=self.bottleneck()
        ineq1=GeoIneq(lambda Tw:self.time.wmin,lambda Tw:Tw)
        ineq2=GeoIneq(lambda Tw:a[0]/Tw+a[1]*Tw+a[2],lambda Tw:self.maxEnergy)
        ineq3=GeoIneq(lambda Tw:Tw,lambda Tw:self.time.wmax)
        return [ineq1,ineq2,ineq3,bot]


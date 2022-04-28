from gpkit import Variable
from supply import EnergyOptimizer,Latency,Time
from plotter import Plotter
import numpy as np

sampleFreqs=[1,2,5,10]
timeWorks=[]
for i in range(0,len(sampleFreqs)):
    timeWorks+=[[]]
latList=np.arange(500,5000,50)
twmin=100
twmax=500

for l in latList: #trying with different limits of latency
    lat=Latency(l,4,9,9,5)

    time=Time(0.95,15*0.62,2.6,twmax,twmin)

    payload=32
    radiorate=31.25
    numRings=8
    numNeighbors=5
    maxEnergy=1

    for i in range(0, len(sampleFreqs)): #trying with different sampling frequencies
        Fs=sampleFreqs[i]/(30*60*1000)
        opt=EnergyOptimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,Fs)
        Tw=Variable("Tw (ms)")
        #print(opt.outFrequency(1/(60*100*30),1))
        a=opt.calcAlpha(1)
        #print(opt.calcAlpha(1))
        #print(opt.calcBeta(8))
        res=opt.solve()
        print("Solution for the first problem: (Fs: "+str(Fs)+" Hz)")
        res.printRes()
        print("\n\n\n\n")
        timeWorks[i]+=[res.xstar["Tw"]]
        
for i in range(0,len(timeWorks)): #making a plot
    p=Plotter(lambda x:latList,lambda x:timeWorks[i])
    Fs=sampleFreqs[i]/(60*30*1000)
    title="Behavior of Latency in Tw (Fs - "+str(Fs)+" Hz)"
    p.title=title
    p.labels("Max Latency","Tw (ms)")
    p.show(0, len(latList),1)
#res.printRes()


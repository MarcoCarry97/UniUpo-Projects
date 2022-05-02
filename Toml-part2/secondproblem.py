from gpkit import Variable
from supply import LatencyOptimizer,Latency,Time
from plotter import Plotter
import numpy as np

sampleFreqs=[1,2,5,10]
timeWorks=[]
for i in range(0,len(sampleFreqs)):
    timeWorks+=[[]]
enerList=np.arange(0.5,5,0.5)
twmin=100
twmax=500

for e in enerList: #trying with different budgets of energy
    lat=Latency(5000,4,9,9,5)

    time=Time(0.95,15*0.62,2.6,twmax,twmin)

    payload=32
    radiorate=31.25
    numRings=8
    numNeighbors=5
    maxEnergy=e

    for i in range(0, len(sampleFreqs)): #trying with different sampling frequencies
        Fs=sampleFreqs[i]/(30*60*1000)
        opt=LatencyOptimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,Fs)
        Tw=Variable("Tw (ms)")
        #print(opt.outFrequency(1/(60*100*30),1))
        a=opt.calcAlpha(1)
        #print(opt.calcAlpha(1))
        #print(opt.calcBeta(8))
        res=opt.solve()
        print("Solution for the second problem: (Fs: "+str(Fs)+" Hz)")
        res.printRes()
        print("\n\n\n\n")
        
        timeWorks[i]+=[round(res.xstar["Tw"],1)]

for i in range(0,len(timeWorks)): #making a plot
    p=Plotter(lambda x:enerList,lambda x:timeWorks[i])
    Fs=sampleFreqs[i]/(60*30*1000)
    title="Behavior of Energy budget in Tw (Fs - "+str(Fs)+"Hz)"
    p.title=title
    p.labels("Energy budget","Tw (ms)")
    p.show(0, len(enerList),1)
    
    #res.printRes()
from gpkit import Variable
from supply import LatencyOptimizer,Latency,Time

lat=Latency(5000,4,9,9,5)

time=Time(0.95,15*0.62,2.6,500,100)

payload=32
radiorate=31.25
numRings=8
numNeighbors=5
maxEnergy=1
sampleFreqs=[1,2,5,10]

for i in range(0, len(sampleFreqs)):
    Fs=sampleFreqs[i]/(30*60*1000)
    opt=LatencyOptimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,Fs)
    Tw=Variable("Tw")
    #print(opt.outFrequency(1/(60*100*30),1))
    a=opt.calcAlpha(1)
    #print(opt.calcAlpha(1))
    #print(opt.calcBeta(8))
    res=opt.solve()
    print("Solution for the second problem: (Fs: "+str(Fs)+" Hz)")
    res.printRes()
    print("\n\n\n\n")
#res.printRes()
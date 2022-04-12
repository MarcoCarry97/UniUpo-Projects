from gpkit import Variable
from supply import EnergyOptimizer,Latency,Time

lat=Latency(5000,4,9,9,5)

time=Time(0.95,15*0.62,2.6,500,100)

payload=32
radiorate=31.25
numRings=8
numNeighbors=5
maxEnergy=1
sampleFreq=1/(60*30*1000)

opt=EnergyOptimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,sampleFreq)

Tw=Variable("Tw")
print(type(Tw))
print(opt.outFrequency(1/(60*100*30),1))
a=opt.calcAlpha(1)
print(opt.calcAlpha(1))
print(opt.calcBeta(8))
res=opt.solve()
print("Solution for the first problem:")
res.printRes()
#res.printRes()


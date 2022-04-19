import gpkit as gp
import cvxpy as cp
from supply import Optimizer,Latency,Time
import numpy as np
from cvxUtils import CvxResult

lat=Latency(5000,4,9,9,5)

time=Time(0.95,15*0.62,2.6,500,100)

payload=32
radiorate=31.25
numRings=8
numNeighbors=5
maxEnergy=1
sampleFreq=1/(60*30*1000)

def bottleneck(opt,Tw):
    I=opt.numInputs(0)
    return I*opt.calcEnergy(Tw,1)<=1/4

opt=Optimizer(payload,radiorate,numRings,numNeighbors,maxEnergy,lat,time,sampleFreq)

a,b=opt.getCoefficients()

energy=lambda Tw:a[0]*Tw**-1+a[1]*Tw+a[2]
latency=lambda Tw:b[0]*Tw+b[1]

Ew=energy(time.wmin)
Lw=latency(time.wmax)

Tw=cp.Variable()
E=cp.Variable()
L=cp.Variable()

fzero=cp.log(Ew-E)+cp.log(Lw-L)

ineq1=Ew>=energy(Tw)
ineq2=E>=energy(Tw)
ineq3=Lw>=latency(Tw)
ineq4=L>=latency(Tw)
ineq5=Tw>=time.wmin
ineq6=time.wmax>=Tw
ineq7=bottleneck(opt,Tw)

cons=[ineq1,ineq2,ineq3,ineq4,ineq4,ineq5,ineq6,ineq7]

def solve(fzero,cons):
    prob=cp.Problem(cp.Maximize(fzero),cons)
    prob.solve()
    res=CvxResult()
    #if isinstance(x,list):
    #    l=[]
    #    for sl in x:
    #        for v in sl:
    #            l+=[v.value]
    #    res.xstar=l
    #else:
    #    res.xstar=x.value
    res.xstar=[Tw.value,E.value,L.value]
    res.pstar=prob.value
    lambdas=[]
    for con in prob.constraints:
        lambdas+=[con.dual_value]
    res.lambdas=lambdas
    res.numIt=prob.solver_stats.num_iters
    #res.dstar=prob.  
    return res

res=solve(fzero,cons)

res.printRes()
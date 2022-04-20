from cvxUtils import CvxProblem,CvxIneq,CvxResult
from supply import Optimizer,Latency,Time
import cvxpy as cp

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

def bottleneck(opt): #bottleneck constraint
    I=opt.numInputs(0)
    return CvxIneq(lambda x:I*opt.calcEnergy(x[0],1)-1/4)

def vars(): #variables
    Tw=cp.Variable()
    E=cp.Variable()
    L=cp.Variable()
    return [Tw,E,L]

opt=preparation()

a,b=opt.getCoefficients()

energy=lambda x:a[0]*x**-1+a[1]*x+a[2] #functions to calc energy and latency
latency=lambda x:b[0]*x+b[1]

Ew=energy(opt.time.wmin) #worst cases
Lw=latency(opt.time.wmax)

fzero=lambda x:cp.log(Ew-x[1])+cp.log(Lw-x[2]) #function to maximize


#function to optimize
ineq0=bottleneck(opt)
ineq1=CvxIneq(lambda x:-Ew+energy(x[0]))
ineq2=CvxIneq(lambda x:-x[1]+energy(x[0]))
ineq3=CvxIneq(lambda x: -Lw+energy(x[0]))
ineq4=CvxIneq(lambda x: -x[2]+latency(x[0]))
ineq5=CvxIneq(lambda x: -x[0]+opt.time.wmin)
ineq6=CvxIneq(lambda x: -opt.time.wmax+x[0])

cons=[ineq0,ineq1,ineq2,ineq3,ineq4,ineq5,ineq6]

#problem resolution
problem=CvxProblem(fzero,1)
for ineq in cons:
    problem.setIneq(ineq)
x=vars()
res=problem.solve(x)
res.printRes()

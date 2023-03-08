from asyncio.windows_events import INFINITE
from scipyUtils import Inequality
from scipyUtils import Equality
from scipyUtils import Problem
import numpy as np


starts=list()
starts+=[(0,0),(10,20),(-10,1),(-30,-30)]

def e(x):
    #if(x[0]<=50):
    return np.exp(x[0])
    #else:
     #   print("Overlimit")
    #return INFINITE;

poly=lambda x:4*(x[0]**2)+2*(x[1]**2)+x[0]*x[1]+2*x[1]+1

fzero=lambda x: e(x)*poly(x)

print("The function fzero is convex because e^x is convex and the quadratic function too")

ineq1=Inequality(lambda x:-(x[0]*x[1]-x[0]-x[1]+1.5))
ineq2=Inequality(lambda x:-(-x[0]*x[1]-10))

p=Problem(fzero,-1)
p.addIneq(ineq1)
p.addIneq(ineq2)

results=[]
for x0 in starts:
    results+=[p.solve(x0,"SLSQP")]

print("NORMAL")
for r in results:
    r.printRes()
      
def jacobian(x):
    dx0=e(x)*(4*x[0]**2+2*x[1]**2+4*x[0]*x[1]+2*x[1]+1+8*x[0]+4*x[1])
    dx1=e(x)*(4*x[1]+4*x[0]+2)
    return  [dx0,dx1]

def hessian(x):
    dxx=e(x)*(4*x[0]**2+2*x[1]**2+4*x[0]*x[1]+2*x[1]+1+8*x[0]+4*x[1]+8*x[0]+4*x[1]+9)
    dxy=e(x)*(4*x[1]+4*x[0]+2+4)
    dyx=e(x)*(4*x[1]+4*x[0]+2+4)
    dyy=e(x)*4
    return [[dxx,dyx],[dxy,dyy]]

results=[]

print("JACOB")
for x0 in starts:
    results+=[p.solveWithJacob(x0,"SLSQP",jacobian)]


for r in results:
    r.printRes()


results=[]

for x0 in starts:
    results+=[p.solveWithJacobHess(x0,jacobian,hessian)]

print("JACOB HESS")
for r in results:
    r.printRes()


#fplot=Plot([10,10,10])
# fplot.show([p.fzero]+p.ineqs+p.eqs)

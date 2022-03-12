from classes import Inequality
from classes import Equality
from classes import Problem
import math

starts=list()
starts+=[(0,0),(10,20),(-10,1),(-30,-30)]

def e(x):
    if(x[0]<=50):
        return math.exp(x[0])
    else: print("Overlimit")
    return -1;

poly=lambda x:4*(x[0]**2)+2*(x[1]**2)+x[0]*x[1]+2*x[1]+1

fzero=lambda x: e(x)*poly(x)

print("The function fzero is convex because e^x is convex and the quadratic function too")

ineq1=Inequality(lambda x:-x[0]*x[1]+x[0]+x[1]-1.5)
ineq2=Inequality(lambda x:+x[0]*x[1]+10)

p=Problem(fzero,-1)
p.addIneq(ineq1)
p.addIneq(ineq2)

results=[]
for x0 in starts:
    print("Use "+str(x0)+":\n\n\n\n\n\n")
    results+=[p.solve(x0,"SLSQP")]

for i in range(0,len(results)):
    print("results for "+ str(starts[i])+" : ")
    print("     pstar:"+ str(results[i].fun))
    print("     xstar:"+str(results[i].x))
      

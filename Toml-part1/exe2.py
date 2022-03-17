from scipyUtils import Inequality
from scipyUtils import Equality
from scipyUtils import Problem
from scipyUtils import Result
import math

fzero=lambda x: (x[0]**2)+(x[1]**2)

problem=Problem(fzero,-1)

problem.addIneq(Inequality(lambda x:x[0]-0.5))
problem.addIneq(Inequality(lambda x:x[0]+x[1]-1))
problem.addIneq(Inequality(lambda x:(x[0]**2)+(x[1]**2)-1))
problem.addIneq(Inequality(lambda x:9*(x[0]**2)+(x[1]**2)-9))
problem.addIneq(Inequality(lambda x:(x[0]**2)-x[1]))
problem.addIneq(Inequality(lambda x:(x[1]**2)-x[0]))

feas=(1,0)
notfeas1=(7,-2)
notfeas2=(0,0)
points=[feas,notfeas1,notfeas2]

results=[]
for p in points:
    results+=[Result(p,problem.solve(p,"SLSQP"))]

for r in results:
    print("point "+str(r.point))
    print("     pstar:"+ str(r.value.fun))
    print("     xstar:"+str(r.value.x))


def jacobian(x):
    return [2*x[0],2*x[1]]

def hessian(x):
    return [[2,0],[0,2]]


results=[]

for p in points:
    results+=[Result(p,problem.solveWithJacob(p,"SLSQP",jacobian))]

for r in results:
    print("point "+str(r.point))
    print("     pstar:"+ str(r.value.fun))
    print("     xstar:"+str(r.value.x))

results=[]

for p in points:
    results+=[Result(p,problem.solveWithJacobHess(p,jacobian,hessian))]

for r in results:
    print("point "+str(r.point))
    print("     pstar:"+ str(r.value.fun))
    print("     xstar:"+str(r.value.x))



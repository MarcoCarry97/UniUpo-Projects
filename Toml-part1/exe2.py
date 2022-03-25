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

feases=[(1,1),(4,3),(2,4)]
notfeases=[(-1,-1),(0,0),(-3,2)]
points=feases+notfeases

results=[]
for p in points:
    results+=[problem.solve(p,"SLSQP")]

for r in results:
    r.printRes()


def jacobian(x):
    return [2*x[0],2*x[1]]

def hessian(x):
    return [[2,0],[0,2]]


results=[]

for p in points:
    #print(str()+" feasible? "+str(problem.isFeasible(p)))
    results+=[problem.solveWithJacob(p,"SLSQP",jacobian)]

for r in results:
    r.printRes()

results=[]

for p in points:
    results+=[problem.solveWithJacobHess(p,jacobian,hessian)]

for r in results:
    r.printRes()



from scipyUtils import Inequality,Problem,Result
import math
import numpy as np

def sum(x):
    acc=0
    for xi in x:
        acc+=math.log(xi)
    return acc

fzero=lambda x: sum(x)

C=[1,2,1,2,1]

ineq0=Inequality(lambda x:-x[0]-x[2]+C[0])
ineq1=Inequality(lambda x:-x[0]-x[1]+C[1])
ineq2=Inequality(lambda x:-x[2]+C[4])
ineq3=Inequality(lambda x:C[3])
ineq4=Inequality(lambda x:C[4])
ineqx1=Inequality(lambda x:x[0])
ineqx2=Inequality(lambda x:x[1])
ineqx3=Inequality(lambda x:x[2])

ineqs=[ineq0,ineq1,ineq2,ineq3,ineq4,ineqx1,ineqx2,ineqx3]

feases=[(0.5,0.5,0.5),(0,0,0),(1,0,0),(0,0,2),(0.5,1,0.5)]
notfeases=[(1,-1,-10),(5,6,7),(10,-10,0),(5,5,5),(4,2,2)]

problem=Problem(fzero,1)

for ineq in ineqs:
    problem.addIneq(ineq)

results=[]

for p in feases+notfeases:
    results+=[problem.solve(p,"SLSQP")]

for r in results:
    print("Point: "+str(r.point))
    print("     x*: "+str(r.value.x))
    print("     p*: "+str(r.value.fun))

def jacobian(x):
    dx0=x[0]**-1
    dx1=x[1]**-1
    dx2=x[2]**-1
    return [dx0,dx1,dx2]

def hessian(x):
    A=[[0,0,0],[0,0,0],[0,0,0]]
    A[0][0]=x[0]**-2
    A[1][1]=x[1]**-2
    A[2][2]=x[2]**-2
    return A

results=[]

for p in feases+notfeases:
    results+=[problem.solveWithJacob(p,"SLSQP",jacobian)]

for r in results:
    print("Point: "+str(r.point))
    print("     x*: "+str(r.value.x))
    print("     p*: "+str(r.value.fun))

results=[]

for p in feases+notfeases:
    results+=[problem.solveWithJacobHess(p,jacobian,hessian)]

for r in results:
    print("Point: "+str(r.point))
    print("     x*: "+str(r.value.x))
    print("     p*: "+str(r.value.fun))

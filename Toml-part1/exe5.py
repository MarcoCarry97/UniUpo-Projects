from classes import Inequality,Problem,Result

fzero=lambda x: x[0]**2 + x[1]**2

ineq1=Inequality(lambda x:-(x[0]-1)**2 - (x[1]-1)**2)
ineq2=Inequality(lambda x:-(x[0]-1)**2 - (x[1]+1)**2)

problem=Problem(fzero,-1)

problem.addIneq(ineq1)
problem.addIneq(ineq2)

feases=[(1,0),(0,-1)]

notfeases=[(0,0),(1,1),(-1,-1),(1,-1),(-1,1),(10,10)]

results=[]
for p in feases+notfeases:
    results+=[problem.solve(p,"SLSQP")]

for r in results:
    print("Point: "+str(r.point))
    print("     Opt. value: "+str(r.value.fun))
    print("     Opt. point: "+str(r.value.x))

def jacobian(x):
    return [2*x[0],2*x[1]]

def hessian(x):
    return [[2,0],[0,2]]

results=[]
for p in feases+notfeases:
    results+=[problem.solveWithJacob(p,"SLSQP",jacobian)]

for r in results:
    print("Point: "+str(r.point))
    print("     Opt. value: "+str(r.value.fun))
    print("     Opt. point: "+str(r.value.x))

results=[]
for p in feases+notfeases:
    results+=[problem.solveWithJacobHess(p,jacobian,hessian)]

for r in results:
    print("Point: "+str(r.point))
    print("     Opt. value: "+str(r.value.fun))
    print("     Opt. point: "+str(r.value.x))
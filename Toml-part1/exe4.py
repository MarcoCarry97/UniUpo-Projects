from classes import Inequality,Problem,Result

fzero=lambda x: x[0]**2 +1

ineq=Inequality(lambda x:-x**2+6*x-8)

problem=Problem(fzero,-1)

problem.addIneq(ineq)

feases=[2,3,4]

notfeases=[0,1,5,6,7]

results=[]
for p in feases+notfeases:
    results+=[problem.solve(p,"SLSQP")]

for r in results:
    print("Point: "+str(r.point))
    print("     Opt. value: "+str(r.value.fun))
    print("     Opt. point: "+str(r.value.x))

def jacobian(x):
    return 2*x

def hessian(x):
    return 2

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
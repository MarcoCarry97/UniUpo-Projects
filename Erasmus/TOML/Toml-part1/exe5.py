from scipyUtils import Inequality,Problem,Result

fzero=lambda x: x[0]**2 + x[1]**2

ineq1=Inequality(lambda x:-(x[0]-1)**2 - (x[1]-1)**2)
ineq2=Inequality(lambda x:-(x[0]-1)**2 - (x[1]+1)**2)

problem=Problem(fzero,-1)

problem.addIneq(ineq1)
problem.addIneq(ineq2)

points=[(2.33,0.11),(1.25,0.18),(-0.12,2.18),(0.68,-1.49),(-1.28,0.66),(0.69,-0.06)]

for p in points:
    print(str(p) +" feasible? "+str(problem.isFeasible(p)))

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
    #print(str(p)+" feasible? "+str(problem.isFeasible(p)))
    results+=[problem.solveWithJacob(p,"SLSQP",jacobian)]

for r in results:
    r.printRes()

results=[]
for p in points:
    #print(str(p)+" feasible? "+str(problem.isFeasible(p)))
    results+=[problem.solveWithJacobHess(p,jacobian,hessian)]

for r in results:
    r.printRes()
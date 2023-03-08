from scipyUtils import Equality,Inequality,Problem,Result

fzero=lambda x:x[0]**2 + x[1]**2

ineq1=Inequality(lambda x: -x[0]**2 -x[0]*x[1]-x[1]**2+3)
ineq2=Inequality(lambda x: 3*x[0]+2*x[1]-3)

p=Problem(fzero,-1)
p.addIneq(ineq1)
p.addIneq(ineq2)

feases=[(1,1),(1,0),(1,0.5)]
notfeases=[(5,-5),(7,-7),(10,-10)]

results=[]
for x in feases+notfeases:
    #print(str(x)+" feasible? "+str(p.isFeasible(x)))
    results+=[p.solve(x,"SLSQP")]

for r in results:
    r.printRes()

def jacobian(x):
    return [2*x[0],2*x[1]]

def hessian(x):
    return [[2,0],[0,2]]

results=[]

for x in feases+notfeases:
    #print(str(x)+" feasible? "+str(p.isFeasible(x)))
    results+=[p.solveWithJacob(x,"SLSQP",jacobian)]

for r in results:
    r.printRes()

results=[]

for x in feases+notfeases:
    results+=[p.solveWithJacobHess(x,jacobian,hessian)]

for r in results:
    r.printRes()

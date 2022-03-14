from classes import Equality,Inequality,Problem,Result

fzero=lambda x:x[0]**2 + x[1]**2

ineq1=Inequality(lambda x: -x[0]**2 -x[0]*x[1]-x[1]**2+3)
ineq2=Inequality(lambda x: 3*x[0]+2*x[1]-3)

p=Problem(fzero,-1)
p.addIneq(ineq1)
p.addIneq(ineq2)

feases=[(1,1),(1,0)]
notfeases=[(15,20),(30,-640),(1000,1004)]

results=[]
for x in feases+notfeases:
    results+=[Result(x,p.solve(x,"SLSQP"))]

for r in results:
    print("point "+str(r.point))
    print("     pstar:"+ str(r.value.fun))
    print("     xstar:"+str(r.value.x))

def jacobian(x):
    return [2*x[0],2*x[1]]

def hessian(x):
    return [[2,0],[0,2]]

results=[]

for x in feases+notfeases:
    results+=[Result(x,p.solveWithJacob(x,"SLSQP",jacobian))]

for r in results:
    print("point "+str(r.point))
    print("     pstar:"+ str(r.value.fun))
    print("     xstar:"+str(r.value.x))

results=[]

for x in feases+notfeases:
    results+=[Result(x,p.solveWithJacobHess(x,jacobian,hessian))]

for r in results:
    print("point "+str(r.point))
    print("     pstar:"+ str(r.value.fun))
    print("     xstar:"+str(r.value.x))

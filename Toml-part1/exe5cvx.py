from cvxUtils import CvxProblem,CvxIneq,CvxEq,CvxResult
import cvxpy as cp
import numpy as np


x0=cp.Variable(2)

fzero=lambda x:x[0]**2 + x[1]**2

ineq1=CvxIneq(lambda x:(x[0]-1)**2 + (x[1]-1)**2-1)
ineq2=CvxIneq(lambda x:(x[0]-1)**2 + (x[1]+1)**2-1)


ineqs=[ineq1,ineq2]
eqs=[]

p=CvxProblem(fzero,-1)

for ineq in ineqs:
    p.setIneq(ineq)

for eq in eqs:
    p.setEq(eq)

res=p.solve(x0)

print("Result:\n")
res.printRes()
#print("    d*="+str(res.dstar))
from cvxUtils import CvxProblem,CvxIneq,CvxEq,CvxResult
import cvxpy as cp
import numpy as np


x0=cp.Variable()


fzero=lambda x:x**2 + 1

ineq1=CvxIneq(lambda x:x**2 -6*x + 8)


ineqs=[ineq1]
eqs=[]

p=CvxProblem(fzero,-1)

for ineq in ineqs:
    p.setIneq(ineq)

for eq in eqs:
    p.setEq(eq)

res=p.solve(x0)

print("Result:\n")
print("    x*="+str(res.xstar))
print("    p*="+str(res.pstar))
print("    l*="+str(res.lambdas))
#print("    d*="+str(res.dstar))
from cvxUtils import CvxProblem,CvxIneq,CvxEq,CvxResult
import cvxpy as cp
import numpy as np

n=2

x0=cp.Variable(n)

P1=np.array(np.mat("1 0.5;0.5 1"))

P0=np.array(np.mat("1 0;0 1"))
fzero=lambda x0:cp.quad_form(x0,P0)

ineq1=CvxIneq(lambda x:cp.quad_form(x,P1)-3)
ineq2=CvxIneq(lambda x:-3*x[0]-2*x[1]+3)

ineqs=[ineq1,ineq2]
eqs=[]

p=CvxProblem(fzero,-1)

for ineq in ineqs:
    p.setIneq(ineq)

for eq in eqs:
    p.setEq(eq)

res=p.solve(x0)

res.printRes()



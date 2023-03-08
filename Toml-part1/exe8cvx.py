from tkinter import Variable
from cvxUtils import CvxIneq,CvxProblem,CvxResult
import cvxpy as cp

n=3

x0=cp.Variable(n,name="x")

r0=cp.Variable(n,name="r")

p0=[x0,r0]

ineq1=CvxIneq(lambda p:p[0][0]+p[0][1]-p[1][0])
ineq2=CvxIneq(lambda p:p[0][0]-p[1][1])
ineq3=CvxIneq(lambda p:p[0][2]-p[1][2])
ineqr=CvxIneq(lambda p:p[1][0]+p[1][1]+p[1][2]-1)

ineqs=[ineq1,ineq2,ineq3,ineqr]

fzero=lambda p:cp.log(p[0][0])+cp.log(p[0][1])+cp.log(p[0][2])

problem=CvxProblem(fzero,1)

for ineq in ineqs:
    problem.setIneq(ineq)

res=problem.solve(p0)

print("Result:\n")
res.printRes()

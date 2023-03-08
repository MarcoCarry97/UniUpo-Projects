from tkinter import Variable
from cvxUtils import CvxIneq,CvxProblem,CvxResult
import cvxpy as cp

n=3

x0=cp.Variable(n)

C=[1,2,1,2,1]

ineq1=CvxIneq(lambda x:x[0]+x[2]-C[0])
ineq2=CvxIneq(lambda x:x[0]+x[1]-C[1])
ineq3=CvxIneq(lambda x:x[2]-C[4])
ineqx1=CvxIneq(lambda x:-x[0])
ineqx2=CvxIneq(lambda x: -x[1])
ineqx3=CvxIneq(lambda x: -x[2])

ineqs=[ineq1,ineq2,ineq3,ineqx1,ineqx2,ineqx3]

fzero=lambda x:cp.log(x[0])+cp.log(x[1])+cp.log(x[2])

problem=CvxProblem(fzero,1)

for ineq in ineqs:
    problem.setIneq(ineq)

res=problem.solve(x0)

print("Result:\n")
res.printRes()

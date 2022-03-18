import cvxpy as cp
import numpy as np

class CvxIneq:
    def __init__(self,fun):
        self.fun=fun
        
    def toLambda(self):
        return lambda x:self.fun(x)<=0

    def applyBool(self,x):
        return self.toLambda()(x)

class CvxEq:
    def __init__(self,fun):
        self.fun=fun

    def toLambda(self):
        return lambda x:self.fun(x)==0

    def applyBool(self,x):
        return self.toLambda()(x)

class CvxResult:
    def __init(self):
        self.xstar=None
        self.pstar=None
        self.lambdas=None
        self.dstar=None

class CvxProblem:
    def __init__(self,fzero,ptype):
        self.fzero=fzero
        self.ptype=ptype
        self.ineqs=[]
        self.eqs=[]

    def setIneq(self,ineq):
        self.ineqs+=[ineq]

    def setEq(self,eq):
        self.eqs+=[eq]

    def solve(self,x):
        fun=lambda x0: -self.ptype*self.fzero(x0)
        cons=[]
        for obj in self.eqs+self.ineqs:
            cons+=[obj.applyBool(x)]
        prob=cp.Problem(cp.Minimize(fun(x)),cons)
        prob.solve()
        res=CvxResult()
        if isinstance(x,list):
            l=[]
            for sl in x:
                for v in sl:
                    l+=[v.value]
            res.xstar=l
        else:
            res.xstar=x.value
        res.pstar=prob.value
        lambdas=[]
        for con in prob.constraints:
            lambdas+=[con.dual_value]
        res.lambdas=lambdas
        #res.dstar=prob.
        return res


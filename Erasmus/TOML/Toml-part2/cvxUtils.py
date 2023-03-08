import cvxpy as cp
import numpy as np
from scipyUtils import Inequality

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
        self.xstar=[]
        self.pstar=None
        self.lambdas=None
        self.dstar=None
        self.numIt=None

    def addVarResult(self,x):
        self.xstar+=[x]

    def printRes(self):
        print("xstar: "+str(self.xstar))
        print("pstar: "+str(self.pstar))
        print("lambdas: "+str(self.lambdas))
        print("numIt: "+str(self.numIt))
        #print("xstar: "+str(self.xstar))

class CvxProblem:
    def __init__(self,fzero,ptype):
        self.fzero=fzero
        self.ptype=ptype
        self.ineqs=[]
        self.eqs=[]
        self.vars={}

    def addVar(self,x):
        self.vars[x.name]=x

    def use(self,name):
        return self.vars[name]

    def setIneq(self,ineq):
        self.ineqs+=[ineq]

    def setEq(self,eq):
        self.eqs+=[eq]

    def solve(self,x):
        fun=None
        if self.ptype==1:
            fun=cp.Maximize(self.fzero(x))
        else:
            fun=cp.Minimize(self.fzero(x))
        cons=[]
        for obj in self.eqs+self.ineqs:
            cons+=[obj.applyBool(x)]
        prob=cp.Problem(fun,cons)
        prob.solve()
        res=CvxResult()
        l=[]
        for xi in x:
            l+=[xi.value]
        res.xstar=l
        res.pstar=prob.value
        lambdas=[]
        for con in prob.constraints:
            lambdas+=[con.dual_value]
        res.lambdas=lambdas
        res.numIt=prob.solver_stats.num_iters       
        return res

    def toConvex(self):
        fzero=lambda x:np.exp(self.fzero(x))
        cons=[]
        for c in self.ineqs+self.eqs:
            ineq=Inequality(lambda x:np.exp(c.apply(x))-1)
        problem=CvxProblem(fzero,self.ptype)
        for c in cons:
            problem.setIneq(c)
        return problem


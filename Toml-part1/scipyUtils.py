from scipy.optimize import minimize

class Inequality:
    def __init__(self,func):
        self.func=func

    def apply(self,x):
        return(self.func(x))

    def applyBool(self,x):
        return(self.apply(x)<=0)

    def toDictio(self):
        return({'type':'ineq','fun':self.func})

class Equality:
    def __init__(self,func):
        self.func=func

    def apply(self,x):
        return(self.func(x))

    def applyBool(self,x):
        return(self.apply(x)==0)

    def toDictio(self):
        return({'type':'eq','fun':self.func})

class Problem:
    def __init__(self,fzero,ptype):
        self.fzero=fzero
        self.ineqs=list()
        self.eqs=list()
        self.ptype=ptype
        self.bnds=[(None,None),(None,None)]

    def addEq(self,eq):
        #assert(isinstance(eq,Equality)==False,"eq must be an Equality")
        self.eqs+=[eq]

    def addIneq(self,ineq):
        #assert(isinstance(ineq,Inequality)==False,"ineq must be an Inequality")
        self.ineqs+=[ineq]



    def solve(self,x,m):
        cons=list()
        fun=lambda x:-self.ptype*self.fzero(x)
        for eq in self.eqs+self.ineqs:
            cons+=[eq.toDictio()]
        sol=minimize(fun,x,method=m,bounds=self.bnds,constraints=cons)
        return Result(x,sol)

    def solveWithJacob(self,x,m,myjac):
        cons=list()
        fun=lambda x:-self.ptype*self.fzero(x)
        for obj in self.eqs+self.ineqs :
            cons+=[obj.toDictio()]
        sol=minimize(fun,x,method=m,bounds=self.bnds,constraints=cons,jac=myjac)
        return Result(x,sol)


    def solveWithJacobHess(self,x,myjac,myhess):
        cons=list()
        fun=lambda x:-self.ptype*self.fzero(x)
        for obj in self.eqs+self.ineqs :
            cons+=[obj.toDictio()]
        sol=minimize(fun,x,bounds=self.bnds,constraints=cons,jac=myjac,hess=myhess)
        return Result(x,sol)

class Result:
    def __init__(self,point,value):
        self.point=point
        self.value=value

    def compare(self,r):
        if(self.value.fun>r.value.fun):
            return(-1)
        elif(self.value.fun<r.value.fun):
            return(1)
        else:
            return(0)

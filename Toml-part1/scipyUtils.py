import scipy.optimize as sp

class Inequality:
    def __init__(self,func):
        self.func=func

    def apply(self,x):
        return(self.func(x))

    def applyBool(self,x):
        return(self.apply(x)>=0)

    def toDictio(self): #convert the inequality in the format of scipy
        return({'type':'ineq','fun':self.func})

class Equality:
    def __init__(self,func):
        self.func=func

    def apply(self,x):
        return(self.func(x))

    def applyBool(self,x):
        return(self.apply(x)==0)

    def toDictio(self): #convert the equality in the format of scipy
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



    def solve(self,x,m): #solve the problem given the point x and the method m
        cons=list()
        fun=lambda x:-self.ptype*self.fzero(x)
        for eq in self.eqs+self.ineqs:
            cons+=[eq.toDictio()]
        sol=sp.minimize(fun,[x],method=m,bounds=self.bnds,constraints=cons)
        print(x)
        print("\n")
        print(sol)
        print("\n")
        return Result(x,sol,sol.nit)

    def solveWithJacob(self,x,m,myjac): #solve the problem using the jacobian
        cons=list()
        fun=lambda x:-self.ptype*self.fzero(x)
        for obj in self.eqs+self.ineqs :
            cons+=[obj.toDictio()]
        sol=sp.minimize(fun,x,method=m,bounds=self.bnds,constraints=cons,jac=myjac)
        print(x)
        print("\n")
        print(sol)
        print("\n")
        return Result(x,sol,sol.nit)


    def solveWithJacobHess(self,x,myjac,myhess): #solve the problem using the jacobian and the hessian
        cons=list()
        fun=lambda x:-self.ptype*self.fzero(x)
        for obj in self.eqs+self.ineqs :
            cons+=[obj.toDictio()]
        sol=sp.minimize(fun,x,bounds=self.bnds,constraints=cons,jac=myjac,hess=myhess)
        print(x)
        print("\n")
        print(sol)
        print("\n")
        return Result(x,sol,sol.nit)

    def isFeasible(self,x):
        res=True
        #print(x)
        for op in self.eqs+self.ineqs:
            tmp=op.applyBool(x)
            #print(tmp)
            res=res and tmp
        return res

class Result:
    def __init__(self,point,value,numIt):
        self.point=point
        self.value=value
        self.numIt=numIt

    def printRes(self):
        print("start: "+str(self.point))
        print("xstar: "+str(self.value.x))
        print("pstar: "+str(self.value.fun))
        print("numIt: "+str(self.numIt))
        print("\n")

    def compare(self,r):
        if(self.value.fun>r.value.fun):
            return(-1)
        elif(self.value.fun<r.value.fun):
            return(1)
        else:
            return(0)

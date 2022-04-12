from gpkit import Variable,Model

class GeoIneq:
    def __init__(self,left,right):
        self.fun=lambda x: left(x)<=right(x)

    def apply(self,x):
        return self.fun(x)

    def applyBool(self,x):
        return self.apply(x)<=1

    def toLambda(self):
        return lambda x:self.apply(x)

    def toDictio(self): #convert the equality in the format of scipy
        return({'type':'eq','fun':self.fun})

class GeoProblem:
    def __init__(self,fzero):
        self.fzero=fzero
        self.ineqs=[]
        self.eqs=[]
        self.vars=[]

    def addVar(self,x):
        self.vars+=[x]

    def addIneq(self,ineq):
        self.ineqs+=[ineq]

    def addEq(self,eq):
        self.eqs+=[eq]

    def solve(self,x):
        cons=[]
        for c in self.ineqs+self.eqs:
            cons+=[c.toLambda()(x)]
        model=Model(self.fzero(x),cons)
        sol=model.solve(verbosity=0)
        #print(sol)
        return GeoResult(sol["variables"],
            sol["cost"],
            sol["sensitivities"]["variablerisk"],
            sol["soltime"]) 

class GeoResult:
    def __init__(self,xstar,cost,risk,time):
        self.xstar=xstar
        self.cost=cost
        self.risk=risk
        self.time=time

    def printRes(self):
        print("xstar: "+str(self.xstar))
        print("cost: "+str(self.cost))
        print("risk: "+str(self.risk))
        print("time: "+str(self.time))
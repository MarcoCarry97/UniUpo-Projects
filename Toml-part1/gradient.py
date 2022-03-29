from random import randrange
from math import sqrt

class GradFunction:
    def __init__(self,fun,grad):
        self.fun=fun
        self.grad=grad
        self.sqgrad=[]
    
    def applyFun(self,x):
        return self.fun(x)

    def applyGrad(self,x): #gradient on x
        lx=[]
        for der in self.grad:
            lx+=[der(x)]
        return lx

    def applySqGrad(self,x): #square gradient on x
        lx=[]
        for der in self.sqgrad:
            lx+=[der(x)]
        return lx
    
    def twoNorm(self,x): #2-norm of the function on x
        acc=0
        for g in self.grad:
            acc+=abs(g(x))**2
        return sqrt(acc)

class GradResult:
    def __init__(self,start,xstar,pstar,numIt):
        self.start=start
        self.xstar=xstar
        self.pstar=pstar
        self.numIt=numIt


class GradientDescent:
    def __init__(self,fun,eps):
        self.fun=fun
        self.eps=eps

    def getT(self,x,d): #Backtracking line search
        a=(31/2)*0.01 
        b=0.45
        count=0
        def cond(x0,t0,d0):
            c=self.fun.applyGrad(x0)[0]
            left=self.fun.applyFun(x0+t0*d)
            right=self.fun.applyFun(x0)+a*t0*c*d0
            return left-right>0
        t=1
        while cond(x,t,d):
            t=b*t
            count+=1
        return t,count

    def getDirection(self,x):
        return -self.fun.applyGrad(x)[0]

    def descend(self,x0): #calc the optimal point beginning from x0
        print(x0)
        x=x0 #step 1
        count=0
        while self.fun.twoNorm(x)>self.eps: #step 5
            d=self.getDirection(x)#step 2
            t,ct=self.getT(x,d) #step 3
            x=x+t*d #step 4
            count+=(ct+1)
            #print("descend")
        return GradResult(x0,x,self.fun.applyFun(x),count)
from random import randrange
from math import sqrt

class GradFunction:
    def __init__(self,fun,grad):
        self.fun=fun
        self.grad=grad
        self.sqgrad=[]
    
    def applyFun(self,x):
        return self.fun(x)

    def applyGrad(self,x):
        lx=[]
        for der in self.grad:
            lx+=[der(x)]
        return lx

    def applySqGrad(self,x):
        lx=[]
        for der in self.sqgrad:
            lx+=[der(x)]
        return lx
    
    def twoNorm(self,x):
        acc=0
        for g in self.grad:
            acc+=g(x)
        return acc

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

    def getT(self,x):
        a=(30/2)*0.01 #randrange(1,30)*0.01
        b=0.1
        t=1
        count=0
        def cond(x0):
            c=self.fun.applyGrad(x0)[0]
            d=-c
            left=self.fun.applyFun(x0+t*d)
            right=self.fun.applyFun(x0)+a*t*c*d
            return left>right
        while cond(x):
            t=b*t
            count+=1
        return t,count

    def descend(self,x0):
        x=x0
        count=0
        while self.fun.twoNorm(x)>self.eps:
            t,ct=self.getT(x)
            d=-self.fun.applyGrad(x)[0]
            x=x+t*d
            count+=(ct+1)
        return GradResult(x0,x,self.fun.applyFun(x),count)
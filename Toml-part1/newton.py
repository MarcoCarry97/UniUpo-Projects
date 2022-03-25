from gradient import GradFunction,GradResult
from random import randrange


class NewtonDescent:
    def __init__(self,fun,eps):
        self.fun=fun
        self.eps=eps

    def getT(self,x,d):
        a=(30/2)*0.01 #randrange(1,30)*0.01
        b=0.45
        count=0
        def cond(x0,t0,d0):
            c=self.fun.applyGrad(x0)[0]
            #c=-d0
            left=self.fun.applyFun(x0+t0*d0)
            right=self.fun.applyFun(x0)+a*t0*c*d0
            return left-right>0
        t=1
        while cond(x,t,d):
            t=b*t
            count+=1
            print("getT")
        return t,count

    def getDec(self,x):
        a=self.fun.applyGrad(x)[0]
        b=self.fun.applySqGrad(x)[0]
        return (a*a)/b

    def getDirection(self,x):
        a=self.fun.applySqGrad(x)[0]
        b=self.fun.applyGrad(x)[0]
        return -b/a

    def descend(self,x0):
        x=x0
        count=0
        while self.getDec(x)/2>self.eps:
            d=self.getDirection(x)
            t,ct=self.getT(x,d)
            x=x+t*d
            count+=(ct+1)
            print("descend")
        return GradResult(x0,x,self.fun.applyFun(x),count)
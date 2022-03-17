
from gradient import GradFunction,GradResult
from newton import NewtonDescent

results=[]

f1=lambda x:2*(x**2)-0.5
g1=lambda x:4*x
fun1=GradFunction(f1,[g1])
fun1.sqgrad=[lambda x:4]
eps1=10**(-4)
x1=[3]

f2=lambda x:2*(x**4)-4*(x**2)+x-0.5
g2=lambda x:8*(x**3)-8*x+1
fun2=GradFunction(f2,[g2])
fun2.sqgrad=[lambda x:24*(x**2)-8]
eps2=10**(-4)
x2=[-2,-0.5,0.5,2]

funs=[fun1,fun2]
epss=[eps1,eps2]
xs=[x1,x2]

for i in range(0, len(funs)):
    gradient=NewtonDescent(funs[i],epss[i])
    for x0 in xs[i]:
        results+=[gradient.descend(x0)]

print("Results: ")
for r in results:
    print("     Start: "+str(r.start))
    print("     Opt. point: "+str(r.xstar))
    print("     Opt. value: "+str(r.pstar))
    print("     Num of it.: "+str(r.numIt)+"\n")

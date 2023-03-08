from gpUtils import GeoIneq,GeoProblem
import gpkit as gp

x=gp.VectorVariable(3,"x")

S=200

fzero=lambda x:1/(x[0]*x[1]*x[2])

ineq1=GeoIneq(lambda x:2*x[0]*x[1]+2*x[0]*x[2]+2*x[1]*x[2]-S)

ineq2=GeoIneq(lambda x: -x[0]+2*x[1])

problem=GeoProblem(fzero)
problem.addIneq(ineq1)
problem.addIneq(ineq2)


sol=problem.solve(x)

print(sol)

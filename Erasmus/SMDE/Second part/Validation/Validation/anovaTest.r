library("FactoMineR")
library("car")

readData=function(original,simulated)
{
  originalModel=read.csv(original)
  simulatedModel=read.csv(simulated)
  
  resInf=data.frame(x1=originalModel,x2="v1")
  resSec=data.frame(x1=simulatedModel,x2="v2")
  
  return(mergeRows(simulatedModel,originalModel,common.only=FALSE))
}

performAnova=function(formula,data)
{
  return(aov(formula,data=data))
}


plots=function(model)
{
  
}

tests=fuction(model)
{
  
}

computeInfections=function()
{
  data=readData("infectedModel1.csv","infectedModel2.csv")
  model=performAnova(V1~x2,data)
  plots(model)
  tests(model)
}

computeSecondEffects=function()
{
  data=readData("secondEfModel1.csv","secondEfModel2.csv")
  model=performAnova(V1~x2,data)
  plots(model)
  tests(model)
}


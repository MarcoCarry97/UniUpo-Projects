library(FactoMinerR)

data=read.csv("decathlon.csv")

#creation

linearRegression=function(x,y,mydata)
{
  cor.test(x,y)
  model=lm(x~y,data=mydata)
  return(model)
}


model=linearRegression(x,y,data)

#prediction

makePrediction=function(model,data)
{
  print(confint(model))
  print(predict.lm(model,interval = "confidence"))
  print(predict.model(model,newdata=data,interval="prediction"))
  
}

newData=data.frame()

makePrediction(model,newData)

#testing

testModel=function(model)
{
  qqnorm(residuals(model))
  shapiro.test(residuals(model))
  bptest(model)
  dwtest(model)
}

plotModel=function(model)
{
  hist(residuals(model))
  plot(residuals(model))
}

testModel(model)
plotModel(model)


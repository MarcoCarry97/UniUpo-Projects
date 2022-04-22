library(FactoMineR)
library(car)
library(lmtest)

data=read.csv("decathlon.csv")

#creation

linearRegression=function(x,y,mydata)
{
  print(cor.test(x,y))
  model=lm(x~y,data=mydata)
  print(model)
  return(model)
}

linearRegr=function(formula,data)
{
  model=lm(formula,data)
  print(model)
  return(model)
}


#model=linearRegression(x,y,data)

#prediction

makePrediction=function(model,mydata)
{
  print(confint(model))
  print(predict.lm(model,interval = "confidence"))
  print("PREDICTION")
  print(predict.lm(model,newdata=mydata[0],interval="prediction"))
  
}

#newData=data.frame()

#makePrediction(model,newData)

#testing

testModel=function(model)
{
  qqnorm(residuals(model))
  qqline(residuals(model),col="red")
  print(shapiro.test(residuals(model)))
  print(bptest(model))
  print(dwtest(model))
}

plotModel=function(model)
{
  hist(residuals(model))
  plot(residuals(model))
}

makePredictTest=function(x,y,data)
{
  model=linearRegression(x,y,data)
  makePrediction(model)
  testModel(model)
  plotModel(model)
}

linearRegression(data$X1500m,data$X100m,data)
linearRegression(data$X1500m,data$Long.jump,data)
linearRegression(data$X1500m,data$Shot.put,data)
linearRegression(data$X1500m,data$High.jump,data)
linearRegression(data$X1500m,data$X400m,data)
linearRegression(data$X1500m,data$X110m.hurdle,data)
linearRegression(data$X1500m,data$Discus,data)
linearRegression(data$X1500m,data$Pole.vault,data)
linearRegression(data$X1500m,data$Javeline,data)
linearRegression(data$X1500m,data$Rank,data)
linearRegression(data$X1500m,data$Points,data)
#makePredictTest(data$X1500m,data$X100m,data)

bestCor=data$X400m


print("CORRELATION")
cor(heptathlon)

model=linearRegression(data$X1500m,bestCor,data)

makePrediction(model,newdata)
testModel(model)

plotModel(model)

#testModel(model)
#plotModel(model)


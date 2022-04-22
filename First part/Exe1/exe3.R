library(FactoMineR)
library(car)
library(lmtest)

deca=read.csv("decathlon.csv")

deca$X=NULL
deca$Competition=NULL

#print(cor(deca))


linearRegr=function(formula,data)
{
  model=lm(formula,data=data)
  print(summary(model))
  return(model)
}

assumptions=function(model)
{
  print(shapiro.test(residuals(model)))
  print(dwtest(model))
  print(bptest(model))
}

plotModel=function(model)
{
  qqnorm(residuals(model))
  qqline(residuals(model),col="red")
  plot(residuals(model))
  plot(density(residuals(model)))
  hist(residuals(model))
}

testModel=function(model,data)
{
  yp=predict(model,data,interval="prediction")
  print("PREDICTION")
  print(yp)
  y=data$X1500m
  print("TRUE VALUE")
  print(y)
  error=cbind(yp[,1,drop=FALSE],y,(y-yp[,1])^2)
  sqError=error[,3]
  mse=mean(sqError)
  print("MSE")
  print(mse)
  rootMse=sqrt(mse/nrow(data))
  print("RMSE")
  print(rootMse)
}

rootMseTraining=function(model)
{
  rmseTrain=sqrt(mean(((model$residuals)^2)/nrow(model)))
  return(rmseTrain)
}

model=linearRegr(deca$X1500m~deca$X400m+deca$Discus+deca$Pole.vault,deca) #variables with higher correlations
assumptions(model)
plotModel(model)

#model1=linearRegr(deca$X1500m~deca$X400m,deca) #variables with higher correlations
#assumptions(model1)
#plotModel(model1)

#dividing data in training and test
n=nrow(deca)
s=sample(1:n,round(0.67*n))
trainSet=deca[s,]
testSet=deca[-s,]

#create the training model

trainModel=linearRegr(deca$X1500m~deca$X400m+deca$Discus+deca$Pole.vault,trainSet)
testModel(trainModel,testSet)
rootMseTraining(trainModel)

#trainModel1=linearRegr(deca$X1500m~deca$X400m,trainSet)
#testModel(trainModel1,testSet)
#rootMseTraining(trainModel)


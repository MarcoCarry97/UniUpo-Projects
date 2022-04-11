library(psych)
library(FactoMineR)
library(HSAUR2)
library(car)

hepta=heptathlon


#PART 1

standard=function(data)
{
  std=data
  for(i in 1:length(data))
  {
    m=mean(data[,i])
    s=sd(data[,i])
    std[,i]=(data[,i]-m)/s
  }
  return(std)
}

saur=function(data)
{
  r=cor(data[,])
  print(r)
  plot(r)
  print(cortest.bartlett(r,length(data)))
  print(KMO(data))
}

changeDirection=function(data)
{
  data$run200m=max(data$run200m)-data$run200m
  data$hurdles=max(data$hurdles)-data$hurdles
  data$highjump=max(data$highjump)-data$highjump
}

mypca=function(data,offset)
{
  std=standard(hepta)
  saur(std)
  changeDirection(std)
  resPca=PCA(std,graph = FALSE,quanti.sup=offset)
  print(resPca$eig)
  plot(resPca,choix="var")
  plot(resPca,choix = "ind")
  print(resPca$ind$coord)
  plot(resPca,choix = "ind")
  return(resPca)
}

mypca(hepta,length(hepta))

#PART 2

pcRegression=function(data)
{
  regr=lm(data$score~.,data=data)
  print(vif(regr))
  resPca=mypca(data,7)
  data$PC1=resPca$ind$coord[,1]
  data$PC2=resPca$ind$coord[,2]
  pcr=training(data)
  return(pcr)
}

sub=function(data,start,stop)
{
  newd=c()
  for( i in start:stop)
   {
    newd=newd+c(data[i])
   }
  return(newd)
}

training=function(data)
{
  n=nrow(data)
  rndSample=sample(1:n,round(0.67*n))
  trainingSet=data[rndSample,]
  testSet=data[-rndSample,]
  print("training")
  print(trainingSet)
  print("test")
  print(testSet)
  pcr=lm(data$score~data$PC1+data$PC2,data=trainingSet)
  print(summary(pcr))
  yp=predict(pcr,testSet,interval="prediction")
  print("predictions")
  print(yp)
  y=testSet$score
  print("true values")
  print(y)
  ys=yp[,1]
  error=cbind(ys,y,(ys-y)^2)
  sqError=error[,3]
  mse=mean(sqError)
  rmse=sqrt(mse/length(testSet))
  print("MSE")
  print(mse)
  print("RMSE")
  print(rmse)
  return(pcr)
}
 
pcRegression(hepta)



library(psych)
library(FactoMineR)
library(HSAUR2)
library(car)

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

stdHepta=standard(heptathlon)

correlation=function(data)
{
  r=cor(data[,])
  plot(r)
  n=nrow(data)
  cortest.bartlett(r,n)
  
}

kmo <- function(x)
{
  x <- subset(x, complete.cases(x))       # Omit missing values
  r <- cor(x)                             # Correlation matrix
  r2 <- r^2                               # Squared correlation coefficients
  i <- solve(r)                           # Inverse matrix of correlation matrix
  d <- diag(i)                            # Diagonal elements of inverse matrix
  p2 <- (-i/sqrt(outer(d, d)))^2          # Squared partial correlation coefficients
  diag(r2) <- diag(p2) <- 0               # Delete diagonal elements
  KMO <- sum(r2)/(sum(r2)+sum(p2))
  MSA <- colSums(r2)/(colSums(r2)+colSums(p2))
  return(list(KMO=KMO, MSA=MSA))
}

makePCA=function(data,offset)
{
  res=PCA(data,quanti.sup = offset)
  print(res$eig)
  print(res$var$coord)
  print(res$var$cor)
  plot(res,choix="var")
  plot(res,choix="ind")
  return(res)
}

linearRegr=function(formula,data)
{
  model=lm(formula,data=data)
  print(summary(model))
  print(vif(model))
  return(model)
}

makePrediction=function(model,data)
{
  yp=predict(model,data,interval="prediction")
  y=data$score
  error=cbind(yp[,1,drop=FALSE],y,(yp[,1]-y)^2)
  sqError=error[,3]
  mse=mean(sqError)
  return(mse)
}

changeDirection=function(data)
{
  data$hurdles=max(data$hurdles)-data$hurdles
  data$longjump=max(data$longjump)-data$longjump
  return(data)
}

#PART 1


stdHepta=standard(heptathlon)
correlation(stdHepta)
kmo(stdHepta)
pca=makePCA(stdHepta,ncol(stdHepta))
print(pca)
stdHepta=changeDirection(stdHepta)

#PART 2
pca=makePCA(stdHepta,offset=ncol(stdHepta))
stdHepta$PC1=pca$ind$coord[,1]
stdHepta$PC2=pca$ind$coord[,2]
n=nrow(stdHepta)
s=sample(1:n,round(0.67*n))
trainSet=stdHepta[s,]
testSet=stdHepta[-s,]

model=linearRegr(stdHepta$score~stdHepta$PC1+stdHepta$PC2,trainSet)
mse=makePrediction(model,testSet)
print("MSE")
print(mse)
rmse=sqrt(mse/nrow(testSet))
print("RMSE")
print(rmse)



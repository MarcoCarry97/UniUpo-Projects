library(gplots)
library(R.utils)
library(fields)
library(grDevices)
library(plotrix)
library(dplyr)
library(pracma)

fluctuations=function (x)
{
  avg=mean(x,na.rm=TRUE)
  return(x-avg)
}

deltaTimes=function(n)
{
  return(1:(n/2))
}

toArray=function(list)
  {
  return(as.array(unlist(list,use.names = FALSE)))
}

correlation=function(x,dt)
  {
  variance=var(x)
  size=length(x)/(dt);
  dtX=c();
  t=1;
  for(t in 1:length(x))
    {
    if(t+dt <=length(x))
      {
      dtX[t]=x[t]*x[t+dt]
      t=t+1;
    }
  }
  return(mean(dtX)/variance)
}

lagrangianTime=function(x)
  {
  r=c()
  for(dt in 0:length(x)-1)
    r[dt]=correlation(x,dt)
  #r=acf(x,plot=FALSE,type=c("correlation"))$acf
  ln=log(abs(r))
  firstCoeff=line(ln)$coefficients[1]
  return(-(1/firstCoeff))
}

getDataOfDay=function(day,type)
{
  fileName=""
  if(day<=9) fileName=paste("settembre/2018-09-0",day,".dat",sep="")
  else fileName=paste("settembre/2018-09-",day,".dat",sep = "")
  return(read.table(fileName,sep=" ")[,type])
}

par(mfrow=c(1,2))
for(i in 1:30)
{
  data=getDataOfDay(i,"V7");
  fluct=fluctuations(data);
  r=c()
  for(dt in 0:32)
    r[dt+1]=correlation(fluct,dt)
  a=acf(fluct, type=c("correlation"))
  lines(0:30,array(data=r,dim=31),type = "l",col="green")
  Lt=lagrangianTime(fluct)
  print(paste("Lagrangian time:",Lt))
}
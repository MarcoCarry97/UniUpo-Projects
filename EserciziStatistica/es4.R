library(gplots)
library(R.utils)
library(fields)
library(grDevices)
library(plotrix)
library(dplyr)

NAclean=function(x)
{
  y=c();
  for(i in 1:length(x))
    if(!is.na(x[i]) && !is.nan(x[i]))
      y[i]=x[i]
  return(y)
}

fluctuations=function (x)
{
  x=NAclean(x)
  avg=mean(x,na.rm=TRUE)
  return(x-avg)
}

toArray=function(list)
{
  return(as.array(unlist(list,use.names = FALSE)))
}

standard=function(x)
{
  return((x-mean(x))/sd(x))
}

chisquare=function (x,numOfIntervals)
{
  o=standard(frequencies(x,numOfIntervals))
  e=expected(o,numOfIntervals)
  acc=0;
  for(k in 2:numOfIntervals)
  {
    value=o[k] - e[k]
    value=value^2;
    value=value/e[k]
    acc=acc+value;
  }
  return(acc)
}

chisquareHist=function (x,numOfIntervals)
  {
  o=standard(hist(x,breaks=numOfIntervals,plot=FALSE)$density)
  e=expected(o,numOfIntervals)
  acc=0;
  for(k in 2:numOfIntervals)
    {
    value=o[k] - e[k]
    value=value^2;
    value=value/e[k]
    acc=acc+value;
  }
  return(acc)
}

getDataOfDay=function(day,type)
{
  fileName=""
  if(day<=9) fileName=paste("settembre/2018-09-0",day,".dat",sep="")
  else fileName=paste("settembre/2018-09-",day,".dat",sep = "")
  return(read.table(fileName,sep=" ")[,type])
}

getDataOfMonth=function(type)
  {
  data=c();
  for(i in 1:30)
  {
    data=c(data,getDataOfDay(i,type))
  }
  return(data)
}

getDataHalf=function(i,type)
  {
  mat=matrix(0,2,720)
  data=getDataOfDay(i,type);
  d=1;
  n=1;
  for(h in 1:1440)
    {
    if(!is.na(data[h]))
      {
      if(h>360 && h<=1080)
        {
        mat[1,d]=data[h]
        d=d+1
      }
      else
        {
        mat[2,n]=data[h]
        n=n+1
      }
    }
  }
  return(mat)
}

sizeOfInterval=function(x,numOfIntervals)
{
  a=min(x,na.rm = TRUE)
  b=max(x,na.rm=TRUE)
  size=0;
  if(a<0 || b<0) size=(abs(a)+abs(b))/numOfIntervals
  else size=(b-a)/numOfIntervals
  return(size)
}

intervals=function (x,numOfIntervals)
{
  ints=matrix(0,2,numOfIntervals)
  left=min(x);
  size=sizeOfInterval(x,numOfIntervals)
  for(i in 1:numOfIntervals)
  {
    right=left+size;
    if(right>max(x)) right=max(x)
    ints[1,i]=left;
    ints[2,i]=right;
    left=right
  }
  return(ints)
}

frequencies=function(x,numOfIntervals)
{
  freqs=array(data=0,dim=numOfIntervals)
  ints=intervals(x,numOfIntervals)
  for(i in 1:length(x))
    for(j in 1:length(freqs))
      if(x[i]>=ints[1,j] && x[i]<=ints[2,j])
        freqs[j]=freqs[j]+1
  return(freqs)
}

expected=function(x,numOfIntervals)
{
  stdX=standard(x)
  e=c(pnorm(stdX[1])*length(x))
  for(i in 2:numOfIntervals)
  {
    down=pnorm(q=stdX[i-1])
    up=pnorm(q=stdX[i])
    e=c(e,(up-down)*length(x))
  }
  return(e)
}

controlIfFits=function(x,numOfIntervals)
{
  chi=chisquare(x,numOfIntervals)
  d=length(frequencies(x,numOfIntervals))-3
  print(paste("Normal; ",chi,"<=",d,":",chi<=d))

}

controlIfHist=function(x,numOfIntervals)
  {
  chi=chisquareHist(x,numOfIntervals)
  d=length(hist(x,breaks = numOfIntervals)$density)-3
  print(paste("Hist: ",chi,"<=",d,":",chi<=d))

}

par(mfrow=c(3,4))

numOfIntervals=7

fluctOneDay=fluctuations(getDataOfDay(1,"V7"));
fluctMonth=fluctuations(getDataOfMonth("V7"));
print("Chi Square of one Day")
controlIfFits(fluctOneDay,numOfIntervals)
controlIfHist(fluctOneDay,numOfIntervals)
print("Chi Square of one Month")
controlIfFits(fluctMonth,numOfIntervals)
controlIfHist(fluctMonth,numOfIntervals)

for(i in 1:10)
{

  windHalf=getDataHalf(i,"V7")
  print(paste("Chi square of half day",i))
  fluctHalfDay=fluctuations(windHalf[1,])
  controlIfFits(fluctHalfDay,numOfIntervals)
  controlIfHist(fluctHalfDay,numOfIntervals)
  print(paste("Chi square of half night",i))
  fluctHalfNight=fluctuations(windHalf[2,])
  controlIfFits(fluctHalfNight,numOfIntervals)
  controlIfHist(fluctHalfNight,numOfIntervals)
}
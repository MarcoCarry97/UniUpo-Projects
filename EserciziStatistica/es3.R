library(gplots)
library(R.utils)
library(fields)
library(grDevices)
library(plotrix)

fluctuations=function (x)
{
  avg=mean(x,na.rm=TRUE)
  return(x-avg)
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

dataDay=getDataOfDay(1,"V7")
dataMonth=getDataOfMonth("V7")


densityDay=density(fluctuations(dataDay))
densityMonth=density(fluctuations(dataMonth))

ylabel="Values"
par(mfrow=c(2,1))
plot(densityDay,xlab="Fluctuations of Wind - One Day (m/s)",ylab = ylabel,main="")
plot(densityMonth,xlab="Fluctuations of Wind - One Month (m/s)",ylab = ylabel,main="")


for(i in 1:10)
{
  dataHalf=getDataHalf(i,"V7")
  densityHalfDay=density(fluctuations(dataHalf[1,]))
  densityHalfNight=density(fluctuations(dataHalf[2,]))
  xlabelDay=paste("Fluctuations half day",i,"(m/s)")
  xlabelNight=paste("Fluctuations half night",i,"(m/s)")
  plot(densityHalfDay,xlab=xlabelDay,ylab = ylabel,main="")
  plot(densityHalfNight,xlab=xlabelNight,ylab=ylabel,main="")
}
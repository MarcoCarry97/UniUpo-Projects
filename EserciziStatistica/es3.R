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
  for(i in 1:1440)
  {
    if(!is.na(data[i]))
    {
      if(i<720)
      {
        mat[1,d]=data[i]
        d=d+1
      }
      else
      {
        mat[2,n]=data[i]
        n=n+1
      }
    }
  }
  return(mat)
}

dataDay=getDataOfDay(1,"V7")
dataMonth=getDataOfMonth("V7")
dataHalf=getDataHalf(1,"V7")

densityDay=density(fluctuations(dataDay))
densityMonth=density(fluctuations(dataMonth))
densityHalfDay=density(fluctuations(dataHalf[1,]))
densityHalfNight=density(fluctuations(dataHalf[2,]))

par(mfrow=c(2,2))
plot(densityDay)
plot(densityMonth)
plot(densityHalfDay)
plot(densityHalfNight)
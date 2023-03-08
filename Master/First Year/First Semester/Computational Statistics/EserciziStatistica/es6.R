library(gplots)
library(R.utils)
library(fields)
library(grDevices)
library(plotrix)
library(dplyr)
library(pracma)

NAclean=function(x)
{
  y=c();
  for(i in 1:length(x))
    if(!is.na(x[i]) && !is.nan(x[i]))
      y=c(y,x[i])
  return(y)
}

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
  return(NAclean(read.table(fileName,sep=" ")[,type]))
}

epsilon=function(x,Lt)
{

  variance=var(x,na.rm = TRUE);
  epsi=2*variance/Lt
  return(epsi)
}

whiteNoise=function(t,dt)
{
  rands=rnorm(t);
  rtDt=sqrt(dt);

  return(rands[t]*rtDt)
}

plotline=function(x,particle,limitX,limitY)
{

  color=c("red","green","blue","yellow","violet","black")
  if(particle==1) plot(1:length(x),x,type="l",xlim=c(0,limitX),ylim=c(-max(abs(x)),max(abs(x))))
  else lines(1:length(x),x, col=color[particle%%length(color)]);
}

differences=function(x,array)
{
  meanArray=mean(array,na.rm=TRUE);
  meanX=mean(x,na.rm=TRUE);
  sdArray=var(array,na.rm = TRUE)
  sdX=var(x,na.rm = TRUE)
  print(paste("Mean differences: ",abs(abs(meanArray) - abs(meanX))))
  print(paste("Deviation differences: ",abs(abs(sdArray) - abs(sdX))))
  print(" ")
}

langevinModel=function(type,Co,numOfParticles,numOfTimes)
{

     for(day in 1:30)
     {
       particlesForInterations=array(data=0, dim=numOfParticles*numOfTimes)
       x=fluctuations(getDataOfDay(day,type))

       Lt=lagrangianTime(x)
       dt=Lt/10;
       for(p in 1:numOfParticles)
         {
         speed=0;
         positions=array(data=0,dim=numOfTimes)
         for(t in 1:numOfTimes)
           {
           speed=0.9*speed+sqrt(2*var(x)/Lt)*whiteNoise(t,dt)
           if(t>1)
           {
             positions[t]=positions[t-1]+speed*dt;
             particlesForInterations[p*t]=positions[t];
           }
         }
         plotline(positions,p,numOfParticles,numOfTimes)
       }
       differences(x,particlesForInterations)
     }
 }



langevinModel("V7",4,100,100)

NAclean=function(x)
  {
  y=c();
  for(i in 1:length(x))
    if(!is.na(x[i]) && !is.nan(x[i]))
      y[i]=x[i]
  return(y)
}

readFile=function(day)
{
  fileName="";
  if(day<=9) fileName=paste("settembre/2018-09-0",day,".dat",sep="")
  else fileName=paste("settembre/2018-09-",day,".dat",sep="");
  return(read.table(fileName))
}

getDataOfDay=function(i,type)
{
  return(readFile(i)[,type])
}

getDataMatrix=function(type)
{
  m=matrix(ncol=60*24,nrow=30, data=0)
  for(i in 1:30)
  {
    day=getDataOfDay(i,type)
    for(j in 1:(60*24))
    {
      if(!is.na(day[i])) m[i,j]=day[j]
    }
  }
  return(m);
}

getDataMonth=function(type)
{
  data=c();
  for(i in 1:30)
  {
     data=c(data,getDataOfDay(i,type))
  }
  return(data)
}

typicalDay=function(type)
{
  means=array(data=0,dim=24*60)
 counts=array(data=0,dim=24*60)
  for(i in 1:30)
  {
    x=getDataOfDay(i,type)
    for(j in 1:length(x))
    {

      if(!is.na(x[j]))
      {
        means[j]=means[j]+x[j]
        counts[i]=counts[j]+1
      }
    }
  }
  for(i in 1:30)
  {
    if(counts[i]!=0) means[i]=means[i]/counts[i]
  }
  return(means)
}

td=typicalDay("V6")

par(mfrow=c(2,2))

plot(1:length(td),td, type="l",xlab = "Day",ylab = "avg")
plot(getDataOfDay(1,"V6"),type="l")
plot(getDataOfDay(2,"V6"),type="l")
plot(getDataOfDay(3,"V6"),type="l")

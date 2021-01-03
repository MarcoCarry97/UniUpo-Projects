
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

getDataMonth=function(type)
{
  data=c();
  for(i in 1:30)
  {
     data=c(data,getDataOfDay(i,type))
  }
  return(data)
}

typicalDay=function(x)
{
  return(mean(x,na.rm = TRUE))
}

data=getDataMonth("V6")
print(paste("Typical day: ",typicalDay(data)))
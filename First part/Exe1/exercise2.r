library(car)
library(carData)
library(sandwich)
library(lmtest)
library(RcmdrMisc)
library(agricolae)

v1=rnorm(200, mean=10, sd=50)
v2=rnorm(200, mean=50, sd=50)
v3=rnorm(200, mean=80, sd=50)

v1n=data.frame(x1=v1, x2="v1")
v2n=data.frame(x1=v2, x2="v2")
v3n=data.frame(x1=v3, x2="v3")

createData=function(x,y,z)
{
  
  plot(density(v1),xlim=c(-200,220),ylim=c(0,0.01),main="Three Normal distributions")
  lines(density(v2),col=2)
  lines(density(v3),col=3)
  
  v1n=data.frame(x1=x, x2="v1")
  v2n=data.frame(x1=y, x2="v2")
  v3n=data.frame(x1=z, x2="v3")
  
  data=mergeRows(v1n, v2n, common.only=FALSE)
  data=mergeRows(as.data.frame(data), v3n, common.only=FALSE)
  head(data)
  return(data)
}

#PART 1

posthoc=function(x1,x2,n1,n2,data)
{
  formula=x1~x2
  model=aov(formula,data=data) 
  print(shapiro.test(residuals(model))) #normality
  print(dwtest(model,alternative = "two.sided")) #independency
  print(bptest(model)) #omogeneity
  #print(LSD.test(model,n1)) 
 # print(LSD.test(model,n2))
  #print(leveneTest(formula,data=data))
}

data=createData(v1,v2,v3)
print("v1 and v2")
posthoc(v1,v2,"x1","x2",data)
print("v1 and v3")
posthoc(v1,v3,"x1","x2",data)
print("v2 and v3")
posthoc(v2,v3,"x1","x2",data)

#PART 2

diabetes=read.csv("diabetes.csv")



diabetes$AgeCat=factor(ifelse(diabetes$Age<=30,"young",
                              ifelse(diabetes$Age<=50,"middle","old")))

diabetes$OutCat=factor(ifelse(diabetes$Outcome==1,"True","False"))

summary(diabetes)
#Q1

postgroup=function(data,independent)
{
  print("PREGNANCY")
  posthoc(data$Pregnancies,independent,"AgeCat","Pregnancies",data)
  print("GLUCOSE")
  posthoc(data$Glucose,independent,"AgeCat","Glucose",data)
  print("BLOOD PRESSURE")
  posthoc(data$BloodPressure,independent,"AgeCat","BloodPressure",data)
  print("THICKNESS")
  posthoc(data$SkinThickness,independent,"AgeCat","SkinThickness",data)
  print("INSULIN")
  posthoc(data$Insulin,independent,"AgeCat","Insulin",data)
  print("BMI")
  posthoc(data$BMI,independent,"AgeCat","BMI",data)
  print("DIABETES FUNCTION")
  posthoc(data$DiabetesPedigreeFunction,independent,"AgeCat","DiabetesPedigreeFunction",data)
  #print("OUTCOME")
  #posthoc(data$Outcome,data$AgeCat,"AgeCat","Outcome",data)
}



plotline=function(data)
{
  plot(density(data$Pregnancies),main="Diabetes")
  lines(density(data$Glucose),col=2)
  lines(density(data$BloodPressure),col=3)
  lines(density(data$SkinThickness),col=4)
  lines(density(data$Insulin),col=5)
  lines(density(data$BMI),col=6)
  lines(density(data$DiabetesPedigreeFunction),col=7)
}

boxgroup=function(data)
{
  boxplot(data$Pregnancies~data$AgeCat+data$Outcome,data=data)
  boxplot(data$Glucose~data$AgeCat+data$Outcome,data=data)
  boxplot(data$BloodPressure~data$AgeCat+data$Outcome,data=data)
  boxplot(data$SkinThickness~data$AgeCat+data$Outcome,data=data)
  boxplot(data$Insulin~data$AgeCat+data$Outcome,data=data)
  boxplot(data$BMI~data$AgeCat+data$Outcome,data=data)
  boxplot(data$DiabetesPedigreeFunction~data$AgeCat+data$Outcome,data=data)
  #boxplot(data$Pregnancies~data$AgeCat+data$Outcome,data=data)
  
}

formhoc=function(formula,data)
{
  model=aov(formula,data=data) 
  print(shapiro.test(residuals(model))) #normality
  print(dwtest(model,alternative = "two.sided")) #independency
  print(bptest(model))
}

analyzeInteraction=function(depVar,indVar1,indVar2,data)
{
  formula=depVar~indVar1+indVar2
  formhoc(formula,data)
}

analyzeInteractionOne=function(depVar,indVar,data)
{
  formula=depVar~indVar
  formhoc(formula,data)
}
  

#Q1

print("\n\n\n\n\n\n\n\n\n")

postgroup(diabetes,diabetes$AgeCat)

plotline(diabetes)

#Q2

postgroup(diabetes,diabetes$OutCat)
  
boxgroup(diabetes)


#Q3


analyzeInteraction(diabetes$BloodPressure,diabetes$AgeCat,diabetes$OutCat)


#Q4

analyzeInteractionOne(diabetes$Insulin,diabetes$AgeCat,diabetes)
analyzeInteractionOne(diabetes$Insulin,diabetes$OutCat,diabetes)
analyzeInteraction(diabetes$Insulin,diabetes$AgeCat,diabetes$OutCat,diabetes)



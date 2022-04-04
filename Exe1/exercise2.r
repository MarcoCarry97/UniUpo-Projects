library(car)
library(carData)
library(sandwich)
library(lmtest)
library(RcmdrMisc)

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

posthoc=function(formula,data)
{
  model=aov(formula,data=data) 
  print(shapiro.test(residuals(model))) #normality
  print(dwtest(model,alternative = "two.sided")) #independency
  print(bptest(model)) #omogeneity
  #print(leveneTest(formula,data=data))
}

data=createData(v1,v2,v3)
print("v1 and v2")
posthoc(v1~v2,data)
print("v1 and v3")
posthoc(v1~v3,data)
print("v2 and v3")
posthoc(v2~v3,data)

#PART 2

diabetes=read.csv("diabetes.csv")

catByYears=factor(ifelse(diabetes$Age<=30,"young",
                  ifelse(diabetes$Age<=50,"middle","old")))

#Q1

postgroup=function(cat,data)
{
  print("PREGNANCY")
  posthoc(data$Age~data$Pregnancies,data)
  print("GLUCOSE")
  posthoc(data$Age~data$Glucose,data)
  print("BLOOD PRESSURE")
  posthoc(data$Age~data$BloodPressure,data)
  print("THICKNESS")
  posthoc(data$Age~data$SkinThickness,data)
  print("INSULIN")
  posthoc(data$Age~data$Insulin,data)
  print("BMI")
  posthoc(data$Age~data$BMI,data)
  print("DIABETES FUNCTION")
  posthoc(data$Age~data$DiabetesPedigreeFunction,data)
  print("OUTCOME")
  posthoc(data$Age~data$Outcome,data)
}

postgroup(catByYears,diabetes)

#Q2

#Q3






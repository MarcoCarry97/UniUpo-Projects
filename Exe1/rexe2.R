### Generating Normal random vectors
library(car)
library(carData)
library(sandwich)

v1=rnorm(200, mean=10, sd=50)
v2=rnorm(200, mean=50, sd=50)
v3=rnorm(200, mean=80, sd=50)

plot(density(v1),xlim=c(-200,220),ylim=c(0,0.01),main="Three Normal distributions")
lines(density(v2),col=2)
lines(density(v3),col=3)

v1n=data.frame(x1=v1, x2="v1")
v2n=data.frame(x1=v2, x2="v2")
v3n=data.frame(x1=v3, x2="v3")

??mergeRows
library(RcmdrMisc)
data=mergeRows(v1n, v2n, common.only=FALSE)
data=mergeRows(as.data.frame(data), v3n, common.only=FALSE)
head(data)

posthoc <- function(x,y,data)
{
  AnovaModel <- aov(x ~ y, data=data)
  # Boxplot(x~y,data=data,id=FALSE)
  # dwtest(AnovaModel, alternative ="two.sided")
  # shapiro.test(residuals(AnovaModel))
  # bptest(AnovaModel)
}

### ANOVA on simulated data ####
AnovaModel.1 <- aov(x1 ~ x2, data=data)
summary(AnovaModel.1)
Boxplot(x1~x2,data=data,id=FALSE)
library(lmtest)
dwtest(AnovaModel.1, alternative ="two.sided")

shapiro.test(residuals(AnovaModel.1))

bptest(AnovaModel.1)

posthoc(v1n,v2n,data)

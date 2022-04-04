library(base)
library(summarytools)

data=read.csv("decathlon.csv")


#step a: Analyze the distribution of X100m using boxplog and write conclusions

comp=as.factor(data$Competition)

x100m=data$X100m

a=data.frame(comp,x100m)


#TODO
boxplot(x100m~comp,data=a,main="Competition comparison")

#Conclusion: The mean of x100m is about 11.



#step b: Create a categorical variable from x100m with 11 as cut-off point.
#Then make a crosstable with Competition.
#These two variables are independent?
#test it with the chi-square test
#Write conclusions, check marginal probs.

ma=11

catb=factor(ifelse(x100m>=ma,"more11","less11"))

x=data.frame(catb,comp)
 
cx=table(catb,comp)

mt=margin.table(cx)

lessProb=(cx[1,1] + cx[1,2])/mt
moreProb=1-lessProb

decaProb=(cx[1,1]+cx[2,1])/mt
olymProb=1-decaProb

chi=chisq.test(cx)
#TODO

#step c: Visualize the distribution of the cat. var.
#does it follow a normal distribution?

h=hist(x100m)

plot(density(x100m))
plot(density(data$Long.jump))
plot(density(data$Shot.put))
plot(density(data$High.jump))
plot(density(data$X400m))
plot(density(data$X110m.hurdle))
plot(density(data$Discus))
plot(density(data$Pole.vault))
plot(density(data$Javeline))
plot(density(data$X1500m))

#TODO

#step d: Generate 3 normal variables of length 50:
#the first two must have the same mean but different deviation
#the third one is the opposite: same deviation but different mean
#compare the mean differences using the t-test

size=50

mean1=7

mean2=9

sd1=15

sd2=3

n1=rnorm(size,mean1,sd1)
n2=rnorm(size,mean1,sd2)
n3=rnorm(size,mean2,sd1)

t1=t.test(n1,n2)
t2=t.test(n1,n3)
t3=t.test(n2,n3)


shapiro.test(n1)
#TODO

#step e: Use the t-test to verify if there are differences
#between X100m and X400m

x400m=data$X400m

t4=t.test(x100m,x400m)

#TODO

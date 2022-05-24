# -*- coding: utf-8 -*-
"""
Created on Tue May 17 00:32:11 2022

@author: Marco-PC
"""

def max(a,b):
    if a>=b:
        return a
    return b

def min(a,b):
    if a<b:
        return a
    return b

import pandas as pd
import numpy as np

infectivity=0.42 #first fsctor
contactDay=15 #second factor
recommended=False
fatigue=0.77 #third factor
contained=0.65 #fourth factor

dt=1
numIt=50
alpha=5.0
beta=infectivity*contactDay
#gamma=5
gamma=0.128866
mu=0.2
omicron=fatigue

M=7653845
N=M*(1-contained)
#N=(1-contained)*M
#N=100000

S=N-1
E=0
I=1
R=0
D=0
C=0
L=0


def compute():
    #dS=-beta*S*I/N
    #dE=beta*S*I/N - alpha*E
    #dI=alpha*E-gamma*I
    #dR=gamma*(1-mu)*I
    #dD=gamma*mu*I
    dS=-beta*S*I/N
    dE=beta*S*I/N -alpha*E
    dI=alpha*E-gamma*I
    dR=gamma*(1-mu)*I
    dD=gamma*mu*I
    #dL=fatigue*R
    return dS,dE,dI,dR,dD

def normalize(S,E,I,R,D,N):
    Nt=S+E+I+R+D
    nS=N*S/Nt
    nE=N*E/Nt
    nI=N*I/Nt
    nR=N*R/Nt
    nD=N*D/Nt
    #nL=N*L/Nt
    return nS,nE,nI,nR,nD

Sa=[S]
Ea=[E]
Ia=[I]
Ra=[R]
Da=[D]
Ca=[C]
La=[L]

steps=int(numIt/dt)
    
for i in range(0,steps):
    Nt=S+E+I+R+D
    print(S,E,I,R,D,Nt)
    dS,dE,dI,dR,dD=compute()
    C=N-S
    S=max(S+dS*dt,0)
    E=max(E+dE*dt,0)
    I=max(I+dI*dt,0)
    R=max(R+dR*dt,0)
    D=max(D+dD*dt,0)
    L=R*fatigue
    S,E,I,R,D=normalize(S, E, I, R, D,N)
    
    #S,E,I,R,D=np.round(normalize(S,E,I,R,D,N))
    Sa+=[S]
    Ea+=[E]
    Ia+=[I]
    Ra+=[R]
    Da+=[D]
    Ca+=[C]
    La+=[L]


#for i in range(0,numIt):
   # loop()
    
data=pd.DataFrame()

data.insert(0,"time",np.arange(0,steps+1,1))

data.insert(0,"L",np.array(La))
data.insert(0,"C",np.array(Ca))
data.insert(0,"D",np.array(Da))
data.insert(0,"R",np.array(Ra))
data.insert(0,"I",np.array(Ia))
data.insert(0,"E",np.array(Ea))
data.insert(0,"S",np.array(Sa)) 


data.plot(x="time",y=["S","E","I","R","D","L","C"],kind="line")
#data.plot(x="time",y="E",kind="line")

for label in data.columns:
    if(label!="time"):
        data.plot(x="time",y=label,kind="line")

data.to_excel("./covidsim.xlsx")
data.to_csv("./covidsim.csv")
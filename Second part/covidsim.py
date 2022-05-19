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

dt=1
numIt=50
alpha=5.1
beta=4.3
#gamma=5
gamma=0.1288659794
mu=0.1
N=7653845
#N=100000

S=N-1
E=0
I=1
R=0
D=0

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
    return dS,dE,dI,dR,dD

def normalize(S,E,I,R,D,N):
    Nt=S+E+I+R+D
    nS=N*S/Nt
    nE=N*E/Nt
    nI=N*I/Nt
    nR=N*R/Nt
    nD=N*D/Nt
    return nS,nE,nI,nR,nD

Sa=[S]
Ea=[E]
Ia=[I]
Ra=[R]
Da=[D]

steps=int(numIt/dt)
    
for i in range(0,steps):
    Nt=S+E+I+R+D
    print(S,E,I,R,D,Nt)
    dS,dE,dI,dR,dD=compute()
    S=max(S+dS*dt,0)
    E=max(E+dE*dt,0)
    I=max(I+dI*dt,0)
    R=max(R+dR*dt,0)
    D=max(D+dD*dt,0)
    S,E,I,R,D=normalize(S, E, I, R, D, N)
    
    #S,E,I,R,D=np.round(normalize(S,E,I,R,D,N))
    Sa+=[S]
    Ea+=[E]
    Ia+=[I]
    Ra+=[R]
    Da+=[D]


#for i in range(0,numIt):
   # loop()
    
data=pd.DataFrame()

data.insert(0,"time",np.arange(0,steps+1,1))
data.insert(0,"D",np.array(Da))
data.insert(0,"R",np.array(Ra))
data.insert(0,"I",np.array(Ia))
data.insert(0,"E",np.array(Ea))
data.insert(0,"S",np.array(Sa)) 


data.plot(x="time",y=["S","E","I","R","D"],kind="line")
#data.plot(x="time",y="E",kind="line")

for label in data.columns:
    if(label!="time"):
        data.plot(x="time",y=label,kind="line")

data.to_excel("./covidsim.xlsx")
data.to_csv("./covidsim.csv")
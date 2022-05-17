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

numIt=50

alpha=-4
beta=0.1259
gamma=5
mu=0.002
N=7653845

S=N-1
E=1
I=0
R=0
D=0
    

def compute():
    #dS=-beta*S*I/N
    #dE=beta*S*I/N - alpha*E
    #dI=alpha*E-gamma*I
    #dR=gamma*(1-mu)*I
    #dD=gamma*mu*I
    dS=-beta*S*I/N
    dE=-dS -alpha*E
    dI=-alpha*E+gamma*I
    dR=gamma*(1-mu)*I
    dD=gamma*mu*I
    return dS,dE,dI,dR,dD

Sa=[S]
Ea=[E]
Ia=[I]
Ra=[R]
Da=[D]

    
for i in range(0,numIt):
    Nt=S+E+I+R+D
    print(S,E,I,R,D,Nt)
    dS,dE,dI,dR,dD=compute()
    S=max(S+np.round(dS),0)
    E+=max(E+np.round(dE),0)
    I+=max(I+np.round(dI),0)
    R+=max(R+np.round(dR),0)
    D+=max(D+np.round(dD),0)
    Sa+=[S]
    Ea+=[E]
    Ia+=[I]
    Ra+=[R]
    Da+=[D]
    
data=pd.DataFrame()

data.insert(0,"D",np.array(Da))
data.insert(0,"R",np.array(Ra))
data.insert(0,"I",np.array(Ia))
data.insert(0,"E",np.array(Ea))
data.insert(0,"S",np.array(Sa)) 

data.to_excel("./covidsim.xlsx")
data.to_csv("./covidsim.csv")
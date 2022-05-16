# -*- coding: utf-8 -*-
"""
Created on Tue May 17 00:32:11 2022

@author: Marco-PC
"""

import pandas as pd
import numpy as np
import os

numIt=50

alpha=5.1
beta=0.17
gamma=5
mu=0.002
N=7653845

S=N-1
E=0
I=1
R=0
D=0
    

def compute():
    dS=-beta*S*I/N
    dE=beta*S*I/N - alpha*E
    dI=alpha*E-gamma*I
    dR=gamma*(1-mu)*I
    dD=gamma*mu*I
    return dS,dE,dI,dR,dD

Sa=[S]
Ea=[E]
Ia=[I]
Ra=[R]
Da=[D]
    
for i in range(0,numIt):
    print(S,E,I,R,D)
    dS,dE,dI,dR,dD=compute()
    S+=np.round(dS)
    E+=np.round(dE)
    I+=np.round(dI)
    R+=np.round(dR)
    D+=np.round(dD)
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
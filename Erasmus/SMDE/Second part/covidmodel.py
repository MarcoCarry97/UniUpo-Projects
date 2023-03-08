# -*- coding: utf-8 -*-
"""
Created on Tue May 24 17:19:04 2022

@author: Marco-PC
"""

import numpy as np
import pandas as pd
import random as rand

class Model:
    def __init__(self,factors):
        self.beta=factors["beta"]
        self.recommendation=factors["recommandation"]
        self.containedPercent=factors["containedPercent"]       
        
    def normalize(self,S,E,I,R,D,N):
        Nt=S+E+I+R+D
        nS=N*S/Nt
        nE=N*E/Nt
        nI=N*I/Nt
        nR=N*R/Nt
        nD=N*D/Nt
        return nS,nE,nI,nR,nD
    
    def update(self,S,E,I,R,D,L,C,N,M,alpha,beta,gamma,mu,omega):
        Nt=S+E+I+R+D
        print(S,E,I,R,D,Nt)
        dS=-beta*S*I/N
        dE=beta*S*I/N -alpha*E
        dI=alpha*E-gamma*I
        dR=gamma*(1-mu)*I
        dD=gamma*mu*I
        dL=omega*R
        dC=M-S
        S=max(S+dS,0)
        E=max(E+dE,0)
        I=max(I+dI,0)
        R=max(R+dR,0)
        D=max(D+dD,0)
        L=dL
        #C=max(C+dC,0)
        C=dC
        S,E,I,R,D=self.normalize(S, E, I, R, D, N)
        #C=N*C/Nt
        #C=min(C,N)     
        return S,E,I,R,D,L,C
    
    def execute(self,steps,alpha,gamma,mu,omega,M,num):
        if(self.recommendation):
            omega=0.08
        beta=self.beta
        N=(1-self.containedPercent)*M     
        Sa=[N-1]
        Ea=[0]
        Ia=[1]
        Ra=[0]
        Da=[0]
        Ca=[M-(N-1)]
        La=[0]
        for i in range(0,steps):
            S,E,I,R,D,L,C=self.update(Sa[i],Ea[i],Ia[i],Ra[i],Da[i],La[i],Ca[i],N,M,alpha,beta,gamma,mu,omega)   
            Sa+=[S]
            Ea+=[E]
            Ia+=[I]
            Ra+=[R]
            Da+=[D]
            La+=[L]
            Ca+=[C]        
        self.plotAndSave(steps,Sa,Ea,Ia,Ra,Da,La,Ca,num)
    
    def plotAndSave(self,steps,Sa,Ea,Ia,Ra,Da,La,Ca,num):
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
        data.to_excel("./covidsim-"+str(num)+".xlsx")
        data.to_csv("./covidsim-"+str(num)+".csv")
        
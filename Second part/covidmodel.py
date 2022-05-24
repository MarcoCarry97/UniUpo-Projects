# -*- coding: utf-8 -*-
"""
Created on Tue May 24 17:19:04 2022

@author: Marco-PC
"""

import numpy as np
import pandas as pd

class Model:
    def __init__(self,factors):
        self.infectivity=factors["infectivity"]
        self.contactPerDay=factors["contactsPerDay"]
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
    
    def execute(self,steps,alpha,gamma,mu,N):
        beta=self.infectivity*self.contactPerDay
        S=N-1
        E=0
        I=1
        R=0
        D=0
        C=0
        Sa=[S]
        Ea=[E]
        Ia=[I]
        Ra=[R]
        Da=[D]
        Ca=[C]
        for i in range(0,steps):
            Nt=S+E+I+R+D
            print(S,E,I,R,D,Nt)
            dS=-beta*S*I/N
            dE=beta*S*I/N -alpha*E
            dI=alpha*E-gamma*I
            dR=gamma*(1-mu)*I
            dD=gamma*mu*I
            C=(N-S-E-I-R-D)*self.containedPercent
            S=max(S+dS,0)
            E=max(E+dE,0)
            I=max(I+dI,0)
            R=max(R+dR,0)
            D=max(D+dD,0)
            S,E,I,R,D=self.normalize(S, E, I, R, D,N)
            Sa+=[S]
            Ea+=[E]
            Ia+=[I]
            Ra+=[R]
            Da+=[D]
            Ca+=[C]
        self.plotAndSave(steps,Sa,Ea,Ia,Ra,Da)
    
    def plotAndSave(self,steps,Sa,Ea,Ia,Ra,Da):
        data=pd.DataFrame()

        data.insert(0,"time",np.arange(0,steps+1,1))
        #data.insert(0,"C",np.array(Ca))
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
        
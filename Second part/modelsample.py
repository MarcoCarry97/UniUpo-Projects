# -*- coding: utf-8 -*-
"""
Created on Tue May 24 17:37:23 2022

@author: Marco-PC
"""

import covidmodel as covid

data={
      "infectivity":0.42, #first factor
      "contactsPerDay":15, #second factor
      "containedPercent":0.35, #third factor
      "recommandation":True #fourth factor
      }

dt=1
numIt=50
alpha=5.0
#beta=infectivity*contactDay
#gamma=5
gamma=0.128866
mu=0.2
omicron=0.65

N=7653845

model=covid.Model(data)
model.execute(numIt, alpha, gamma, mu,omicron, N)
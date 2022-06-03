# -*- coding: utf-8 -*-
"""
Created on Tue May 24 17:37:23 2022

@author: Marco-PC
"""

import fullmodel as fm

data={
      #"beta":0.42*15, #first factor
      "beta":0.42*15, #first factor
      "containedPercent":0.35, #second factor
      "recommandation":True #third factor
      }

dt=1
#numIt=10000
alpha=5
#beta=infectivity*contactDay
#gamma=5
gamma=0.13
#gamma=5
mu=0.2
omicron=0.65

N=7653845

numIter=1000
design=fm.FullFractionalDesign()
design.execute(alpha, gamma, mu, omicron, N, numIter)
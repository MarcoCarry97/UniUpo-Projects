# -*- coding: utf-8 -*-
"""
Created on Tue May 24 17:37:23 2022

@author: Marco-PC
"""

import fullmodel as fm

dt=1
alpha=5.5
gamma=1/7.76
mu=0.2
omega=0.85
N=7653845

numIter=200
design=fm.FullFactorialDesign()
design.execute(alpha, gamma, mu, omega, N, numIter)




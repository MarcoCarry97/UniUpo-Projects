# -*- coding: utf-8 -*-
"""
Created on Sat May 21 19:47:50 2022

@author: Marco-PC
"""
from yates import YatesAlgorithm

ya=YatesAlgorithm()
effects=ya.conputeEffects([71,61,90,82,68,61,87,80,61,50,89,83,59,51,85,78], 4)
print(effects)
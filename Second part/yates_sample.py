# -*- coding: utf-8 -*-
"""
Created on Sat May 21 19:47:50 2022

@author: Marco-PC
"""
from yates import YatesAlgorithm

ya=YatesAlgorithm()
effects=ya.conputeEffects([60,72,54,68,52,83,45,80], 3)
print(effects)
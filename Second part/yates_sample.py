# -*- coding: utf-8 -*-
"""
Created on Sat May 21 19:47:50 2022

@author: Marco-PC
"""
from yates import YatesAlgorithm

list1=[2723104,
       886941,
       952996,
       310431,
       2723104,
       886941,
       952996,
       310431]

list2=[6450261,
       5560859,
       2257591,
       1946307,
       607083,
       523375,
       212479,
       183182]

ya=YatesAlgorithm()
effects=ya.conputeEffects(list2, 3)
print("effects: ",effects)
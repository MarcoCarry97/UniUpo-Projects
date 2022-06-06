# -*- coding: utf-8 -*-
"""
Created on Sat May 21 19:47:50 2022

@author: Marco-PC
"""
from yates import YatesAlgorithm

list1=[2723104,#2811795
       886941,#1263427
       952996,#3610045
       310431,#1263427
       2723104,#-1836163
       886941,#-921955
       952996,#-1836163
       310431]#

list2=[6450261,#
       5560859,#
       2257591,#
       1946307,#
       607083,#
       523375,#
       212479,#
       183182]#

list3=[60,72,54,68,52,83,45,80]

ya=YatesAlgorithm()
effects=ya.conputeEffects(list1, 3)
print("effects: ",effects)
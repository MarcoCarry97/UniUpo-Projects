# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 14:23:29 2022

@author: Marco-PC
"""
import random
import itertools
import networkx as nx

def random_num(seed):
    return random.random()%seed

def random_choice(choices):
    return random.choice(choices)

def random_sample(choices, num):
    return random.sample(choices,num)

def random_choices(choices,weights):
    return random.choices()
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 26 15:32:01 2022

@author: Marco-PC
"""

def init_state(G):
    state={}
    for node in G.nodes:
        state[node]="S"
    return state;

def state_transition(G,current,p):
    next_state={}
    for node in G.nodes:
        if current[node]=="S":
            if random.random()<p:
                next_state[node]="I"
                
    
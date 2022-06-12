# -*- coding: utf-8 -*-
"""
Created on Sat Jun 11 01:01:14 2022

@author: Marco-PC
"""

import dlUtils as dl

nn=dl.NeuralNetwork()
nn.generateDataSet([1,1.5],noise=0)
nn.compute()


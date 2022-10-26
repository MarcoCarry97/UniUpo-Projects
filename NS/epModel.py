import networkx as nx
import matplotlib.pyplot as plt
import numpy as np

def get_nodes_of_grade(G,grade):
    res=[]
    for node in G.nodes():
        if(G.degree(node)==grade):
           res+=[node]
    return res

def get_leaves(G):
    return get_nodes_of_grade(G,1)

def max_degree(G):
    res=None
    for node in G.nodes:
        if(res==None):
            res=(node,G.degree(node))
        elif(res[1]<G.degree(node)):
            res=(node,G.degree(node))
    return res
        
def mutual_friends(G,node_1,node_2):
    set_1=set(G[node_1])
    set_2=set(G[node_2])
    return set_1.intersection(set_2)

def draw(g):
    nx.draw(g, with_labels=True, font_weight="bold")
    plt.show()
    
G = nx.Graph()
G.add_edges_from([
        ('a', 'b'),
        ('a', 'd'),
        ('c', 'd'),
    ])
assert set(get_leaves(G)) == {'c', 'b'}



SG = nx.read_adjlist('./datasets/friends.adjlist')
draw(SG)
assert max_degree(SG) == ('Claire', 4)

assert mutual_friends(SG, 'Alice', 'Claire') == {'Frank'}
assert mutual_friends(SG, 'George', 'Bob') == set()
assert mutual_friends(SG, 'Claire', 'George')== {'Dennis', 'Frank'}



draw(G)
draw(SG)

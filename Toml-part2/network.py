
from random import randrange

class Node:
    def __init__(self,next, level):
        self.next=next
        self.previouses=[]
        #if(next!=None):
            #next.printNode()
         #   next.previouses+=[self]
        self.level=level
        self.left=None
        self.right=None   

    def printNode(self):
        print(self)
        print(self.next)
        print(self.previouses)
        print(self.left)
        print(self.right)
        print(self.level)
        print("\n")


class Edge:
    def __init__(self,tail,head):
        self.tail=tail
        self.head=head
     
class Network:
    def __init__(self,numRings,numNeigh):
        self.numRings=numRings
        self.numNeigh=numNeigh #C
        #self.numNodes=(numRings*2+1)**2
        self.root=None
        self.numNodes=0
        
    def randomTopology(self):
        gateway=Node(None,0)
        self.root=gateway
        nodes=[gateway]
        #for d in range(1,self.numRings):
        neighs=[]
        for node in nodes:
            newnodes=[]
            if(node.level<self.numRings): 
                #node.printNode()
                num=randrange(1,self.numNeigh+1)
                for i in range(0,num):
                    #print(len(neighs))
                    #print(neighs)
                    lev=node.level+1
                    if(lev<self.numRings):
                        print("nodo nuovo")
                        self.numNodes+=1
                        neigh=Node(node,node.level+1)
                        node.previouses+=[neigh]
                        newnodes+=[neigh]
                        if(neigh not in neighs):
                            if(len(neighs)>1):
                                neigh.left=neighs[len(neighs)-1]
                                neighs[len(neighs)-1].right=neigh
                            neighs+=[neigh]
            if(len(neighs)>0):
                neighs[0].left=neighs[len(neighs)-1]
                neighs[len(neighs)-1].right=neighs[0]
            nodes+=newnodes

    def connectBounds(self,neighs):
        if(len(neighs)>1):
            start=neighs[0]
            end=neighs[len(neighs)-1]
            end.right=start
            start.left=end

    def printNet(self):
        def recPrintNode(node):
            if(node!=None):
                node.printNode()
                for prev in node.previouses:
                    recPrintNode(prev)
        recPrintNode(self.root)


    
class Routing:
    def __init__(self,net,

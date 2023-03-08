def contaparole(stringa):
    lista=stringa.split()
    dizio={}
    for p in lista:
        if p in dizio:
            dizio[p]+=1
        else:
            dizio[p]=1
    return dizio

def sommadiz(num,dizio):
    somma=0
    for s in dizio:
        if num==len(s):
            somma+=dizio[s]
    return somma
            
def fieraest(lista):
    fiera=[]
    stringa=lista[0]
    for i in range(1,len(lista)):
        for j in range(i-1,i):
            stringa=lista[i]+">"+stringa
        fiera+=[stringa]
    return fiera
            
    

def mancante(nome):
    f=open(nome)
    numeri=[]
    for s in f:
        numeri+=[int(s)]
    f.close()
    numeri.sort
    for i in range(0,len(numeri)):
        if not(i+1 in numeri):
            return i+1
       
def ruota(stri):
    nuovastri=""
    lettera=stri[0]
    for i in range(1,len(stri)):
        nuovastri+=stri[i]   
    nuovastri+=lettera
    return nuovastri

def ruotatutte(stri):
    nuovestri=[stri]
    for i in range(0,len(stri)-1):
        nuovestri+=[ruota(nuovestri[i])]
    return nuovestri
    
def rotazioni(stri):
    listastri=ruotatutte(stri)
    f=open("rotazioni.txt","w")
    for s in listastri:
        f.write(s+"\n")
    f.close()
    return

def spezza(stri):
    a=stri.split()
    goal=a[0].split("-")
    team=a[1].split("-")
    return team[0], int(goal[0]),team[1], int(goal[1])

def ordinateam(nome):
    f=open(nome)
    g=open(nome+".goal","w")
    contat=[]
    strilista=[]
    for s in f:
        team0,goal0,team1,goal1=spezza(s)
        contat+=[goal0+goal1]
        contat.sort(reverse=True)
    for i in range(0,len(contat)):
        strilista=[spezza(f[i])]
        if contat[i]==goal0+goal1:
            g.write(f[i])
    g.close()
    f.close()
    return 
            
    
    

    

    
        

        
        

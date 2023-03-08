def fattoriale(n):
    fatt=1
    for i in range(1,n+1):
        fatt=fatt*i
    return fatt

def elencofatt(n):
    fatt=1
    for i in range(1,n+1):
        print(fattoriale(i))
    return

def sommafatt(n):
    somma=0
    for i in range(1, n+1):
        somma+=fattoriale(i)
    return somma

def numeri(a,b):
    stringa=""
    for i in range(a,b+1):
        stringa+=str(i)
    return stringa

def linee(n):
    stringa="+"
    for i in range(1,n+1):
        stringa=stringa+i*"-"+"+"
    return stringa

def vocale(let):
    assert isinstance(let,str),"non è una stringa"
    assert len(let)==1,"non è una lettera"
    voc="aeiouyAEIOUY"
    for i in range(0,len(voc)):
        if let[0]==voc[i]:
            return True
    return False

def vocali(stri):
    assert isinstance(stri,str),"non è una stringa"
    cont=0
    for i in range(0,len(stri)):
        if vocale(stri[i])==True:
            cont+=1
    return cont

def inverti(stri):
    irts=""
    for i in range(len(stri)-1,-1,-1):
        irts+=stri[i]
    return irts
                   
def potenza2(n):
    potsomma=0
    sommapot=0
    for i in range(1,n+1):
        sommapot+=i**2
        potsomma+=i
    return pow(potsomma,2)-sommapot

def contadiv(n):
    cont=0
    for i in range(1,n+1):
        if n%i==0:
            cont+=1
    return cont

def primo(n):
    if n<2:
        return False
    elif n%2==0:
        if n==2:
            return True
        else:
            return False
    else:
        for i in range(3,n+1,2):
            if contadiv(n)==2:
                return True
    return False

def primopos(n):
    assert isinstance(n,int),"non è un intero"
    pos=0
    for i in range(1,10**7):
        if primo(i)==True:
            pos+=1
        if pos==n:
            return i

def pulista(lista,a,b):
    assert isinstance(lista,list),"non è una lista"
    tot=[]
    for i in range(0,len(lista)):
        if lista[i]<a or lista[i]>b:
            tot+=[lista[i]]
    return tot

def invlis(lista):
    inv=[]
    for i in range(len(lista)-1,-1,-1):
        inv+=[lista[i]]
    return inv

def doppiainv(lista):
    assert isinstance(lista,list),"non è una lista"
    inv=[]
    for i in range(0,len(lista)):
        inv+=[inverti(lista[i])]
    return invlis(inv)
        
def palindromo1(stri):
    if stri==inverti(stri):
        return True
    return False

def palindromo2(stri):
    i=0
    j=len(stri)-1
    while i<=len(stri) and j>=0:
        if stri[i]!=stri[j]:
            return False
        i+=1
        j-=1
    return True

def frasepal(stri):
    senzaspa=""
    for i in range(0,len(stri)):
        if stri[i]!=" ":
            senzaspa+=stri[i]
    return palindromo2(senzaspa)

def visualizza_file(nome):
  assert(isinstance(nome,str))
  f = open(nome);       
  righe = 0
  for s in f:
    print(s[:-1])     
    righe += 1
  f.close()           
  return righe

def nientea(stri):
    nota=""
    for i in range(0,len(stri)):
        if stri[i]=="a" or stri[i]=="A":
            continue
        nota+=stri[i]
    return nota

def noa(nome):
  assert(isinstance(nome,str))
  f = open(nome);
  g= open(nome+".noa"+"w")
  for s in f:
    print(nientea(s),file=g)    
  g.close()
  f.close()           
  return 

def duplica(nome):
  assert(isinstance(nome,str))
  f = open(nome);
  g= open(nome+"."+nome+"w")
  for i in range(0,2):
      for s in f:
        g.write(s)    
  g.close()
  f.close()           
  return 

def lunghe(nome):
  assert(isinstance(nome,str))
  mas=0
  f = open(nome);
  for s in f:
    if(mas<len(s)):
        mas=len(s)
  f.close()
  f = open(nome);
  g= open(nome+".noa"+"w")
  for s in f:
    if len(s)==mas:
        g.write(s)
  g.close()
  f.close() 
  return           

def esercizio13(nome):
    assert(isinstance(nome,str))
    f=open(nome)
    g=open(nome+".clear"+"w")
    tot=0
    tots=""
    for s in f:
        tot+=int(s)
    tots=str(tot)
    return tots[0:10]

def esercizio20(n):
    sfatt=""
    somma=0
    sfatt=str(fattoriale(n))
    for i in range(0,len(sfatt)):
        somma+=int(sfatt[i])
    return somma

def squadre(nome):
    dizio={}
    f=open(nome)
    for s in f:
        if len(s)>3:
            team0,goal0,team1,goal1=spezza(s)
            dizio=aggiorna(dizio,team0,goal0)
            dizio=aggiorna(dizio,team1,goal1)
    f.close()
    return dizio

def spezza(s):
    a=s.split()
    goal=a[0].split("-")
    team=a[1].split("-")
    return team[0],int(goal[0]),team[1],int(goal[1])

def aggiorna(dizio,team,goal):
    if team in dizio:
        dizio[team]+=goal
    else:
        dizio[team]=goal
    return dizio

def classifica(partita):
    punti={}
    f=open(partita)
    for s in f:
        team0,goal0,team1,goal1=spezza(s)
        if goal0>goal1:
            punti=aggiorna(punti,team0,3)
            punti=aggiorna(punti,team1,0)
        elif goal1>goal0:
            punti=aggiorna(punti,team0,0)
            punti=aggiorna(punti,team1,3)
        else:
            punti=aggiorna(punti,team0,1)
            punti=aggiorna(punti,team1,1)
    f.close()
    return punti

def mostra(nome):
    dizio=classifica(nome)
    lista=list(dizio.items())
    stringa=""
    mas,mim=maxmin(lista)
    for i in range(mas,mim-1,-1):
        stringa=str(i)
    for j in range(0,len(lista)):
        stringa=stringa+" "+lista[j]
    return stringa+"\n"

def maxmin(lista):
    mas=-1
    mim=1000
    for s in lista:
        if mas<s[1]:
            mas=s[1]
        if mim>s[1]:
            mim=s[1]
    return mas,mim

def estrai_parole(stringa):
    # converti stringa in minuscolo e mettila in una lista
    lista = [stringa.lower()]
    # spezza la stringa secondo gli spazi e simboli punteggiatura
    for sep in "' .,;:?!\"\n":
      tmp = []
      for s in lista:
        tmp += s.split(sep)
      lista = tmp
    # elimina le parole troppo corte
    return [s for s in lista if len(s)>3]

def ventiparole(nome):
    dizio={}
    lista=[]
    elenco=[]
    f=open(nome)
    for s in f:
        lista+=estrai_parole(s)
    f.close()
    elenco+=conta(lista,dizio)[0:20]
    for s in elenco:
        print(s)
    return

def conta(lista,dizio):
    for s in lista:
        if s in dizio:
            dizio[s]+=1
        else:
            dizio[s]=1
    return sorted(list(dizio.items()),key=secondo,reverse=True)

def secondo(x):
    return x[1]

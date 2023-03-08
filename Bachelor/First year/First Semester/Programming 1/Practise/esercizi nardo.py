def fattoriale(num): #calcola fattoriale
    fatt=1
    for i in range(1,num+1):
        fatt=fatt*i
    return fatt

def elencofat(num): #stampa elenco fattoriali da 1 a num
    for i in range(1,num+1):
        print(fattoriale(i))
    return

def sommafat(num): #somma i fattoriali da 1 a num
    somma=0
    for i in range(1,num+1):
        somma=somma+fattoriale(i)
    return somma

def numeri(a,b): #concatena i numeri da a a b convertendoli in stringa
    stringa=""
    for i in range(a,b+1):
        stringa=stringa+str(i)+" "
    return stringa

def linee(num): #stampa una linea di + e -
    stringa="+"
    for i in range(1,num+1):
        stringa=stringa+i*"-"+"+"
    return stringa

def vocale(stri): # controlla se è una vocale
    vocali="aeiouyAEIOUY"
    for i in range(0,len(vocali)):
        if stri[0]==vocali[i]:
            return True
    return False
        
def vocali(stringa): #conta le vocali in una stringa
    assert isinstance(stringa,str),"Non è una stringa"
    conta=0 #dichiaro un contatore
    for i in range(0,len(stringa)):
        if vocale(stringa[i])==True: #verifico se il carattere è una vocale
            conta+=1
    return conta

def invstr(stringa): #inverte una stringa
    inv=""
    for i in range(len(stringa)-1,-1,-1): #ciclo for che decrementa di 1
        inv+=stringa[i]
    return inv

def sommaquad(num):
    somma=0
    for i in range(1,num+1):
        somma+=i**2
    return somma

def quadsomma(num):
    somma=0
    for i in range(1,num+1):
        somma+=i
    return somma**2
    
def problema6(num):
    tot1=sommaquad(num) #calcola la somma dei quadrati da 1 a num
    tot2=quadsomma(num) #calcola il quadrato della somma da 1 a num
    return tot2-tot1

def problema7(): #verifica numeri primo nella posizione 10001
    conta=0
    for i in range(1,10**9):
        if primo(i)==True: #se è primo, incremento il contatore
            conta+=1
        if conta==10001: #se il contatore è a 10001, restituisco i
            return i

def pulista(lista,num1,num2):
    pulita=[]
    for i in range(0,len(lista)):
        if lista[i]<num1 or lista[i]>num2: #se non é tra num1 e num2, lo aggiungo all lista pulita
            pulita+=[lista[i]]
    return pulita

def invlist(lista): #inverte una lista
    inv=[]
    for i in range(len(lista)-1,-1,-1): #ciclo for che decrementa di 1
        inv+=[lista[i]]
    return inv

def doppiainv(lista): #inverte prima le stringhe e poi la lista
    inv=[]
    for i in range(0,len(lista)):
        inv+=[invstr(lista[i])] #inverto le stringhe e le inserisco nella lista inv
    return invlist(inv) #inverto la lista inv
        
def palindromo1(stri):
    if stri==invstr(stri):
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

def frasepal(stringa):
    senzaspa=""
    for i in range(0,len(stringa)):
        if stringa[i]!=" ":
           senzaspa+=stringa[i]
    return palindromo2(senzaspa)
    
def noa(nome):
    f=open(nome)
    g=open(nome+".noa.txt","w")
    for s in f:
        stri=""
        for c in s:
            if c=="a" or c=="A":
                continue
            stri+=c
        g.write(stri)
    g.close()
    f.close()
    return

def duplica(nome):
    g=open(nome+"."+nome,"w")
    for i in range(0,2):
        f=open(nome)
        for s in f:
            g.write(s)
        f.close()
    g.close()
    return

def maxstr(lista):
    mas=0
    for s in lista:
        if len(s)>mas:
            mas=len(s)
    return mas

def filelung(nome):
    f=open(nome)
    mas=maxstr(f)
    f.seek(0,0)
    g=open(nome+".lunghe.txt","w")
    for s in f:
        if len(s)==mas:
            g.write(s)
    g.close()
    f.close()
    return

def esercizio13(nome):
    f=open(nome)
    somma=0
    conta=0
    for s in f:
        somma+=int(s)
        conta+=1
        if conta==150:
            break
    f.close()
    return str(somma)[0:10]

def esercizio20(num):
    fatt=str(fattoriale(num))
    somma=0
    for c in fatt:
        somma+=int(c)
    return somma

def trovanum(nome):
    f=open(nome)
    i=1
    while(i<=1000):
        for s in f:
            if i+1!=int(s):
                i+=1
            else:
                break
    f.close()
    return s

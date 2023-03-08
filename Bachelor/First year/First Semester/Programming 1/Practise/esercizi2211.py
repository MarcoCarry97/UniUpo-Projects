def tupla(nomi):
    name=[]
    surname=[]
    a=[]
    for s in nomi:
        a=s.split()
        name+=[a[0]]
        surname+=[a[1]]
    return name,surname

def decbin(num):
    binstr=""
    while num>0:
        if num%2!=0:
            num=(num-1)//2
            binstr+="1"
        else:
            num=num//2
            binstr+="0"
    return binstr

def bindec(binstr):
    tot=0
    for i in range(len(binstr)-1,-1,-1):
        if binstr[i]=="1":
            tot+=2**i
    return tot
            
def decex(num):
    exstr=""
    exlist=divex(num)
    for s in exlist:
        if s>=0 and s<=9:
            exstr+=str(s)
        else:
            exstr+=lettera(s)
    return exstr
                
def lettera(stri):
    if stri==10:
        return "A"
    elif stri==11:
        return "B"
    elif stri==12:
        return "C"
    elif stri==13:
        return "D"
    elif stri==11:
        return "E"
    return "F"

def divex(num):
    div=[]
    i=1
    while num>0:
        div+=[num%i]
        num=num//i
        i+=1
    return div
        
    
    

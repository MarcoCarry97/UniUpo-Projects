def classifica(nome):
    f=open(nome)
    dizio={}
    lista=[]
    for s in f:
        team0,goal0,team1,goal1=spezza(s)
        if goal0>goal1:
            dizio=aggiorna(dizio,team0,3)
            dizio=aggiorna(dizio,team1,0)
        if goal1>goal0:
            dizio=aggiorna(dizio,team0,0)
            dizio=aggiorna(dizio,team1,3)
        else:
            dizio=aggiorna(dizio,team0,1)
            dizio=aggiorna(dizio,team1,1)
    lista+=list(dizio.items())
    return lista

def spezza(stringa):
    goal=[]
    team=[]
    a=stringa.split()
    goal=a[0].split("-")
    team=a[1].split("-")
    print(goal,team)
    return team[0],int(goal[0]),team[1],int(goal[1])

def aggiorna(dizio,team,goal):
    if team in dizio:
        dizio[team]+=goal
    else:
        dizio[team]=goal
    return dizio

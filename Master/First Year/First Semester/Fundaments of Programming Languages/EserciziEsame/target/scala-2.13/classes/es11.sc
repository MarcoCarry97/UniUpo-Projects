val paola =("Paola", true,Nil)
val andrea =("Andrea", true,List(paola))
val peter =("Peter", false,Nil)
val giulia =("Giulia", true, List(paola, peter))
val persone = List(paola, peter, giulia)

val startWithChar:(List[(String,Boolean,List[Any])],Char)=>List[(String,Boolean,List[Any])]=(list,c)=>
{
  for(person<- list
      if person._1.charAt(0)==c)
    yield person;
}

val motherSon:List[(String,Boolean,List[(String,Boolean,List[Any])])]=>List[(String,String)]=(list)=>
{
  for(person<- list;
      son <- person._3)
    yield (person._1,son._1)
}

startWithChar(persone,'P')
motherSon(persone)
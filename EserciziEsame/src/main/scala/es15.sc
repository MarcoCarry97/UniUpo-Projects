

val tryVal:(=> Int)=>Option[Int] =(a)=>
  {
    try Some(a)
    catch { case e: Exception => None }
  }

val sequence:List[Option[Int]]=>Option[List[Int]]=(list)=>
{
  list match
  {
    case Nil => Some(List())
    case None::tail => None
    case Some(value)::tail =>{
      val tmp=sequence(tail)
      if(tmp.isDefined) Some(value::tmp.get)
      else None
    }
  }
}

sequence(List(Some(1),Some(2),Some(77)))
sequence(List(Some(1),None,Some(77)))

val parseInts:List[String]=>Option[List[Int]]=(list)=>
{
  sequence(for(value <- list) yield tryVal(value.toInt))
}

parseInts (List("1","2","77"))
parseInts (List("1","due","77"))
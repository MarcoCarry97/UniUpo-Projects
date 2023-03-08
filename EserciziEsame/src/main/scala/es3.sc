val chars:(List[Char])=>Tuple5[Int,Int,Int,Int,Int]=(list)=>
{
  def charAux(l:List[Char],res:Tuple5[Int,Int,Int,Int,Int]):Tuple5[Int,Int,Int,Int,Int]=
  {
    l match
    {
      case Nil=> res;
      case 'a'::tail => charAux(tail,Tuple5(res._1+1,res._2,res._3,res._4,res._5))
      case 'e'::tail => charAux(tail,Tuple5(res._1,res._2+1,res._3,res._4,res._5))
      case 'i'::tail => charAux(tail,Tuple5(res._1,res._2,res._3+1,res._4,res._5))
      case 'o'::tail => charAux(tail,Tuple5(res._1,res._2,res._3,res._4+1,res._5))
      case 'u'::tail => charAux(tail,Tuple5(res._1,res._2,res._3,res._4,res._5+1))
      case _::tail => charAux(tail,Tuple5(res._1,res._2,res._3,res._4,res._5))
    }
  }
  charAux(list,Tuple5(0,0,0,0,0))
}

chars(List[Char]('a','b','e','i','a','c'))
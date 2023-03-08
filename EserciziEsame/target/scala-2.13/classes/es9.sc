val convertLeft:List[Int]=>Int=(bin)=>
{
  bin.foldLeft(0)((acc,x)=>acc+(acc+x)*2*x)
}

val convertRight:List[Int]=>Int=(bin)=>
{
  bin.foldRight(0)((x,acc)=>acc*2+x)
}

convertLeft(List(1,0,1,0,1,0))
convertRight(List(1,0,1,0,1,0))
convertLeft(List(0,1,1,1))
convertRight(List(0,1,1,1))
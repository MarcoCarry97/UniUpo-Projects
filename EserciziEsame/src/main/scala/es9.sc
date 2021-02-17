val convertLeft:List[Int]=>Int=(bin)=>
{
  var pos=0;
  bin.foldLeft(0)((acc,x)=>{
    var p=pos;
    pos=pos+1
    acc+x*math.pow(2,p).toInt
  })
}

val convertRight:List[Int]=>Int=(bin)=>
{
  bin.foldRight(0)((x,acc)=>acc*2+x)
}

convertLeft(List(1,0,1,0,1,0))
convertRight(List(1,0,1,0,1,0))
convertLeft(List(0,1,1,1))
convertRight(List(0,1,1,1))
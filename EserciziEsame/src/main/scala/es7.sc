val fact:Int=>BigInt=(n)=>
{
  1.to(n).reduce[Int](_*_)
}

fact(10)
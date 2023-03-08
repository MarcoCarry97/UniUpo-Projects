val fib:BigInt=>BigInt=(n)=>
{
  def fibAux(m:BigInt,prev:BigInt,acc:BigInt):BigInt=
  {
    if(m==0) acc;
    else fibAux(m-1,acc,acc+prev);
  }
  fibAux(n-1,0,1)
}

fib(1000000)
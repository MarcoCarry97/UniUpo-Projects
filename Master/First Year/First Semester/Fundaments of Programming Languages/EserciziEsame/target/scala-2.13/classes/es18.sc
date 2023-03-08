class Stack[+T](list:List[T])
{
  def this()=this(List())

  def push[E>:T](value:E):Stack[E]=Stack[E](value::list)

  def pop[E>:T]():Stack[E]=list match
  {
    case Nil=>throw new IllegalStateException("Empty stack")
    case _::tail=>Stack[E](tail)
  }

  def top[E>:T]():E=list match
  {
    case Nil=> throw new IllegalStateException("Empty stack")
    case head::_=>head;
  }

  def isEmpty:Boolean=list.isEmpty

}

object Stack
{
  def apply[E](): Stack[E] = new Stack[E]()

  def apply[E](list: List[E]): Stack[E] = new Stack[E](list)

  def unapply[E](arg: Stack[E]): Option[List[E]] =
  {
    def aux(s:Stack[E]):List[E]={
      if(s.isEmpty) List()
      else s.top()::aux(s.pop())
    }
    Some(aux(arg))
  }
}

var s=Stack[Int]();
s.isEmpty
try s.pop()
catch
{
  case e:IllegalStateException=>println(e.getMessage)
}
try s.top()
catch
{
  case e:IllegalStateException=>println(e.getMessage)
}

s=s.push(1).push(2);
s.isEmpty
println(s.top())
s=s.pop()
println(s.top())
println(s.push(new Object()).top())
s=s.pop()
s.isEmpty
var opt:Option[List[Int]]=Stack.unapply(s.push(1).push(2).push(3))

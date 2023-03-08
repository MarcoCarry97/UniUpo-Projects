
class Rational(n: Int, d: Int) {
  require(d != 0)
  private val m = mcd(n.abs, d.abs)
  val numer = n / m
  val denom = d / m
  def this(n: Int) = this(n, 1)
  def + (that: Rational): Rational =
    new Rational(
      numer * that.denom + that.numer * denom,
      denom * that.denom
    )
  def + (that:Int):Rational =Rational(numer+that*denom,denom)
  def * (that:Rational):Rational = Rational(numer*that.numer,denom*that.denom)
  def * (that:Int):Rational = Rational(numer*that,denom)
  override def toString = numer +"/"+ denom
  private def  mcd(a: Int, b: Int): Int =
  {
    var list=for(i <- 1.to(math.min(a,b)) if(a%i==0 && b%i==0)) yield i
    list.reduce((a,b)=>math.max(a,b))
  }
}

object Rational
{
  def apply(n: Int, d: Int): Rational = new Rational(n, d)

  def unapply(arg: Rational): Option[(Int, Int)] = Some((arg.numer,arg.denom))
}

var r1=Rational(10,5)
var r2=Rational(7,2)
r1+r2
r1*r2
r1*5
r2+3
var r3=r1*r2+r1
var r4=r2*2+4
r3+r4
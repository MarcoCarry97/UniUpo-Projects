abstract class Expr
{
  def simplify():Expr;
}
case class Var(name: String) extends Expr {
  override def simplify() = Var(name)

  override def toString: String = name
}
case class Number(num: Double) extends Expr {
  override def simplify() = Number(num)

  override def toString: String = num.toString
}
case class UnOp(operator: String, arg: Expr) extends Expr {
  override def simplify() =
    {
      var tmp=arg.simplify()
      UnOp("-",tmp) match
      {
        case UnOp("-",UnOp("-",expr))=>expr
        case UnOp("-",expr)=>UnOp("-",expr)
      }
    }

  override def toString: String = " ( "+operator+" "+arg.toString+" ) ";
}
case class BinOp(operator: String,
                 left: Expr, right: Expr) extends Expr {
  override def simplify() = {
    var l=left.simplify()
    var r=right.simplify()
    BinOp(operator,l,r) match {
      case BinOp("+",left,Number(0))=>left
      case BinOp("+",Number(0),right)=>right
      case BinOp("*",left,Number(1))=>left
      case BinOp("*",Number(1),right)=>right
      case BinOp("*",_,Number(0))=>Number(0)
      case BinOp("*",Number(0),_)=>Number(0)
      case BinOp(op,left,right) => BinOp(op,left,right)
    }
  }

  override def toString: String = " ( "+left.toString+" "+operator+" "+right.toString+" ) "
}

var unop:Expr=UnOp("-",UnOp("-",Number(1)))
var binOp:Expr=BinOp("+",BinOp("+",unop,Var("x")),Var("y"))
var bin2:Expr=BinOp("*",binOp,binOp)
var bin3=BinOp("*",Number(1),bin2)
var bin4=BinOp("+",Number(0),BinOp("*",Var("z"),Number(0)))
var bin5=BinOp("+",UnOp("-",BinOp("+",Number(0),UnOp("-",Var("x")))),Var("z"))
var bin6=BinOp("*",Var("x"),BinOp("+",Var("y"),BinOp("*",Var("z"),Var("x"))))
var bin7=BinOp("+",Var("x"),BinOp("*",Var("y"),Number(0)))
var bin8=BinOp("*",Number(7),BinOp("*",Var("x"),Var("y")))
var bin9=BinOp("+",Var("x"),BinOp("+",Var("y"),Var("z")))

unop.simplify()
binOp.simplify()
bin2.simplify()
bin3.simplify()
bin4.simplify()
bin5.simplify()
bin6.simplify()
bin7.simplify()
bin8.simplify()
bin9.simplify()

var simplify:Expr=>Expr=(expr)=>
{
  expr match {
    case Var(name)=>Var(name)
    case Number(num)=>Number(num)
    case BinOp(op,left,right)=>{
      var l=simplify(left)
      var r=simplify(right)
      BinOp(op,l,r) match
      {
        case BinOp("+",left,Number(0))=>left
        case BinOp("+",Number(0),right)=>right
        case BinOp("*",left,Number(1))=>left
        case BinOp("*",Number(1),right)=>right
        case BinOp("*",_,Number(0))=>Number(0)
        case BinOp("*",Number(0),_)=>Number(0)
        case BinOp(op,left,right) => BinOp(op,left,right)
      }
    }
    case UnOp(op,e)=>
    {
      var x=simplify(e)
      UnOp(op,x) match
      {
        case UnOp("-",UnOp("-",e))=>e
        case UnOp(op,e)=>UnOp(op,e)
      }
    }
    case expr: Expr=>expr
  }
}

simplify(unop)
simplify(binOp)
simplify(bin2)
simplify(bin3)
simplify(bin4)
simplify(bin5)
simplify(bin6)
simplify(bin7)
simplify(bin8)
simplify(bin9)
package es15

import scala.io.Source

object Main15 extends App
{
  val divide:String=>Map[String,Int]= (name)=>
  {
    def divideAux(list:List[String],acc:Map[String,Int]):Map[String,Int]={
      list match
      {
        case Nil=>acc;
        case head::tail=>{
          if(acc.contains(head)) divideAux(tail,acc+(head->(acc.get(head).get+1)));
          else divideAux(tail,acc+(head->1));
        }
      }
    }
    var lines:List[String]=Source.fromFile(name).getLines().toList
    var seps:Array[Char]=Array(',',';',' ')
    var words:List[String]=for(line<-lines;word<-line.split(seps); if(!word.trim().equals(""))) yield word.trim();
    divideAux(words,Map())
  }

  val frequencies:String=>List[(String,Int)]=(name)=>
  {
    divide(name).toList.sortWith((a,b)=>a._2<=b._2)

  }

  println(frequencies("sample.txt"))
}

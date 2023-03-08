package es19.Main

import java.io.{File, PrintWriter}

trait Logger {
  def log(msg: String):Unit // Un metodo astratto
}

class Conto (sIn: Double) {
  protected var saldo = sIn
  def preleva (x: Double)={
    if (x<=saldo) {saldo -= x;Some(x)}
    else None
  }
  // altri metodi della classe Conto
}

trait ConsoleLogger extends Logger {
  def log(msg: String):Unit = { println(msg) }
}

trait FileLogger extends Logger {
  var fileName="app.log"
  def log(msg: String):Unit = {
    var out=new PrintWriter(fileName)
    out.println(s"# ${java.time.Instant.now()}")
    out.println(msg);
    out.flush()
  }
}

trait CeasarLogger extends ConsoleLogger with FileLogger
{
  var shift=3

  def ceasar(s:String):String= for(c:Char <- s) yield (c+shift).toChar

  override def log(msg: String): Unit = super.log(ceasar(msg))
}

class ContoConConsoleLog(sIn:Double) extends Conto(sIn) with ConsoleLogger {
  override def preleva (x: Double)={
    if (x<=saldo) {saldo -= x;Some(x)}
    else {log("Saldo insufficiente");None}
  }
}

abstract class ContoConLog(sIn:Double) extends Conto(sIn) with Logger{
  override  def preleva (x: Double)={
    if (x<=saldo) {saldo -= x;Some(x)}
    else {
      log("Saldo insufficiente");None
    }
  }
}



trait TimestampLogger extends ConsoleLogger {
  override def log(msg: String):Unit ={
    super.log(s"${java.time.Instant.now()} $msg")
  }
}

/*trait ShortLogger extends ConsoleLogger {
  override def log(msg: String):Unit = {
    super.log(if (msg.length <= 15) msg else s"${msg.substring(0, 12)}...")
  }
}*/

trait ShortLogger extends Logger {
  var maxLength:Int = 10//un campo concreto
  abstract override def log(msg: String):Unit= {
    super.log(
      if (msg.length <= maxLength) msg
      else s"${msg.substring(0, maxLength - 3)}...")}
}


object Main extends App
{
  val conto = new ContoConLog(100) with ConsoleLogger

  conto.preleva(150)
  var contoCeasar=new ContoConConsoleLog(1000) with CeasarLogger
  contoCeasar.shift=5
  contoCeasar.log("Prova Ceasar")

  var contoFileCeasar=new ContoConConsoleLog(100) with CeasarLogger
  contoFileCeasar.fileName="conto.log"
  conto.preleva(200)

  var contoShort=new ContoConConsoleLog(124) with TimestampLogger with ShortLogger
  contoShort.preleva(200)

  var contoTime=new ContoConConsoleLog(124) with CeasarLogger with TimestampLogger with ShortLogger
  contoTime.maxLength=8;
  contoTime.fileName="contotime.log"
  contoTime.shift=2
  contoTime.preleva(1)
  contoTime.preleva(1234)

  var contoConsoleShort=new ContoConConsoleLog(124) with ConsoleLogger with ShortLogger
  contoConsoleShort.preleva(1234)
}

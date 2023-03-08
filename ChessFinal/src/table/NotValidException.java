/**
 * Eccezione sollevata quando si verifica un'avvenimento inatteso
 */





package table;

public class NotValidException extends Exception
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 8482777067497769509L;
	String msg;
	/**
	 * Costruttore
	 * 
	 * @param msg Messaggio da visulizzare
	 */
	public NotValidException(String msg)
	{
		super(msg);
		this.msg=msg;
	}
	/**
	 * Costruttore
	 */
	public NotValidException()
	{
		super("Posizione non valida");
	}
	/**
	 * Ritorna il messaggio dell'errore
	 * 
	 * @return Stringa
	 */
	public String getMessage()
	{
		return msg;
	}
}

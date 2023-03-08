/**
 * Eccezione sollevata quando si verifica un errore in qualche formato di lettura
 */


package table;

public class FormatException extends Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 6434680472554050027L;
	String msg;
	
	/**
	 * Costruttore
	 * @param msg messaggio da visualizzare
	 */
	public FormatException(String msg)
	{
		super(msg);
		this.msg=msg;
	}
	/**
	 * Costruttore
	 */
	public FormatException()
	{
		super("Posizione non valida");
	}
	/**
	 * Ritorna il messaggio di errore
	 * 
	 * @return Stringa
	 */
	public String getMessage()
	{
		return msg;
	}
}

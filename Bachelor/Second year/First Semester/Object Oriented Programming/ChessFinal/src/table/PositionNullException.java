/**
 * Eccezione sollevata quando l'elemento non ha una posizione
 */



package table;

public class PositionNullException extends Exception {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -5081331851580675705L;
	String msg;
	/**
	 * Costruttore
	 */
	public PositionNullException(){
		super("L'elemento provato a catturare non ha una posizione");
	}
	/**
	 * Costruttore
	 * @param msg messaggio da visualizzare
	 */
	public PositionNullException(String msg) {
		super(msg);
		this.msg = msg;
	}
	/**
	 * Ritorna il messaggio di errore
	 * @return Stringa
	 */
	public String getMsg() {
		return msg;
	}
}

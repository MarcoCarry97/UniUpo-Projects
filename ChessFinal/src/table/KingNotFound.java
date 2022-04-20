/**
 * Eccezione lanciata quando non viene trovato un re sulla scacchiera
 */


package table;

public class KingNotFound extends Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 6712896935956668046L;
	
	String msg;
	
	/**
	 * Costruttore
	 */
	public KingNotFound(){
		super("Re non trovato");
	}
	/**
	 * Costruttore
	 * @param msg messaggio da visualizzare
	 */
	public KingNotFound(String msg) {
		super(msg);
		this.msg = msg;
	}
	/**
	 * Ritorna il messaggio
	 * @return Stringa
	 */
	public String getMessage() {
		return msg;
	}
}

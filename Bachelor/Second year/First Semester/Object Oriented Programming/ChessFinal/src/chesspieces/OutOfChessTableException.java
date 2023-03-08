/**
 * Eccezione sollevata quando si prova a posizionare un elemento fuori dalla ChessTable
 */

package chesspieces;

public class OutOfChessTableException extends Exception {
	
	private static final long serialVersionUID = 2490726129606029721L;
	String msg;
	
	/**
	 * Costruttore
	 */
	public OutOfChessTableException(){
		super("Posizionato un pezzo fuori dalla scacchiera");
	}
	
	/**
	 * Costruttore
	 * @param msg messaggio da visualizzare
	 */
	public OutOfChessTableException(String msg) {
		super(msg);
		this.msg = msg;
	}
	
	/**
	 * Ritorna il messaggio all'interno dell'eccezione
	 */
	public String getMessage() {
		return msg;
	}
}

/**
 * Elemento Bishop (Alfiere)
 */

package chesspieces;

import java.util.ArrayList;

import table.ChessTable;
import table.Colour;
import table.Position;

public class Bishop extends Element
{	
	/**
	 * Costruttore
	 * @param colour colore che assume il Bishop
	 * @param p posizione iniziale di Bishop
	 * @param CT ChessTable a cui appartiene Bishop
	 * @param numPastMoves numero di mosse effettuate dal Bishop
	 * @throws OutOfChessTableException se si tenta di posizionare il Bishop fuori dai range della ChessTable
	 */
	public Bishop(Colour colour, Position p,ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		super(colour,p,CT, numPastMoves);
	}
	
	/**
	 * Costruttore
	 * @param colour colore che assume il Bishop
	 * @param p posizione iniziale di Bishop
	 * @param CT ChessTable a cui appartiene Bishop
	 * @throws OutOfChessTableException se si tenta di posizionare il Bishop fuori dai range della ChessTable
	 */
	public Bishop(Colour colour, Position p,ChessTable CT) throws OutOfChessTableException
	{
		this(colour,p,CT, 0);
	}
	
	/**
	 * Costruttore
	 * @param e Bishop da copiare
	 * @throws OutOfChessTableException se si tenta di posizionare il Bishop fuori dai range della ChessTable
	 */
	public Bishop(Bishop e ) throws OutOfChessTableException {
		this(e.getColour(),e.begin,e.CT);
	}
	
	/**
	 * Imposta le posizioni possibili senza considerare un possibile scacco al proprio re
	 */
	public void setPositionBasic()
	{
		possiblePos= new ArrayList<Position>();
		set(1,1);
		set(1,-1);
		set(-1,1);
		set(-1,-1);
		possiblePos.remove(begin);
		//System.out.println(possiblePos.toString());
	}

	/**
	 * Ritorna la stringa "BISHOP"
	 * @return "BISHOP"
	 */
	@Override
	public String getType()
	{
		return "BISHOP";
	}
	/**
	 * Ritorna il simbolo di Bishop
	 * @return 'B' o 'b'
	 */
	public char getSymbol()
	{
		if (colour.equals(Colour.WHITE)) return 'B';
		else return 'b';
	}
	@Override
	protected boolean validDirection(Position p)
	{
		return begin.sameDiagonal(p);
	}
}

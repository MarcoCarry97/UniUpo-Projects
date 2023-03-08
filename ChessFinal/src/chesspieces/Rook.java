/**
 * Elemento Rook (Torre)
 */

package chesspieces;

import java.util.ArrayList;

import table.ChessTable;
import table.Colour;
import table.Position;

public class Rook extends Element
{
	/**
	 * Costruttore
	 * @param colour colore di Rook
	 * @param p posizione di Rook
	 * @param CT scacchiera a cui appartiene Rook
	 * @throws OutOfChessTableException se si tenta di posizionare la Rook fuori dalla scacchiera
	 */
	public Rook(Colour colour,Position p,ChessTable CT) throws OutOfChessTableException
	{
		this(colour, p, CT,0);
	}
	/**
	 * Costruttore
	 * @param colour colore di Rook
	 * @param p posizione di Rook
	 * @param CT scacchiera a cui appartiene Rook
	 * @param numPastMoves numero di mosse già effettuate di Rook
	 * @throws OutOfChessTableException se si tenta di posizionare la Rook fuori dalla scacchiera
	 */
	public Rook(Colour colour,Position p,ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		super(colour, p, CT, numPastMoves);
	}
	/**
	 * Costruttore
	 * @param e Rook da copiare
	 * @throws OutOfChessTableException Se si prova a posizionare la Rook fuori dalla ChessTable
	 */
	public Rook(Rook e) throws OutOfChessTableException {
		this(e.getColour(),e.begin,e.CT);
	}

	/**
	 * Ritorna "ROOK"
	 * @return "ROOK
	 */
	@Override
	public String getType()
	{
		return "ROOK";
	}
	/**
	 * Ritorna il simbolo di Rook
	 * @return 'R' o 'r'
	 */
	public char getSymbol() {
		if (colour.equals(Colour.WHITE)) return 'R';
		else return 'r';
	}
	
	/**
	 * Imposta le posizioni di Rook senza considerare eventuali scacchi matti
	 */
	public void setPositionBasic()
	{
		possiblePos=new ArrayList<Position>();
		set(0,1);
		set(1,0);
		set(0,-1);
		set(-1,0);
		possiblePos.remove(begin);
	}

	@Override
	protected boolean validDirection(Position p)
	{
		return begin.sameLine(p) || begin.sameColumn(p);
	}
}

/**
 * Element Queen (Regina)
 */

package chesspieces;

import java.util.ArrayList;

import table.ChessTable;
import table.Colour;
import table.Position;

public class Queen extends Element
{

	/**
	 * Costruttore
	 * @param colour colore della Queen
	 * @param p posizione di Queen
	 * @param CT ChessTable a cui appartiene la Queen
	 * @param numPastMoves Numero di mosse già effettuate
	 * @throws OutOfChessTableException Se il pezzo viene messo fuori dai range della scacchiera
	 */
	public Queen(Colour colour, Position p, ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		super(colour,p,CT,numPastMoves);
	}
	
	/**
	 * Costruttore
	 * @param colour colore della Queen
	 * @param p posizione di Queen
	 * @param CT ChessTable a cui appartiene la Queen
	 * @throws OutOfChessTableException Se il pezzo viene messo fuori dai range della scacchiera
	 */
	public Queen(Colour colour, Position p, ChessTable CT) throws OutOfChessTableException
	{
		this(colour,p,CT,0);
	}
	
	/**
	 * Costruttore
	 * @param e Queen da copiare
	 * @throws OutOfChessTableException Se il pezzo viene messo fuori dai range della scacchiera
	 */
	public Queen(Queen e) throws OutOfChessTableException {
		this(e.getColour(),e.begin,e.CT);
	}

	/**
	 * Ritorna "QUEEN"
	 * @return "QUEEN"
	 */
	@Override
	public String getType()
	{
		return "QUEEN";
	}
	
	/**
	 * Ritorna il simbolo di Queen
	 * @return 'K' o 'k'
	 */
	public char getSymbol()
	{
		if (colour.equals(Colour.WHITE)) return 'Q';
		else return 'q';
	}
	
	@Override
	protected boolean validDirection(Position p)
	{
		return begin.sameDiagonal(p) || begin.sameColumn(p) || begin.sameLine(p);
	}
	
	/**
	 * Imposta le posizioni possibili di Queen senza considerare che essere potrebbero portare a uno scacco matto
	 */
	@Override
	public void setPositionBasic()
	{
		possiblePos = new ArrayList<Position>();
		set(1,1);
		set(1,-1);
		set(-1,1);
		set(-1,-1);
		set(1,0);
		set(0,1);
		set(0,-1);
		set(-1,0);
		possiblePos.remove(begin);
	}
}

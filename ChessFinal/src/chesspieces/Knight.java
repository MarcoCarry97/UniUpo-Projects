/**
 * Elemento Knight (Cavallo)
 */

package chesspieces;

import java.util.ArrayList;

import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public class Knight extends Element
{
	
	//ArrayList<Position> possiblePos;
	

	/**
	 * Costruttore
	 * @param colour Colore di Knight
	 * @param p posizione di Knight
	 * @param CT ChessTable a cui appartiene Knight
	 * @param numPastMoves numero di mosse effettuate
	 * @throws OutOfChessTableException se si prova a posizionare il Knight fuori dalla ChessTable
	 */
	public Knight(Colour colour,Position p,ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		super(colour,p,CT,numPastMoves);
	}
	
	/**
	 * Costruttore
	 * @param colour Colore di Knight
	 * @param p posizione di Knight
	 * @param CT ChessTable a cui appartiene Knight
	 * @throws OutOfChessTableException se si prova a posizionare il Knight fuori dalla ChessTable
	 */
	public Knight(Colour colour,Position p,ChessTable CT) throws OutOfChessTableException
	{
		this(colour,p,CT,0);
	}
	/**
	 * Costruttore
	 * @param e Knight da copiare
	 * @throws OutOfChessTableException se si prova a posizionare il Knight fuori dalla ChessTable
	 */
	public Knight(Knight e) throws OutOfChessTableException
	{
		this(e.getColour(),e.begin,e.CT);
	}
	
	/**
	 * Ritorna "KNIGHT"
	 * @return "KNIGHT"
	 */
	@Override
	public String getType()
	{
		return "KNIGHT";
	}
	
	/**
	 * Ritorna il simbolo di Knight
	 * @return "H" o "h"
	 */
	public char getSymbol()
	{
		if (colour.equals(Colour.WHITE)) return 'H';
		else return 'h';
	}
	
	/**
	 * Imposta le posizioni senza considerare eventuali scacchi matti causati dalla mossa
	 */
	public void setPositionBasic()
	{
		possiblePos= new ArrayList<Position>();
		int a=2, b=1;
		Position p;
		p=new Position(begin.getLine()+a,begin.getColumn()+b);
		AddToPositionBasicIfPossible(p);
		p= new Position(begin.getLine()+a,begin.getColumn()-b);
		AddToPositionBasicIfPossible(p);
		p= new Position(begin.getLine()-a,begin.getColumn()+b);
		AddToPositionBasicIfPossible(p);
		p= new Position(begin.getLine()-a,begin.getColumn()-b);
		AddToPositionBasicIfPossible(p);
		a=1;
		b=2;
		p= new Position(begin.getLine()+a,begin.getColumn()+b);
		AddToPositionBasicIfPossible(p);
		p= new Position(begin.getLine()+a,begin.getColumn()-b);
		AddToPositionBasicIfPossible(p);
		p= new Position(begin.getLine()-a,begin.getColumn()+b);
		AddToPositionBasicIfPossible(p);
		p =new Position(begin.getLine()-a,begin.getColumn()-b);
		AddToPositionBasicIfPossible(p);
	}
	
	private void AddToPositionBasicIfPossible(Position p) {
		if (CT.isInRange(p)&&((CT.isFree(p))||(eatable(p)==EAT))) possiblePos.add(p);
	}
	
	/**
	 * Prova a muovere Knight in p
	 * @param p posizione verso cui si prova a muovere il Knight
	 */
	@Override
	public void moveTo(Position p) throws NotValidException, KingNotFound, OutOfChessTableException, PositionNullException
	{
		setPosition();
		switch(isValid(p))
		{
			case(EAT): eat(p); break;
			case(FREESQUARE): CT.put(begin, p); break;
			default: throw new NotValidException("Posizione non valida");
		}
		CT.changeTurn();
	}
	
	/**
	 * Prova a muovere Knight nella posizione indicata da line e column
	 * @param line riga della posizione verso cui si prova a muovere il Knight
	 * @param column colonna della posizione verso cui si prova a muovere il Knight
	 */
	@Override
	public void moveTo(int line, int column) throws NotValidException, KingNotFound, OutOfChessTableException, PositionNullException
	{
		moveTo(new Position(line,column));
	}

	@Override
	protected int isValid(Position p)
	{
		if(!possiblePos.contains(p)) return -1;
		else if(CT.isFree(p)) return 0;
		else return eatable(p);
	}
	
	@Override
	protected boolean validDirection(Position p)
	{
		throw new UnsupportedOperationException();
	}
}

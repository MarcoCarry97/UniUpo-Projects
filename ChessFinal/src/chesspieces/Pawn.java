/**
 * Element Pawn (Pedone)
 */


package chesspieces;

import java.util.ArrayList;

import jbook.util.Input;
import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public class Pawn extends Element
{
	private final int ENPASSANT=2;
	private int end;
	private final Position START;
	
	
	/**
	 * Imposta le posizioni verso cui è possibile spostarsi senza causare uno scacco matto
	 */
	public void setPosition() throws KingNotFound, OutOfChessTableException
	{
		possiblePos=new ArrayList<Position>();
		int color=1;;
		if(colour.equals(Colour.BLACK)) color=-1;
		King k = CT.findKing(colour);
		for(int i=-1;i<2;i++)
		{
			Position p= new Position(begin.getLine()+color, begin.getColumn()+i);
			if((CT.isInRange(p)) && (!k.isTrap(p, this)))
			{
				if(CT.isFree(p))
				{
					
					if((eatable(p)==ENPASSANT)) possiblePos.add(p);
					else if(begin.sameColumn(p)) possiblePos.add(p);
				}
				else if(eatable(p)==EAT) possiblePos.add(p);
			}
		}
		if(numPastMoves==0)
		{
			Position p= new Position(begin.getLine()+2*color, begin.getColumn());
			if((noObstacles(p)!=POSEXC) &&(CT.isInRange(p)) && (!k.isTrap(p, this))) possiblePos.add(p); 
		}
	}

	public Pawn(Colour colour,Position place, ChessTable CT) throws OutOfChessTableException
	{
		this(colour,place,place,CT);
	}
	
	public Pawn(Colour colour, Position place, Position start, ChessTable CT) throws OutOfChessTableException
	{
		this(colour,place,start,CT,0);
	}
	
	public Pawn(Colour colour, Position place, Position start, ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		super(colour,place,CT,numPastMoves);
		this.START=new Position(start);
		if(colour.equals(Colour.WHITE)) end=7;
		else end=0;
	}
	
	public Pawn(Pawn e) throws OutOfChessTableException
	{
		this(e.getColour(),e.begin,e.CT);
	}
	
	@Override
	public String toString()
	{
		return (getType()+" "+getColour()+" "+begin.toString()+" "+START.toString()+ " "+numPastMoves);
	}
	
	@Override
	public String getType()
	{
		return "PAWN";
	}
	
	public char getSymbol()
	{
		if (colour.equals(Colour.WHITE)) return 'P';
		else return 'p';
	}
	
	public int numMoves()
	{
		return numPastMoves;
	}
	
	@Override
	public void moveTo(Position p) throws NotValidException, KingNotFound, OutOfChessTableException, PositionNullException
	{
		setPosition();
		switch(isValid(p))
		{
			case(EAT): eat(p); incMoves(); break;
			case(ENPASSANT): enPassant(p); incMoves(); break;
			case(FREESQUARE): CT.put(begin,p); incMoves(); break;
			default: throw new NotValidException("Posizione non valida");
		}
		if(begin.getLine()==end) promote();
		CT.changeTurn();
	}
	
	@Override
	protected int eatable(Position p)
	{
		Element e;
		int linea;
		if(!CT.isFree(p))
		{
			e=CT.getElement(p);
			if(e.getColour().equals(colour)) return POSEXC;
			else
			{
				if (colour.equals(Colour.WHITE)) linea = -1;
				else linea = 1;
			}
			//if(e instanceof King) return POSEXC;
			if((begin.sameDiagonal(p)) && (begin.distance(p)==1) && (begin.getLine()-p.getLine()==linea)) return EAT; //MANGIA
			else return POSEXC;
		}
		else
		{
			int line;
			if(colour.equals(Colour.WHITE)) line=-1;
			else line=1;
			e=CT.getElement(p.getLine()+line,p.getColumn());
			if(!(e instanceof Pawn)|| e==null) return POSEXC;
			Pawn e2 = (Pawn) e;
			if(e2.numMoves()!=1 || (e2.getColour().equals(colour))) return POSEXC;
			if(((e2.getPosition().sameColumn(e2.START)) && (e2.getPosition().distance(e2.START)) == 2) && (CT.lastMoved == e2))
				return ENPASSANT; //ENPASSANT
			return POSEXC;
		}
	}
	
	private Element choosePiece() throws NotValidException, OutOfChessTableException
	{
		Element e=null;
		do
		{
			try
			{
				System.out.println("Scegli tra CAVALLO, REGINA, TORRE e ALFIERE");
				String s=Input.readString();
				switch(s)
				{
					case("CAVALLO"): e=new Knight(colour,begin,CT); break;
					case("REGINA"): e=new Queen(colour,begin,CT); break;
					case("TORRE"): e=new Rook(colour,begin,CT); break;
					case("ALFIERE"): e=new Bishop(colour,begin,CT); break;
					default: throw new NotValidException("Pezzo non valido");
				}
			}
			catch(NotValidException exc)
			{
				System.out.println(exc.getMessage());
			}
		}
		while(e==null);
		return e;
	}
	
	private void enPassant(Position p) throws NotValidException, PositionNullException, KingNotFound, OutOfChessTableException
	{
		int color=1;
		if(colour.equals(Colour.WHITE)) color=-1;
		Position q= new Position(p.getLine()+color,p.getColumn());
		Element e=CT.getElement(q);
		CT.eaten(e);
		CT.put(begin,p);
		//CT.removeElement(q);
	}
	
	public void promote() throws NotValidException, OutOfChessTableException
	{
		Element e=choosePiece();
		CT.newPiece(e);
	}
	
	public void setPositionBasic(){
		possiblePos = new ArrayList<Position>();
		int c;
		if (colour.equals(Colour.WHITE)) c = 1;
		else c=-1;
		Position p1 = new Position(begin.getLine()+c, begin.getColumn()-1);
		if (CT.isInRange(p1)) possiblePos.add(p1);
		Position p2 = new Position(begin.getLine()+c, begin.getColumn()+1);
		if (CT.isInRange(p2)) possiblePos.add(p2);
	}

	@Override
	protected int noObstacles(Position p)
	{
	if (p.getColumn()!=begin.getColumn()) return 0;
		if (colour.equals(Colour.WHITE)) {
			for(int i=1;i<=Math.abs(p.getLine()-begin.getLine());i++)
			{
				Position q= new Position(begin.getLine()+i,p.getColumn());
				if(CT.isInRange(q))
					if(!CT.isFree(q)) return -1;
			}
		}
		else {
			for(int i=1;i<=Math.abs(p.getLine()-begin.getLine());i++)
			{
				Position q= new Position(begin.getLine()-i,p.getColumn());
				if(CT.isInRange(q))
					if(!CT.isFree(q)) return -1;
			}
		}
		return 0;
	}
	
	@Override
	protected int isValid(Position p) throws NotValidException
	{
		if(!possiblePos.contains(p)) return -1;
		else if(begin.sameDiagonal(p)) return eatable(p);
		else return 0;
	}

	@Override
	protected boolean validDirection(Position p)
	{
		throw new UnsupportedOperationException();
	}
}
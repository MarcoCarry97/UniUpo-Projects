/**
 * Elemento King (Re)
 */


package chesspieces;

import java.util.ArrayList;

import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public class King extends Element
{
	private final int CASTLE=3; //Arrocco
	/**
	 * Costruttore
	 * @param colour colore di King
	 * @param place posizione di King
	 * @param CT ChessTable a cui appartiene King
	 * @param numPastMoves numero di mosse già effettuate
	 * @throws OutOfChessTableException Se l'elemento viene piazzato fuori dalla ChessTable
	 */
	public King(Colour colour, Position place, ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		super(colour, place, CT, numPastMoves);
		possiblePos = new ArrayList<Position>();
	}
	
	
	/**
	 * Costruttore
	 * @param colour colore di King
	 * @param place posizione di King
	 * @param CT ChessTable a cui appartiene King
	 * @throws OutOfChessTableException Se l'elemento viene piazzato fuori dalla ChessTable
	 */
	public King(Colour colour, Position place, ChessTable CT) throws OutOfChessTableException
	{
		this(colour, place, CT,0);
		possiblePos = new ArrayList<Position>();
	}
	/**
	 * Costruttore
	 * @param e King da copiare
	 * @throws OutOfChessTableException Se si tenta di di posizionare il King fuori dalla ChessTable
	 */
	public King(King e) throws OutOfChessTableException
	{
		this(e.getColour(),e.begin,e.CT);
	}
	
	/**
	 * Ritorna la stringa "KING"
	 * @return "KING"
	 */
	@Override
	public String getType()
	{
		return "KING";
	}
	
	/**
	 * Imposta le posizioni in cui si può muovere escludendo le posizioni che causerebbero eventuali scacchi matti
	 * @throws OutOfChessTableException se si trova una posizione fuori dagli scacchi
	 */
	public void setPosition() throws OutOfChessTableException //Imposta le posizioni in cui il re può spostarsi senza venir messo sotto scacco
	{
		//boolean end=false;
		possiblePos= new ArrayList<Position>();
		Position p1 = new Position(begin.getLine(),begin.getColumn()+2); //Prima posizione possibile arrocco
		Position p2 = new Position(begin.getLine(),begin.getColumn()-2); //Seconda posizione possibile arrocco
		if (CT.isInRange(p1) && canCastle(p1)) possiblePos.add(p1); //Se possibile primo arrocco
		if (CT.isInRange(p2) && canCastle(p2)) possiblePos.add(p2); //Se possibile secondo arrocco
		for(int i=-1;i<2;i++)
		{
			//end=false;
			for(int j=-1;j<2  /*&& !end*/;j++) //Controllo tutte le posizioni accanto al re
			{
				Position p=new Position(begin.getLine()+i, begin.getColumn()+j);
				if ((CT.isInRange(p)) &&  (!isTrap(p,this)) && (((CT.isFree(p))||(eatable(p)==EAT)))) possiblePos.add(p); //Le aggiungo se è possibile per il re spostarsi lì
			}
			possiblePos.remove(begin); //Rimuovo tra le posizioni possibili quella in cui il re è gia
		}	
	}
	/**
	 * Imposta le posizioni in cui si può muovere ignorando eventuali scacchi matti
	 */
	public void setPositionBasic() //Imposta le posizioni possibili senza considerare che potrebbe venire mangiato
	{
		//boolean end=false;
		possiblePos= new ArrayList<Position>();
		Position p1 = new Position(begin.getLine(),begin.getColumn()+2);
		Position p2 = new Position(begin.getLine(),begin.getColumn()-3);
		if (CT.isInRange(p1) && canCastle(p1)) possiblePos.add(p1);
		if (CT.isInRange(p2) && canCastle(p2)) possiblePos.add(p2); //Gestione arrocco
		for(int i=-1;i<2;i++)
		{
			//end=false;
			for(int j=-1;j<2/* && !end*/;j++)
			{
				Position p=new Position(begin.getLine()+i, begin.getColumn()+j);
				if ((CT.isInRange(p)) && ((CT.isFree(p))||(eatable(p)==EAT))) possiblePos.add(p);
			}
			possiblePos.remove(begin);
		}
	}
	
	/**
	 * Ritorna true le la posizione è sotto scacco
	 * @param p posizione da analizzare
	 * @param scacchiera ChessTable su cui si analizza la posizione
	 * @return booleano
	 */
	public boolean isChecked(Position p, ChessTable scacchiera){ //Controlla se la posizione è sotto scacco
		for (int x=0;x<scacchiera.MAXIMUM_LINES;x++)
		{
			for (int y=0; y<scacchiera.MAXIMUM_COLUMNS;y++)
			{
				Element e = scacchiera.getElement(new Position(x,y));
				if (e!=null)
				{
					if(!e.getColour().equals(colour))
					{
						if (e instanceof Pawn)
						{
							((Pawn)e).setPositionBasic();
							if (((Pawn)e).getPossiblePos().contains(p))
								return true;//Controllo particolare per i pedoni
						}
						if (e.possiblePos.contains(p))
							return true; //Controllo se esiste un pezzo avversario che potrebbe SPOSTARSI nella posizione
					}
				}
			}
		}
		return false;
	}
	
	/**
	 * Ritorna true se lo spostamento di e in p causerebbe uno scacco matto
	 * @param p posizione verso cui si sposta e
	 * @param e l'elemento che si sposta
	 * @return booelano
	 * @throws OutOfChessTableException Se esiste un pezzo posizionato fuori dalla ChessTable
	 */
	public boolean isTrap(Position p, Element e) throws OutOfChessTableException
	{ //Controlla se l'elemento spostandosi in e causerebbe uno scacco matto
		ChessTable prova = ChessTable.ChessTableSupport(CT,p,begin,e); //Costruisco una nuova scacchiera per vedere se il re nella nuova posizione sarebbe sotto scacco
		if (e instanceof King) return (isChecked(p,prova));
		return (isChecked(begin,prova)); 
	}
	
	private boolean canCastle(Position end) //Controlla se è possibile l'arrocco
	{
		if((numPastMoves!=0)||(isChecked(begin,CT))) return false; //Se il re si è mosso o se è sotto scacco non è possibile effettuare l'arrocco
		int column;
		if(end.getColumn()-begin.getColumn()>0){ //Se la posizione analizzata è a destra
			if (isChecked(new Position(begin.getLine(),begin.getColumn()+1),CT)) return false; //Se la posizione intermedia è sotto scacco non è possibile effettuare l'arrocco
			else column=7; //La torre sarà a destra
			for (int i =begin.getColumn()+1;i<CT.MAXIMUM_LINES-1;i++)
			{
				if (!CT.isFree(new Position(begin.getLine(),i)))
					return false; //Se le posizioni intermedie non sono libere non è permesso effettuare l'arrocco
			}
		}
		else
		{
			if (isChecked(new Position(begin.getLine(),begin.getColumn()-1),CT)) return false; //Se la posizione intermedia è sotto scacco non è possibile effettuare l'arrocco
			else column=0; //La torre sarà a sinistra
			for (int i =begin.getColumn()-1;i>0;i--)
			{
				if (!CT.isFree(new Position(begin.getLine(),i)))
					return false; //Se le posizioni intermedie non sono libere non è permesso effettuare l'arrocco
			}
		}
		Element e=CT.getElement(end.getLine(),column);
		if(!(e instanceof Rook)) return false; //Se non è una torre non permette l'arrocco
		if (!e.colour.equals(colour)) return false; //Se la torre non è dello stesso colore del re non permette l'arrocco
		if(e.numMoves()!=0) return false; //Se la torre si è mossa almeno una volta non è possibile effettuare l'arrocco
		return true;
	}
	
	@Override
	protected int isValid(Position end) throws OutOfChessTableException
	{ //Controlla se la posizione verso cui vuole spostarsi il re è valida
		setPosition();
		if(!possiblePos.contains(end)) return POSEXC; 
		if(canCastle(end)) return CASTLE;
		if(CT.isFree(end)) return FREESQUARE;
		return eatable(end);
	}
	

	/**
	 * Prova a spostare il King nella posizione end
	 * @param end posizione verso cui si tenta di spostare il King
	 * @throws NotValidException Se non è possibile spostare il King in end
	 * @throws PositionNullException se un pezzo risulta senza posizione
	 */
	@Override
	public void moveTo(Position end) throws NotValidException, PositionNullException //Sposta il re richiamando la funzione appropriata al caso
, KingNotFound, OutOfChessTableException
	{
		switch(isValid(end))
		{
			case(EAT): eat(end); incMoves(); break;
			case(FREESQUARE): CT.put(begin,end); incMoves(); break;
			case(CASTLE): castle(end); incMoves(); break;
			default: throw new NotValidException("Posizione non valida");
		}
		CT.changeTurn();
	}
	
	/**
	 * Prova a spostare il King nella posizione indicata da line e column
	 * @param line Riga della posizione verso cui si tenta lo spostamento
	 * @param column Colonna della posizione verso cui si tenta lo spostamento
	 * @throws NotValidException Se non è possibile spostare il King in end
	 * @throws PositionNullException se un pezzo risulta senza posizione
	 */
	@Override
	public void moveTo(int line, int column) throws NotValidException, PositionNullException, KingNotFound, OutOfChessTableException
	{
		moveTo(new Position(line,column));
	}
	
	private void castle(Position end) throws NotValidException //Esecuzione arrocco
, KingNotFound, OutOfChessTableException
	{
		int a;
		int column;
		if(end.getColumn()>begin.getColumn())
		{//Se la torre è a destra
			a=-1; 
			column = 7;
		}
		else
		{ //Torre a sinistra
			a=1;
			column = 0;
		}
		CT.put(begin,end); //Sposto il re
		Position bp=new Position(begin.getLine(),column); //Calcolo la posizione in cui si trova la torre
		Rook r = (Rook) (CT.getElement(bp)); //Ottengo la torre
		Position fp=new Position(begin.getLine(), begin.getColumn()+a); //Calcolo la posizione in cui andrà la torre
		CT.put(r.getPosition(),fp); //Sposto la torre
		//CT.changeTurn();
	}
	
	@Override
	protected int eatable(Position end) //Ritorna EAT se un elemento è catturabile
	{
		Element e=CT.getElement(end);
		if(e.getColour().equals(colour)) return -2;
		else return EAT;
	}
	
	@Override
	protected int eatable(int line, int column)
	{
		return eatable(new Position(line,column));
	}

	@Override
	protected boolean validDirection(Position p) 
	{
		return begin.sameDiagonal(p) ||begin.sameColumn(p) || begin.sameLine(p);
	}
	
	/**
	 * Ritorna il simbolo di King
	 * @return 'K' o 'k'
	 */
	public char getSymbol() //Ritorna il simbolo di re
	{
		if (colour.equals(Colour.WHITE)) return 'K';
		else return 'k';
	}
}

/*
 * Classe astratta per tutti i pezzi degli scacchi
 */



package chesspieces;

import java.util.ArrayList;

import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public abstract class Element
{
	/**
	 * Valore che segna che la mossa è una cattura
	 */
	public final int EAT=1;
	
	/**
	 * Valore che segna che la mossa è un movimento in una posizione libera
	 */
	public final int FREESQUARE=0;
	/**
	 * Valore che segna quando la mossa non è valida
	 */
	public final int POSEXC=-1;
	
	protected int numPastMoves;
	//protected String type;
	protected Colour colour;
	protected Position begin;
	protected ChessTable CT;
	protected ArrayList<Position> possiblePos;
	
	protected Element(Colour colour, Position place, ChessTable CT, int numPastMoves) throws OutOfChessTableException
	{
		this.colour=colour;
		this.CT = CT;
		if (!CT.isInRange(place)) throw new OutOfChessTableException();
		this.begin=place;
		this.numPastMoves=numPastMoves;
		possiblePos = new ArrayList<Position>();
	}
	
	protected Element (Colour colour, Position place, ChessTable CT) throws OutOfChessTableException {
		this(colour,place,CT,0);
	}
	
	protected Element(Element e) throws OutOfChessTableException {
		this(e.getColour(),e.begin,e.CT);
	}

	
	protected abstract boolean validDirection(Position p);
	/**
	 * Ritorna una stringa che indica quale elemento è l'oggetto
	 * @return Stringa
	 */
	public abstract String getType();
	/**
	 * Ritorna il simbolo dell'elemento da utilizzare in ChessTable
	 * @return un carattere
	 */
	public abstract char getSymbol();
	/**
	 * Imposta possiblePos con l'insieme di tutte le posizioni in cui l'elemento potrebbe mangiare un altro pezzo
	 */
	public abstract void setPositionBasic(); 
	
	/**
	 * Imposta possiblePos con l'insieme delle posizioni raggiungibili senza causare uno scacco matto
	 * @throws KingNotFound eccezione sollevata se non si trova il re
	 * @throws OutOfChessTableException eccezione sollevata se un pezzo risulta fuori dalla scacchiera
	 */
	public void setPosition() throws KingNotFound, OutOfChessTableException
	{
		setPositionBasic();
		removeTraps();
	}
	
	protected void set(int a, int b)
	{
		boolean end=false;
		for(int i=1;!end;i++)
		{
			Position p= new Position(begin.getLine()+a*i, begin.getColumn()+b*i);
			if(CT.isInRange(p))
			{
				if(!possiblePos.contains(p))
				{
					if(CT.isFree(p)) possiblePos.add(p);
					else if(eatable(p)==EAT) {
						possiblePos.add(p);
						end = true;
					}
					else end=true;
				}
			}
			else end=true;
		}
	}
	/**
	 * Ritorna la dimensione dell'ArrayList possiblePos, ovvero il numero di mosse effettuabili dall'Element
	 * @return intero
	 */
	public int getPossibleSize()
	{
		return possiblePos.size();
	}
	/**
	 * Ritorna la mossa possibile all'indice index
	 * @param index indice della posizione da ritornare
	 * @return Position
	 */
	public Position getPossible(int index)
	{
		return possiblePos.get(index);
	}
	
	/**
	 * Ritorna una copia dell'insieme delle posizioni raggiungibili da Element
	 * @return ArrayList di Position
	 */
	public ArrayList<Position> getPossiblePos(){
		return (new ArrayList<Position>(possiblePos));
	}
	/**
	 * Cambia la ChessTable di Element
	 * @param cambio nuova ChessTable
	 */
	public void changeChessTable(ChessTable cambio) {
		CT = cambio;
	}
	/**
	 * Ritorna il colore dell'elemento
	 * @return Colour
	 */
	public Colour getColour()
	{
		return colour;
	}
	
	/**
	 * Ritorna la posizione attuale dell'elemento
	 * @return Position
	 */
	public Position getPosition()
	{
		return begin;
	}
	/**
	 * Prova a mangiare l'elemento in posizione end
	 * @param end Posizione da catturare e in cui spostarsi
	 * @throws NotValidException Se si prova a spostare un elemento nullo
	 * @throws PositionNullException se l'elemento che si tenta di mangiare non ha definito il campo relativo alla propria posizione
	 * @throws KingNotFound Se non risulta presente il re del colore di Element
	 * @throws OutOfChessTableException Se si prova a mettere l'elemento in una posizione esterna alla scacchiera
	 */
	public void eat(Position end) throws NotValidException, PositionNullException, KingNotFound, OutOfChessTableException
	{
		Element e=CT.getElement(end);
		CT.eaten(e);
		CT.put(begin, end);
		//CT.changeTurn();
	}
	
	protected int isValid(Position p) throws NotValidException, KingNotFound, OutOfChessTableException
	{
		setPosition();
		if(!possiblePos.contains(p)) return POSEXC;
		else if(begin.equals(p)) return POSEXC;
		else if(!validDirection(p)) return POSEXC;
		else if((noObstacles(p)==0) && (CT.isFree(p)))return FREESQUARE;
		else return eatable(p);
	}
	/**
	 * Aumenta il numero di mosse effettuate dall'elemento
	 */
	public void incMoves()
	{
		numPastMoves++;
	}
	
	/**
	 * Ritorna il numero di mosse effettuate dall'elemento
	 * @return intero
	 */
	public int numMoves()
	{
		return numPastMoves;
	}
	/**
	 * Prova a spostare l'elemento nella posizione end, e a capire se si tratta di uno spostamento o di una cattura
	 * @param end posizione da analizzare
	 * @throws NotValidException Se la posizione non è valida
	 * @throws KingNotFound Se non si trova il re del colore di Element
	 * @throws PositionNullException Se si prova a spostare un elemento privo di posizione
	 * @throws OutOfChessTableException Se si prova a spostare un elemento fuori dalla ChessTable
	 */
	public void moveTo(Position end) throws NotValidException, KingNotFound, PositionNullException, OutOfChessTableException
	{
		switch(isValid(end))
		{
			case(EAT): eat(end); incMoves(); break; 
			case(FREESQUARE): CT.put(begin,end); incMoves(); break;
			default: throw new NotValidException("Posizione non valida");
		}
		CT.changeTurn();
	}
	/**
	 *  Prova a spostare l'elemento nella posizione indicata da line e column, e a capire se si tratta di uno spostamento o di una cattura
	 * 
	 * @param line Riga della posizione
	 * @param column Colonna della posizione
	 * @throws NotValidException Se la posizione non è valida
	 * @throws KingNotFound Se non si trova il re del colore di Element
	 * @throws PositionNullException Se si prova a spostare un elemento privo di posizione
	 * @throws OutOfChessTableException Se si prova a spostare un elemento fuori dalla ChessTable
	 */
	public void moveTo(int line, int column) throws NotValidException, KingNotFound, PositionNullException, OutOfChessTableException
	{
		moveTo(new Position(line,column));
	}
	
	protected int noObstacles(Position end)
	{
		if(begin.sameLine(end))
			return controlPos(end.getLine()-begin.getLine(),0);
		else if(begin.sameColumn(end))
			return controlPos(0,end.getColumn()-begin.getColumn());
		else if(begin.sameDiagonal(end))
			return controlPos(end.getLine()-begin.getLine(),end.getColumn()-begin.getColumn());
		else return -1;
	}
	
	private int controlPos(int line, int column)
	{
		int l=1, c=1;
		if(line<0) 
		{
			line=Math.abs(line);
			l=-1;
		}
		if(column<0) 
		{
			column=Math.abs(column);
			c=-1;
		}
		int i=1, j=1;
		while(i<=line && j<=column)
		{
			int x=begin.getLine()+i*l;
			int y=begin.getColumn()+j*c;
			if(!CT.isFree(x,y)) return POSEXC;
			if(i<=line) i++;
			if(j<=column) j++;
		}
		return FREESQUARE;
	}
	
	protected int noObstacles(int line, int column)
	{
		return noObstacles(new Position(line,column));
	}
	
	protected int eatable(Position p)
	{
		Element e=CT.getElement(p);
		if(e.getColour().equals(colour)) return POSEXC;
		//else if(e instanceof King) return POSEXC;
		else return EAT;
		
	}
	
	protected int eatable(int line, int column)
	{
		return eatable(new Position(line, column));
	}
	/**
	 * Ritorna la conversione dell'elemento a stringa
	 * @return Stringa
	 */
	public String toString()
	{
		return getType() + ' '+getColour()+' '+ begin.toString()+' '+numPastMoves;
	}
	
	/**
	 * Ritorna true se due elementi sono uguali
	 * @return boolean
	 */
	public boolean equals(Object obj)
	{
		Element e=(Element)obj;
		if(!e.getColour().equals(colour))return false;
		else if(!e.getType().equals(getType())) return false;
		else return true;
	}
	/**
	 * Ritorna la conversione a stringa delle posizioni possibili
	 * @return String
	 */
	public String possibleString()
	{
		return possiblePos.toString();
	}
	/**
	 * Rimuove dalle posizioni possibili quelle che causerebbero uno scacco matto
	 * @throws KingNotFound Se non viene trovato il proprio re
	 * @throws OutOfChessTableException se un pezzo risulta fuori dalla scacchiera
	 */
	public void removeTraps() throws KingNotFound, OutOfChessTableException {
		King k = CT.findKing(colour);
		int index=0;
		while(index<possiblePos.size()) {
			Position p = possiblePos.get(index);
			if (k.isTrap(p,this)) possiblePos.remove(p);
			else index++;
		}
	}
		
}

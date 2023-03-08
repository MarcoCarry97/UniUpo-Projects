/*
 * Classe che gestisce tutti gli aspetti inerenti alla <i>scacchiera<i>
 * @author
 * Desogus Michael, Carega Marco
 */


package table;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
//import java.util.ArrayList;

import chesspieces.*;

public class ChessTable
{
	/**
	 * Numero di righe della scacchiera
	 */
	public final int MAXIMUM_LINES = 8;
	/**
	 * Numero di colonne della scacchiera
	 */
	public final int MAXIMUM_COLUMNS = 8;
	private Square[][] table; //Matrice in cui memorizzare gli elementi
	//private eaten ArrayEaten; //Classe in cui sono memorizzati i pezzi mangiati
	private boolean turn; //Variabile che segna di chi è il turno
	/**
	 * Variabile che segna l'ultimo elemento mosso
	 */
	public Element lastMoved; 
	
//	class eaten
//	{
//		ArrayList<Element> white;
//		ArrayList<Element> black; //I pezzi mangiati sono gestiti da due vettori separati
//		
//		private eaten()
//		{
//			white = new ArrayList<Element>();
//			black = new ArrayList<Element>();
//		}
//		
//		private eaten(eaten copy)
//		{
//			white = new ArrayList<Element>(copy.white);
//			black = new ArrayList<Element>(copy.black);
//		}
//	}
	/**
	 * Costruttore di una scacchiera vuota
	 */
	
	public ChessTable() 
	{
		//ArrayEaten = new eaten();
		table = new Square[MAXIMUM_LINES][MAXIMUM_COLUMNS];
		setSquares();
		turn = true;
		lastMoved = null;
	}
	
	/**
	 * Copia la ChessTable data come input
	 * 
	 * @param copy ChessTable di cui effettuare la copia
	 */
	
	public ChessTable(ChessTable copy) {
		//ArrayEaten = new eaten(copy.ArrayEaten);
		table = new Square[MAXIMUM_LINES][MAXIMUM_COLUMNS];
		setSquares();
		turn = copy.turn;
		
	}
	/**
	 * Ritorna il valore di turno
	 * 
	 * @return Valore di turno
	 */
	public boolean getTurn()
	{
		return turn;
	}

	/**
	 * Metodo che crea una scacchiera di supporto per analizzare la validità di una mossa
	 * 
	 * @param copy La ChessTable da copiare
	 * @param arrivo Posizione finale della mossa
	 * @param partenza Posizione da analizzare se sotto scacco
	 * @param e Elemento che si sposta durante la mossa
	 * @return Una ChessTable
	 * @throws OutOfChessTableException  se si crea un pezzo con una poszione non possibile per la ChessTable
	 */
	public static ChessTable ChessTableSupport(ChessTable copy, Position arrivo, Position partenza, Element e) throws OutOfChessTableException
	{ //Metodo fondamentale per controllare che la mossa del re non causi un "suicidio", ritorna una scacchiera identica a quella in input ma con la mossa voluta già effettuata
		ChessTable output = new ChessTable(copy);
		Element trial=null;
		for (int x=0; x<copy.MAXIMUM_LINES; x++)
		{
			for (int y=0; y<copy.MAXIMUM_COLUMNS; y++){
				Position tempPosition = new Position(x,y);
				if (tempPosition.equals(arrivo)|| tempPosition.equals(partenza)|| tempPosition.equals(e.getPosition())) continue; //Gli elementi in quelle posizioni non vengono copiati
				Element temp = copy.getElement(x,y);
				Element copying;
				if (temp!=null) { //Costruisco un pezzo analogo a quello analizzato nella posizione x,y nella scacchiera da copiare e lo metto nella nuova
					switch(temp.getType()) {
						case ("PAWN"):
							copying = new Pawn((Pawn)temp);
							break;
						case("ROOK"):
							copying = new Rook((Rook)temp); 
							break;
						case("KNIGHT"):
							copying = new Knight((Knight)temp);
							break;
						case("BISHOP"):
							copying = new Bishop((Bishop)temp);
							break;
						case("QUEEN"):
							copying = new Queen((Queen)temp);
							break;
						default:
							copying = new King((King)temp);
							break;
					}
					copying.changeChessTable(output);
					output.newPiece(copying);
				}
			}
		}
		switch(e.getType()) { //Se l'elemento che si sposta non è il re allora il re si mette dov'è nella scacchiera originale e si sposta il pezzo desiderato, altrimenti si sposta il re
		case("PAWN"): trial = new Pawn(e.getColour(),arrivo,output); King k = new King(e.getColour(),partenza,output); output.newPiece(k); break;
		case("ROOK"): trial = new Rook(e.getColour(),arrivo,output); k = new King(e.getColour(),partenza,output); output.newPiece(k); break;
		case("KNIGHT"): trial = new Knight(e.getColour(),arrivo,output); k = new King(e.getColour(),partenza,output); output.newPiece(k); break;
		case("BISHOP"): trial = new Bishop(e.getColour(),arrivo,output); k = new King(e.getColour(),partenza,output); output.newPiece(k); break;
		case("QUEEN"): trial = new Queen(e.getColour(),arrivo,output); k = new King(e.getColour(),partenza,output); output.newPiece(k); break;
		case("KING"): trial = new King(e.getColour(),arrivo,output);
		}
		output.newPiece(trial);
		if (e.getColour().equals(Colour.BLACK)) { //Se il re è nero
			output.refreshPossiblePosBasic(Colour.BLACK);
			output.refreshPossiblePosBasic(Colour.WHITE);
		}
		else {
			output.refreshPossiblePosBasic(Colour.WHITE);
			output.refreshPossiblePosBasic(Colour.BLACK);
		}
		return output;
	}
	
	/**
	 * Imposta i quadrati a null e ne imposta il colore
	 */
	
	public void setSquares() //Imposta i colori dei quadrati e imposta a null gli elementi sopra ai quadrati
	{
		boolean flag = false;
		for (int i=0; i<MAXIMUM_LINES; i++)
			for (int j=0; j<MAXIMUM_COLUMNS; j++)
			{
				if (flag) table[i][j]=new Square(null,Colour.WHITE);
				else table[i][j] = new Square(null,Colour.BLACK);
				flag=!flag;
			}
	}
	
	/**
	 * Inizializza la scacchiera per una classica partita degli scacchi
	 * @throws OutOfChessTableException se si crea un pezzo con una posizione impossibile
	 */
	
	public void initialize() throws OutOfChessTableException //Inizializza la scacchiera per una nuova partita
	{
		newPiece(new Rook(Colour.WHITE,new Position(0,0),this));
		newPiece(new Knight(Colour.WHITE,new Position(0,1),this));
		newPiece(new Bishop(Colour.WHITE,new Position(0,2),this));
		newPiece(new Queen(Colour.WHITE,new Position(0,3),this));
		newPiece(new King(Colour.WHITE,new Position(0,4),this));
		newPiece(new Bishop(Colour.WHITE,new Position(0,5),this));
		newPiece(new Knight(Colour.WHITE,new Position(0,6),this));
		newPiece(new Rook(Colour.WHITE,new Position(0,7),this));
		for (int i=0;i<MAXIMUM_COLUMNS;i++)
		{
			newPiece(new Pawn(Colour.WHITE,new Position(1,i),this));
			newPiece(new Pawn(Colour.BLACK,new Position(MAXIMUM_LINES-2,i),this));
		}
		newPiece(new Rook(Colour.BLACK,new Position(MAXIMUM_LINES-1,0),this));
		newPiece(new Knight(Colour.BLACK,new Position(MAXIMUM_LINES-1,1),this));
		newPiece(new Bishop(Colour.BLACK,new Position(MAXIMUM_LINES-1,2),this));
		newPiece(new Queen(Colour.BLACK,new Position(MAXIMUM_LINES-1,3),this));
		newPiece(new King(Colour.BLACK,new Position(MAXIMUM_LINES-1,4),this));
		newPiece(new Bishop(Colour.BLACK,new Position(MAXIMUM_LINES-1,5),this));
		newPiece(new Knight(Colour.BLACK,new Position(MAXIMUM_LINES-1,6),this));
		newPiece(new Rook(Colour.BLACK,new Position(MAXIMUM_LINES-1,7),this));
	}
	
	/**
	 * Gestisce l'elemento catturato
	 * @param e Elemento catturato
	 * @throws PositionNullException L'elemento provato a catturare non ha una posizione
	 */
	
	public void eaten(Element e) throws PositionNullException //Gestisce un pezzo mangiato
	{
		if(e==null) throw new NullPointerException();
		Position p=e.getPosition();
		if(p==null) throw new PositionNullException();
		removeElement(e);
		//if (e.getColour().equals(Colour.WHITE)) ArrayEaten.white.add(e);
		//else ArrayEaten.black.add(e);
		//changeTurn();
	}
	
	/**
	 *Memorizza le informazioni della ChessTable corrente su un file di testo
	 *
	 *@param nomeFile nome del file su cui viene salvata la partita 
	 *@throws FileNotFoundException Non riesce ad aprire il file in scrittura
	 *@throws FormatException Formato della stringa non corretta
	 */
	
	public void saveMatch(String nomeFile) throws FileNotFoundException //Salva la partita corrente su un file di testo
, FormatException
	{
		if(!nomeFile.matches("[\\w]+.txt"))
			throw new FormatException("Formato nome file no valido");
		PrintWriter out = new PrintWriter(new File(nomeFile));
		if (turn) out.println("WHITE");
		else out.println("BLACK");
		for (int i=0; i<MAXIMUM_LINES; i++)
			for(int j=0;j<MAXIMUM_COLUMNS;j++)
			{
				Element e = table[i][j].getElement();
				if(e!=null) out.printf("%s\n",e.toString());
			}
		out.close();
	}
	
	/**
	 * Posiziona i pezzi come riportato nel file di testo in lettura
	 * 
	 * @param nomeFile nome del file da aprire
	 * @throws IOException Problemi durante le operazioni sui file
	 * @throws NotValidException  Individuati problemi nel file in lettura
	 * @throws FormatException Formato del nome del file non corretto
	 */
	public void loadMatch(String nomeFile) throws IOException, NotValidException //Carica una partita da un file di testo
, FormatException
	{
		if(!nomeFile.matches("[\\w]+.txt"))
			throw new FormatException("Formato nome file no valido");
		BufferedReader in = new BufferedReader(new FileReader(nomeFile));
		String linea=in.readLine();
		Element e;
		while(linea!=null)
		{
			String[] dati = linea.split(" ");
			if(dati.length>=4)
			{
				try {
					switch(dati[0])
					{
						case("PAWN"): if(dati.length==5) e=new Pawn(Colour.stringToColour(dati[1]),Position.parsePosition(dati[2]),Position.parsePosition(dati[3]),this,Integer.parseInt(dati[4]));
									  else throw new NotValidException("il pedone ha bisogno di 4 parametri"); break;
						case("ROOK"): e=new Rook(Colour.stringToColour(dati[1]),Position.parsePosition(dati[2]),this, Integer.parseInt(dati[3])); break;
						case("KNIGHT"): e=new Knight(Colour.stringToColour(dati[1]),Position.parsePosition(dati[2]),this,Integer.parseInt(dati[3])); break;
						case("BISHOP"): e=new Bishop(Colour.stringToColour(dati[1]),Position.parsePosition(dati[2]),this,Integer.parseInt(dati[3])); break;
						case("QUEEN"): e=new Queen(Colour.stringToColour(dati[1]),Position.parsePosition(dati[2]),this,Integer.parseInt(dati[3])); break;
						case("KING"): e=new King(Colour.stringToColour(dati[1]),Position.parsePosition(dati[2]),this,Integer.parseInt(dati[3])); break;
						default: throw new NotValidException("Nella partita ci sono pezzi non validi");
					}
					newPiece(e);
				}catch(OutOfChessTableException err) {
					System.out.println("Errore nella costruzione di un pezzo");
				}
			}
			else if (dati.length==1) {
				if (dati[0].equals("WHITE")) turn = true;
				else if (dati[0].equals("BLACK")) turn=false;
			}
			linea = in.readLine();
		}
		in.close();
	}
	
	/**
	 * Ritorna l'elemento in posizione p
	 * @param p posizione da cui si vuole ricavare l'elemento
	 * @return un Element
	 */
	
	public Element getElement(Position p) //Ritorna l'elemento in posizione p
	{
		return (getElement(p.getLine(),p.getColumn()));
	}
	
	/**
	 * Ritorna l'elemento alle cordinate indicate
	 * @param line riga in cui cercare
	 * @param column colonna in cui cercare
	 * @return un Element
	 */
	
	public Element getElement(int line, int column)
	{
		return (table[line][column]).getElement();
	}
	
//	public ArrayList<Element> getWhiteEaten(){ //Ritorna una copia degli elementi bianchi catturati
//		return (new ArrayList<Element>(ArrayEaten.white));
//	}
//	
//	public ArrayList<Element> getBlackEaten(){//Ritorna una copia degli elementi neri catturati
//		return (new ArrayList<Element>(ArrayEaten.black));
//	}
	/**
	 * Sposta l'elemento in posizione place da place a p
	 * @param place Posizione iniziale
	 * @param p Posizione finale
	 * @throws NotValidException Se si sta spostando un elemento nullo
	 * @throws KingNotFound Se non si trova il re
	 * @throws OutOfChessTableException posizione non possibile per la scacchiera
	 */
	
	public void put(Position place, Position p) throws NotValidException //Sposta un elemento dalla posizione place alla posizione p
, KingNotFound, OutOfChessTableException
	{
		Element e = getElement(place); 
		if(e==null) throw new NotValidException("Element Nullo");
		removeElement(place);
		place.update(p);
		newPiece(e);
		if (e.getColour().equals(Colour.WHITE))
		{
			refreshPossiblePosBasic(Colour.WHITE);
			refreshPossiblePos(Colour.BLACK);
		}
		else
		{
			refreshPossiblePosBasic(Colour.BLACK);
			refreshPossiblePos(Colour.WHITE);
		}
		//changeTurn();
		lastMoved = e;
	}
	
	/**
	 * Sposta l'elemento in posizione place da place alla posizione indicata da line e column
	 * @param place Posizione iniziale
	 * @param line riga di destinazione
	 * @param column colonna di destinazione
	 * @throws NotValidException Se si sta spostando un elemento nullo
	 * @throws KingNotFound Se il re non si trova sulla scacchiera
	 * @throws OutOfChessTableException posizione non possibile per la scacchiera
	 */
	public void put(Position place, int line, int column) throws NotValidException, KingNotFound, OutOfChessTableException
	{
		put(place,new Position(line,column));
	}
	
	/**
	 * Ritorna true se la posizione p è libera, altrimenti false
	 * @param p posizione analizzata
	 * @return valore booleano
	 */
	
	public boolean isFree(Position p) //Restituisce true se la posizione p è libera
	{
		return(isFree(p.getLine(),p.getColumn()));
	}
	
	/**
	 * Ritorna true se la posizione indicata da line e column è libera, altrimenti false
	 * @param line riga da analizzare
	 * @param column colonna da analizzare
	 * @return un valore booleano
	 */
	public boolean isFree (int line, int column)
	{
		return (table[line][column].getElement() == null);
	}
	
	/**
	 * Aggiunge l'elemento e alla scacchiera
	 * @param e elemento da aggiungere
	 */
	
	public void newPiece(Element e) //Mette l'elemento all'interno della matrice nella giusta posizione
	{
		Position p=e.getPosition();
		if ((isFree(p)) || (getElement(p).getClass() == Pawn.class))
			table[p.getLine()][p.getColumn()].changeElement(e);
		
	}
	
	/**
	 * Cambia l'elemento in posizione p
	 * @param e nuovo elemento
	 * @param p posizione in cui posizionare il nuovo elemento
	 */
	public void changeElement(Element e, Position p) //Cambia l'elemento in posizione p
	{
		table[p.getLine()][p.getColumn()].changeElement(e);
	}
	
	/**
	 * Rimuove l'elemento in posizione p
	 * @param p posizione da cui rimuovere l'elemento
	 */
	
	public void removeElement(Position p) //Rimuove l'elemento in posizione p
	{
		changeElement(null,p);
	}
	/**
	 * Rimuove l'elemento indicato dai parametri
	 * @param line riga della posizione da cui rimuovere l'elemento
	 * @param column colonna della posizione da cui rimuovere l'elemento
	 */
	public void removeElement(int line, int column)
	{
		removeElement(new Position(line,column));
	}
	
	/**
	 * Rimuove l'elemento e
	 * @param e elemento da rimuovere
	 */
	public void removeElement(Element e) {
		removeElement(e.getPosition());
	}
	
	/**
	 * Ritorna true se la posizione è valida per la scacchiera, altrimenti false
	 * @param p posizione da analizzare
	 * @return valore booleano
	 */
	public boolean isInRange(Position p) //Ritorna true se la posizione esiste sulla scacchiera
	{
		return (inRangeLine(p.getLine()) && inRangeColumn(p.getColumn()));
	}
	/**
	 * Ritorna true se la posizione è valida per la scacchiera, altrimenti false
	 * @param line riga della posizione da analizzare
	 * @param column colonna della posizione da analizzare
	 * @return valore booleano
	 */
	public boolean isInRange(int line, int column)
	{
		return isInRange(new Position(line,column));
	}

	private boolean inRangeLine(int num) //Ritorna true se la riga è compresa tra la prima e l'ultima riga
	{
		return (num>=0 && num<MAXIMUM_LINES);
	}
	
	private boolean inRangeColumn(int num) //Ritorna true se la colonna è compresa tra la prima e l'ultima colonna
	{
		return (num>=0 && num<MAXIMUM_COLUMNS);
	}
	
	/**
	 * Aggiorna i valori di colore c con le posizioni in cui potrebbero mangiare il re
	 * @param c colore da analizzare
	 */
	public void refreshPossiblePosBasic(Colour c) { //Aggiorna le posizioni possibili per uno spostamento senza considerare eventuali pericoli
		for (int x=0;x<MAXIMUM_LINES;x++){
			for (int y=0; y<MAXIMUM_COLUMNS;y++){
				Element e = getElement(new Position(x,y));
				if (e!=null){
					if(e.getColour().equals(c)) e.setPositionBasic();
				}
			}
		}
	}
	/**
	 * Aggiorna i valori di colori c con le posizioni in cui possono spostarsi
	 * @param c colore da analizzare
	 * @throws KingNotFound se il re non è presente sulla scacchiera
	 * @throws OutOfChessTableException posizione non possibile per la scacchiera
	 */
	public void refreshPossiblePos(Colour c) throws KingNotFound, OutOfChessTableException { //Aggiorna gli spostamenti possibili escludendo quelli che porrebbero il re sotto scacco
		for (int x=0;(x<MAXIMUM_LINES);x++){
			for (int y=0; (y<MAXIMUM_COLUMNS);y++){
				Element e = getElement(new Position(x,y));
				if (e!=null){
					if(e.getColour().equals(c)){
						if (e.getClass()==King.class) ((King)e).setPosition();
						else e.setPosition();
					}
				}
			}
		}
	}
	/**
	 * Ritorna il re del colore c
	 * @param c colore del re da cercare
	 * @return King
	 * @throws KingNotFound se non trova il re
	 */
	public King findKing(Colour c) throws KingNotFound {
		Element output;
		for (int x=0; x<MAXIMUM_LINES;x++) {
			for(int y=0; y<MAXIMUM_COLUMNS;y++) {
				output = getElement(new Position(x,y));
				if (output!=null) {
					if ((output.getColour().equals(c))&&(output instanceof King)) return ((King)output);
				}
			}
		}
	throw new KingNotFound();
	}

	/**
	 * Converte la scacchiera in una stringa
	 * @return Stringa
	 */
	public String toString() 
	{
		String output="";
		String separator = "  ";
		for (int i=0;i<(1+4*MAXIMUM_LINES);i++) separator +="-";
		for (int x=MAXIMUM_LINES-1; x>=0;x--)
		{
			output+=(separator) +"\n"+x+" |";
			for (int y=0; y<MAXIMUM_COLUMNS;y++)
			{
				String temp = " ";
				if(!(isFree(x,y))) temp+=getElement(x,y).getSymbol() +" |";
				else temp+="  |";
				output+=temp;
			}
			output+="\n";
		}
		output+=separator+"\n  ";
		for (int i=0; i<MAXIMUM_LINES;i++) {
			output+="  "+i+" ";
		}
		output+="\n";
		return output;
	}
	/**
	 * Cambia il valore della variabile booleana turn
	 */
	public void changeTurn() {
		turn = !turn;
	}
	/**
	 * Ritorna CHECKMATE se il re di colore c è in una situazione di scacco matto, PATTA se la partita è in stallo, altrimenti NIENTE
	 * @param c colore da analizzare
	 * @return 0,1,2
	 * @throws KingNotFound se il re non si trova sulla scacchiera
	 * @throws OutOfChessTableException posizione non presente sulla scacchiera
	 */
	public int checkmate(Colour c) throws KingNotFound, OutOfChessTableException {
		final int CHECKMATE = 2;
		final int PATTA = 1;
		final int NIENTE = 0;
		refreshPossiblePosBasic(Colour.reverse(c));
		refreshPossiblePos(c);
		for (int x=0; x<MAXIMUM_LINES; x++) {
			for(int y=0; y<MAXIMUM_COLUMNS; y++) {
				Element e = getElement(new Position(x,y));
				if (e!=null) {
					if (e.getColour().equals(c)) {
						if (e.getPossibleSize()>0)return NIENTE;
					}
				}
			}
		}
		King k = findKing(c);
		if (k.isChecked(k.getPosition(), this)) return CHECKMATE;
		else return PATTA;
	}
}

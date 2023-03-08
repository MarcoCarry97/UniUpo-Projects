/**
 * Posizioni formate da un'ascissa e da un'ordinata
 */



package table;

public class Position
{
	private int line;
	private int column;
	
	/**
	 * ritorna l'ascissa della posizione
	 * @return intero
	 */
	public int getLine()
	{
		return line;
	}
	
	/**
	 * ritorna l'ordinata della posizione
	 * @return intero
	 */
	
	public int getColumn()
	{
		return column;
	}
	/**
	 * Calcola la distanza tra due punti, se non sono allineati viene ritornato -1
	 * @param p punto da cui calcolare la distanza
	 * @return int
	 */
	public int distance(Position p)
	{
		int a=Math.abs(p.getLine()-line);
		int b=Math.abs(p.getColumn()-column);
		if(a==0) return b;
		else if(b==0) return a;
		else if(a==b) return a; // oppure return b;
		else return -1;
	}
	
	/**
	 * Aggiorno la posizione
	 * 
	 * @param line ascissa della nuova posizione
	 * @param column ordinata della nuova posizione
	 */
	public void update(int line, int column)
	{
		update(new Position(line,column));
	}
	/**
	 * Aggiorno la posizione
	 * 
	 * @param p nuova posizione
	 */
	public void update(Position p)
	{
		this.line=p.getLine();
		this.column=p.getColumn();
	}
	/**
	 * Ritorna true se due posizioni hanno la stessa ascissa
	 * @param p posizione con cui effettuare il confronto
	 * @return booleano
	 */
	public boolean sameLine(Position p)
	{
		return line==p.getLine();
	}
	
	/**
	 * Ritorna true se due posizioni hanno la stessa ordinata
	 * @param p posizione con cui effettuare il confronto
	 * @return booleano
	 */
	public boolean sameColumn(Position p)
	{
		return column==p.getColumn();
	}
	/**
	 * Ritorna true se due posizioni sono allineate in diagonale
	 * @param p posizione con cui effettuare il confronto
	 * @return booleano
	 */
	public boolean sameDiagonal(Position p)
	{
		int a=Math.abs(line-p.getLine());
		int b=Math.abs(column-p.getColumn());
		return a==b;
	}
	
	/**
	 * Converte una posizione in stringa
	 * 
	 * @return Stringa
	 */
	public String toString()
	{
		StringBuffer s=new StringBuffer();
		s.append(line);
		s.append(',');
		s.append(column);
		return s.toString();
	}
	/**
	 * Ritorna true se due posizioni sono uguali, altrimenti false
	 * 
	 * @return booleano
	 */
	public boolean equals(Object obj)
	{
		Position p= (Position) obj;
		int line=p.getLine(), column=p.getColumn();
		if(this.line!=line) return false;
		else if(this.column!=column) return false;
		else return true;
	}
	/**
	 * Converte una stringa in posizione
	 * @param s stringa da convertire
	 * @return Position
	 * @throws NotValidException Se la stringa presenta più di due parametri
	 * @throws FormatException Formato non valido
	 */
	public static Position parsePosition(String s) throws NotValidException, FormatException
	{
		if(s.matches("[0-9]+,+[0-9]"))
		{
			String[] num=s.split(",");
			if(num.length==2)
			{
				int line=Integer.parseInt(num[0]);
				int column=Integer.parseInt(num[1]);
				return new Position(line,column);
			}
			else throw new NotValidException("La posizione ha solo due parametri");
		}
		else throw new FormatException(" Scrivere la posizione nel seguente formato: numero,numero\n");
	}
	
	/**
	 * Costruttore
	 * 
	 * @param line ascissa
	 * @param column ordinata
	 */
	public Position(int line, int column)
	{
		this.line=line;
		this.column=column;
	}

	/**
	 * Costruttore
	 * 
	 * @param start Posizione da copiare
	 */
	public Position(Position start)
	{
		this(start.line,start.column);
	}

}

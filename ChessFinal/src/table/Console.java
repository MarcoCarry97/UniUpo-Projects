package table;

import java.io.IOException;

import chesspieces.Element;
import chesspieces.King;
import chesspieces.OutOfChessTableException;
import jbook.util.Input;

public class Console
{
	public static void main(String[] args) throws KingNotFound, OutOfChessTableException, PositionNullException, FormatException
	{
		final int CHECKMATE = 2;
		final int PATTA = 1;
		final int NIENTE = 0;
		ChessTable ct= new ChessTable();
		int endMatch=NIENTE;
		boolean deadOnLoading = false;
		boolean noExc;
		do
		{
			noExc=true;
			try
			{
				String choice;
				do
				{
					choice = Input.readString("Iniziare una nuova partita(START) o caricarne una gi� iniziata(LOAD)?\n").toUpperCase();
					if (choice.equals("START")) ct.initialize();
					if (choice.equals("LOAD"))
					{
						boolean valid = true;
						do {
							valid = true;
							try {
								ct.loadMatch(Input.readString("Inserire partita da caricare\n"));
							}catch (FormatException e) {
								System.out.println("Nome file non valido, inserire \"nomeFile.txt\"");
								valid = false;
							}
						}while(!valid);
						if (ct.getTurn())
						{
							King k = ct.findKing(Colour.BLACK);
							if (ct.checkmate(Colour.WHITE) == CHECKMATE)
							{
								System.out.println("Il giocatore black ha già vinto");
								deadOnLoading = true;
								endMatch = CHECKMATE;
							}
							if (k.isChecked(k.getPosition(), ct)) {
								System.out.println("Il giocatore white ha già vinto");
								deadOnLoading = true;
								endMatch = PATTA;
							}
							if (ct.checkmate(Colour.WHITE)==PATTA) {
								System.out.println("Partita patta, giocatore bianco non può muovere");
								deadOnLoading = true;
								endMatch = PATTA;
							}
						}
						else
						{
							King k = ct.findKing(Colour.WHITE);
							if (ct.checkmate(Colour.BLACK) == CHECKMATE)  {
								System.out.println("Il giocatore white ha già vinto");
								deadOnLoading = true;
								endMatch=CHECKMATE;
							}
							if (k.isChecked(k.getPosition(), ct)) {
								System.out.println("Il giocatore black ha già vinto");
								deadOnLoading = true;
								endMatch = PATTA;
							}
							if (ct.checkmate(Colour.BLACK)==PATTA) {
								System.out.println("Partita patta, giocatore nero non può muovere");
								deadOnLoading = true;
								endMatch = PATTA;
							}
						}
					}
				}
				while((!choice.equals("START"))&&(!choice.equals("LOAD")));
			}
			catch(NotValidException e)
			{
				noExc = false;
				System.out.println(e.getMessage());
			}
			catch(IOException e)
			{
				noExc = false;
				System.out.println(e.getMessage());
			}
		}
		while(!noExc);
		String player;
		if (ct.getTurn()) player = "white";
		else player = "black";
		Colour colour= Colour.stringToColour(player);
		while(endMatch==NIENTE)
		{
			if (ct.getTurn()) player = "white";
			else player = "black";
			System.out.println("Turno del giocatore "+player);
			System.out.println(ct.toString());
			boolean startPhase=false;
			Position begin=null;
			do
			{
				String input;
				try
				{
					do
					{
						input= Input.readString("Inserire coordinate del pezzo da muovere o digita \"SAVE\" per salvare la partita\n");
						if (input.toUpperCase().equals("SAVE"))
						{
							try
							{
								String name=Input.readString("inserire il nome della partita da salvare");
								//if(!name.matches("[\\w]+.txt"))
									//throw new FormatException("Formato nome file no valido");
								ct.saveMatch(name);
								System.out.println("Partita Salvata");
								
							}
							catch(IOException e)
							{
								System.out.println("Errore durante il salvataggio");
							}
							catch(FormatException e)
							{
								System.out.println(e.getMessage());
							}
						}
					}
					while(input.equals("SAVE"));
					begin=Position.parsePosition(input);
					if(!ct.isInRange(begin)) throw new NotValidException("Posizione fuori dalla scacchiera\n");
					Element e=ct.getElement(begin);
					if(e==null) throw new NotValidException("Posizione Vuota\n");
					else if(!e.getColour().equals(colour)) throw new NotValidException("Puoi spostare solo pezzi di colore "+player+'\n');
					ct.refreshPossiblePosBasic(Colour.reverse(colour));
					e.setPosition();
					if(e.getPossibleSize()==0) throw new NotValidException("Non ho mosse eseguibili per: "+ e.getType()+'\n');
					System.out.println("Mosse del "+e.getType()+" disponibili: "+e.possibleString());
					startPhase=true;
				}
				catch(NotValidException e)
				{
					System.out.print(e.getMessage());
				}
				catch(FormatException e) {
					System.out.println(e.getMessage());
				}
			}
			while(!startPhase);
			boolean endPhase=false;
			Position end=null;
			do
			{
				try
				{
					end=Position.parsePosition(Input.readString("Inserire coordinate della posizione d'arrivo\n"));
					Element e=ct.getElement(begin);
					e.moveTo(end);
					endMatch=ct.checkmate(Colour.reverse(colour));
					if (endMatch!=CHECKMATE)
					{
						if(ct.getTurn()) player="White";
						else player="Black";
						colour=Colour.stringToColour(player);
					}
					endPhase=true;
				}
				catch(NotValidException e)
				{
					System.out.println(e.getMessage());
				}
				catch(NumberFormatException e)
				{
					System.out.println(e.getMessage());
				}
			}
			while(!endPhase);
		}
		if((endMatch == CHECKMATE) && (!deadOnLoading))
		{
			System.out.println("Vince il Giocatore "+ player);
		}
		if((endMatch == PATTA) && (!deadOnLoading)) {
			System.out.println("Partita patta, "+player+" non può muovere");
		}
	}
}

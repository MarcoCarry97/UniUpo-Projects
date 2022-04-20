package chesspieces;

import static org.junit.Assert.*;

import org.junit.Test;

import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public class PawnTest {
	
	ChessTable CT;
	Pawn p;

	@Test
	public void testSetPosition() throws NotValidException, OutOfChessTableException, KingNotFound, PositionNullException
	{
		CT = new ChessTable();
		Pawn PawnEater = new Pawn(Colour.WHITE, new Position(2,2),CT);
		CT.newPiece(PawnEater);
		Pawn Pawn1 = new Pawn(Colour.BLACK, new Position(4,1),CT);
		CT.newPiece(Pawn1);
		Pawn Pawn2 = new Pawn(Colour.BLACK, new Position(3,2),CT);
		CT.newPiece(Pawn2);
		Pawn Pawn3 = new Pawn(Colour.BLACK, new Position(4,3),CT);
		CT.newPiece(Pawn3);
		King k1 = new King(Colour.BLACK, new Position(7,7),CT);
		CT.newPiece(k1);
		King k2 = new King(Colour.WHITE, new Position(0,0),CT);
		CT.newPiece(k2);
		Pawn1.moveTo(new Position(2,1));
		Pawn3.moveTo(new Position(2,3));
		PawnEater.setPosition(); //Test sull'enpassant
		assertEquals(PawnEater.getPossibleSize(),1);
		assertEquals(PawnEater.getPossible(0).toString(),"3,3");
		CT.removeElement(2,1);
		CT.removeElement(2,3);
		Pawn1 = new Pawn(Colour.BLACK, new Position(4,1),CT);
		CT.newPiece(Pawn1);
		Pawn3 = new Pawn(Colour.BLACK, new Position(4,3),CT);
		CT.newPiece(Pawn3);
		Pawn3.moveTo(new Position(2,3));
		Pawn1.moveTo(new Position(2,1));
		PawnEater.setPosition(); //altro test sull'enpassant
		assertEquals(PawnEater.getPossibleSize(),1);
		assertEquals(PawnEater.getPossible(0).toString(),"3,1");
		CT.removeElement(2,1);
		CT.removeElement(2,3);
		PawnEater.setPosition();
		assertEquals(PawnEater.getPossibleSize(),0); //Un pedone non può mangiare un pezzo davanti
		Pawn1 = new Pawn(Colour.BLACK,new Position(3,3),CT);
		CT.newPiece(Pawn1);
		Pawn3 = new Pawn(Colour.BLACK, new Position(3,1),CT);
		CT.newPiece(Pawn3);
		PawnEater.setPosition(); //Test sulla possibilità di cattura standard
		assertEquals(PawnEater.getPossibleSize(),2);
		assertEquals(PawnEater.getPossible(0).toString(),"3,1");
		assertEquals(PawnEater.getPossible(1).toString(),"3,3");
		Pawn1.moveTo(2,3);
		Pawn3.moveTo(2,1);
		PawnEater.setPosition(); //Non può mangiare i pezzi di fianco se non rispettono l'enpassant
		assertEquals(PawnEater.getPossibleSize(),0);
		Pawn1.moveTo(1,3);
		Pawn3.moveTo(1,1);
		PawnEater.setPosition(); //Non posso mangiare i pezzi all'indietro
		assertEquals(PawnEater.getPossibleSize(),0);
		CT.removeElement(1,3);
		CT.removeElement(1,1);
		Pawn1 = new Pawn (Colour.WHITE,new Position(3,1),CT);
		Pawn3 = new Pawn (Colour.WHITE,new Position(3,3),CT);
		CT.newPiece(Pawn1);
		CT.newPiece(Pawn3);
		PawnEater.setPosition();
		assertEquals(PawnEater.getPossibleSize(),0); //Non posso mangiare pezzi dello stesso colore
		CT.removeElement(3,2);
		PawnEater.setPosition();
		assertEquals(PawnEater.getPossibleSize(),2); //Devo poter muovermi di una o due caselle in avanti
		assertEquals(PawnEater.getPossible(0).toString(),"3,2");
		assertEquals(PawnEater.getPossible(1).toString(),"4,2");
		Rook r1 = new Rook(Colour.BLACK,new Position(5,0),CT);
		CT.newPiece(r1);
		r1.setPositionBasic();
		PawnEater.setPosition();
		assertEquals(PawnEater.getPossibleSize(),0);
		System.out.println(CT.toString());
	}
	
	@Test
	public void testToString() throws OutOfChessTableException
	{
		init();
		assertEquals(p.toString(),"PAWN WHITE 3,4 3,4 0");
	}
	
	@Test
	public void testGetType() throws OutOfChessTableException {
		init();
		assertEquals(p.getType(), "PAWN");
	}
	
	@Test
	public void testGetSymbol() throws OutOfChessTableException
	{
		init();
		Pawn q = new Pawn(Colour.BLACK,new Position(3,5),CT);
		assertEquals(p.getSymbol(),'P');
		assertEquals(q.getSymbol(),'p');
	}
	
	@Test
	public void testGetNumPastMoves() throws NotValidException, OutOfChessTableException, KingNotFound, PositionNullException
	{
		init();
		King k1 = new King(Colour.BLACK, new Position(7,7),CT);
		CT.newPiece(k1);
		King k2 = new King(Colour.WHITE, new Position(0,0),CT);
		CT.newPiece(k2);
		p.moveTo(new Position(4,4));
		assertEquals(p.numPastMoves,1);
		p.moveTo(new Position(5,4));
		assertEquals(p.numPastMoves,2);
	}
	
	private void init() throws OutOfChessTableException
	{
		CT = new ChessTable();
		p = new Pawn(Colour.WHITE,new Position(3,4),CT);
		CT.newPiece(p);
	}

}

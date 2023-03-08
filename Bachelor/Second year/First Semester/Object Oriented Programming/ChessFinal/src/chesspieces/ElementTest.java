package chesspieces;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public class ElementTest
{

	Element pawn,bishop,rook,knight,queen,king,king2;
	ChessTable ct;
	
	@Before
	public void setElement() throws NotValidException, OutOfChessTableException
	{
		ct=new ChessTable();
		pawn=new Pawn(Colour.WHITE,new Position(0,0),ct);
		bishop=new Bishop(Colour.WHITE,new Position(0,1),ct);
		rook=new Rook(Colour.WHITE, new Position(0,2), ct);
		knight=new Knight(Colour.WHITE, new Position(0,3),ct);
		queen=new Queen(Colour.WHITE, new Position(0,4),ct);
		king=new King(Colour.WHITE, new Position(0,6),ct);
		king2=new King(Colour.BLACK,new Position(7,6),ct);
		ct.newPiece(pawn);
		ct.newPiece(bishop);
		ct.newPiece(knight);
		ct.newPiece(rook);
		ct.newPiece(queen);
		ct.newPiece(king);
		ct.newPiece(king2);
	}

	@Test
	public void testGetType()
	{
		assertEquals(pawn.getType(),"PAWN");
		assertEquals(bishop.getType(),"BISHOP");
		assertEquals(rook.getType(),"ROOK");
		assertEquals(knight.getType(),"KNIGHT");
		assertEquals(queen.getType(),"QUEEN");
		assertEquals(king.getType(),"KING");
	}

	@Test
	public void testGetColour()
	{
		assertEquals(pawn.getColour(),Colour.WHITE);
		assertEquals(bishop.getColour(),Colour.WHITE);
		assertEquals(rook.getColour(),Colour.WHITE);
		assertEquals(knight.getColour(),Colour.WHITE);
		assertEquals(queen.getColour(),Colour.WHITE);
		assertEquals(king.getColour(),Colour.WHITE);
	}

	@Test
	public void testGetPosition()
	{
		assertEquals(pawn.getPosition(),new Position(0,0));
		assertEquals(bishop.getPosition(),new Position(0,1));
		assertEquals(rook.getPosition(),new Position(0,2));
		assertEquals(knight.getPosition(),new Position(0,3));
		assertEquals(queen.getPosition(),new Position(0,4));
		assertEquals(king.getPosition(),new Position(0,6));	
	}

	@Test
	public void testEat() throws NotValidException, OutOfChessTableException, KingNotFound, PositionNullException
	{
		Element p1= new Pawn(Colour.BLACK,new Position(1,1), ct);
		ct.newPiece(p1);
		Element p2= new Pawn(Colour.BLACK,new Position(4,5), ct);
		ct.newPiece(p2);
		Element p3= new Pawn(Colour.BLACK,new Position(3,2), ct);
		ct.newPiece(p3);
		Element p4= new Pawn(Colour.BLACK,new Position(2,4), ct);
		ct.newPiece(p4);
		Element pq= new Pawn(Colour.BLACK,new Position(4,6), ct);
		ct.newPiece(pq);
		Element p6= new Pawn(Colour.BLACK,new Position(2,4), ct);
		ct.newPiece(p6);
		System.out.println(ct.getElement(1,1).toString());
		System.out.println(pawn.toString());
		System.out.println(pawn.possibleString());
		System.out.println(ct.toString());
		pawn.moveTo(1,1);
		System.out.println(ct.toString());
		//System.out.println(ct.getElement(1,1).toString());
		//System.out.println(pawn.toString());
		assertTrue(ct.getElement(1,1) instanceof Pawn);
		
		
		bishop.moveTo(4,5);
		//System.out.println(bishop.possibleString());
		//assertTrue(ct.getElement(4,5) instanceof Bishop);
		
		
		//System.out.println(rook.possibleString());
		rook.moveTo(3,2);
		assertTrue(ct.getElement(3,2) instanceof Rook);
		
		//System.out.println(queen.possibleString());
		queen.moveTo(2,4);
		assertTrue(ct.getElement(2,4) instanceof Queen);
		
		queen.moveTo(4,6);
		assertTrue(ct.getElement(4,6) instanceof Queen);
		
		Element p5= new Pawn(Colour.BLACK,new Position(0,7), ct);
		ct.newPiece(p5);
		king.moveTo(0,7);
		assertTrue(ct.getElement(0,7) instanceof King);

		knight.moveTo(2,4);
		assertTrue(ct.getElement(2,4) instanceof Knight);
	}

	@Test
	public void testMoveToPosition() throws NotValidException, KingNotFound, PositionNullException, OutOfChessTableException
	{
		Position p= new Position(1,0);
		Position b= new Position(6,7);
		Position r1= new Position(2,2);
		Position r2= new Position(2,5);
		Position k= new Position(2,2);
		Position q1= new Position(2,4);
		//Position q2= new Position(2,6);
		Position q3= new Position(0,4);
		Position k1= new Position(1,6);
		Position k2= new Position(1,7);
		Position k3= new Position(0,6);
		pawn.moveTo(p);
		assertTrue(ct.getElement(p) instanceof Pawn);
		bishop.moveTo(b);
		assertTrue(ct.getElement(b) instanceof Bishop);
		rook.moveTo(r1);
		assertTrue(ct.getElement(r1) instanceof Rook);
		rook.moveTo(r2);
		assertTrue(ct.getElement(r2) instanceof Rook);
		knight.moveTo(k);
		assertTrue(ct.getElement(k) instanceof Knight);
		queen.moveTo(q1);
		assertTrue(ct.getElement(q1) instanceof Queen);
		//queen.moveTo(q2);
		//assertTrue(ct.getElement(q2) instanceof Queen);
		queen.moveTo(q3);
		assertTrue(ct.getElement(q3) instanceof Queen);
		assertNull(ct.getElement(k1));
		king.moveTo(k1);
		assertTrue(ct.getElement(k1) instanceof King);
		king.moveTo(k2);
		assertTrue(ct.getElement(k2) instanceof King);
		king.moveTo(k3);
		assertTrue(ct.getElement(k3) instanceof King);
	}

	@Test
	public void testMoveToIntInt() throws NotValidException, KingNotFound, PositionNullException, OutOfChessTableException
	{
		//System.out.println(ct.toString());
		pawn.moveTo(1,0);
		//for(int i=0;i<bishop.getPossibleSize();i++)
			//System.out.println(bishop.getPossible(i));
		bishop.moveTo(6,7);
		
		rook.moveTo(2,2);
		rook.moveTo(2,5);
		
		knight.moveTo(2,2);
		knight.moveTo(0,3);
		queen.moveTo(2,4);
		
		//queen.moveTo(2,6);
		
		queen.moveTo(0,4);
		
		king.moveTo(1,6);
		king.moveTo(1,7);
		king.moveTo(0,6);
	}
	
	@Test
	public void TestEnPassant() throws NotValidException, OutOfChessTableException, KingNotFound, PositionNullException
	{
		Element w= new Pawn(Colour.WHITE,new Position(1,5), ct);
		Element b= new Pawn(Colour.BLACK,new Position(6,4), ct);
		ct.newPiece(w);
		ct.newPiece(b);
		System.out.println(ct.toString());
		w.moveTo(3,5);
		w.moveTo(4,5);
		b.moveTo(4,4);
		System.out.println(ct.toString());
		w.moveTo(5,4);
		System.out.println(ct.toString());
	}
	
	@Test
	public void TestKing() throws OutOfChessTableException, KingNotFound, PositionNullException
	{
		Element w= new King(Colour.WHITE,new Position(2,5), ct);
		Element b= new King(Colour.BLACK,new Position(6,5), ct);
		ct.newPiece(w);
		ct.newPiece(b);
		try
		{
			w.moveTo(3,5);
			b.moveTo(5,5);
			w.moveTo(4,5);
			fail("Nessuna eccezione");
		}
		catch(NotValidException e)
		{
			assertNull(ct.getElement(4, 5));
			assertTrue(ct.getElement(5,5) instanceof King);
		}
	}
}

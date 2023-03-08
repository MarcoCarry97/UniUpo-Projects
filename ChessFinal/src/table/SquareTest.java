package table;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import chesspieces.*;

public class SquareTest {
	ChessTable ct;
	Element e;
	Square s;
	
	@Before
	public void init() throws OutOfChessTableException {
		ct=new ChessTable();
		e = new Rook(Colour.WHITE,new Position(0,0), ct);
		s = new Square (e,Colour.BLACK);
	}
	@Test
	public void testGetElement() throws OutOfChessTableException {
		init();
		assertEquals(s.getElement(),e); 
	}
	
	@Test
	public void testChangeElement() throws OutOfChessTableException {
		Element f = new Rook(Colour.BLACK,new Position(0,1), ct);
		s.changeElement(f);
		assertEquals(s.getElement(),f);
	}

}

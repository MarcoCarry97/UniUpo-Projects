package chesspieces;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import table.ChessTable;
import table.Colour;
import table.Position;

public class BishopTest {
	
	ChessTable CT;
	Bishop b;

	@Test
	public void testSetPositionBasic() {
		b.setPositionBasic();
		assertEquals(b.getPossibleSize(),13);
	}
	
	@Test
	public void testGetType() {
		assertEquals(b.getType(),"BISHOP");
	}
	
	@Test
	public void testGetSymbol() throws OutOfChessTableException {
		assertEquals(b.getSymbol(),'B');
		Bishop b2 = new Bishop(Colour.BLACK, new Position(0,0),CT);
		assertEquals(b2.getSymbol(),'b');
	}
	
	@Before
	public void init() throws OutOfChessTableException {
		CT = new ChessTable();
		b = new Bishop(Colour.WHITE,new Position(3,3),CT);
	}
}

package chesspieces;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import table.ChessTable;
import table.Colour;
import table.Position;

public class RookTest
{

	ChessTable CT;
	Rook r;

	@Test
	public void testSetPositionBasic() {
		r.setPositionBasic();
		assertEquals(r.getPossibleSize(),14);
	}
	
	@Test
	public void testGetType() {
		assertEquals(r.getType(),"ROOK");
	}
	
	@Test
	public void testGetSymbol() throws OutOfChessTableException {
		assertEquals(r.getSymbol(),'R');
		Rook r2 = new Rook(Colour.BLACK, new Position(0,0),CT);
		assertEquals(r2.getSymbol(),'r');
	}
	
	@Before
	public void init() throws OutOfChessTableException {
		CT = new ChessTable();
		r = new Rook(Colour.WHITE,new Position(3,3),CT);
	}

}

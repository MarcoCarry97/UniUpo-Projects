package chesspieces;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import chesspieces.Knight;
import table.ChessTable;
import table.Colour;
import table.Position;

public class KnightTest {
	ChessTable CT;
	Knight h;
	

	@Test
	public void testSetPositionBasic() throws OutOfChessTableException {
		init();
		h.setPositionBasic();
		assertEquals(h.getPossibleSize(),8);
	}
	
	@Before
	public void init() throws OutOfChessTableException {
		CT = new ChessTable();
		h = new Knight(Colour.WHITE,new Position(3,3), CT);
		CT.newPiece(h);
	}
}

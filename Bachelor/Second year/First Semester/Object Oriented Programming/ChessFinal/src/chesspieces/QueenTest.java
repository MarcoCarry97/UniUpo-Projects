package chesspieces;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import table.ChessTable;
import table.Colour;
import table.Position;

public class QueenTest {

	ChessTable CT;
	Queen q;

	@Test
	public void testSetPositionBasic() {
		q.setPositionBasic();
		System.out.println(CT.toString());
		for (Position x:q.getPossiblePos()) System.out.println(x.toString());
		assertEquals(q.getPossibleSize(),27);
	}
	
	@Test
	public void testGetType() {
		assertEquals(q.getType(),"QUEEN");
	}
	
	@Test
	public void testGetSymbol() throws OutOfChessTableException {
		assertEquals(q.getSymbol(),'Q');
		Queen q2 = new Queen(Colour.BLACK, new Position(0,0),CT);
		assertEquals(q2.getSymbol(),'q');
	}
	
	@Before
	public void init() throws OutOfChessTableException {
		CT = new ChessTable();
		q = new Queen(Colour.WHITE,new Position(3,3),CT);
		CT.newPiece(q);
	}
}

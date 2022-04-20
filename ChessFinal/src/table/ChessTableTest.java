package table;

import chesspieces.*;
import static org.junit.Assert.*;

import java.io.FileNotFoundException;
import java.io.IOException;
//import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

public class ChessTableTest {
	
	
	ChessTable CT;
	
	@Before
	public void init() throws NotValidException, OutOfChessTableException {
		CT = new ChessTable();
		CT.initialize();
	}
	
//	@Test
//	public void testEaten() {
//		CT.eaten(CT.getElement(new Position(0,0)));
//		assertEquals(CT.getWhiteEaten().size(),1);
//		assertTrue(CT.isFree(new Position(0,0)));
//	}
	
	@Test
	public void testGetElement() throws OutOfChessTableException {
		Element e = CT.getElement(0,0);
		Element f = new Rook(Colour.WHITE, new Position(0,0),CT);
		assertTrue(confrontaElement(e,f));
	}
	
	@Test
	public void testPut() throws NotValidException, KingNotFound, PositionNullException, OutOfChessTableException {
		Element e = new Pawn(Colour.WHITE, new Position(2,3),CT);
		CT.newPiece(e);
		e.moveTo(3,3);
		assertEquals(e.getPosition(),new Position(3,3));
		/*ChessTable.put(e.getPosition(), new Position(4,3));
		assertEquals(e,ChessTable.getElement(0,0));
		assertEquals(e.getPosition().getLine(), 0);
		assertEquals(e.getPosition().getColumn(),0);
		assertEquals(ChessTable.getElement(new Position(2,3)),null);*/
	}
	
	@Test
	public void testIsFree() {
		for (int i=2; i<6; i++) {
			for(int j=0;j<7;j++) {
				assertTrue(CT.isFree(new Position(i,j)));
			}
		}
	}
	
	@Test
	public void testRemoveElement(){
		Position p = new Position(0,0);
		CT.removeElement(p);
		assertEquals(CT.getElement(p),null);
	}
	
	
	@Test
	public void testSaveMatch() throws FileNotFoundException, FormatException{
		CT.saveMatch("Prova.txt");
	}
	
	@Test
	public void testLoadMatch() throws IOException, NotValidException, FormatException{
		ChessTable CT2 = new ChessTable();
		CT2.loadMatch("Prova.txt");
		assertEquals(CT.toString(), CT2.toString());
	}
	
	
	private boolean confrontaElement(Element a, Element b) {
		return ((a.getClass() == b.getClass()) && (a.getPosition().sameColumn(b.getPosition())) && (a.getPosition().sameLine(b.getPosition())) && (a.getColour()== b.getColour()));
	}

}

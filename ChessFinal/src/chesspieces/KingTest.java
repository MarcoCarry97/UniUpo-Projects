package chesspieces;

import static org.junit.Assert.*;

import org.junit.Test;

import table.ChessTable;
import table.Colour;
import table.KingNotFound;
import table.NotValidException;
import table.Position;
import table.PositionNullException;

public class KingTest {
	
	ChessTable CT;
	King k;

	@Test
	public void testSetPosition() throws NotValidException, OutOfChessTableException, KingNotFound, PositionNullException {
		init(new Position(0,2));
		King k2 = new King (Colour.BLACK,new Position(1,2),CT); //Posiziono due re di fronte N.B. nel gioco vero questa situazione non può mai verificarsi
		CT.newPiece(k2);
		k2.setPosition();
		k.setPosition();
		assertEquals(k.getPossibleSize(),1); //k potrebbe solamente mangiare il re avversario
		k2.setPosition();
		assertEquals(k2.getPossibleSize(),4); //k2 può mangiare il re avversario o scappare nelle posizioni indietro
		CT.removeElement(k2);
		k2 = new King (Colour.BLACK,new Position(5,1),CT);
		CT.newPiece(k2);
		Rook r1 = new Rook(Colour.BLACK,new Position(0,0),CT);
		CT.newPiece(r1);
		Rook r2 = new Rook (Colour.BLACK, new Position(1,0),CT); //Queste torri mettono in scacco matto il re avversario
		CT.newPiece(r2);
		r1.setPosition();
		r2.setPosition();
		k.setPosition();
		assertEquals(k.getPossibleSize(),0); //Il re non ha più movimenti possibili, scacco matto
		CT.removeElement(r1);
		CT.removeElement(r2);
		Bishop B = new Bishop(Colour.BLACK,new Position(1,3),CT);
		CT.newPiece(B);
		r1 = new Rook(Colour.BLACK, new Position(2,3),CT); //Se il re mangia l'alfiere si trova in una situazione di scacco, quindi la mossa non deve essere possibile
		CT.newPiece(r1);
		B.setPosition();
		r1.setPosition();
		k.setPosition();
		assertFalse(k.getPossiblePos().contains(new Position(1,3))); //Il re non deve poter mangiare l'alfiere
		assertEquals(k.getPossibleSize(), 4); //Però può muoversi nelle restanti 4 posizioni adiacenti
		CT.removeElement(B);;
		CT.removeElement(r1);
		k2.moveTo(new Position(6,1));
		k.moveTo(1,2);
		r1 = new Rook(Colour.BLACK,new Position(7,2),CT);
		CT.newPiece(r1);
		B = new Bishop(Colour.WHITE, new Position(3,2),CT);
		CT.newPiece(B);
		r1.setPosition();
		B.setPosition();
		assertEquals(B.getPossibleSize(),0); //L'alfiere non può togliersi perché causerebbe lo scacco matto
	}
	
	@Test
	public void testMoveTo() throws OutOfChessTableException, PositionNullException, KingNotFound {
		init(new Position(0,3));
		k.setPosition();
		try {
			Pawn p1 = new Pawn(Colour.BLACK,new Position(1,2),CT);
			CT.newPiece(p1);
			Pawn p2 = new Pawn(Colour.BLACK,new Position(2,2),CT);
			CT.newPiece(p2);
			Pawn p4 = new Pawn(Colour.BLACK,new Position(3,4),CT);
			CT.newPiece(p4);
			Pawn p5 = new Pawn(Colour.BLACK,new Position(2,5),CT);
			CT.newPiece(p5);
			Pawn p6 = new Pawn(Colour.BLACK,new Position(1,5),CT);
			CT.newPiece(p6);
			Pawn p7 = new Pawn(Colour.BLACK,new Position(0,4),CT); //Posiziono dei pedoni da mangiare
			CT.newPiece(p7);
			King k2 = new King(Colour.BLACK, new Position(6,7),CT);
			CT.newPiece(k2);
			k.moveTo(new Position(1,2));
			k.moveTo(new Position(2,2));
			Pawn p3 = new Pawn(Colour.BLACK,new Position(3,3),CT);
			CT.newPiece(p3);
			k.moveTo(new Position(3,3));
			k.moveTo(new Position(3,4));
			k.moveTo(new Position(2,5));
			k.moveTo(new Position(1,5));
			k.moveTo(new Position(0,4));
			Pawn p8 = new Pawn(Colour.BLACK,new Position(0,3),CT);
			CT.newPiece(p8);
			k.moveTo(new Position(0,3)); //Li mangio tutti
			k.moveTo(1,2);
			k.moveTo(2,2);
			k.moveTo(3,3);
			k.moveTo(3,4);
			k.moveTo(2,5);
			k.moveTo(1,5);
			k.moveTo(0,4);
			k.moveTo(0,3); //Verifico che possa muoversi anche senza mangiare
			p1 = new Pawn(Colour.BLACK, new Position(2,3),CT);
			CT.newPiece(p1);
			p1.setPosition();
			k.setPosition();
			k.moveTo(new Position(1,3)); //Mi sposto verso il pedone, verifico che il programma non pensi erroneamente che quella posizione non sia disponibile perché teoricamente ci si poteva spostare anche il pedone
			//CT.removeElement(p1);
		}catch(NotValidException e) {
			fail("Mossa non valida");
		}
		try {
			k.moveTo(new Position(3,3));
			fail("Eccezione non raggiunta"); //Non deve essere un movimento possibile
		}catch(NotValidException e) {}
		CT.removeElement(k);
		try {
			King k2 = new King(Colour.BLACK,new Position(7,4),CT); //Provo i quattro possibili arrocchi
			CT.newPiece(k2);
			k2.setPosition();
			Rook r1 = new Rook(Colour.BLACK,new Position(7,0),CT);
			CT.newPiece(r1);
			r1.setPosition();
			k2.moveTo(new Position(7,2));
			assertEquals(k2.getPosition(), new Position(7,2));
			assertEquals(r1.getPosition(), new Position(7,3));
			CT.removeElement(k2);
			CT.removeElement(r1);
		}catch(NotValidException e) {
			fail("Mossa non valida");
		}
		try {
			King k2 = new King(Colour.BLACK, new Position(7,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.BLACK,new Position(7,7),CT);
			CT.newPiece(r1);
			k2.moveTo(new Position(7,6));
			assertEquals(k2.getPosition(), new Position(7,6));
			assertEquals(r1.getPosition(), new Position(7,5));
			CT.removeElement(k2);
			CT.removeElement(r1);
		}catch(NotValidException e) {
			fail("Mossa non valida");
		}
		try {
			King k2 = new King(Colour.WHITE,new Position(0,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,0),CT);
			CT.newPiece(r1);
			k2.setPosition();
			k2.moveTo(new Position(0,2));
			assertEquals(k2.getPosition(), new Position(0,2));
			assertEquals(r1.getPosition(), new Position(0,3));
			CT.removeElement(k2);
			CT.removeElement(r1);
		}catch(NotValidException e) {
			fail("Mossa non valida");
		}
		try {
			King k2 = new King(Colour.WHITE, new Position(0,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,7),CT);
			CT.newPiece(r1);
			Pawn p1 = (Pawn)CT.getElement(2, 3);
			p1.setPosition();
			k2.moveTo(new Position(0,6));
			assertEquals(k2.getPosition(), new Position(0,6));
			assertEquals(r1.getPosition(), new Position(0,5));
			CT.removeElement(k2);
			CT.removeElement(r1);
		}catch(NotValidException e) {
			fail("Mossa non valida");
		}
		try { //Arrocco non possibile, la posizione intermedia è sotto scacco
			King k2 = new King(Colour.WHITE, new Position(0,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,7),CT);
			CT.newPiece(r1);
			k = new King (Colour.BLACK, new Position(3,2),CT);
			CT.newPiece(k);
			Rook r = new Rook(Colour.BLACK, new Position(7,5),CT);
			CT.newPiece(r);
			r.setPositionBasic();
			k2.moveTo(new Position(0,6));
			fail("La mossa deve sollevare un'eccezione");
		}catch(NotValidException e) {
			CT.removeElement(new Position(0,4));
			CT.removeElement(new Position(0,7));
			CT.removeElement(new Position(7,4));
		}
		try { //Arrocco non possibile, la posizione finale è sotto scacco
			King k2 = new King(Colour.WHITE, new Position(0,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,7),CT);
			CT.newPiece(r1);
			Rook r = new Rook(Colour.BLACK, new Position(7,6),CT);
			CT.newPiece(r);
			r.setPosition();
			k2.moveTo(new Position(0,6));
			fail("La mossa deve sollevare un'eccezione");
		}catch(NotValidException e) {
			CT.removeElement(new Position(0,4));
			CT.removeElement(new Position(0,7));
		}
		try { //Arrocco non possibile, il re è sotto scacco
			King k2 = new King(Colour.WHITE, new Position(0,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,7),CT);
			CT.newPiece(r1);
			Rook r = new Rook(Colour.BLACK, new Position(7,4),CT);
			CT.newPiece(r);
			r.setPosition();
			k2.moveTo(new Position(0,6));
			fail("La mossa deve sollevare un'eccezione");
		}catch(NotValidException e) {
			CT.removeElement(new Position(0,4));
			CT.removeElement(new Position(0,7));
		}
		try { //Arrocco non possibile, la posizione intermedia è occupata
			King k2 = new King(Colour.WHITE, new Position(0,4),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,7),CT);
			CT.newPiece(r1);
			Queen q = new Queen(Colour.WHITE, new Position(0,5),CT);
			CT.newPiece(q);
			q.setPosition();
			k2.moveTo(new Position(0,6));
			fail("La mossa deve sollevare un'eccezione");
		}catch(NotValidException e) {
			CT.removeElement(new Position(0,4));
			CT.removeElement(new Position(0,7));
		}
		try { //Arrocco non possibile, il re è troppo distante dalla torre
			King k2 = new King(Colour.WHITE, new Position(0,3),CT);
			CT.newPiece(k2);
			Rook r1 = new Rook(Colour.WHITE,new Position(0,7),CT);
			CT.newPiece(r1);
			k2.moveTo(new Position(0,5));
			fail("La mossa deve sollevare un'eccezione");
		}catch(NotValidException e) {
			CT.removeElement(new Position(0,4));
			CT.removeElement(new Position(0,7));
		}
	}
	
	@Test
	public void testGetType() throws OutOfChessTableException {
		init(new Position(0,0));
		assertEquals(k.getType(), "KING");
	}
	
	@Test
	public void testSetPositionBasic() throws OutOfChessTableException {
		init(new Position(4,4));
		k.setPositionBasic();
		assertEquals(k.getPossibleSize(),8);
		King k2 = new King(Colour.BLACK,new Position(7,4),CT);
		CT.newPiece(k2);
		Rook r = new Rook(Colour.BLACK, new Position(7,7),CT);
		CT.newPiece(r);
		k2.setPositionBasic();
		assertEquals(k2.getPossibleSize(),6);
		assertTrue(k2.getPossiblePos().contains(new Position(7,6)));
		CT.removeElement(k2);
		CT.removeElement(k);
		CT.removeElement(r);
		k = new King (Colour.WHITE, new Position(0,0),CT);
		k.setPositionBasic();
		assertEquals(k.getPossibleSize(),3);
		CT.removeElement(k);
		k = new King (Colour.WHITE, new Position(7,7),CT);
		k.setPositionBasic();
		assertEquals(k.getPossibleSize(),3);
		Pawn p1 = new Pawn(Colour.WHITE,new Position(7,6),CT);
		CT.newPiece(p1);
		Pawn p2 = new Pawn(Colour.WHITE,new Position(6,6),CT);
		CT.newPiece(p2);
		Pawn p3 = new Pawn(Colour.WHITE,new Position(6,7),CT);
		CT.newPiece(p3);
		k.setPositionBasic();
		assertEquals(k.getPossibleSize(),0);
	}
	private void init(Position p) throws OutOfChessTableException {
		CT = new ChessTable();
		k = new King(Colour.WHITE, p,CT);
		CT.newPiece(k);
	}

}

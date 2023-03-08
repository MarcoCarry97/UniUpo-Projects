package table;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class PositionTest
{
	Position p, q, r, s, t;
	
	@Before
	public void set()
	{
		p=new Position(1,3);
		q=new Position(5,3);
		r=new Position(5,7);
		s=new Position(6,3);
		t=new Position(7,4);	
	}
	
	@Test
	public void testGetLine()
	{
		assertTrue(p.getLine()==1);
		assertTrue(q.getLine()==5);
		assertTrue(r.getLine()==5);
		assertTrue(s.getLine()==6);
		assertTrue(t.getLine()==7);
	}

	@Test
	public void testGetColumn()
	{
		assertTrue(p.getColumn()==3);
		assertTrue(q.getColumn()==3);
		assertTrue(r.getColumn()==7);
		assertTrue(s.getColumn()==3);
		assertTrue(t.getColumn()==4);
	}

	@Test
	public void testDistance()
	{
		assertTrue(p.distance(q)==4);
		assertTrue(q.distance(r)==4);
		assertTrue(r.distance(s)==-1);
		assertTrue(s.distance(t)==1);
		assertTrue(t.distance(p)==-1);
	}

	@Test
	public void testUpdateIntInt()
	{
		assertTrue(p.getLine()==1);
		assertTrue(p.getColumn()==3);
		p.update(q.getLine(), q.getColumn());
		assertTrue(p.getLine()==5);
		assertTrue(p.getColumn()==3);
	}

	@Test
	public void testUpdatePosition()
	{
		assertTrue(p.getLine()==1);
		assertTrue(p.getColumn()==3);
		p.update(q);
		assertTrue(p.getLine()==5);
		assertTrue(p.getColumn()==3);
	}

	@Test
	public void testSameLine()
	{
		assertTrue(q.sameLine(r));
		assertFalse(q.sameLine(p));
	}

	@Test
	public void testSameColumn()
	{
		assertTrue(p.sameColumn(q));
		assertFalse(p.sameColumn(t));
	}

	@Test
	public void testSameDiagonal()
	{
		assertFalse(p.sameDiagonal(q));
		assertTrue(s.sameDiagonal(t));
	}

	@Test
	public void testToString()
	{
		assertEquals(p.toString(),"1,3");
		assertEquals(q.toString(),"5,3");
		assertEquals(r.toString(),"5,7");
		assertEquals(s.toString(),"6,3");
		assertEquals(t.toString(),"7,4");
	}

	@Test
	public void testParsePosition() throws FormatException
	{
		String s=new String("2,3");
		Position p=new Position(2,3);
		try
		{
			assertEquals(p,Position.parsePosition(s));
		}
		catch(NotValidException e)
		{
			fail("Stringa non convertita");
		}
	}
	
	@Test
	public void testEqualsObject()
	{
		Position u= new Position(p.getLine(),p.getColumn());
		assertEquals(p,u);
	}
}

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;

public class SoftwareSystemTest
{
	public SoftwareSystem systemCycle;
	public SoftwareSystem systemNotCycle;
	
	@Before
	public void set()
	{
		systemCycle=new SoftwareSystem(new DirectedGraph("3;0 1;1 2;2 0"));
		systemNotCycle=new SoftwareSystem(new DirectedGraph("3;0 1;0 2;1 2"));
	}
	
	@Test
	public void testSoftwareSystem()
	{
		assertNotNull(systemCycle);
		assertNotNull(systemNotCycle);
	}

	@Test
	public void testHasCycle()
	{
		assertTrue(systemCycle.hasCycle());
		assertFalse(systemNotCycle.hasCycle());
	}

	@Test
	public void testGetCycle()
	{
		ArrayList<Integer> cycle=systemCycle.getCycle();
		assertNotNull(cycle);
		assertNull(systemNotCycle.getCycle());
		System.out.println(cycle.toString());
		assertEquals(cycle.size(),3);
	}
}

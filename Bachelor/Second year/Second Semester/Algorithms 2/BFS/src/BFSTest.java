import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;
import it.uniupo.graphLib.UndirectedGraph;

public class BFSTest
{

	public BFS dirBFS;
	public BFS undirBFS;
	
	@Before
	public void set()
	{
		dirBFS=new BFS(new DirectedGraph("3;0 1;1 2;2 0"));
		undirBFS= new BFS(new UndirectedGraph("4;0 2;0 1;2 3;1 3"));
	}
	
	@Test
	public void testCreate()
	{
		assertNotNull(dirBFS);
		assertNotNull(undirBFS);
	}
	
	@Test
	public void testVisitedNodes()
	{
		ArrayList<Integer> retDir=dirBFS.getNodesInOrderToVisit(1);
		ArrayList<Integer> retUndir=undirBFS.getNodesInOrderToVisit(2);
		assertEquals(retDir.size(),3);
		assertEquals(retUndir.size(),4);
	}
	

}

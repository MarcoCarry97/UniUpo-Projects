import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;
import it.uniupo.graphLib.GraphInterface;
import it.uniupo.graphLib.UndirectedGraph;

public class DFSTest
{
	DFS dirVisit, undirVisit;
	GraphInterface dirGraph,undirGraph;
	
	@Before
	public void set()
	{
		dirGraph=new DirectedGraph("3;0 1;1 2;2 0");
		undirGraph=new UndirectedGraph("3;0 1;1 2;2 0");
		dirVisit = new DFS(dirGraph);
		undirVisit = new DFS(undirGraph);
	}
	
	@Test
	public void testCreate()
	{
		assertNotNull(dirVisit);
		assertNotNull(undirVisit);
	}

	@Test
	public void testFound()
	{
		dirVisit.getTree(0);
		undirVisit.getTree(0);
	}
	
	@Test
	public void testNumberOfEdges()
	{
		GraphInterface dirTree=dirVisit.getTree(0);
		GraphInterface undirTree=undirVisit.getTree(0);
		assertEquals(dirTree.getEdgeNum(),dirTree.getOrder());
		assertEquals(undirTree.getEdgeNum(),undirTree.getOrder());
	}
	
	@Test
	public void testViewedNodes()
	{
		GraphInterface dirTree=dirVisit.getTree(0);
		GraphInterface undirTree=undirVisit.getTree(0);
		BFS dirBFS=new BFS(dirTree);
		BFS undirBFS=new BFS(undirTree);
		//assertEquals(dirGraph.getOrder(),dirBFS.getNodesInOrderToVisit(0).size());
		assertEquals(undirGraph.getOrder(),undirBFS.getNodesInOrderToVisit(0).size());
	}
	
	@Test
	public void testDFSEdges()
	{
		GraphInterface dirTree=dirVisit.getTree(0);
		GraphInterface undirTree=undirVisit.getTree(0);
		assertTrue(dirTree.hasEdge(0,1));
		assertTrue(dirTree.hasEdge(1,2));
		assertFalse(dirTree.hasEdge(2,0));
		assertTrue(undirTree.hasEdge(0,1));
		assertTrue(undirTree.hasEdge(1,2));
		assertFalse(undirTree.hasEdge(2,0));
	}
}
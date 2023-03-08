import java.util.ArrayList;
import java.util.Stack;

import it.uniupo.graphLib.Edge;
import it.uniupo.graphLib.GraphInterface;

public class DFS
{
	private GraphInterface graph;
	boolean[] found;
	
	public DFS(GraphInterface graph)
	{
		this.graph=graph;
		found=new boolean[graph.getOrder()];
	}

	private void makeTree(int node, int[] father )
	{
		for(int neighbour: graph.getNeighbors(node))
			if(!found[neighbour])
			{
				found[neighbour]=true;
				father[node]=neighbour;
				makeTree(neighbour,father);
			}
	}
	
	public GraphInterface getTree(int supply)
	{
		GraphInterface tree=graph.create();
		int father[]=new int[graph.getOrder()];
		found[supply]=true;
		father[supply]=-1;
		makeTree(supply,father);
		for(int i=graph.getOrder()-1;i>=0;i--)
			if(father[i]!=-1)
				tree.addEdge(father[i],i);
		return tree;	
	}
}

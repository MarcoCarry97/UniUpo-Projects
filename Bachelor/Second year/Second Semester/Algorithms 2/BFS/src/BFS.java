import java.util.ArrayList;
import java.util.Collection;

import it.uniupo.graphLib.GraphInterface;

public class BFS
{
	GraphInterface graph;
	ArrayList<Integer> queue;
	
	public BFS(GraphInterface graph)
	{
		this.graph=graph;
		queue= new ArrayList<Integer>();
		
	}
	
	public ArrayList<Integer> getNodesInOrderToVisit(int supply)
	{
		ArrayList<Integer> result= new ArrayList<Integer>();
		queue.add(supply);
		while(!queue.isEmpty())
		{
			int node=queue.remove(0);
			Iterable<Integer> neighbours=graph.getNeighbors(node);
			for(int i: neighbours) 
				if(!result.contains(i))
				{
					result.add(i);
					queue.add(i);
				}
		}
		return result;
	}
}

import java.util.ArrayList;

import it.uniupo.graphLib.DirectedGraph;

public class SoftwareSystem
{
	private DirectedGraph graph;
	private boolean[] found;
	private boolean[] terminated;
	private int[] father;
	
	public SoftwareSystem(DirectedGraph graph)
	{
		this.graph=graph;
		found=new boolean[graph.getOrder()];
		terminated=new boolean[graph.getOrder()];
	}
	
	public boolean hasCycle()
	{
		reset(found);
		reset(terminated);
		boolean ret=false;
		for(int i=0;i<graph.getOrder() && !ret;i++)
			if(!found[i])
				ret=findNodes(i);
		return ret;
	}
	
	private boolean findNodes(int node)
	{
		found[node]=true;
		boolean ret=false;
		for(int neighbour:graph.getNeighbors(node))
			if(!found[neighbour] && !ret)
				ret=findNodes(neighbour);
			else if(!terminated[neighbour])
				ret=true;
		terminated[node]=true;
		return ret;
	}
	
	public ArrayList<Integer> getCycle()
	{
		reset(found);
		reset(terminated);
		father=new int[graph.getOrder()];
		for(int i=0;i<father.length;i++) father[i]=-1;
		ArrayList<Integer> ret=new ArrayList<Integer>();
		for(int i=0;i<graph.getOrder() && ret.size()==0;i++)
			if(!found[i]) ret.addAll(findCycle(i));
		return (ret.size()!=0) ? ret : null;
	}
	
	private ArrayList<Integer> findCycle(int node)
	{
		found[node]=true;
		ArrayList<Integer> result=new ArrayList<Integer>();
		for(int neighbour:graph.getNeighbors(node))
		{
			if(!found[neighbour])
			{
				father[neighbour]=node;
				for(int v:findCycle(neighbour))
					result.add(v);
			}
			else if(!terminated[neighbour])
			{
				int v=node;
				result.add(v);
				while(father[v]!=neighbour)
				{
					if(v==-1) result.add(father[v]);
					v=father[v];
				}
			}
		}
		terminated[node]=true;
		return result;
	}
	
	private void reset(boolean array[])
	{
		for(int i=0;i<array.length;i++)
			array[i]=false;
	}
}

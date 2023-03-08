
public class IDCT2D implements Transform
{
	private double source[][];
	private double result[][];
	
	@Override
	public void setSourceData(Object src)
	{
		source=(double[][]) src;
	}

	@Override
	public void calculate()
	{
		result=new double[source.length][source[0].length];
		for(int x=0;x<source.length;x++)
		{
			for(int y=0;y<source[x].length;y++)
			{
				double sum=0;
				for(int u=0;u<source.length;u++)
				{
					double a=alpha(u);
					double fractu=(2.0*x+1)*u*Math.PI/(2*source.length);
					double cosu=Math.cos(fractu);
					for(int v=0;v<source[u].length;v++)
					{
						double b=alpha(v);
						double fractv=(2.0*y+1)*v*Math.PI/(2*source.length);
						double cosv=Math.cos(fractv);
						sum+=a*b*source[u][v]*cosu*cosv;
					}
				}
				result[x][y]=sum;
			}
		}
	}

	@Override
	public Object getResults()
	{
		return result;
	}
	
	private double alpha(int k)
	{
		int ret=0;
		if(k==0) ret=1;
		else ret=2;
		return Math.sqrt((double)ret/source.length);
	}
}

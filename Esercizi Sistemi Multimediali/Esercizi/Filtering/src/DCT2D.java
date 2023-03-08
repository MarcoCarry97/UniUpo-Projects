
public class DCT2D implements Transform
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
		for(int u=0;u<source.length;u++)
		{
			double a=alpha(u);
			for(int v=0;v<source[u].length;v++)
			{
				double b=alpha(v);
				double sum=0;
				for(int x=0;x<source.length;x++)
				{
					double fractx=(2.0*x+1)*u*Math.PI/(2*source.length);
					double cosx=Math.cos(fractx);
					for(int y=0;y<source[u].length;y++)
					{
						double fracty=(2.0*y+1)*v*Math.PI/(2*source.length);
						double cosy=Math.cos(fracty);
						sum+=source[x][y]*cosx*cosy;
					}
				}
				result[u][v]=a*b*sum;
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

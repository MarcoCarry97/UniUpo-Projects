
public class IDCT1D implements Transform
{
	private double source[];
	private double result[];
	
	@Override
	public void setSourceData(Object src)
	{
		source=(double[]) src;
	}

	@Override
	public void calculate()
	{
		result=new double[source.length];
		for(int x=0;x<source.length;x++)
		{
			double part=0;
			for(int u=0;u<source.length;u++)
			{
				double fract=(2.0*x+1)*u*Math.PI;
				double cosine=Math.cos(fract/(2.0*source.length));
				part+=alpha(u)*source[u]*cosine;
			}
			result[x]=part;
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

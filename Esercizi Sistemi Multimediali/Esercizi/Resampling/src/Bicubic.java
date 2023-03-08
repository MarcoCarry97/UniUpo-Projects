import java.awt.image.BufferedImage;

public class Bicubic implements Transform
{
	private BufferedImage source, result;
	private double m;

	public void setRatio(double ratio)
	{
		m=ratio;
	}
	
	@Override
	public void setSourceData(Object src)
	{
		source=(BufferedImage) src;
	}

	@Override
	public void calculate()
	{
		int width=(int) (source.getWidth()*m);
		int height=(int) (source.getHeight()*m);
		result=new BufferedImage(width,height,source.getType());
		for(int x=0;x<width;x++)
			for(int y=0;y<height;y++)
				for(int k=-1;k<=2;k++)
					for(int l=-1;l<=2;l++)
					{
						int i=(int) (k+x/m);
						int j=(int) (l+y/m);
						//int band=source.getRaster().getNumBands();
						
					}
						
	}

	@Override
	public Object getResults()
	{
		return result;
	}
	
	private double phi(int k, double h)
	{
		if(k==-1) return minOne(h);
		else if(k==0) return zero(h);
		else if(k==1) return one(h);
		else if(k==2) return two(h);
		else return -1;
	}

	private double minOne(double h)
	{
		double pot=-Math.pow(h, 3);
		double potM=3*Math.pow(h,2);
		double mul=-2*h;
		return (pot+potM+mul)/6;
	}
}

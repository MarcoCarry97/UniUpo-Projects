import java.awt.image.BufferedImage;

public class NearestNeighbor implements Transform
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
			{
				int bands=source.getRaster().getNumBands();
				for(int b=0;b<bands;b++)
				{
					int value=source.getRaster().getSample((int)(x/m),(int)(y/m), b);	
					result.getRaster().setSample(x, y, b, value);
				}
			}
						
	}

	@Override
	public Object getResults()
	{
		return result;
	}
	
	
}

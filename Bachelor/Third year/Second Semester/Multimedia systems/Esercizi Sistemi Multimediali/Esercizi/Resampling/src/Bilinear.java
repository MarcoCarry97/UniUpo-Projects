import java.awt.image.BufferedImage;

public class Bilinear implements Transform
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
		for(int xp=0;xp<width;xp++)
			for(int yp=0;yp<height;yp++)
			{
				int bands=source.getRaster().getNumBands();
				for(int s=0;s<bands;s++)
				{
					double i= xp/m;
					double j= yp/m;
					int x= (int)(i);
					int y= (int)(j);
					double a=i-x;
					double b=j-y;
					int leftTop=source.getRaster().getSample(x,y, s);
					int xi=controlX(x+1);
					int rightTop=source.getRaster().getSample(xi,y, s);
					int yi=controlY(y+1);
					int leftDown=source.getRaster().getSample(x,yi, s);
					xi=controlX(x+1);
					yi=controlY(y+1);
					int rightDown=source.getRaster().getSample(xi,yi, s);
					int value=(int) ((1-a)*(1-b)*leftTop+a*(1-b)*leftDown+(1-a)*b*rightTop+a*b*leftDown);
					result.getRaster().setSample(xp, yp, s, value);
				}
			}
						
	}

	@Override
	public Object getResults()
	{
		return result;
	}
	
	int controlX(int x)
	{
		if(x<source.getWidth()) return x;
		else return x-1;
	}
	
	int controlY(int y)
	{
		if(y<source.getHeight()) return y;
		else return y-1;
	}
}

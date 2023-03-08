import java.awt.image.BufferedImage;

public class Convolution implements Transform
{
	private BufferedImage source, result;
	private double kernel[][];
	
	public void setKernel(double kernel[][])
	{
		this.kernel=kernel;
	}
	
	@Override
	public void setSourceData(Object src)
	{
		source=(BufferedImage) src;
	}

	@Override
	public void calculate()
	{
		int n=kernel.length;
		double sumK=sumKernel();
		result=new BufferedImage(source.getWidth(),source.getHeight(),source.getType());
		for(int x=0;x<source.getWidth();x++)
		{
			double sum=0;
			for(int y=0;y<source.getHeight();y++)
			{
				int bx=source.getWidth()-1-n/2;
				int by=source.getHeight()-1-n/2;
				if(x<n/2 || y<n/2 ||x>bx||y>by) result.getRaster().setSample(x, y, 0, source.getRaster().getSample(x, y, 0));
				else
				{
					sum=0;
					double[][] piece=getPiece(x,y,n);
					for(int k=-n/2;k<=n/2;k++)
					{
						for(int l=-n/2;l<=n/2;l++)
						{
							sum+=piece[k+n/2][l+n/2]*kernel[k+n/2][l+n/2];
						}
					}
					result.getRaster().setSample(x, y, 0, sum/sumK);
				}
			}
		}			
	}

	@Override
	public Object getResults()
	{
		return result;
	}

	private double sumKernel()
	{
		double sum=0;
		for(int i=0;i<kernel.length;i++)
			for(int j=0;j<kernel[i].length;j++)
				sum+=kernel[i][j];
		return sum;
	}
	
	private double[][] getPiece(int x,int y,int size)
	{
		double[][] piece=new double[size][size];
		for(int i=-size/2;i<=size/2;i++)
			for(int j=-size/2;j<=size/2;j++)
				piece[i+size/2][j+size/2]=source.getRaster().getSampleDouble(x+i, y+j, 0);
		return piece;
	}
}

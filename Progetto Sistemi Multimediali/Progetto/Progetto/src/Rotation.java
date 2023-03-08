import java.awt.image.BufferedImage;

public class Rotation implements Transform
{
	private BufferedImage source;
	//private BufferedImage result;
	private MultipleBuffer result;
	private int centerX;
	private int centerY;
	private double tetha;
	
	@Override
	public void setSourceData(Object src)
	{
		source=(BufferedImage) src;
		result=new MultipleBuffer(2,source.getWidth(),source.getHeight(),source.getType());
	}

	@Override
	public void calculate()
	{
		//result=new BufferedImage(source.getWidth(),source.getHeight(),source.getType());
		double[][] matrix=invert(getMatrix());
		//double[][] matrix=getMatrix();
		for(int xi=0;xi<source.getWidth();xi++)
			for(int yi=0;yi<source.getHeight();yi++)
			{
				int i=xi-centerX;
				int j=yi-centerY;
				int x= (int) (i*matrix[0][0] + j*matrix[1][0])+centerX;
				int y= (int) (i*matrix[0][1] + j*matrix[1][1])+centerY;
				int sample=0;
				int bands=source.getRaster().getNumBands();
				for(int b=0;b<bands;b++)
				{
					if(x<0 || x>=source.getWidth()) sample=0;
					else if(y<0 || y>=source.getHeight()) sample=0;
					else sample=source.getRaster().getSample(x, y, b);
					result.setSample(xi, yi, b, sample);
				}
			}
		
	}

	@Override
	public Object getResults()
	{
		return result.get();
	}
	
	public void setCenter(int x, int y)
	{
		centerX=x;
		centerY=y;
	}

	public void setAngle(double angle)
	{
		tetha=angle;
	}
	
	private double[][] getMatrix()
	{
		double degree=Math.toRadians(tetha);
		double[][] matrix=new double[2][2];
		matrix[0][0]=Math.cos(degree);
		matrix[0][1]=-Math.sin(degree);
		matrix[1][0]=Math.sin(degree);
		matrix[1][1]=Math.cos(degree);
		return matrix;
	}
	
	private double[][] invert(double[][] matrix) 
	{
		double det=getDet(matrix);
		double[][] trasp=traspose(matrix);
		double[][] inverse=new double[2][2];
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				inverse[i][j]=Math.pow(-1, i+j)*trasp[i][j]/det;
		return trasp;
	}
	
	private double getDet(double[][] matrix)
	{
		double a=matrix[0][0];
		double b=matrix[1][0];
		double c=matrix[0][1];
		double d=matrix[1][1];
		return a*d - b*c;
	}
	
	private double[][] traspose(double[][] matrix)
	{
		double trasp[][]=new double[2][2];
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				trasp[i][j]=matrix[2-i-1][2-j-1];
		return trasp;
	}
}

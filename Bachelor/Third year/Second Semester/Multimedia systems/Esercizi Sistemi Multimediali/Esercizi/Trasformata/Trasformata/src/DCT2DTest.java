import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class DCT2DTest
{
	private double source[][];
	private DCT2D d;
	private IDCT2D id;
	
	public void init()
	{
		source=new double[][]{new double[] {1,2,3},new double[] {4,5,6},new double[] {7,8,9}};
		d=new DCT2D();
		id=new IDCT2D();
		d.setSourceData(source);
	}
	
	@Test
	void testCalculate()
	{
		init();
		d.calculate();
		double res[][]=(double[][]) d.getResults();
		id.setSourceData(res);
		id.calculate();
		res=(double[][]) id.getResults();
		for(int i=0;i<source.length;i++)
			for(int j=0;j<source[i].length;j++)
			{
				double x=Math.round(source[i][j]);
				double y=Math.round(res[i][j]);
				assertTrue(x==y);
			}
	}

}

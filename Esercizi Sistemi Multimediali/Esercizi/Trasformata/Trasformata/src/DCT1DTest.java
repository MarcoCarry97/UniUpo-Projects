import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class DCT1DTest
{
	private double source[];
	private Transform id, iId;
	
	public void init()
	{
		id=new DCT1D();
		iId=new IDCT1D();
		source=new double[] {1,2,3,4,5,6,7,8,9,10};
		id.setSourceData(source);
	}
	
	@Test
	public void testCalc()
	{
		init();
		id.calculate();
		double res[]=(double[]) id.getResults();
		iId.setSourceData(res);
		iId.calculate();
		res=(double[])iId.getResults();
		for(int i=0;i<res.length;i++)
		{
			double x=Math.round(source[i]);
			double y=Math.round(res[i]);
			assertTrue(x==y);
		}
	}

}

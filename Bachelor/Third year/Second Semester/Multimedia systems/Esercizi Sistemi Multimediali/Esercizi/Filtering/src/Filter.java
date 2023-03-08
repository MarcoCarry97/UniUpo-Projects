
public class Filter
{
	public static double[][] getIdentity(int size)
	{
		double matrix[][]=new double[size][size];
		int n=matrix.length;
		matrix[n/2][n/2]=1;
		return matrix;
	}
	
	public static double[][] getLowPass(int size)
	{
		double matrix[][]=new double[size][size];
		int n=matrix.length;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				matrix[i][j]=1;
		return matrix;
	}
	
	public static double[][] getHighPass(int size)
	{
		double id[][]=new double[size][size];
		double low[][]=new double[size][size];
		return matSum(low,id);
	}
	
	private static double[][] matSum(double[][] m1, double[][] m2)
	{
		double ret[][]=new double[m1.length][m2.length];
		for(int i=0;i<m1.length;i++)
			for(int j=0;j<m1[i].length;j++)
				ret[i][j]=m1[i][j]-m2[i][j];
		return ret;
	}
}

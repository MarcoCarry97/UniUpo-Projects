import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Quant
{
	private File image;
	private BufferedImage origin=null, process=null;	
	private double in[][], out[][];
	private int[][] table
			= {
			{16,11,10,16,24,40,51,61},
			{12,12,14,19,26,58,60,55},
			{14,13,16,24,40,57,69,56},
			{14,17,22,29,51,87,80,62},
			{18,22,37,56,68,109,103,77},
			{24,35,55,64,81,104,113,92},
			{49,64,78,87,103,121,120,101},
			{72,92,95,98,112,100,103,99}
			};
	
	public Quant(String name)
	{
		image=new File(name);
		loadImage();
	}
	
	private void loadImage()
	{
		try
		{
			origin=ImageIO.read(image);
			process=ImageIO.read(image);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
	
	private double[][] invert(double input[][])
	{
		IDCT2D idct=new IDCT2D();
		idct.setSourceData(input);
		idct.calculate();
		return (double[][]) idct.getResults();
	}
	
	private double[][] transform(int a,int b)
	{
		double input[][]=new double[8][8];
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				input[i][j]=process.getRaster().getSample(a, b, 0);
		DCT2D dct=new DCT2D();
		dct.setSourceData(input);
		dct.calculate();
		return (double[][]) dct.getResults();
	}
	
	private int[][] quantize(double input[][])
	{
		int output[][]=new int[8][8];
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				output[i][j]=(int) Math.round(out[i][j]/table[i][j]);
		return output;
	}
	
	private double[][] dequantize(int input[][])
	{
		double output[][]=new double[8][8];
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				output[i][j]=input[i][j]*table[i][j];
		return output;
	}
	
	private void set(double input[][],int a, int b)
	{
		for(int i=0;i<8;i++)
			for(int j=0;j<8;j++)
				process.getRaster().setSample(a+i,b+j,0,input[i][j]);
	}
	
	private void show()
	{
		view(origin,"Original",20,20);
		view(process,"Quantized",100,100);
	}
	
	private void view(BufferedImage image,String message,int x,int y)
	{
		JLabel label=new JLabel(new ImageIcon(image));
		JFrame frame=new JFrame(message);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().add(label);
		frame.pack();
		frame.setLocation(x,y);
		frame.setVisible(true);
	}
	
	private void save()
	{
		try
		{
			File output=new File("quantized.png");
			ImageIO.write(process, "png", output);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
	
	public void execute()
	{
		for(int i=0;i<process.getWidth();i+=8)
		{
			for(int j=0;j<process.getHeight();j+=8)
			{
				double trans[][]=transform(i,j);
				int quant[][]=quantize(trans);
				double deq[][]=dequantize(quant);
				double inv[][]=invert(deq);
				set(inv,i,j);
			}
		}
		show();
		save();
	}
}

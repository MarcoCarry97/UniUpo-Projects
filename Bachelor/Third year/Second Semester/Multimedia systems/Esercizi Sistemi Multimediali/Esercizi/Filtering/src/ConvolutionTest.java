import static org.junit.jupiter.api.Assertions.*;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

import org.junit.jupiter.api.Test;

class ConvolutionTest
{
	Convolution conv=null;
	BufferedImage image=null, process=null;
	
	@Test
	void testGetResults()
	{
		init();
		conv.calculate();
		process=(BufferedImage) conv.getResults();
		view(process,"filtered",20,20);
		save();
	}

	private void init()
	{
		conv=new Convolution();
		try
		{
			image=ImageIO.read(new File("Sample.jpg"));
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		conv.setSourceData(image);
		conv.setKernel(Filter.getHighPass(3));
	}
	
	private void view(BufferedImage img,String message,int x,int y)
	{
		JLabel label=new JLabel(new ImageIcon(img));
		JFrame frame=new JFrame(message);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().add(label);
		frame.pack();
		frame.setLocation(x,y);
		frame.setVisible(true);
		try
		{
			Thread.sleep(30000);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	private void save()
	{
		try
		{
			File output=new File("filtered.png");
			ImageIO.write(process, "png", output);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
	
}

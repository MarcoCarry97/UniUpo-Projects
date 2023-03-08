import static org.junit.jupiter.api.Assertions.*;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

import org.junit.jupiter.api.Test;

class NearestNeighborTest
{
	private BufferedImage src;
	private NearestNeighbor nn;
	
	private void init()
	{
		try
		{
			src=ImageIO.read(new File("Sample.jpg"));
			nn=new NearestNeighbor();
			nn.setRatio(1);
			nn.setSourceData(src);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	@Test
	void testGetResults()
	{
		init();
		nn.calculate();
		BufferedImage res=(BufferedImage) nn.getResults();
		view(res,"Resized",20,20);
		save(res);
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
	
	private void save(BufferedImage image)
	{
		try
		{
			File output=new File("resized.png");
			ImageIO.write(image, "png", output);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}

}

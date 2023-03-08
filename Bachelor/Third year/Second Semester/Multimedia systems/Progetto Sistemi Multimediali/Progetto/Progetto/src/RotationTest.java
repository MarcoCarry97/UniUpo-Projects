import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

import org.junit.jupiter.api.Test;

class RotationTest {

	@Test
	void testCalculate()
	{
		BufferedImage src=null;
		try
		{
			src=ImageIO.read(new File("piera-resized.png"));
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		Rotation rotation=new Rotation();
		rotation.setSourceData(src);
		rotation.setAngle(90);
		rotation.setCenter(src.getWidth()/2,src.getHeight()/2);
		//rotation.setCenter(0,0);
		rotation.setSourceData(src);
		rotation.calculate();
		BufferedImage result=(BufferedImage) rotation.getResults();
		show(result);
		try {
			Thread.sleep(30000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void show(BufferedImage image)
	{
		JLabel label= new JLabel(new ImageIcon(image));
		JFrame f = new JFrame("Originalpicture");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.getContentPane().add(label);
		f.pack();
		f.setLocation(20,20);
		f.setVisible(true);
	}

}

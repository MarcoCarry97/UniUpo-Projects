import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Animation implements Runnable
{
	private BufferedImage source;
	private Rotation rotation;
	private double angle;
	private boolean end;
	
	public Animation(String name)
	{
		try
		{
			source=ImageIO.read(new File(name));
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		rotation=new Rotation();
		rotation.setSourceData(source);
		angle=0;
		rotation.setAngle(angle);
		end=false;
	}
	
	@Override
	public void run()
	{
		BufferedImage result=null;
		//rotation.setSourceData(source);
		rotation.setCenter(source.getWidth()/2,source.getHeight()/2);
		JLabel label=show(source);
		while(!end) //ogni 167 millisecondi (ovvero 60fps), l'angolo viene incrementato
		{
			angle=(angle+30)%360;
			rotation.setAngle(angle);
			rotation.calculate();
			result=(BufferedImage) rotation.getResults();
			label.setIcon(new ImageIcon(result));
			try
			{
				Thread.sleep(1000/60);
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}

	private JLabel show(BufferedImage image) //crea la finestra dell'immagine data.
	{
		JLabel label= new JLabel(new ImageIcon(image));
		JFrame f = new JFrame("Original picture");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.getContentPane().add(label);
		f.pack();
		f.setLocation(20,20);
		f.setVisible(true);
		return label;
	}
	
	public void setEnd(boolean end)
	{
		this.end=end;
	}
}

import java.awt.image.BufferedImage;

public class MultipleBuffer
{
	private BufferedImage[] buffers;
	private int size; //dimensione del buffer
	private int current; //indice al buffer corrente
	
	public MultipleBuffer(int size,int width,int height,int type) //inizializza i buffer in base ai parametri dati
	{
		buffers=new BufferedImage[size];
		this.size=size;
		this.current=0;
		for(int i=0;i<size;i++)
			buffers[i]=new BufferedImage(width,height,type);
	}
	
	public BufferedImage get() //restituisce il buffer e passa a quello successivo
	{
		int index=current;
		current=(current+1)%size;
		return buffers[index];
	}
	
	public void setSample(int x,int y, int b,int s) //imposta il campione sul buffer corrente
	{
		buffers[current].getRaster().setSample(x, y, b, s);
	}
	
}

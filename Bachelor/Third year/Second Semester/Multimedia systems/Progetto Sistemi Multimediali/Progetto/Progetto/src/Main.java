import jbook.Input;

public class Main
{

	public static void main(String[] args)
	{
		Animation animation=new Animation("piera-resized.png");
		Thread thread=new Thread(animation);
		thread.start();
		Input.readString("Premere INVIO per finire"); //finchè non si preme invio, l'immagine continuerà a girare
		animation.setEnd(true);
	}

}

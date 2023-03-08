import java.util.Random;

import jbook.util.Input;

public class Main
{
	public static int size=20;
	public static int numProd=new Random().nextInt()%size/2;
	public static int numCons=new Random().nextInt()%size/2;
	public static Thread prod[], cons[];
	public static MessageQueue messageQueue;
	
	public static void main(String[] args) throws InterruptedException
	{
		if(numProd<0)numProd=0-numProd; //Il numero di thread non può essere negativo o uguale a 0.
		if(numCons<0)numCons=0-numCons;
		if(numProd==0) numProd=1; 
		if(numCons==0) numCons=1;
		System.out.println("Ci sono "+numProd+" produttori e "+numCons+" consumatori.");
		prod=new Producer[numProd];
		cons=new Consumer[numCons];
		messageQueue=new MessageQueue(size);
		for(int i=0;i<numProd;i++) //Creazione e avvio produttori.
		{
			prod[i]=new Producer(messageQueue);
			prod[i].start();
		}
		for(int i=0;i<numCons;i++) //Creazione e avvio consumatori.
		{
			cons[i]=new Consumer(messageQueue);
			cons[i].start();
		}
		Input.readString(); //Quando si preme un tasto, si predispone il tutto per far finire i thread.
		for(int i=0;i<numCons;i++) messageQueue.send(new Message("END","END")); //fine dei consumatori.
		for(int i=0;i<numProd;i++) ((Producer) prod[i]).setEnding(); //fine dei produttori.
		int prodEnd=0, consEnd=0, i=0;
		while(consEnd!=numCons) //controlla se tutti i consumatori hanno finito.
		{
			if(cons[i].isAlive()) consEnd++;
			i=(i+1)%numCons;
			//messageQueue.wait();
		}
		System.out.println("\nTUTTI I CONSUMATORI HANNO FINITO");
		i=0;
		while(prodEnd!=numProd) //controlla se tutti i produttori hanno finito.
		{
			if(prod[i].isAlive()) prodEnd++;
			i=(i+1)%numProd;
			//messageQueue.wait();
		}
		System.out.println("\nTUTTI I PRODUTTORI HANNO FINITO");
		System.out.println("FINE");
	}

}


public class MessageQueue
{
	private int size;
	private Message queue[];
	private int writer;
	private int reader;
	private int freeSlots; //Indica il numero di blocchi liberi in coda.
	private int dataItems; //Indica il numero di blocchi occupati in coda.
	
	public MessageQueue(int size)
	{
		this.size=size;
		queue=new Message[size];
		writer=0;
		reader=0;
		freeSlots=size;
		dataItems=0;
	}
	
	public int getSize() 
	{
		return size;
	}
	
	public synchronized void send(Message message) throws InterruptedException
	{
		freeSlots--;
		while(freeSlots<=-1) //Quando non ci sono celle libere, il produttore aspetta.
		{
			System.out.println("\nCoda piena");
			wait();
		}
		//Thread.sleep(500);
		queue[writer]=message;
		writer=(writer+1)%size;
		dataItems++;
		System.out.println("\nSITUAZIONE: "+freeSlots+" liberi, "+dataItems+" occupati");
		notifyAll();
	}
	
	public synchronized Message receive() throws InterruptedException
	{
		dataItems--;
		while(dataItems<=-1) //Quando la coda è piena, il consumatore aspetta.
		{
			System.out.println("\nCoda vuota");
			wait();
		}
		//Thread.sleep(500);
		Message message=queue[reader];
		reader=(reader+1)%size;
		freeSlots++;
		System.out.println("\nSITUAZIONE: "+freeSlots+" liberi, "+dataItems+" occupati");
		notifyAll();
		return message;
	}
}

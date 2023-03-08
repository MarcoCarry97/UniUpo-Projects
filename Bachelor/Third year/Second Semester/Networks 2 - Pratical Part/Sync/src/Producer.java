
public class Producer extends Thread
{
	private MessageQueue messageQueue;
	private boolean ending;
	
	public Producer(MessageQueue messageQueue)
	{
		this.messageQueue=messageQueue;
		ending=false;
	}
	
	public void setEnding()
	{
		ending=true;
	}
	
	public void run()
	{
		boolean end=false;
		while(!end)
		{
			String topic="Prod"+getId();
			String body=String.valueOf(getId());
			Message message=new Message(topic,body);
			try
			{
				messageQueue.send(message);
				//System.out.println("inviato");
			}
			catch (InterruptedException e)
			{
				end=true;
				System.out.println("Produttore lancia eccezione");
			}
			if(ending) end=true;
		}
		System.out.println("\nProduttore terminato");
	}
}

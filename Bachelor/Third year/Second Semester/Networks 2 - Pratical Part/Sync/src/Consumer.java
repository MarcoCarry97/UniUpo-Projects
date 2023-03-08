
public class Consumer extends Thread
{
	private MessageQueue messageQueue;
	
	public Consumer(MessageQueue messageQueue)
	{
		this.messageQueue=messageQueue;
	}
	
	public void run()
	{
		boolean end=false;
		while(!end)
		{
			Message message;
			try
			{
				message = messageQueue.receive();
				if(message!=null) System.out.println("\n\nMessaggio letto da "+getId()+":\n"+message);
				if(message!=null && message.getTopic().equals("END")) end=true;
			}
			catch (InterruptedException e)
			{
				end=true;
				System.out.println("Consumatore lancia eccezione");
			}
		}
		System.out.println("\nConsumatore terminato");
	}
}

import java.util.Date;

public class Message
{
	private String topic;
	private String body;
	private String timeStamp;
	
	public Message(String topic, String body)
	{
		this.topic=topic;
		this.body=body;
		timeStamp=new Date(System.currentTimeMillis()).toString();
	}
	
	public String getTopic() //Restituisce l'argomento del messaggio.
	{
		return topic;
	}
	
	public String getBody() //Restituisce il corpo del messaggio.
	{
		return body;
	}
	
	public String getTimeStamp() //Restituisce la data di creazione del messaggio.
	{
		return timeStamp;
	}
	
	public String toString()
	{
		return "Topic: "+topic+ " "+timeStamp+"\nBody: "+body;
	}
}

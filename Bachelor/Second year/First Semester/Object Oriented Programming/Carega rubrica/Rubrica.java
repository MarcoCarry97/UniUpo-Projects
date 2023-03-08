import java.util.ArrayList;

public class Rubrica
{

	private static ArrayList<String> rubrica;
	public final static int MAX=6;
	public static void crea()
	{
		// TODO Auto-generated method stub
		rubrica = new ArrayList<String>();
	}
	
	public static int numEl()
	{
		// TODO Auto-generated method stub
		return rubrica.size();
	}
	
	public static int aggiungi(String contatto)
	{
		// TODO Auto-generated method stub
		if(rubrica.size()==MAX) return -1;
		else if(rubrica.contains(contatto)) return 0;
		else
		{
			rubrica.add(contatto);
			return 1;
		}
	}
	
	public static ArrayList<String> cerca(String string)
	{
		ArrayList<String> list = new ArrayList<String>();
		for(int i=0;i<rubrica.size();i++)
		{
			String temp=rubrica.get(i);
			if(!different(temp,string)) list.add(temp);
		}
		return list;
	}
	
	private static boolean different(String riga,String search)
	{
		char[] rigachar = riga.toCharArray();
		char[] searchchar = search.toCharArray();
		boolean diverso=false;
		for(int i=0;i<searchchar.length && !diverso;i++)
			if(rigachar[i]!=searchchar[i]) diverso=true;
		return diverso;
	}
	
	public static boolean elimina(String string)
	{// TODO Auto-generated method stub
		boolean delete=false;
		if(string.equals("")) delete=rubrica.removeAll(rubrica);
		else for(int i=0;i<rubrica.size();i++)
		{
			String temp=rubrica.get(i);
			if(!different(temp,string))
			{
				rubrica.remove(i);
				delete=true;
			}
		}
		return delete;
	}
	
	
}

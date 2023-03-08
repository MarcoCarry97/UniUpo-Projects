import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;


public class TestRubrica {

	@Before
	public void creazione() {
		Rubrica.crea();
		assertTrue(Rubrica.numEl()==0);
	}

	@Test
	
	public void testCreazione() {
		assertTrue(Rubrica.numEl()==0);
	}
	
	@Test
	public void testAggiungi() {
		assertEquals(Rubrica.aggiungi("Giovanni=123456"),1);
		assertEquals(Rubrica.numEl(),1); 
		assertEquals(Rubrica.aggiungi("Mattia = 345216789"), 1);
		assertEquals(Rubrica.numEl(),2);
	}
	
	@Test
	public void testAggiuntaMassima() {
		assertEquals(Rubrica.aggiungi("Mattia = 345216789"), 1);
		assertEquals(Rubrica.numEl(),1);
		assertEquals(Rubrica.aggiungi("Roberta = 312789560"), 1);
		assertEquals(Rubrica.numEl(),2);
		assertEquals(Rubrica.aggiungi("Alice = 333214576"), 1);
		assertEquals(Rubrica.numEl(),3);
		assertEquals(Rubrica.aggiungi("Matteo = 312456712"), 1);
		assertEquals(Rubrica.numEl(),4);
		assertEquals(Rubrica.aggiungi("Enzo = 367891239"), 1);
		assertEquals(Rubrica.numEl(),5);
	}

	
	@Test
	public void testAggiuntaOltreLimite() {
		assertEquals(Rubrica.aggiungi("Martina = 346789123"), 1);
		assertEquals(Rubrica.numEl(),1);
		assertEquals(Rubrica.aggiungi("Sara = 331452673"), 1);
		assertEquals(Rubrica.numEl(),2);
		assertEquals(Rubrica.aggiungi("Lucia = 333123789"), 1);
		assertEquals(Rubrica.numEl(),3);
		assertEquals(Rubrica.aggiungi("Margherita = 334331245"), 1);
		assertEquals(Rubrica.numEl(),4);
		assertEquals(Rubrica.aggiungi("Noemi = 345123879"), 1);
		assertEquals(Rubrica.numEl(),5);
		assertEquals(Rubrica.aggiungi("Graziella = 331456234"), 1);
		assertEquals(Rubrica.numEl(),6);
		assertEquals(Rubrica.aggiungi("Paolo = 331456234"), -1);
		assertEquals(Rubrica.numEl(),6);
	}

	
	@Test
	public void testAggiuntaGiaPresente() {
		Rubrica.aggiungi("Martina = 346789123");
		assertEquals(Rubrica.numEl(),1);
		Rubrica.aggiungi("Sara = 331452673");
		assertEquals(Rubrica.numEl(),2);
		Rubrica.aggiungi("Marco = 345678123"); 
		assertEquals(Rubrica.numEl(),3);
		assertEquals(Rubrica.aggiungi("Martina = 346789123"), 0);
		assertEquals(Rubrica.numEl(),3);
		assertEquals(Rubrica.aggiungi("Marco = 345678123"), 0);
		assertEquals(Rubrica.numEl(),3);
	}

	@Test
	public void testRicerca() {
		addElementiRubricaStatica(); // Aggiunge 6 elementi alla rubrica
		assertEquals(Rubrica.cerca("Giov").size(), 2); // Presente come primo e ultimo
		assertEquals(Rubrica.cerca("Sara").size(), 1);
		assertEquals(Rubrica.cerca("Sat").size(), 0); // Non ci sono stringhe con questo prefisso
		assertEquals(Rubrica.cerca("123").size(), 0); // ma ce ne sono che lo contengono
		assertEquals(Rubrica.cerca("G").size(), 3);
		assertEquals(Rubrica.cerca("Giorgio=7689453201").size(), 1);
		assertEquals(Rubrica.cerca("Giorgio=7689453200").size(), 0); // Confrontare con precedente
		assertEquals(Rubrica.cerca("").size(), 6); // Tutte le stringhe inizano con la stringa vuota
	}

	@Test
	public void testElimina() {
		addElementiRubricaStatica(); // Aggiunge 6 elementi alla rubrica
		assertTrue(Rubrica.elimina("")); // Li rimuove tutti
		assertEquals(Rubrica.numEl(), 0); // Non ci sono piu' stringhe
		addElementiRubricaStatica(); // Ri-aggiunge 6 elementi alla rubrica
		assertTrue(Rubrica.elimina("Giov"));
		assertEquals(Rubrica.numEl(), 4);
		assertFalse(Rubrica.elimina("Sat"));
		assertEquals(Rubrica.numEl(), 4);
		assertFalse(Rubrica.elimina("Giorgio=7689453200"));
		assertEquals(Rubrica.numEl(), 4);
		assertTrue(Rubrica.elimina("Giorgio=7689453201"));
		assertEquals(Rubrica.numEl(), 3);
		assertTrue(Rubrica.elimina("E"));
		assertTrue(Rubrica.elimina("S"));
		assertTrue(Rubrica.elimina("P"));
		assertEquals(Rubrica.numEl(), 0);
	}
	
	private void addElementiRubricaStatica() {
			Rubrica.aggiungi("Giovanni=0123456789");
			Rubrica.aggiungi("Enzo=4593782610");
			Rubrica.aggiungi("Paola=0123456789");
			Rubrica.aggiungi("Sara=0354768912");
			Rubrica.aggiungi("Giorgio=7689453201");
			Rubrica.aggiungi("Giovanni=0123456784");
		}
}

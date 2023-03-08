package lab.cc.simulazioni;

import static org.junit.Assert.*;

import org.junit.Test;

import org.junit.Before;

import static lab.cc.simulazioni.Environment.TESTLRSTOLR;
import static lab.cc.simulazioni.Environment.BLANK_CHAR;


import it.uniupo.utilityLib.TTRep;
import it.uniupo.utilityLib.TTRepStandard;
import it.uniupo.utilityLib.Tools;

public class TestLRStoLR {

	char[] alfa = {BLANK_CHAR, '0','1'};
	TTRepStandard mdtLRS;
	TTRepStandard risultato;
	int newState;
	int sLine;
	int firstSimuLine;
	int maxState;
		
	@Before
	public void Setup() {
		 mdtLRS = TTRep.getInstance(TESTLRSTOLR);
	     risultato = Simulazioni.mdtLRS2LR(mdtLRS, alfa);
		 sLine = mdtLRS.whereDefined(1, '1');
		 firstSimuLine = risultato.whereDefined(1, '1');
		 maxState = mdtLRS.getMaxStateNumber();	
	}

	
	@Test
	public void testStatoTemporaneo() { //la nuova MdT entra in uno stato temporaneo quando deve simulare uno spostamento 'S'
		int sState =  Tools.getStateNumber(mdtLRS.getNewState(sLine));
		int tempState = Tools.getStateNumber(risultato.getNewState(firstSimuLine));
		assertNotEquals ("Se non avete rinominato tutti gli stati, questi devono essere diversi\nTEST VALIDO SOLO SE NON AVETE RINOMINATO TUTTI GLI STATI DELLA MDT", sState, tempState);
	}
	
	@Test
	public void testStatoTemporaneoNuovo() { //lo stato temporaneo deve essere uno stato nuovo
		int tempState = Tools.getStateNumber(risultato.getNewState(firstSimuLine));
		assertTrue ("Se non avete rinominato tutti gli stati, questi devono essere diversi\nTEST VALIDO SOLO SE NON AVETE RINOMINATO TUTTI GLI STATI DELLA MDT", tempState > maxState);
	}
	
	@Test
	public void testSpostamentoTemporaneo() { //Per simulare uno spostamento 'S', meglio che si muova prima a 'R' e poi a 'L'
		char tempMove = risultato.getMove(firstSimuLine);
		assertEquals ("E' meglio che la MdT faccia il passo di servizio a destra, per non cadere dal nastro", 'R', tempMove);
	}

	@Test
	public void testStatoGiustoRaggiunto() { //alla fine della simulazione del passo 'S' la MdT deve essere rientrata nello stato originale
		int sState =  Tools.getStateNumber(mdtLRS.getNewState(sLine));
		int tempState = Tools.getStateNumber(risultato.getNewState(firstSimuLine));
		for (int i=0; i < alfa.length; ++i) {
			int finalSimuLine = risultato.whereDefined(tempState,alfa[i]);
			int finalState = Tools.getStateNumber(risultato.getNewState(finalSimuLine));
			assertEquals ("La MdT simulante deve terminare la simulazione nello stato giusto\nTEST VALIDO SOLO SE NON AVETE RINOMINATO TUTTI GLI STATI DELLA MDT", sState, finalState);
	
		}
	}
}

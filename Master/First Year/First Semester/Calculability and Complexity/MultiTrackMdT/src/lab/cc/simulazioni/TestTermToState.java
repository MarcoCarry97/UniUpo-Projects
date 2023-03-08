package lab.cc.simulazioni;

import static org.junit.Assert.*;

import org.junit.Before;

import static lab.cc.simulazioni.Environment.TESTTERM2STATE;
import static lab.cc.simulazioni.Environment.BLANK_CHAR;



import org.junit.Test;

import it.uniupo.utilityLib.TTRep;
import it.uniupo.utilityLib.TTRepStandard;
import it.uniupo.utilityLib.Tools;

public class TestTermToState {
	
	char[] alfa = {BLANK_CHAR, '0','1'};
	TTRepStandard mdtTerm;
	TTRepStandard risultato;
	int newState;
		
	@Before
	public void Setup() {
		 mdtTerm = TTRep.getInstance(TESTTERM2STATE);
	     risultato = Simulazioni.mdtTermToState(mdtTerm, alfa);
		 newState = Tools.getStateNumber(risultato.getNewState(risultato.whereDefined(2, '1')));


	}
	
	@Test
	public void testAggiuntaLinea() { //dove la delta non e' definita e' stata aggiunta una nuova linea di delta
		assertTrue(risultato.isDefined(2, '1'));
	}
	
	@Test
	public void testStatoNuovo() { //lo stato in cui viene mandata la macchina in caso di terminazione e' nuovo
		assertTrue( newState > mdtTerm.getMaxStateNumber());
	}
	
	@Test
	public void testNonDefinito() { //la delta non e' mai definita sul nuovo stato
		for (int i = 0; i < alfa.length; ++i) {
			assertFalse(risultato.isDefined(newState,alfa[i]));
		}
	}


	
	

}

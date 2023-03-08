package lab.cc.mdtBase;


import static it.uniupo.mdtLib.EnvironmentStaticInterface.HALTED;
import static it.uniupo.mdtLib.EnvironmentStaticInterface.RUNNING;
import static it.uniupo.mdtLib.EnvironmentStaticInterface.TAPE_ERROR;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import org.junit.Before;
import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import it.uniupo.mdtLib.DynamicEnvironment;
import it.uniupo.mdtLib.EnvironmentStaticInterface;
import it.uniupo.mdtLib.ReadMachine;
import it.uniupo.mdtLib.RunInterface;
import it.uniupo.mdtLib.State;
import it.uniupo.mdtLib.Tape;
import it.uniupo.mdtLib.TapeInterface;
import it.uniupo.mdtLib.TransitionTable;
import it.uniupo.mdtLib.TransitionTableValue;
@FixMethodOrder(MethodSorters.NAME_ASCENDING)

public class TestStep {
public static final String TEST_DELTA_FILE = "testTM";
    MdT mdt;
	RunInterface run;
	TapeInterface t;
	State s;
	TransitionTableValue tri;
	DynamicEnvironment workEnv;

	
	@Before
	public void setUp(){
		EnvironmentStaticInterface e = DefaultEnvironmentStandardTM.getInstance();
		workEnv = DynamicEnvironment.getInstance(e);
		workEnv.setDeltaFile(TEST_DELTA_FILE);
		
		s = State.getState("q3");
		t = new Tape();
		t.setTape("011", 2);
		TransitionTable tt = ReadMachine.readTT();
		mdt = new MdT(tt);
		run = new Run(mdt); // create the MdT's run manager
		mdt.initializeConfig(State.getState("q3"),"011", "2");
	}
	
	@Test
	public void test00Create() {
		assertNotNull("l'oggetto mdt non e' stato creato", mdt);
	}
	
	@Test
	public void test05NewState() { // per ora sistemate lo step() quando la delta e' definita
										//cioe' TransitionTableValue sempre non null
		mdt.initializeConfig(State.getState("q3"),"011", "2");
		mdt.step();
		assertEquals("Errore nuovo stato","q4", mdt.getCurrentState().toString());
	}
	
	@Test
	public void test07Tape() { // per ora sistemate lo step() quando la delta e' definita
										//cioe' TransitionTableValue sempre non null
		mdt.initializeConfig(State.getState("q3"),"011", "2");
		mdt.step();
		assertTrue("Errore di scrittura su nastro, deve essere 01$B",mdt.getTapeString().equals("01$ "));
	}
	
	@Test
	public void test10MoveR() { // per ora sistemate lo step() quando la delta e' definita
										//cioe' TransitionTableValue sempre non null
		mdt.initializeConfig(State.getState("q3"),"011", "2");
		mdt.initializeConfig(s,"0111", "2");
		mdt.step();
		assertEquals("Errore spostamento a destra quando ci sono ancora simboli diversi da blank a destra", 3, mdt.getHeadPosition());
	}
	
	@Test
	public void test15MoveRblank() { // per ora sistemate lo step() quando la delta e' definita
										//cioe' TransitionTableValue sempre non null
		mdt.initializeConfig(s,"011", "2");
		mdt.step();
		assertEquals("Errore spostamento a destra quando sono finiti i simboli diversi da blank a destra", 3, mdt.getHeadPosition());
	}
	
	@Test
	public void test20MoveL() { // per ora sistemate lo step() quando la delta e' definita
										//cioe' TransitionTableValue sempre non null
		mdt.initializeConfig(State.getState("q4"),"011", "2");
		mdt.step();
		assertEquals("Errore nello spostamento a sinistra, quando la testina non cade dal nastro", 1, mdt.getHeadPosition());
	}
	
	@Test
	public void test25Stay() { // per ora sistemate lo step() quando la delta e' definita
										//cioe' TransitionTableValue sempre non null
		mdt.initializeConfig(State.getState("q2"),"011", "1");
		mdt.step();
		assertEquals("Errore, la testina avrebbe dovuto rimanere ferma", 1, mdt.getHeadPosition());
	}
	
	@Test
	public void test30Running() { //sistemate il valore restituito dal metodo
		mdt.initializeConfig(State.getState("q3"),"011", "2");
		char stateOfRun = mdt.step();
		assertEquals("La computazione non deve essere terminata", RUNNING, stateOfRun);
	}
	
	@Test
	public void test35Halted() { //adesso considerate il caso della delta non definita
								//sistemate il valore restituito
		mdt.initializeConfig(State.getState("q6"),"011", "2");
		char stateOfRun = mdt.step();
		assertEquals("La computazione deve essere terminata", HALTED, stateOfRun);
	}
	
	@Test
	public void test40TapeError() { //TEST NON VALIDO PER NASTRO TWO_WAY
									//adesso considerate il caso in cui la MdT cade dal nastro
									//sistemate il valore restituito
		
		if (mdt.getTape() instanceof Tape) {
		mdt.initializeConfig(State.getState("q4"),"111", "0");
		char stateOfRun = mdt.step();
		assertEquals("La testina e' caduta dal nastro, il metodo deve resituire TAPE_ERROR\n"
				+ "QUESTO TEST NON HA SENSO SE IL NASTRO E' TWO_WAY\n", TAPE_ERROR, stateOfRun);
		}
	}
	
	@Test
	public void test50DiversiPassi() { //test del metodo con diversi passi di computazione
		MdT otherMdT;
		otherMdT = new MdT(null);	
		otherMdT.initializeConfig(State.getState("q4"),"011*1", "0");
		mdt.initializeConfig(State.getState("q3"),"01111", "3");
		mdt.step();
		mdt.step();
		mdt.step();
		mdt.step();
		mdt.step();
		char stateOfRun = mdt.step();
		assertTrue("Qualcosa non va nella computazione: ", mdt.toString().equals(otherMdT.toString()));
		assertEquals("La computazione deve essere terminata", HALTED, stateOfRun);
	}
	
	
	@Test
public void test60NumeroPassi() { //test del numero di passi
	mdt.initializeConfig(State.getState("q4"),"01111", "2");
	run.exec();
	assertEquals("La computazione deve essere terminata", 3, run.getNumberOfSteps());
}

@Test
public void test70NumeroPassi() { //altro test del numero di passi
	mdt.initializeConfig(State.getState("q4"),"01111111", "7");
	run.exec();
	assertEquals("La computazione deve essere terminata", 8, run.getNumberOfSteps());
}

}

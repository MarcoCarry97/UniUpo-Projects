package lab.cc.simulazioni;

public class Environment {
	public static final char BLANK_CHAR = ' '; /*attenzione! se si cambia il BLANK_CHAR si devono chiamare
	 											* i metodi TransitionTableRep.encodeMdT e decodeMdT con
	 											* Environment.BLANK_CHAR come parametro aggiuntivo
	 											*/
	public static final int BASE = 10;
	public final static int LENGTH = 2;
	public static final String TESTPATH = "src/test/resources/";
	public static final String TESTTERM2STATE = TESTPATH + "mdtTerm";
	public static final String TESTLRSTOLR = TESTPATH + "mdtLRS";
}

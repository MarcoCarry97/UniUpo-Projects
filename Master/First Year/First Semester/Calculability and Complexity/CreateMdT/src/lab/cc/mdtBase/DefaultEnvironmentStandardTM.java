/****************************************
 * Default environment parameters for
 * a standard TM with one tape that has
 * a single track. 
 * 
 * The default environment is a singleton
 * class. It is created at the beginning of
 * the execution and used to initialize
 * the dynamic environment (the latter can
 * be customized).
 * 
 * @author Lavinia Egidi
 * @date Jan 2015
 *******************************************/
package lab.cc.mdtBase;

import it.uniupo.mdtLib.EnvironmentStaticInterface;
import it.uniupo.mdtLib.State;
import it.uniupo.mdtLib.Symbol;

public class DefaultEnvironmentStandardTM implements EnvironmentStaticInterface  {

	//***************these constants can be customized***********
	//path and files
//		public static final String PATH = "./";
		private static final String PATH = "src/main/resources/";
		private static final String DELTA_FILE = "delta_base";
		private static final String RUN_LOG_FILE = "runlog_base";
		private static final String OUTFILE = "output";
			
	//blank and initial config
		private static final char BLANK = ' '; 
		private static final String INITIAL_STATE_NAME = "q0";
		private static final int INITIAL_HEAD_POS = 0;
			
	//halt and error states
		private static final boolean PRINT_ERROR_STATE = true;
		private static final boolean PRINT_HALT = true;
//		private static final String HALT_STATE_NAME = "HALT";
//		private static final String ERROR_STATE_NAME = "ERROR";	
		
	//MdT variations
		private final int MODEL = STANDARD_TM;
		private static final int NUMBER_OF_TAPES = 1; //number of heads
		//if NUMBER_OF_HEADS >1 must implement correctly getHeadPosSep()
		private static final int NUMBER_OF_TRACKS = 1; // number of tracks 
		private static final boolean NON_DETERMINISTIC = false;

	// output behavior
		private static final boolean OUT_BEHAVIOR = OUTPUT_CONFIGURATIONS;
		
	//**************the constants above can be customized************
		
		//this is a singleton class		
				public static DefaultEnvironmentStandardTM instance = null;
		//attributes:
		
		//path and files
				private final String path = PATH;
				private final String deltaFile = DELTA_FILE;
				private final String runLogFile = RUN_LOG_FILE;
				private final String outFile = OUTFILE;
		//blank and initial config
				private final char blankChar = BLANK;
				private  final Symbol blankSymbol; 
				private  final State initialState;
				private  final String initialHeadPos;
		//halt and error states
				private final boolean printErrorState = PRINT_ERROR_STATE;
				private final boolean printHalt = PRINT_HALT;
//				private final State haltState = State.getState(HALT_STATE_NAME);
//				private final State errorState = State.getState(ERROR_STATE_NAME);
		//mdt variations
				private final int model = MODEL;
				private final int numberOfTapes = NUMBER_OF_TAPES;
				private final int numberOfTracks = NUMBER_OF_TRACKS;
				private final boolean nonDet = NON_DETERMINISTIC;
		//other		
				private final boolean outBehavior = OUT_BEHAVIOR;
		
		
	private DefaultEnvironmentStandardTM(){	
		blankSymbol = Symbol.getSymbol(BLANK);
		initialState = State.getState(INITIAL_STATE_NAME);
		initialHeadPos = setInitialHeadPosition();
	}
	
	public static DefaultEnvironmentStandardTM getInstance() {
		if (instance == null){
			instance = new DefaultEnvironmentStandardTM();
		}
		return instance;
	}
	
	private String setInitialHeadPosition(){
		return new String(Integer.toString(INITIAL_HEAD_POS));	
	}
	
	@Override
	public String getPath() {
		return path;
	}

	@Override
	public String getDeltaFile() {
		return deltaFile;
	}


	@Override
	public String getRunLogFile() {
		return runLogFile;
	}
	
	public String getOutFile(){
		return outFile;
	}


	@Override
	public Symbol getBlankSymbol() {
		return blankSymbol;
	}


	@Override
	public State getInitialState() {
		return initialState;
	}


	@Override
	public String getInitialHeadPos() {
		return initialHeadPos;
	}

	@Override
	public boolean isStdOutputRequired() {
		return outBehavior;
	}


	@Override
	public boolean isPrintingErrorStateRequired() {
		return printErrorState;
	}


	@Override
	public boolean isPrintingHaltRequired() {
		return printHalt;
	}


//	@Override
//	public State getHaltState() {
//		return haltState;
//	}
//
//
//	@Override
//	public State getErrorState() {
//		return errorState;
//	}

	@Override
	public int getNumberOfTapes(){
		return numberOfTapes;
	}

	@Override
	public int getNumberOfTracks(){
		return numberOfTracks;
	}
	
	@Override
	public boolean isNonDet() {
		return nonDet;
	}
	@Override
	public String getHeadPosSep(){   //not meaningful for a single tape MdT
		return null;
	}

//	@Override
	public char getBlankChar() {
		// TODO Auto-generated method stub
		return blankChar;
	}

//	@Override
	public int getModel() {
		return model;
	}

//	@Override
	public boolean isTapeTwoWay() { //unimplemented
		// TODO Auto-generated method stub
		return false;
	}
}

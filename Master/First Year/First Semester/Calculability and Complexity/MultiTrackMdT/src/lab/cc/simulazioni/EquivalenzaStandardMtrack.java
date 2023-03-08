package lab.cc.simulazioni;

import static lab.cc.simulazioni.Environment.BLANK_CHAR;


import it.uniupo.utilityLib.CartesianProduct;
import it.uniupo.utilityLib.TTRep;
import it.uniupo.utilityLib.TTRepMultitrack;
import it.uniupo.utilityLib.TTRepStandard;
import it.uniupo.utilityLib.Tools;

public class EquivalenzaStandardMtrack {
	

	public static TTRepMultitrack oneTrack2Multitrack(TTRepStandard oneTrackDelta, int numberOfTracks) {
		
		/*
		 * simulazione di una MdT con nastro ad una sola traccia, con MdT che usa nastro multitraccia
		 */
			TTRepMultitrack multiTrackDelta = TTRep.getInstanceMultitrack(numberOfTracks);
					for (int j = 0; j<oneTrackDelta.getNumberOfLines(); ++j){
						char[] currentTrack=new char[numberOfTracks];
						char[] newTrack=new char[numberOfTracks];
						for(int i=0; i<numberOfTracks;i++)
						{
							currentTrack[i]=BLANK_CHAR;
							newTrack[i]=BLANK_CHAR;
						}
						currentTrack[0]=oneTrackDelta.getCurrentSymbol(j);
						newTrack[0]=oneTrackDelta.getNewSymbol(j);
						String currentState=multiTrackDelta.getCurrentState(j);
						String newState=multiTrackDelta.getNewState(j);
						char move=oneTrackDelta.getMove(j);
						multiTrackDelta.addLine(currentState,currentTrack,newState,newTrack,move);
						/********************
						 * manca del codice
						 ********************/
									
					}		
					return multiTrackDelta;
					
		
	}

	
	
public static TTRepStandard multitrack2OneTrack(TTRepMultitrack multiTrackDelta, char[] inputAlphabet, char[] workAlphabet) {
		
	/*
	 * simulazione di una MdT che usa nastro multitraccia, con una MdT standard
 	 * (ricordate che l’alfabeto di input non contiene il blank)
	 * 
	 */				TTRepStandard oneTrackDelta = TTRep.getInstance();
					int numberOfTracks = multiTrackDelta.getNumberOfTracks();
					
					CartesianProduct cp = new CartesianProduct(workAlphabet, numberOfTracks, Environment.BLANK_CHAR); 
				
					System.out.println(cp.toString());
					
					
					oneTrackDelta.addLine("q0",Environment.BLANK_CHAR,"q1",Environment.BLANK_CHAR,'R'); //inizializzazione del nastro
					
					for (int i=0;i<inputAlphabet.length; ++i){   // notate che l’alfabeto di input non contiene il blank
						
						char[] key = new char[numberOfTracks]; 
						key[0]=inputAlphabet[i];
						for(int j = 1; j<numberOfTracks; ++j){
							key[j] = Environment.BLANK_CHAR;
						}
						char c = cp.getChar(key);
						for(int j=0;j<multiTrackDelta.getNumberOfLines();j++)
						{
							String currentState=multiTrackDelta.getCurrentState(j);
							String newState=multiTrackDelta.getNewState(j);
							char currentSymbol=cp.getChar(multiTrackDelta.getCurrentSymbols(j));
							char newSymbol=cp.getChar(multiTrackDelta.getCurrentSymbols(j));
							char move=multiTrackDelta.getMove(j);
							oneTrackDelta.addLine(currentState,currentSymbol,newState,newSymbol,move);
						}
						/********************
						 * manca del codice
						 ********************/
					}
					
					/**********************
					 * manca ancora codice
					 **********************/
							
					return oneTrackDelta;
	}


	


}	


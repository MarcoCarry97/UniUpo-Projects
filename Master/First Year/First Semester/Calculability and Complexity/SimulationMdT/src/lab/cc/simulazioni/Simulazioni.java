package lab.cc.simulazioni;

import static lab.cc.simulazioni.Environment.BLANK_CHAR;

import it.uniupo.utilityLib.InOut;
import it.uniupo.utilityLib.TTRep;
import it.uniupo.utilityLib.TTRepStandard;
import it.uniupo.utilityLib.Tools;

public class Simulazioni {
	
	/*
	 * Per capire come funzionano le simulazioni vi puo' essere utile fare il seguente test:
	 *
	 * 1) leggete una MdT da file: TTRepStandard mdt = TTrep.getInstance(nomefile);
	 * 2) usate il vostro metodo per costruire la macchina equivalente mdtEquiv nel nuovo modello
	 * 3) salvate la nuova mdtEquiv su file usando 
	 *    InOut.writeString(mdtEquiv.toString(), "nomefile");  
	 * 4) a questo punto utilizzate il simulatore tm.jar per verificare che il comportamento di 
	 * 		mdtEquiv sia effettivamente equivalente a quello della mdt in input.
	 */
	
	/*
	 * Metodi utili per il lavoro:
	 * Tools.getStateString(String) //vi raccomando di usarlo per generare le stringhe che rappresentano gli stati
	 * 
	 * dell'interfaccia TTRepStandard:
	 * getCurrentState(int)
	 * getCurrentSymbol(int)
	 * getNewSymbol(int)
	 * getNewState(int)
	 * addLine(String currState,char currSymbol,String newState,char newSymbol,char movement)
	 * getLine(int)
	 * addLine(String lineAsString)
	 * isDefined(int stateNumber, char symbol)
	 */


	public static TTRepStandard mdtLRS2LR(TTRepStandard deltaLRS, char[] alphabet) {
		/*
		 * simulazione di una MdT standard con una MdT che deve spostare la
		 * testina ad ogni passo (cioe' il "movimento" S non e' ammesso)
		 */
		TTRepStandard deltaLR = TTRep.getInstance();
		int currentMaxState = deltaLRS.getMaxStateNumber();
		

		for (int j = 0; j < deltaLRS.getNumberOfLines(); ++j) {
			if (deltaLRS.getMove(j) != 'S') {

				deltaLR.addLine(deltaLRS.getLine(j));
			} else {
				String leftState=Tools.getStateString(deltaLRS.getMaxStateNumber()+1);
				String currentState=deltaLRS.getCurrentState(j);
				char currentSymbol=deltaLRS.getCurrentSymbol(j);
				deltaLR.addLine(currentState,currentSymbol,leftState,currentSymbol,'R');
				String newState=deltaLRS.getNewState(j);
				for(int i=0;i<deltaLRS.getNumberOfLines();i++)
				{
					char curSymbol=deltaLRS.getCurrentSymbol(i);
					char newSymbol=deltaLRS.getNewSymbol(i);

					deltaLR.addLine(leftState,curSymbol,newState,curSymbol,'L');
					deltaLR.addLine(leftState,newSymbol,newState,newSymbol,'L');
				}
				/********************
				 * manca del codice
				 ********************/				

			}
		}
		

		return deltaLR;

	}
	
	
	public static TTRepStandard mdtTermToState(TTRepStandard deltaTerm, char[] alphabet) {
		/*
		 * simulazione di una MdT standard che accetta per terminazione
		 * con una MdT che accetta per stato finale con stato finale unico
		 * e lo stato finale deve essere lo stato di numero massimo
		 */
		TTRepStandard deltaState = TTRep.getInstance();
		int currentMaxState = deltaTerm.getMaxStateNumber();
		String finalState=Tools.getStateString(currentMaxState+1);
		for (int j = 0; j < deltaTerm.getNumberOfLines(); ++j) {
			String currentState=deltaTerm.getCurrentState(j);
			for(int i=0;i<deltaTerm.getNumberOfLines();i++)
			{
				char currentSymbol=deltaTerm.getCurrentSymbol(i);
				if(!deltaTerm.isDefined(Tools.getStateNumber(currentState),currentSymbol))
				{
					System.out.println("Not defined");
					deltaState.addLine(currentState,currentSymbol,finalState,currentSymbol,'S');
				}
				else
				{
					System.out.println("Defined");
					deltaState.addLine(deltaTerm.getLine(j));
				}
			}
			/********************
			 * manca del codice
			 ********************/

		}
		/********************
		 * manca altro codice
		 ********************/
		
		return deltaState;

	}

}


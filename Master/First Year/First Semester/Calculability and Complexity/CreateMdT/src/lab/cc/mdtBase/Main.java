/***********************************
 * The Main class is the same for all TM models,
 * except for: 
 * - the method create() that specifies
 * the TM to be created and used;
 * -the default environment used 
 * 
 * @author Lavinia Egidi
 * @date Jan 2015
 ****************************************/
package lab.cc.mdtBase;

import it.uniupo.mdtLib.ConfigOutput;
import it.uniupo.mdtLib.DynamicEnvironment;
import it.uniupo.mdtLib.EnvironmentStaticInterface;
import it.uniupo.mdtLib.MdTInterface;
import it.uniupo.mdtLib.ReadMachine;
import it.uniupo.mdtLib.RunInterface;
import it.uniupo.mdtLib.TransitionTable;
import it.uniupo.mdtLib.UserSimulatorInteraction;


public class Main {

	public static MdTInterface createMdT() { // reads the transition table and
												// creates a TM
		UserSimulatorInteraction ui = UserSimulatorInteraction.getInstance();

		TransitionTable tt = ReadMachine.readTT();
		while (tt == null) {
			ui.customFileConfig();
			tt = ReadMachine.readTT();
		}
		MdTInterface mdt = new MdT(tt);
		return mdt;
	}

	public static void main(String[] args) {

		EnvironmentStaticInterface e = DefaultEnvironmentStandardTM
				.getInstance(); // default environment

		DynamicEnvironment.getInstance(e); // work environment (can be
											// customized by the user)
											// initialized to default
											// environment parameters

		UserSimulatorInteraction ui = UserSimulatorInteraction.getInstance();
		ConfigOutput.initLogFile(); // initialization of log file

		MdTInterface mdt = createMdT(); // create the mdt to be simulated
		RunInterface run = new Run(mdt); // create the MdT's run manager
		ui.init(mdt, run);

		int restart = 1; //any value > 0 to enter the cycle

		while (restart > 0) {
			restart = ui.start(); // restart is true if the user changed
									// input file information
			if (restart > 0) {
				if (restart > 1) {
					ConfigOutput.initLogFile(); // initialization of log file

				}
				if (restart < 3) {
					mdt = createMdT();
					run = new Run(mdt);
					ui.init(mdt, run);
				}
			}
		}
	}

}

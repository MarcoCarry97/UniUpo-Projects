using Smile;
using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace ProgettoAI
{
	public delegate double Mau(Network bn,string decision,string choice); 
    abstract class BayesBehaviour
    {

        private License license;
		public Network DecisionNetwork { get; set; }
        public BayesBehaviour()
        {
			license = GenieLicense();
			DecisionNetwork = new Network();
        }

		public void Step() => DecisionNetwork.UpdateBeliefs(); //Ricalcola le probabilità della rete tenendo conto delle evidenze

		protected void TakeDecision(string nodeId, string decision) //Setta una decisione al nodo
		{
			DecisionNetwork.SetEvidence(nodeId, decision);
			Step();
		}

		public List<double> Values(string nodeId) => DecisionNetwork.GetNodeValue(nodeId).ToList<double>(); //Restituisce i possibili valori di un nodo (Probabilità o Utilità)

		public Dictionary<string,double> Outcomes(string nodeId,Mau mau) //Restituisce un dizionario contenenti le decisioni con relative utilità
		{
			List<string> outcomes=DecisionNetwork.GetOutcomeIds(nodeId).ToList<string>();
			Dictionary<string,double> dictionary = new Dictionary<string, double>();
			foreach (string outcome in outcomes)
				dictionary.Add(outcome, mau(DecisionNetwork,nodeId, outcome));
			return dictionary;
		}

		public KeyValuePair<string,double> BestDecision(string nodeId,Mau mau) //Restituisce la decisione con utilità maggiore
		{
			if (!DecisionNetwork.GetNodeType(nodeId).Equals(Network.NodeType.List))
				throw new SmileException(string.Format("Node {0} is not a decision", nodeId));
			Dictionary<string,double> decisions =Outcomes(nodeId,mau);
			KeyValuePair<string,double> max = decisions.Aggregate((x, y) => x.Value > y.Value ? x : y);
			return max;
		}

		public KeyValuePair<string, double> RandomEvidence(string nodeId)
		{
			Dictionary<string, double> chances = ChancesWithProbabilities(nodeId);
			double num = new Random().NextDouble();
			KeyValuePair<string, double> choice = chances.ToList()[0];
			double sum = 0;
			bool end = false;
			for(int i=0;i<chances.Count() && !end;i++)
            {
				KeyValuePair<string, double> pair = chances.ToList<KeyValuePair<string,double>>()[i];
				sum += pair.Value;
				if (num <= sum)
                {
					choice = pair;
					end = true;
				}
            }
			DecisionNetwork.SetEvidence(nodeId, choice.Key);
			Step();
			return choice;
		}

		private Dictionary<string,double> ChancesWithProbabilities(string nodeId)
        {
			List<string> chances = DecisionNetwork.GetOutcomeIds(nodeId).ToList<string>();
			List<double> probs = DecisionNetwork.GetNodeValue(nodeId).ToList<double>();
			Dictionary<string, double> set = new Dictionary<string, double>();
			for (int i = 0; i < chances.Count; i++)
				set.Add(chances[i], probs[i]);
			return set;
        } 

		public void SetEvidence(string nodeId, string evidence) => DecisionNetwork.SetEvidence(nodeId, evidence); //Imposta l'evidenza di un nodo

		public Dictionary<string, double> Evidence(string nodeId)
		{
			Dictionary<string, double> set = new Dictionary<string, double>();
			Dictionary<string, double> chances = ChancesWithProbabilities(nodeId);
			foreach (KeyValuePair<string, double> chance in chances)
				if (chance.Value > 0) set.Add(chance.Key,chance.Value);
			return set;
		}

		private License GenieLicense() //Licenza di Genie
		{
			return new Smile.License
			(
				"SMILE LICENSE 95be0887 c9924a76 c61b126b " +
				"THIS IS AN ACADEMIC LICENSE AND CAN BE USED " +
				"SOLELY FOR ACADEMIC RESEARCH AND TEACHING, " +
				"AS DEFINED IN THE BAYESFUSION ACADEMIC " +
				"SOFTWARE LICENSING AGREEMENT. " +
				"Serial #: ufpnqoykjcwewwa1hvynko5j " +
				"Issued for: MARCO CAREGA (20018128@studenti.uniupo.it) " +
				"Academic institution: Universit\u00e0 del Piemonte Orientale " +
				"Valid until: 2021-07-17 " +
				"Issued by BayesFusion activation server",
				new byte[]
				{
					0x62,0x42,0x87,0x24,0x45,0x06,0xdd,0x0f,0x4d,0x57,0x42,0x95,0xec,0x3b,0x1f,0x38,
					0x55,0x73,0xf6,0xb3,0x60,0xfa,0x46,0x30,0xb3,0xca,0xe2,0xa0,0x80,0xc1,0xce,0x30,
					0x54,0x48,0x49,0xf1,0xa3,0x88,0xb2,0x6e,0xc2,0x5d,0x07,0xdd,0xe1,0x60,0x15,0x26,
					0x94,0x2b,0x69,0x94,0xba,0x51,0xad,0xa6,0x12,0x20,0x45,0x3d,0xa2,0xa5,0x75,0x19
				}
			);
		}
	}

    
}

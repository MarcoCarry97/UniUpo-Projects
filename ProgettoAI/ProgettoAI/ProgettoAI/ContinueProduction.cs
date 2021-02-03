using System;
using System.Collections.Generic;
using System.Linq;
using Smile;

namespace ProgettoAI
{
    class Production : BayesBehaviour
    {
        public const string RESEARCH = "MarketResearch";
        public const string PROTOTYPE = "DevelopPrototype";
        public const string PRODUCTION = "ContinueProduction";
        public const string YES = "Yes";
        public const string NO = "NO";
        public const string TOTAL = "Total";
        public const string RESEARCHCHANCE = "Research";
        public const string QUALITYCHANCE = "ProductQuality";
        public const string PROFICTCHANCE = "FutureProficts";

        private Mau mau = new Mau((bn,decisionNode, choice) => //Funzione che permette calcola l'utilità attesa massima per una data decisione
        {
            bn.SetEvidence(decisionNode, choice);
            bn.UpdateBeliefs();
            List<double> values = bn.GetNodeValue("Total").ToList<double>();
            bn.ClearEvidence(decisionNode);
            return values.Max();
        });

        public Production() : base()
        {
            DecisionNetwork.ReadFile("Networks/ContinueProduction.xdsl");
            Step();
        }

        public void DoMarketResearch(string decision) => TakeDecision(RESEARCH, decision);
        public void DevelopPrototype(string decision) => TakeDecision(PROTOTYPE, decision);
        public void Continue(string decision) => TakeDecision(PRODUCTION, decision);
        public List<double> Utilities() => Values(TOTAL); //Restituisce le utilità
        public KeyValuePair<string,double> BestMarketDecision() => BestDecision(RESEARCH,mau);
        public KeyValuePair<string, double> BestPrototypeDecision() => BestDecision(PROTOTYPE,mau);
        public KeyValuePair<string, double> BestContinueDecision() => BestDecision(PRODUCTION,mau);
        public Dictionary<string,double> MarketDecisions() => Outcomes(RESEARCH,mau);
        public Dictionary<string, double> PrototypeDecisions() => Outcomes(PROTOTYPE,mau);
        public Dictionary<string, double> ProductionDecisions() => Outcomes(PRODUCTION,mau);
        public KeyValuePair<string,double> RandomEvidenceResearch() => RandomEvidence(RESEARCHCHANCE);
        public KeyValuePair<string, double> RandomEvidencePrototype() => RandomEvidence(QUALITYCHANCE);
        public KeyValuePair<string, double> RandomEvidenceProficts() => RandomEvidence(PROFICTCHANCE);
        public Dictionary<string, double> ResearchEvidence() => Evidence(RESEARCHCHANCE);
        public Dictionary<string, double> PrototypeEvidence() => Evidence(QUALITYCHANCE);
        public Dictionary<string, double> ProfictsEvidence() => Evidence(PROFICTCHANCE);
        public void SetResearchEvidence(string evidence) => SetEvidence(RESEARCHCHANCE, evidence);
        public void SetPrototypeEvidence(string evidence) => SetEvidence(QUALITYCHANCE, evidence);
        public void SetProfictEvidence(string evidence) => SetEvidence(PROFICTCHANCE, evidence);
    }
}

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

        private Mau mau = new Mau((bn,decisionNode, choice) =>
        {
            bn.SetEvidence(decisionNode, choice);
            bn.UpdateBeliefs();
            List<double> values = bn.GetNodeValue("Total").ToList<double>();
            return values.Max();
        });

        public Production() : base()
        {
            DecisionNetwork.ReadFile("Networks/ContinueProduction.xdsl");
            Step();
        }

        public void DoMarketResearch(bool decision) => TakeDecision(RESEARCH, decision ? YES : NO);
        public void DevelopPrototype(bool decision) => TakeDecision(PROTOTYPE, decision ? YES : NO);
        public void Continue(bool decision) => TakeDecision(PRODUCTION, decision ? YES : NO);
        public List<double> Utilities() => Values(TOTAL);
        public KeyValuePair<string,double> BestMarketDecision() => BestDecision(RESEARCH,mau);
        public KeyValuePair<string, double> BestPrototypeDecision() => BestDecision(PROTOTYPE,mau);
        public KeyValuePair<string, double> BestContinueDecision() => BestDecision(PRODUCTION,mau);
        public Dictionary<string,double> MarketDecisions() => Outcomes(RESEARCH,mau);
        public Dictionary<string, double> PrototypeDecisions() => Outcomes(PROTOTYPE,mau);
        public Dictionary<string, double> ProductionDecisions() => Outcomes(PRODUCTION,mau);
    }
}

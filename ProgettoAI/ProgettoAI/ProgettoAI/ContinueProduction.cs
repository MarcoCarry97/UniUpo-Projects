using System;
using System.Collections.Generic;
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
        public Production():base()
        {
            DecisionNetwork.ReadFile("Networks/ContinueProduction.xdsl");
        }

        public void DoMarketResearch(bool decision)
        {
            TakeDecision(RESEARCH, decision ? YES : NO);
        }

        public void DevelopPrototype(bool decision)
        {
            TakeDecision(PROTOTYPE, decision ? YES : NO);
        }

        public void Continue(bool decision)
        {
            TakeDecision(PRODUCTION, decision ? YES : NO);
        }

        public List<double> Utilities()
        {
            return this.Values("Total");
        }


    }
}

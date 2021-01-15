using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ProgettoAI
{
    class MainFirstExercise
    {
        public static Production production;

        static void Main(string[] args)
        {
            production = new Production();
            CheckMarketDecision();
        }

        private static void CheckMarketDecision()
        {
            Console.WriteLine("Possible decisions for market research:");
            Dictionary<string,double> decisions = production.MarketDecisions();
            foreach (KeyValuePair<string, double> decision in decisions)
                Console.WriteLine(string.Format("{0}, Utility: {1}", decision.Key, decision.Value));
            KeyValuePair<string, double> bestDecision = production.BestMarketDecision();
            Console.WriteLine(string.Format("The best decision is {0}, so I take it!",bestDecision.Key));

            KeyValuePair<string, double> bestMarketDec = production.BestMarketDecision();
        }
    }
}

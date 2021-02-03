using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Linq;

namespace ProgettoAI
{
    class MainFirstExercise
    {
        public static Production production;

        public static bool auto;

        public static void Execute(string[] args)
        {
            production = new Production();
            Console.WriteLine("The first two decision can be auto-taken, do you want it? (y/n)");
            auto = ReadAuto();
            CheckMarketDecision();
            CheckPrototypeDecision();
            CheckProductionDecision();
            Console.WriteLine("The final utility is {0}!", production.Utilities()[0]);
        }

        private static void PrintDecisions(Dictionary<string,double> decisions)
        {
            foreach (KeyValuePair<string, double> decision in decisions)
                Console.WriteLine(string.Format("{0}, Utility: {1}", decision.Key, decision.Value));
        }

        private static string ReadChoice(List<string> possibleChoices)
        {
            bool correct = false;
            string input = "";
            while (!correct)
            {
                input=Console.ReadLine();
                if (possibleChoices.Contains(input))
                    correct = true;
                else Console.WriteLine("{0} isn't a valid choice, please type another one!",input);
            }
            return input;
        }

        private static bool ReadAuto()
        {
            bool correct = false;
            string input="";
            while (!correct)
            {
                input = Console.ReadLine();
                if (input.Equals("y") || input.Equals("n"))
                    correct = true;
                else Console.WriteLine("{0} isn't a valid choice, please type another one!", input);
            }
            return input.Equals("y") ? true : false;
        }

        private static void CheckMarketDecision()
        {
            Console.WriteLine("Do you want do to a market research?");
            Dictionary<string,double> decisions = production.MarketDecisions();
            PrintDecisions(decisions);
            KeyValuePair<string, double> bestDecision = production.BestMarketDecision();
            Console.WriteLine(string.Format("The best decision is {0}!",bestDecision.Key));
            if (auto)
            {
                production.DoMarketResearch(bestDecision.Key);
                Console.WriteLine("Auto-Decision: I took {0}", bestDecision.Key);
                KeyValuePair<string, double> rand = production.RandomEvidenceResearch();
                Console.WriteLine("Random choice with prob. {1} : {0}", rand.Key, rand.Value);
            }
            else
            {
                string choice = ReadChoice(decisions.Keys.ToList<string>());
                production.DoMarketResearch(choice);
                Console.WriteLine("Which evidence for Research?");
                Dictionary<string, double> evidences = production.ResearchEvidence();
                foreach (KeyValuePair<string, double> pair in evidences)
                    Console.WriteLine("{0} {1}", pair.Key, pair.Value);
                choice = ReadChoice(evidences.Keys.ToList<string>());
                production.SetResearchEvidence(choice);
            }
            
            Console.WriteLine();
        }

        private static void CheckPrototypeDecision()
        {
            Console.WriteLine("Do you want to develop a prototype?");
            Dictionary<string, double> decisions = production.PrototypeDecisions();
            foreach (KeyValuePair<string, double> decision in decisions)
                Console.WriteLine(string.Format("{0}, Utility: {1}", decision.Key, decision.Value));
            KeyValuePair<string, double> bestDecision = production.BestPrototypeDecision();
            if (auto)
            {
                production.DevelopPrototype(bestDecision.Key);
                Console.WriteLine("Auto-Decision: I took {0}", bestDecision.Key);
                KeyValuePair<string, double> rand = production.RandomEvidencePrototype();
                Console.WriteLine("Random choice with prob. {1} : {0}", rand.Key, rand.Value);
            }
            else
            {
                string choice = ReadChoice(decisions.Keys.ToList<string>());
                production.DevelopPrototype(choice);
                Console.WriteLine("Which evidence for ProductQuality?");
                Dictionary<string, double> evidences = production.PrototypeEvidence();
                foreach (KeyValuePair<string, double> pair in evidences)
                    Console.WriteLine("{0} {1}", pair.Key, pair.Value);
                choice = ReadChoice(evidences.Keys.ToList<string>());
                production.SetPrototypeEvidence(choice);
            }
            
            Console.WriteLine();
        }

        private static void CheckProductionDecision()
        {
            Console.WriteLine("Do you want to continue the production?");
            Dictionary<string, double> decisions = production.ProductionDecisions();
            PrintDecisions(decisions);
            KeyValuePair<string, double> bestDecision = production.BestContinueDecision();
            Console.WriteLine(string.Format("The best decision is {0}!", bestDecision.Key));
            string choice = ReadChoice(decisions.Keys.ToList<string>());
            production.Continue(choice);
            Console.WriteLine("Do you want to set the evidence of FutureProficts? (y/n)");
            choice = ReadChoice(new string[] { "y", "n" }.ToList<string>());
            if (choice.Equals("y"))
            {
                KeyValuePair<string, double> rand = production.RandomEvidenceProficts();
                Console.WriteLine("Random choice a prob. {1} : {0}", rand.Key, rand.Value);
            }
            else Console.WriteLine("No Evidence selected for FutureProficts");
            Console.WriteLine();
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProgettoAI
{
    class MainSecondExercise
    {
        public static SamBot samBot;

        public static int time = 5;

        public static void Execute(string[] args)
        {
            samBot = new SamBot();
            Console.WriteLine("Does Sam want coffee? (y/n)");
            samBot.SamWantsCoffee(ReadAuto());
            Console.WriteLine("This exercise can auto-take the decisions, do you want it? (y/n)");
            bool auto = ReadAuto();
            for (int t = 0; t < time - 1; t++)
                DecisionProcess(t, auto);
            DecisionProcess(time - 1, false);
            Console.WriteLine("Utility: {0}", samBot.Values(samBot.TOTAL)[0]);
            Console.WriteLine("Probability of Coffee ad time {0}: {1}", time-1, samBot.ProbabilityOfCoffee(time-1));
        }

        private static void DecisionProcess(int t, bool auto)
        {
            Dictionary<string, double> decisions = samBot.Decisions(t);
            Console.WriteLine("Possible Decisions at time {0}:", t);
            foreach (KeyValuePair<string, double> decision in decisions)
                Console.WriteLine("{0} {1}", decision.Key, decision.Value);
            KeyValuePair<string, double> best = samBot.BestDecision(t);
            if(auto)
            {
                Console.WriteLine("The best decision is {0}, so I take it!", best.Key);
                samBot.TakeDecision(t, best.Key);
            }
            else
            {
                Console.WriteLine("The best decision is {0}!", best.Key);
                Console.WriteLine("Which action do you want to execute?");
                string choice = ReadChoice(decisions.Keys.ToList<string>());
                samBot.TakeDecision(t, choice);
            }
            Console.WriteLine();
        }

        private static string ReadChoice(List<string> possibleChoices)
        {
            bool correct = false;
            string input = "";
            while (!correct)
            {
                input = Console.ReadLine();
                if (possibleChoices.Contains(input))
                    correct = true;
                else Console.WriteLine("{0} isn't a valid choice, please type another one!", input);
            }
            return input;
        }

        private static bool ReadAuto()
        {
            bool correct = false;
            string input = "";
            while (!correct)
            {
                input = Console.ReadLine();
                if (input.Equals("y") || input.Equals("n"))
                    correct = true;
                else Console.WriteLine("{0} isn't a valid choice, please type another one!", input);
            }
            return input.Equals("y") ? true : false;
        }

        private static string Name(string node, int deltaTime)
        {
            if (deltaTime == 0) return node;
            else return string.Format("{0}_{1}", node, deltaTime);
        }

       

    }
}

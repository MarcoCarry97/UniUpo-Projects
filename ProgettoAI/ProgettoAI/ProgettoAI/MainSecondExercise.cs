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

            for(int t=0;t<time-1;t++)
            {
                Dictionary<string, double> decisions = samBot.Decisions(t);
                Console.WriteLine("Possible Decisions at time {0}:", t);
                foreach (KeyValuePair<string, double> decision in decisions)
                    Console.WriteLine("{0} {1}", decision.Key, decision.Value);
                KeyValuePair<string, double> best = samBot.BestDecision(t);
                Console.WriteLine("The best decision is {0}, so I take it!");
                samBot.TakeDecision(t, best.Key);
            }
            Dictionary<string,double>lastDecs = samBot.Decisions(time);
            Console.WriteLine("What do you want to do?");
            foreach (KeyValuePair<string, double> decision in lastDecs)
                Console.WriteLine("{0} {1}", decision.Key, decision.Value);
            KeyValuePair<string,double> lastBest = samBot.BestDecision(time);
            Console.WriteLine("The best decision is {0}!", lastBest.Key);
            string choice = ReadChoice(lastDecs.Keys.ToList<string>());
            samBot.TakeDecision(time,choice);
            //Console.WriteLine("Utility: {0}",samBot.Outcomes("Total",mau);
            Console.WriteLine("Probability of Coffee ad time {0}: {1}", time, samBot.ProbabilityOfCoffee(time));
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

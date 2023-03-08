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
            bool choice = ReadAuto();
            samBot.SamWantsCoffee(choice);
            if (choice) samBot.SetEvidence(Name("Coffee", 0), "No");
            Console.WriteLine("Where is the robot? (Lab/Office/Shop)");
            samBot.Position(ReadChoice(new string[] { "Lab", "Office", "Shop" }.ToList<string>()));
            Console.WriteLine("This exercise can auto-take the decisions, do you want it? (y/n)");
            bool auto = ReadAuto();
            for (int t = 0; t < time - 1; t++)
                DecisionProcess(t, auto);
            DecisionProcess(time - 1, false);
            Console.WriteLine("Utility: {0}", samBot.Values(samBot.TOTAL)[0]);
            Console.WriteLine("Probability of Coffee ad time {0}: {1}", time-1, samBot.ProbabilityOfCoffee(time-1));
        }

        private static void DecisionProcess(int t, bool auto) //indica il processo decisionale
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
                if(t<time-1)
                {
                    samBot.RandomPosition(t + 1);
                    if (best.Equals("PC")) samBot.RandomTakeCoffee(t + 1);
                    else if (best.Equals("CC")) samBot.RandomDeliverCoffee(t + 1);
                }
            }
            else
            {
                Console.WriteLine("The best decision is {0}!", best.Key);
                Console.WriteLine("Which action do you want to execute?");
                string choice = ReadChoice(decisions.Keys.ToList<string>());
                samBot.TakeDecision(t, choice);
                if(t<time-1)
                {
                    samBot.RandomPosition(t + 1);
                    Console.WriteLine("Has robot the coffee?");
                    Dictionary<string, double> chances = samBot.RandomCoffeeChances(t + 1);
                    foreach (KeyValuePair<string, double> chance in chances)
                        Console.WriteLine("{0} - {1}", chance.Key, chance.Value);
                    if (choice.Equals("PC")) samBot.TakeCoffee(ReadChoice(chances.Keys.ToList<string>()), t + 1);
                    else if (choice.Equals("CC")) samBot.TakeCoffee(ReadChoice(chances.Keys.ToList<string>()), t + 1);
                }
            }
            Console.WriteLine();
        }

        private static string ReadChoice(List<string> possibleChoices) //Restituisce la stringa in input da tasteria se questa è una di quelle presenti in possibleChioces
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

        private static bool ReadAuto() //Restituisce un booleano in base all'input da tastiera: y->true, n->false
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

        private static string Name(string node, int deltaTime) //Restituisce un nome in base al tempo deltaTime dato.
        {
            if (deltaTime == 0) return node;
            else return string.Format("{0}_{1}", node, deltaTime);
        }

       

    }
}

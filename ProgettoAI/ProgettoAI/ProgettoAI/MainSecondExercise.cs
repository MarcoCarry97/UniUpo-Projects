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

        private static Mau mau = new Mau((bn, decisionNode, choice) =>
        {
            bn.SetEvidence(decisionNode, choice);
            bn.UpdateBeliefs();
            List<double> values = bn.GetNodeValue("Total").ToList<double>();
            bn.ClearEvidence(decisionNode);
            return values.Max();
        });

        public static void Execute(string[] args)
        {
            samBot = new SamBot();
            Console.WriteLine("OK");
            for (int i = 0; i < time; i++)
                samBot.TakeDecision(i, "MAR");
            foreach (double value in samBot.Values("Total"))
                Console.WriteLine(value);
        }

        private static string Name(string node, int deltaTime)
        {
            if (deltaTime == 0) return node;
            else return string.Format("{0}_{1}", node, deltaTime);
        }

       

    }
}

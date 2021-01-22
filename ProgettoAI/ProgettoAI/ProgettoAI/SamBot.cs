using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProgettoAI
{
   class SamBot : BayesBehaviour
    {
        public string TOTAL = "Total";

        public string ACTION = "Action";

        private Mau mau = new Mau((bn, decisionNode, choice) =>
        {
            bn.SetEvidence(decisionNode, choice);
            bn.UpdateBeliefs();
            List<double> values = bn.GetNodeValue("Total").ToList<double>();
            bn.ClearEvidence(decisionNode);
            return values.Max();
        });

        public SamBot():base()
        {
            DecisionNetwork.ReadFile("Networks/SamBotUnrolled.xdsl");
            Step();
        }
        private string Name(string node, int deltaTime)
        {
            if (deltaTime == 0) return node;
            else return string.Format("{0}_{1}", node, deltaTime);
        }

        public void TakeDecision(int deltaTime, string choice) => base.TakeDecision(Name(ACTION, deltaTime), choice);

        public Dictionary<string, double> Decisions(int deltaTime) => Outcomes(Name(ACTION, deltaTime), mau);

        public KeyValuePair<string, double> BestDecision(int deltaTime) => Outcomes(Name(ACTION, deltaTime), mau).Aggregate((x, y) => x.Value >= y.Value ? x : y);

        public double ProbabilityOfCoffee(int deltaTime) => DecisionNetwork.GetNodeValue(Name("Coffee", deltaTime)).ToList<double>()[0];

        public void SamWantsCoffee(bool choice) => DecisionNetwork.SetEvidence("Order", choice ? "Yes" : "No");
    }

    
}

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

        private Mau mau = new Mau((bn, decisionNode, choice) => // funzione che l'utilità di una decisione
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
        private string Name(string node, int deltaTime) //Restituisce il nome del nodo a tempo deltaTime
        {
            if (deltaTime == 0) return node;
            else return string.Format("{0}_{1}", node, deltaTime);
        }

        public void TakeDecision(int deltaTime, string choice) => base.TakeDecision(Name(ACTION, deltaTime), choice); //Imposta la decisione del nodo Action a tempo deltaTime

        public Dictionary<string, double> Decisions(int deltaTime) => Outcomes(Name(ACTION, deltaTime), mau); //Restituisce le possibili decision del nodo Action a tempo deltaTime

        public KeyValuePair<string, double> BestDecision(int deltaTime) => Outcomes(Name(ACTION, deltaTime), mau).Aggregate((x, y) => x.Value >= y.Value ? x : y); //Restituisce la decisione a tempo deltaTIme con utilità maggiore

        public double ProbabilityOfCoffee(int deltaTime) => DecisionNetwork.GetNodeValue(Name("Order", deltaTime)).ToList<double>()[2]; //Restuisce la probabilità che Sam abbia il caffè a tempo deltaTime

        public void SamWantsCoffee(bool choice) => DecisionNetwork.SetEvidence("Order", choice ? "Yes" : "No"); //Imposta l'evidenza del nodo Order per indicare se Sam voglia o meno il caffè

        public void Position(string pos) => DecisionNetwork.SetEvidence("Position", pos);

        public KeyValuePair<string,double> RandomTakeCoffee(int deltaTime) => RandomEvidence(Name("Coffee", deltaTime));
        public KeyValuePair<string, double> RandomDeliverCoffee(int deltaTime)
        {
            KeyValuePair<string, double> rand = RandomEvidence(Name("Coffee", deltaTime));
            RandomEvidence(Name("Order", deltaTime));
            return rand;
        }

        public void TakeCoffee(string choice, int deltaTime) => DecisionNetwork.SetEvidence(Name("Coffee", deltaTime), choice);
        public void DeliverCoffee(string choice, int deltaTime)
        {
            DecisionNetwork.SetEvidence(Name("Coffee", deltaTime),choice);
            if(choice.Equals("No")) DecisionNetwork.SetEvidence(Name("Order", deltaTime), "Satisfied");
            Step();
        }

        public KeyValuePair<string,double> RandomPosition(int deltaTime) => RandomEvidence(Name("Position", deltaTime));

        public Dictionary<string, double> PositionChances(int deltaTime) => Evidence(Name("Position", deltaTime));
        public Dictionary<string, double> RandomCoffeeChances(int deltaTime) => Evidence(Name("Coffee", deltaTime));
    }

    
}

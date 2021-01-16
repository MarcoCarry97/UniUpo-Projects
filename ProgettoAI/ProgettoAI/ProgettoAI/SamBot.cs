using System;
using System.Collections.Generic;
using System.Text;

namespace ProgettoAI
{
   class SamBot : BayesBehaviour
    {
        public string TOTAL = "Total";


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

        public void TakeDecision(int deltaTime, string choice) => base.TakeDecision(Name(TOTAL, deltaTime), choice);
    }

    
}

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ProgettoAI
{
    class MainFirstExercise
    {
        public static BayesBehaviour production;

        static void Main(string[] args)
        {
            production = new Production();
            Console.WriteLine("OK");
        }
    }
}

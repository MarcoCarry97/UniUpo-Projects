using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

namespace ProgettoAI
{
    class MainConsole
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Which Exercise? 1 or 2?");
            List<string> choices = new string[] { "1", "2" }.ToList<string>();
            String choice = ReadChoice(choices);
            if (choice.Equals("1")) MainFirstExercise.Execute(args);
            else MainSecondExercise.Execute(args);
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
    }
}

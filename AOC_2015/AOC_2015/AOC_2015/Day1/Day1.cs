using System;
using System.IO;

namespace AOC_2015
{
    public class Day1 : Solutions
    {
        public void SolveDay1()
        {
            ReadInput();
        }

        public override void ReadInput()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), "Day1Example.txt");
            using StreamReader sr = new StreamReader(path);
            string input = sr.ReadToEnd();
            ProcessPartOne(input);
        }

        private static void ProcessPartOne(string input)
        {

        }
    }
}

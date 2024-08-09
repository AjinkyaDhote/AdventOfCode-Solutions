//---Day 1: Now Quite Lisp---//

namespace AOC_2015
{
    public static class Day1
    {
        public static void Solve()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day1\Input.txt");
            var input = Utility.ReadToEnd(path);
            ProcessPartOne(input);
            ProcessPartTwo(input);
            ;
        }

        private static void ProcessPartOne(string input)
        {
            int step = 0;
            foreach (char ch in input)
            {
                if (ch == '(')
                    step++;
                else if (ch == ')')
                    step--;
            }

            Console.WriteLine($"Reached Floor: {step}");
        }

        private static void ProcessPartTwo(string input)
        {
            int step = 0;
            int basement = 0;
            foreach (char ch in input)
            {
                if (ch == '(')
                    step++;
                else if (ch == ')')
                    step--;
                if (step == -1)
                    break;
                basement++;
            }

            Console.WriteLine($"Reached basement: {++basement}");
        }
    }
}

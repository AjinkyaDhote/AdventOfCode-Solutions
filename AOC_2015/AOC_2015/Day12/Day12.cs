//--- Day 12: JSAbacusFramework.io ---

using System.Text;

namespace AOC_2015
{
    public static class Day12
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day12\Input.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void Process(string input)
        {
            int sum = 0;
            for (int i = 0; i < input.Length; i++)
            {
                if (input[i] == '-')
                {
                    if((i < input.Length - 1) && (char.IsDigit(input[i+1])))
                    {
                        StringBuilder sb = new ();
                        i++;
                        while (i < input.Length && char.IsDigit(input[i]))
                            sb.Append(input[i++]);
                        sum -= Int32.Parse(sb.ToString());
                    }
                        
                }

                else if (char.IsDigit(input[i]))
                {
                    StringBuilder sb = new ();
                    sb.Append(input[i++]);
                    while(i < input.Length && char.IsDigit(input[i]))
                        sb.Append(input[i++]);
                    sum += Int32.Parse(sb.ToString());
                }
            }

            Console.WriteLine($"Sum: {sum}");
        }
    }
}

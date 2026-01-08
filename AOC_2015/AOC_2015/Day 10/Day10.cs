//---Day 10: Elves Look, Elves Say ---

using System.Text;

namespace AOC_2015
{ 
    public static class Day10
    {
        public static void Solve() //~2245 ms
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day10\Input.txt");
            var input = Utility.ReadToEnd(path);
            string ret = Process(input, 50);
            Console.WriteLine($"String: {input}, Sequence: {ret}, Length: {ret.Length}");
            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        static string Process(string input, int times)
        {
            if(times == 0)
                return input;

            StringBuilder sb = new ();
            for (int i = 0; i < input.Length;)
            {
                int charCount = 1;
                int j = i + 1;
                while (j < input.Length && input[i] == input[j])
                {
                    charCount++;
                    j++;
                }
                sb.Append(charCount);
                sb.Append(input[i]);
                i += charCount;
            }
            //Console.WriteLine($"String: {input}, Sequence: {sb}, Length: {sb.Length}");
            return Process(sb.ToString(), times-1);
        }
    }
}

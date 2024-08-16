//---Day 8: Matchsticks---


using System.Text;

//Wrong 1339 : low
//Wrong 1455: high
namespace AOC_2015
{
    public static class Day8
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day8\Example.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void Process(string input)
        {
            int literalLength = 0; int actualLength = 0;
            List<string> strings = Utility.SplitString(input);
            foreach(string str in strings)
            {
                literalLength += str.Length;
                StringBuilder sb = new ();
               
                for(int i = 0; i < str.Length; i++)
                {
                    char temp = str[i];
                    if (str[i] == '"') //Lone \" (double quote) character
                        continue;
                    if (str[i] == '\\') //Single backlash
                    {
                        if (i < str.Length - 1)
                        {
                            if (str[i + 1] == 'x') //"\x" hex escape
                            {
                                if(i < str.Length - 3)
                                {
                                    string sub = str.Substring(i+2, 2);
                                    int value = Convert.ToInt32(sub,16);
                                    sb.Append(Char.ConvertFromUtf32(value));
                                    i += 4;
                                }
                                else
                                {
                                    sb.Append(str[i + 1]);
                                    i++;
                                    continue;
                                }
                            }
                            else
                            {
                                sb.Append(str[i + 1]);
                                i++;
                                continue;
                            }
                        }
                    }
                   
                }
                actualLength += sb.Length;
                Console.WriteLine ($"{str}: Literal Length {str.Length}, Actual Length {sb.Length}");
            }

            Console.WriteLine($"Part One: {literalLength - actualLength}");
        }
    }
}

//---Day 8: Matchsticks---

using System.Text;

namespace AOC_2015
{
    public static class Day8
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day8\Input.txt");
            var input = Utility.ReadToEnd(path);
            //ProcessPartOne(input);
            ProcessPartTwo(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void ProcessPartOne(string input)
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
                                    i += 3;
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
                    else
                    {
                        sb.Append(str[i]);
                    }
                   
                }
                actualLength += sb.Length;
                Console.WriteLine ($"{str}: Literal Length {str.Length}, Actual Length {sb.Length}");
            }

            Console.WriteLine($"Part One: {literalLength - actualLength}");
        }

        private static void ProcessPartTwo(string input)
        {
            int literalLength = 0; int extendedLength = 0;
            List<string> strings = Utility.SplitString(input);
            foreach (string str in strings)
            {
                literalLength += str.Length;
                StringBuilder sb = new();
                sb.Append('"');
                for (int i = 0; i < str.Length; i++)
                {
                    if(str[i] == '"') 
                        sb.Append("\\\"");
                    else if (str[i] ==  '\\')
                        sb.Append("\\\\");   
                    else
                        sb.Append(str[i]);

                }
                sb.Append('"');
                extendedLength += sb.Length;
                Console.WriteLine($"{str}: Literal Length {str.Length}, {sb}: Extended Length {sb.Length}");
            }

            Console.WriteLine($"Part Two: {extendedLength - literalLength}");
        }
    }
}

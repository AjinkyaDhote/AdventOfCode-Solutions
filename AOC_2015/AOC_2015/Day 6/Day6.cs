using System.Text.RegularExpressions;

namespace AOC_2015
{
    enum Instruction
    {
        TurnOn,
        Toggle,
        TurnOff,
        Invalid
    }

    public static class Day6
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day6\Input.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;

            Console.WriteLine($"Elapsed Time {elapsedMs} ms");
        }

        private static void Process(string input)
        {
            List<string> instructions = Utility.SplitString(input);
            Int64 onCount = 0; Int64 totalBrightness = 0;
            Int64[,] grid1 = new Int64[1000,1000];
            Int64[,] grid2 = new Int64[1000,1000];

            for (int i = 0; i < instructions.Count; i++)
            {
                Instruction instruction = Instruction.Invalid;
               
                MatchCollection collection = Regex.Matches(instructions[i], @"-?\d+");

                if(!int.TryParse(collection[0].Value, out int x1) ||
                    !int.TryParse(collection[1].Value, out int y1) ||
                    !int.TryParse(collection[2].Value, out int x2) ||
                    !int.TryParse(collection[3].Value, out int y2))  
                        throw new InvalidDataException("Unable to parse int value from instruction string");
                
                if (instructions[i].Contains("turn on"))
                    instruction = Instruction.TurnOn;
                else if (instructions[i].Contains("toggle"))
                    instruction = Instruction.Toggle;
                else if (instructions[i].Contains("turn off"))
                    instruction = Instruction.TurnOff;

                switch (instruction)
                {
                    case Instruction.TurnOn:

                        for (int m = x1; m <= x2; m++)
                        {
                            for (int n = y1; n <= y2; n++)
                            {
                                grid1[m, n] = 1;
                                grid2[m, n]++;
                            }
                        }
                        break;
                    case Instruction.TurnOff:
                        for (int m = x1; m <= x2; m++)
                        {
                            for (int n = y1; n <= y2; n++)
                            {
                                grid1[m, n] = 0;
                                if (grid2[m, n] > 0)
                                    grid2[m,n]--;
                            }
                        }
                        break;
                    case Instruction.Toggle:
                        for (int m = x1; m <= x2; m++)
                        {
                            for (int n = y1; n <= y2; n++)
                            {
                                grid1[m,n] = grid1[m,n] == 1 ? 0 : 1;
                                grid2[m,n] += 2;
                            }
                        }
                        break;
                    default:
                        throw new InvalidDataException();
                }
            }

            for (int i = 0; i < 1000; i++)
            {
                for (int j = 0; j < 1000; j++)
                {
                    if (grid1[i,j] == 1) onCount++;
                    totalBrightness += grid2[i, j];
                }
            }

            Console.WriteLine($"Total Lights on {onCount}");
            Console.WriteLine($"Total Brightness {totalBrightness}");
        }
    }
}

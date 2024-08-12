// ---Day 3: Perfectly Spherical Houses in a Vacuum ---

namespace AOC_2015
{
    public static class Day3
    {
        public static void Solve()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day3\Input.txt");
            var input = Utility.ReadToEnd(path);
            ProcessPartOne(input);
            ProcessPartTwo(input);
        }

        private static void ProcessPartOne(string input)
        {
            Dictionary<KeyValuePair<int, int>, bool> map = new Dictionary<KeyValuePair<int, int>, bool>();
            int x = 0; int y = 0;
            map.Add(new KeyValuePair<int, int>(x,y), true);
            int count = 1;
            foreach (char c in input)
            {
                switch (c)
                {
                    case '^':
                        ++y;
                        break;
                    case '<':
                        --x;
                        break;
                    case '>':
                        ++x;
                        break;
                    case 'v':
                        --y;
                        break;
                    default:
                        break;

                }
                if (!map.ContainsKey(new KeyValuePair<int, int>(x, y)))
                {
                    map.Add(new KeyValuePair<int, int>(x, y), true);
                    count++;
                }
            }

            Console.WriteLine($"Number of Houses visited atleast once: {count}");
        }

        private static void ProcessPartTwo(string input)
        {
            Dictionary<KeyValuePair<int, int>, bool> map1 = [];
            Dictionary<KeyValuePair<int, int>, bool> map2 = [];
            int x = 0; int y = 0; int a = 0; int b = 0;
            map1.Add(new KeyValuePair<int, int>(x, y), true);
            map2.Add(new KeyValuePair<int, int>(a, b), true);
            int count = 1;
            bool isSanta = true;

            foreach(char c in input)
            {
                if (isSanta)
                {
                    switch (c)
                    {
                        case '^':
                            ++y;
                            break;
                        case '<':
                            --x;
                            break;
                        case '>':
                            ++x;
                            break;
                        case 'v':
                            --y;
                            break;
                        default:
                            break;
                    }

                    if ((!map1.ContainsKey(new KeyValuePair<int, int>(x, y)) && (!map2.ContainsKey(new KeyValuePair<int, int>(x,y)))))
                    {
                        map1.Add(new KeyValuePair<int, int>(x, y), true);
                        count++;
                    }
                }
                else //Robot Santa
                {
                    switch (c)
                    {
                        case '^':
                            ++b;
                            break;
                        case '<':
                            --a;
                            break;
                        case '>':
                            ++a;
                            break;
                        case 'v':
                            --b;
                            break;
                        default:
                            break;
                    }
                    if ((!map2.ContainsKey(new KeyValuePair<int, int>(a, b))) && (!map1.ContainsKey(new KeyValuePair<int, int>(a,b))))
                    {
                        map2.Add(new KeyValuePair<int, int>(a, b), true);
                        count++;
                    }
                }

                isSanta = !isSanta;
            }

            Console.WriteLine($"Houses visited by Santa and Robot Santa {count}");

        }
    }
}

//---Day 9: All in a Single Night ---

namespace AOC_2015
{
    public static class Day9
    {
        public struct Route
        {
            public string from; public string to; public uint dist;
        }

        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day9\Input.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        static void Process(string input)
        {
            List<string> paths = Utility.SplitString(input);
            HashSet<string> locations = [];
            Dictionary<Tuple<string, string>, UInt32> routes = [];
            UInt32 totalDistance = 0; UInt32 shortestDistance = UInt32.MaxValue; UInt32 longestDistance = UInt32.MinValue;
            foreach(string path in paths)
            {
                List<string> split = Utility.SplitStringAndRemoveSpaces(path, ["=", "to", " "]);
                                routes.Add(new Tuple<string, string>(split[0], split[1]), UInt32.Parse(split[2]));
                routes.Add(new Tuple<string, string>(split[1], split[0]), UInt32.Parse(split[2]));

                locations.Add(split[0]);
                locations.Add(split[1]);
            }

            //Now find all the possible permutations.
            IEnumerable<IEnumerable<string>> allPermutations = BuildPermutations( new List<string> ( locations ) ); //LINQ

            foreach(var permutation in allPermutations)
            {
                List<string> path = permutation.ToList();

                int i = 0; int j = i + 1;

                while(j < path.Count) 
                {
                    string from = path[i++];
                    string to = path[j++];
                    Tuple<string, string> t = new (from, to);

                    if(routes.TryGetValue(t, out UInt32 dist))
                        totalDistance += dist;
                }

                shortestDistance = totalDistance < shortestDistance ? totalDistance : shortestDistance;
                longestDistance = totalDistance > longestDistance ? totalDistance : longestDistance;
                totalDistance = 0;  
            }

            Console.WriteLine($"Shortest Distance: {shortestDistance}");
            Console.WriteLine($"Longest Distance:  {longestDistance}");
        }

        static List<List<string>> BuildPermutations(List<string> items)
        {
            if (items.Count > 1)
            {
                return items.SelectMany(item => BuildPermutations(items.Where(i => !i.Equals(item)).ToList()),
                                       (item, permutation) => new[] { item }.Concat(permutation).ToList()).ToList();
            }

            return [ items ];
        }
        
    }
}

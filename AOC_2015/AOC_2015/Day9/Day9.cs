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

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day9\Example.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        static void Process(string input)
        {
            List<string> paths = Utility.SplitString(input);
            List<Route> routes = new List<Route>();
            List<string> visited = [];
            uint shortest = uint.MaxValue;
            KeyValuePair<string, string> shortestRoute;
            foreach(string path in paths)
            {
                List<string> split = Utility.SplitStringAndRemoveSpaces(path, ["=", "to", " "]);
                //KeyValuePair<string, string> pair = new KeyValuePair<string, string>(split[0], split[1]);
                Route route1 = new()
                {
                    from = split[0],
                    to = split[1],
                    dist = UInt32.Parse(split[2])
                };

                Route route2 = new ()
                {
                    from = split[1],
                    to = split[0],
                    dist = route1.dist
                };
                routes.Add(route1);
                routes.Add(route2);
            }
        }
        
    }
}

//---Day 13: Knights of the Dinner Table---

using System.Text.RegularExpressions;

namespace AOC_2015
{
    public static class Day13
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day13\Input.txt");
            var input = Utility.ReadToEnd(path);
            ProcessPartOne(input);
            ProcessPartOne(input, true);
            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void ProcessPartOne(string input, bool PartTwo = false)
        {
            List <string> lines = Utility.SplitString(input);
            Dictionary<KeyValuePair<string, string>, int> map = [];
            HashSet<string> people = [];
            
            foreach(string line in lines) 
            {
                string firstWord = line.Split(' ').First();
                string lastWord = line.Split(' ').Last().Trim('.');

                people.Add(firstWord);
                people.Add(lastWord);

                string hI = Regex.Match(line, @"\d+").Value;
                bool isGain = Regex.IsMatch(line, @"gain");

                if (Int32.TryParse(hI, out int happinessIndex))
                    map.Add(new (firstWord, lastWord), isGain ? happinessIndex : - happinessIndex);
                else
                    throw new InvalidDataException();
            }

            if (PartTwo)
            {
                foreach (string p in people)
                {
                    map.Add(new (p, "Ajinkya"), 0);
                    map.Add(new ("Ajinkya", p), 0);
                }
                people.Add("Ajinkya");
            }


            List<List<string>> allPermutations = BuildPermutations(people.ToList());

            int totalChangeInHappiness = int.MinValue;
            int happinessChange = 0;
            foreach (var permutation in allPermutations)
            {
                int i = 0; int j = i + 1;

                while (j < permutation.Count)
                {
                    if (map.TryGetValue(new(permutation[i], permutation[j]), out int value1))
                        happinessChange += value1;
                    if(map.TryGetValue(new(permutation[j], permutation[i]), out int value2))
                        happinessChange += value2;

                    i++; j++;
                }

                //last person, wrap around
                if (map.TryGetValue(new(permutation[0], permutation[j - 1]), out int value3))
                    happinessChange += value3;
                if (map.TryGetValue(new(permutation[j - 1], permutation[0]), out int value4))
                    happinessChange += value4;

                totalChangeInHappiness = happinessChange > totalChangeInHappiness ? happinessChange : totalChangeInHappiness;
                happinessChange = 0;
            }

            Console.WriteLine($"Optimal Change in happiness: {totalChangeInHappiness}");
        }


        static List<List<string>> BuildPermutations(List<string> items)
        {
            if (items.Count > 1)
            {
                return items.SelectMany(item => BuildPermutations(items.Where(i => !i.Equals(item)).ToList()),
                                       (item, permutation) => new[] { item }.Concat(permutation).ToList()).ToList();
            }

            return [items];
        }

    }
}

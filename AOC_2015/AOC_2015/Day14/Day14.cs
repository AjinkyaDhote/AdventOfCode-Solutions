


using System.Numerics;

namespace AOC_2015
{
    public struct Reindeer
    {
        public string name;
        public int velocity;
        public int flyTime;
        public int restTime;

        public Reindeer(string name, int velocity, int flyTime, int restTime)
        {
            this.name = name;
            this.velocity = velocity;
            this.flyTime = flyTime;
            this.restTime = restTime;
        }
    }
        
    public static class Day14
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            List<Reindeer> list = [];
            list.Add(new Reindeer("Vixen", 8, 8, 53));
            list.Add(new Reindeer("Blitzen", 13, 4, 49));
            list.Add(new Reindeer("Rudolph", 20, 7, 132));
            list.Add(new Reindeer("Cupid", 12, 4, 43));
            list.Add(new Reindeer("Donner", 9, 5, 38));
            list.Add(new Reindeer("Dasher", 10, 4, 37));
            list.Add(new Reindeer("Comet", 3, 37, 76));
            list.Add(new Reindeer("Prancer", 9, 12, 97));
            list.Add(new Reindeer("Dancer", 37, 1, 36));

            ProcessPartOne(list);
            ProcessPartTwo(list);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void ProcessPartOne(List<Reindeer> list)
        {
            int winningDistance = 0; string winningReindeer = "";
            int raceTime = 2503;
            
            foreach (Reindeer r in list)
            {
                int velocity = r.velocity;
                int flyTime = r.flyTime;
                int restTime = r.restTime;

                int d = 0; int t = 0;

                while (true)
                {
                    if (t + flyTime + restTime < raceTime)
                    {
                        d += velocity * flyTime;
                        t += flyTime + restTime;
                    }
                    else
                        break;
                }

                //check if we can fly for rest of the remaining time
                int remainingFlyTime = raceTime - t;

                while (remainingFlyTime > 0)
                {
                    if (remainingFlyTime < flyTime)
                    {
                        d += velocity;
                        remainingFlyTime--;
                    }
                    else
                    {
                        remainingFlyTime -= flyTime;
                        d += velocity * flyTime;
                        if (flyTime + restTime > remainingFlyTime)
                            break;
                    }
                }

                if (d > winningDistance)
                {
                    winningDistance = d;
                    winningReindeer = r.name;
                }

                Console.WriteLine($"Reindeer: {r.name}, Total Distance: {d}");
            }
            Console.WriteLine();
            Console.WriteLine($"Part One Winner: {winningReindeer}, Total Distance = {winningDistance}");
        }

        private static void ProcessPartTwo(List<Reindeer> list)
        {
            int raceTime = 2503;
            int t = 0;

            //After every second we need to test who is in the lead and give them points.
            int[] distance = [0, 0, 0, 0, 0, 0, 0, 0, 0];
            int[] points = [0, 0, 0, 0, 0, 0, 0, 0, 0];
            int[] flyTimes = [0, 0, 0, 0, 0, 0, 0, 0, 0];
            int[] restTimes = [0, 0, 0, 0, 0, 0, 0, 0, 0];

            for (int i = 0; i < list.Count; i++) { flyTimes[i] = list[i].flyTime; }
                
            while (t++ < raceTime)
            {
                for (int i = 0; i < list.Count; i++)
                {
                    int velocity = list[i].velocity;
                    int flyTime = list[i].flyTime;
                    int restTime = list[i].restTime;

                    if (flyTimes[i] > 0)
                    {
                        distance[i] += velocity;
                        flyTimes[i]--;
                    }
                    else if (restTimes[i] != restTime)
                    {
                        restTimes[i]++;
                    }
                    else
                    {
                        distance[i] += velocity;
                        flyTimes[i] = flyTime - 1;
                        restTimes[i] = 0;
                    }
                }

                int maxValue = distance.Max();                
                for(int i = 0; i < list.Count;i++)
                {
                    if (distance[i] == maxValue)
                        points[i]++;
                }
            }

            int winningPoints = points.Max();
            int maxIndex = points.ToList().IndexOf(winningPoints);
            Console.WriteLine();
            Console.WriteLine($"Part Two Winner: {list[maxIndex].name}, Maximum Winning Points {winningPoints}");
        }
    }
}

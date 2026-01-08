//--- Day 11: Corporate Policy ---

using System.Text;

namespace AOC_2015
{
    public static class Day11
    {
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day11\Example.txt");
            var input = Utility.ReadToEnd(path);
            StringBuilder sb = new (input);
            List<string> expiredPasswords = [];

            for (int i = 0; i < 2; i++)
            {
                if (expiredPasswords.Count == 2)
                  break;

                while (!CheckPasswordValidity(ref sb, expiredPasswords)) next(ref sb); 
                expiredPasswords.Add(sb.ToString());        
            }

            Console.WriteLine($"Part One password: {expiredPasswords[0]}");
            Console.WriteLine($"Part Two password: {expiredPasswords[1]}");

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static bool CheckPasswordValidity(ref  StringBuilder sb, List<string> expiredPasswords)
        {
            foreach (string pass in expiredPasswords) 
            { 
                if (pass == sb.ToString()) return false;
            }
            int count = 0; 
            for(int m = 0; m < sb.Length - 1;)
            {
                if (sb[m] == sb[m + 1])
                {
                    if (m + 2 < sb.Length && sb[m] != sb[m + 2])
                        count++;
                    else if(m+2 == sb.Length)
                        count++;
                    m += 2;
                }
                else m++;
            }

            if(count < 2)
                return false;

            bool valid = false;

            //sliding window of size 3 to find pattern like abc, def, xyz
            for(int i = 0; i < sb.Length - 3; i++)
            {
                if (sb[i + 1] == sb[i] + 1)
                    if (sb[i + 2] == sb[i] + 2)
                    {
                        valid = true;
                        break;
                    }
            }

            return valid;
        }

        private static char nextletter(char c)
        {
            if (c == 'z') return 'a';
            if (c == 'h' || c == 'n' || c == 'k') return (char)(c + 2);
            return (char)(c + 1);
        }

        private static void next(ref StringBuilder sb)
        {
            int i = sb.Length - 1;
            sb[i] = nextletter(sb[i]);

            while (i >= 0 && sb[i] == 'a')
            {
                i--;
                sb[i] = nextletter(sb[i]);
            }
        }
    }
}

//---Day 4: The Ideal Stocking Stuffer ---

using System.Text;
using System.Security.Cryptography;

namespace AOC_2015
{
    public static class Day4
    {
        public static void Solve()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day4\Input.txt");
            var input = Utility.ReadToEnd(path);
            ProcessPartOne(input);
            ProcessPartTwo(input);
        }

        static void ProcessPartOne(string input)
        {
            int result = 0;
            for(int i = 0; i < int.MaxValue; i++)
            {
                bool found = true;
                string temp = input + i;

                byte[] inputBytes = Encoding.UTF8.GetBytes(temp);
                byte[] hashBytes = MD5.HashData(inputBytes);
                       
                string hexString = Convert.ToHexString(hashBytes);
                
                for (int j = 0; j < 5; j++)
                {
                    if (hexString[j] != '0')
                    {
                        found = false;
                        break;
                    }
                }

                if (found)
                {
                    result = i;
                    break;
                }
            }
            Console.WriteLine($"Required number is {result}");
        }

        static void ProcessPartTwo(string input)
        {
            int result = 0;
            for (int i = 0; i < int.MaxValue; i++)
            {
                bool found = true;
                string temp = input + i;

                byte[] inputBytes = Encoding.UTF8.GetBytes(temp);
                byte[] hashBytes = MD5.HashData(inputBytes);

                string hexString = Convert.ToHexString(hashBytes);

                for (int j = 0; j < 6; j++)
                {
                    if (hexString[j] != '0')
                    {
                        found = false;
                        break;
                    }
                }

                if (found)
                {
                    result = i;
                    break;
                }
            }
            Console.WriteLine($"Required number is {result}");
        }

    }
}

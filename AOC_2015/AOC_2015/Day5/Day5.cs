namespace AOC_2015
{
    public static class Day5
    {
        public static void Solve()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day5\Input.txt");
            var input = Utility.ReadToEnd(path);
            ProcessPartOne(input);
            ProcessPartTwo(input);
        }

        private static bool IsVowel(char c)
        {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o'  || c == 'u';
        }

        private static bool IsNiceString(string str)
        {
            bool isNice = true;
            int appearsTwiceInARow = 0;
            Dictionary<char, int> vowelCount = [];
            vowelCount['a'] = 0;
            vowelCount['e'] = 0;
            vowelCount['i'] = 0;
            vowelCount['o'] = 0;
            vowelCount['u'] = 0;

            //Contains atleast three vowels (aeiou)

            //contains atleast one letter that appears twice in a row, like "xx", "abcdde (dd)", or aabbccdd

            //Does not contain ab, cd, pq, or xy

            for (int i = 0; i < str.Length; i++)
            {
                if (IsVowel(str[i]))
                    vowelCount[str[i]]++;

                if (i < str.Length - 1)
                {
                    if (str[i] == str[i + 1])
                        appearsTwiceInARow++;

                    switch (str[i])
                    {
                        case 'a':
                            if (str[i + 1] == 'b')
                                isNice = false;
                                break;
                        case 'c':
                            if (str[i + 1] == 'd')
                                isNice = false;
                                break;
                        case 'p':
                            if(str[i + 1] == 'q')
                                isNice = false;
                                break;
                        case 'x':
                            if (str[i + 1] == 'y')
                                isNice = false;
                                break;
                        default:
                            break;
                    }
                }
            }

            if (isNice)
            {
                int numberOfVowels = 0;
                foreach (KeyValuePair<char, int> keyValuePair in vowelCount)
                {
                    numberOfVowels += keyValuePair.Value;
                }
                if (numberOfVowels < 3 || appearsTwiceInARow < 1)
                    isNice = false;
            }

            return isNice;
        }

        static void ProcessPartOne(string input)
        {
            List<string> strings = Utility.SplitString(input);
            int niceString = 0;
            foreach (string s in strings)
            {
                if (IsNiceString(s))
                    niceString++;
            }

            Console.WriteLine($"Part One, Total Nice Strings: {niceString}");
        }


        private static bool IsNiceStringModified(string str)
        {
            bool isNice = true;
            int repeatCondition = 0;//At least one letter which repeats with exactly one letter between them, like xyx, abcdefeghi (efe)

            //Contains Pair of two letters that appears at least twice in the string without overlapping 
            Dictionary<string, int> pairs = [];

            for (int i = 0; i < str.Length; i++)
            {
                if (i < str.Length - 1)
                {
                        string add = String.Concat(str[i], str[i + 1]);
                        if (!pairs.TryAdd(add, 1))
                        {
                            if (str[i] == str[i +1]) //overlap?
                            {
                                if (i < str.Length - 2)
                                {
                                    if (str[i] == str[i + 2])
                                        pairs[add]++;
                                    else if(str[i] != str[i - 1])
                                        pairs[add]++;
                                }    
                                else if (str[i] != str[i-1])
                                    pairs[add]++;
                        }
                            else
                                pairs[add]++;
                            
                        }
                }

                if (i < str.Length - 2)
                    if (str[i] == str[i + 2])
                        repeatCondition++;
            }

            if (repeatCondition < 1) isNice = false;

            if(isNice)
            {
                bool greaterThanTwoPairs = false;
                foreach (KeyValuePair<string, int> pair in pairs)
                {
                    if (pair.Value > 1)
                    {
                        greaterThanTwoPairs = true;
                        break;
                    }
                     
                }
                isNice = greaterThanTwoPairs;
            }

            return isNice;
        }

        static void ProcessPartTwo(string input)
        {
            List<string> strings = Utility.SplitString(input);
            int niceString = 0;
            foreach (string s in strings)
            {
                if (IsNiceStringModified(s))
                {
                    //Console.WriteLine($"{s} ----> Nice String");
                    niceString++;
                }
                //else { Console.WriteLine($"{s} ----> Naughty String"); }
                    
            }

            Console.WriteLine($"Part Two, Total Nice Strings: {niceString}");
        }
    }
}

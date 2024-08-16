namespace AOC_2015
{
    public static class Utility
    {
        private static readonly string INPUT_PATH = Path.GetFullPath(@"..\..\..\");
        
        public static string GetInputPath() { return INPUT_PATH; }

        public static string ReadToEnd(string input)
        {
            using StreamReader sr = new(input);
            return sr.ReadToEnd();
        }

        public static List<string> SplitString(string input)
        {
             string[] separator = ["\r\n", "\r"];
             return input.Split(separator, StringSplitOptions.RemoveEmptyEntries).ToList();
        }

        public static List<string> SplitString(string input, string separator)
        {
            string[] newSeparator = ["\r\n", "\r", separator];
            return input.Split(newSeparator, StringSplitOptions.RemoveEmptyEntries).ToList();
        }

        public static List<string> SplitStringAndRemoveSpaces(string input, string separator)
        {
            string[] newSeparator = ["\r\n", "\r", separator, " "];
            return input.Split(newSeparator, StringSplitOptions.RemoveEmptyEntries).ToList();
        }
    }
}

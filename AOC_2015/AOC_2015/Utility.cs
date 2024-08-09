
namespace AOC_2015
{
    public static class Utility
    {
        private static readonly string INPUT_PATH = Path.GetFullPath(@"..\..\..\");
        public static string GetInputPath() { return INPUT_PATH;  }

        public static string ReadToEnd(string input)
        {
            using StreamReader sr = new (input);
            return sr.ReadToEnd();
        }

    }
}


namespace AOC_2015
{

    public abstract class Solutions
    {
        public abstract void ReadInput();
        
    }


    internal class Program
    {
        static void Main(string[] args)
        {
            //Console.WriteLine("Hello, World!");
            Day1 day1 = new Day1();
            day1.SolveDay1();
        }
    }
}

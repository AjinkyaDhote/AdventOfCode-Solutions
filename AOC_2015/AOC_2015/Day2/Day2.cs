//---Day 2: I Was Told There Would Be No Math---//

using System.Text.RegularExpressions;

namespace AOC_2015
{

    public struct Dim
    {
        public int l, w, h;
        public Dim()
        {
            l = 0; w = 0; h = 0;
        }
        public Dim(int _l, int _w, int _h)
        {
            this.l = _l; this.w = _w; this.h = _h;
        }
    }

    public static class Day2
    {
        public static void Solve()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day2\Input.txt");
            var input = Utility.ReadToEnd(path);
            List<string> dimensions = Utility.SplitString(input);
            ProcessPartOne(dimensions);
            //ProcessPartTwo(input);
        }

        private static void ProcessPartOne(List<string> dimensions)
        {
            int paperRequired = 0;
            int ribbonRequired = 0;
            for(int i = 0; i < dimensions.Count; i++)
            {
                string[] nums = Regex.Split(dimensions[i], @"\D+");

                Dim dim = new ();

                Int32.TryParse(nums[0], out dim.l);
                Int32.TryParse(nums[1], out dim.w);
                Int32.TryParse(nums[2], out dim.h);

                int surfaceArea = 2 * (dim.l * dim.w) + 2 * (dim.w * dim.h) + 2 * (dim.h * dim.l);
                List<int> l = [dim.l, dim.w, dim.h];
                l.Sort();
                surfaceArea += l[0] * l[1];
                paperRequired += surfaceArea;

                //Ribbon Calculation
                int perimeterOfShortestSide = l[0] + l[0] + l[1] + l[1];
                int volume  = (l[0] * l[1] * l[2]);
                ribbonRequired += perimeterOfShortestSide + volume;

            }

            Console.WriteLine($"Total Paper Required: {paperRequired}");
            Console.WriteLine($"Total Ribbon Required: {ribbonRequired}");
        }
    }
}

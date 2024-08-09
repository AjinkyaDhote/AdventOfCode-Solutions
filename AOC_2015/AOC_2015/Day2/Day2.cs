using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace AOC_2015
{

    public struct Dim
    {
        public int l, w, h;
        public Dim()
        {
            l = 0;
            w = 0;
            h = 0;    
        }
    }

    public static class Day2
    {
        public static void Solve()
        {
            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day2\Example.txt");
            var input = Utility.ReadToEnd(path);
            List<string> dimensions = Utility.SplitString(input);
            ProcessPartOne(dimensions);
            //ProcessPartTwo(input);
        }

        private static void ProcessPartOne(List<string> dimensions)
        {
            int paperRequired = 0;
            for(int i = 0; i < dimensions.Count; i = i+2)
            {
                string rect = dimensions[i];
                if (rect[rect.Length - 1] == '\r')
                    rect.TrimEnd('\r');
                string[] nums = Regex.Split(rect, @"\D+");
            }

                //int surfaceArea = 2 * (dim.l * dim.w) + 2 * (dim.w * dim.h) + 2 * (dim.h * dim.l);
                //List<int> l = new List<int> { dim.l, dim.w, dim.h};
                //l.Sort();
                //surfaceArea += l[0] * l[1];
                //paperRequired += surfaceArea;
         
        }

        

    }
}

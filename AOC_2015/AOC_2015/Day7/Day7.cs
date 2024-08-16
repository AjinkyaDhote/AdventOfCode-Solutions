//---Day 7: Some Assembly Required-- -

namespace AOC_2015
{
    public static class Day7
    {
        private static readonly Dictionary<string, string> map = [];
        private static readonly Dictionary<string, UInt16> signals = [];


        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day7\Input.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        static UInt16 FindValue(string input)
        {
            if(!map.TryGetValue(input, out var output))
                throw new KeyNotFoundException(input);

            if (signals.TryGetValue(input, out UInt16 ret))
                return ret;
            else if (UInt16.TryParse(output, out UInt16 sig))
            {
                signals.TryAdd(input, sig);
                return sig;
            }
                
            else if(output.Contains("AND")) //Gate1 AND Gate2
            {
                UInt16 valueToReturn;
                List<string> wires = Utility.SplitStringAndRemoveSpaces(output, " AND ");
                
                //Here either of two could be numbers to try deducing that
                bool bWire0 = UInt16.TryParse(wires[0], out UInt16 signal0);
                bool bWire1 = UInt16.TryParse(wires[1], out UInt16 signal1);

                if (bWire0 && bWire1)
                    valueToReturn = (UInt16)(signal0 & signal1); //Both are numbers.
                else if(bWire0 && !bWire1)
                    valueToReturn = (UInt16)(signal0 & FindValue(wires[1])); //wire0 is number, wire1 in unknown.
                else if(!bWire0 && bWire1)
                    valueToReturn = (UInt16)(FindValue(wires[0]) & FindValue(wires[1])); //wire0 is unknown, wire1 is number.
                else
                    valueToReturn = (UInt16)(FindValue(wires[0]) & FindValue(wires[1])); //Both are unknowns.

                signals.TryAdd(input, valueToReturn);
                return valueToReturn;
            }

            else if (output.Contains("OR")) //Gate1 OR Gate2
            {
                UInt16 valueToReturn;
                List<string> wires = Utility.SplitStringAndRemoveSpaces(output, " OR ");
                // Here either of two could be numbers to try deducing that
                bool bWire0 = UInt16.TryParse(wires[0], out UInt16 signal0);
                bool bWire1 = UInt16.TryParse(wires[1], out UInt16 signal1);

                if (bWire0 && bWire1)
                    valueToReturn = (UInt16)(signal0 | signal1); //Both are numbers.
                else if (bWire0 && !bWire1)
                    valueToReturn = (UInt16)(signal0 | FindValue(wires[1])); //wire0 is number, wire1 in unknown.
                else if (!bWire0 && bWire1)
                    valueToReturn = (UInt16)(FindValue(wires[0]) & FindValue(wires[1])); //wire0 is unknown, wire1 is number.
                else
                    valueToReturn = (UInt16)(FindValue(wires[0]) | FindValue(wires[1]));

                signals.TryAdd(input, valueToReturn);
                return valueToReturn;
            }
            
            else if (output.Contains("NOT")) //~Gate
            {
                UInt16 valueToReturn;
                List<string> wires = Utility.SplitStringAndRemoveSpaces(output, "NOT ");
                bool bWire0 = UInt16.TryParse(wires[0], out UInt16 signal1);

                if (bWire0)
                    valueToReturn = (UInt16)(~signal1);
                else
                    valueToReturn = (UInt16)(~FindValue(wires[0]));

                signals.TryAdd(input, valueToReturn);
                return valueToReturn;
            }
            
            else if(output.Contains("LSHIFT")) //Gate LSHIFT <value>
            {
                UInt16 valueToReturn;
                List<string> wires = Utility.SplitStringAndRemoveSpaces(output, " LSHIFT ");
                bool bWire0 = UInt16.TryParse(wires[0], out UInt16 signal0);
                bool bWire1 = UInt16.TryParse(wires[1], out UInt16 signal1);

                if (!bWire0 && bWire1)
                    valueToReturn = (UInt16)(FindValue(wires[0]) << signal1);
                else if (bWire0 && !bWire1)
                    valueToReturn = (UInt16)(signal0 << FindValue(wires[1]));
                else if (bWire0 && bWire1)
                    valueToReturn = (UInt16)(signal0 << signal1);
                else
                    valueToReturn = (UInt16)(FindValue(wires[0]) << FindValue(wires[1]));

                signals.TryAdd(input, valueToReturn);
                return valueToReturn;
            }

            else if(output.Contains("RSHIFT")) //Gate RSHIFT <value>
            {
                UInt16 valueToReturn;
                List<string> wires = Utility.SplitStringAndRemoveSpaces(output, " RSHIFT ");
                bool bWire0 = UInt16.TryParse(wires[0], out UInt16 signal0);
                bool bWire1 = UInt16.TryParse(wires[1], out UInt16 signal1);

                if (!bWire0 && bWire1)
                    valueToReturn =  (UInt16)(FindValue(wires[0]) >> signal1);
                else if (bWire0 && !bWire1)
                    valueToReturn =  (UInt16)(signal0 >> FindValue(wires[1]));
                else if (bWire0 && bWire1)
                    valueToReturn = (UInt16)(signal0 >> signal1);
                else
                    valueToReturn = (UInt16)(FindValue(wires[0]) >> FindValue(wires[1]));

                signals.TryAdd(input, valueToReturn);
                return valueToReturn;

            }

            return FindValue(output); //This is another unknown gate.
        }


        static void Process(string input)
        {
            List<string> instructions = Utility.SplitString(input);

            foreach (string instruction in instructions) //Create the map with all output as key and all input as corresponding values.
            {
                List<string> split = Utility.SplitString(instruction, " -> ");
                map.Add(split[1], split[0]);
            }

            //Real Input
            UInt16 valueA;
            valueA = FindValue("a");
            Console.WriteLine($"Part One a: {valueA}");

            //Part Two
            signals.Clear();
            signals.Add("b", valueA);
            valueA = FindValue("a");
            Console.WriteLine($"Part Two a: {valueA}");
        }
    }
}

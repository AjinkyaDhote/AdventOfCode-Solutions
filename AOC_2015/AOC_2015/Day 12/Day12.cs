//--- Day 12: JSAbacusFramework.io ---

using System.Text;
using System.Text.Json;

namespace AOC_2015
{
    public static class Day12
    {
        private static ReadOnlySpan<byte> Utf8Bom => [ 0xEF, 0xBB, 0xBF ];
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day12\Input.txt");
            var input = Utility.ReadToEnd(path);
            ProcessPartOne(input);

            ReadOnlySpan<byte> jsonReadOnlySpan = File.ReadAllBytes(Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day12\Input.txt"));

            // Read past the UTF-8 BOM bytes if a BOM exists.
            if (jsonReadOnlySpan.StartsWith(Utf8Bom))
                jsonReadOnlySpan = jsonReadOnlySpan.Slice(Utf8Bom.Length);

            var reader = new Utf8JsonReader(jsonReadOnlySpan);
            ProcessPartTwo(ref reader);
            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void ProcessPartOne(string input)
        {
            int sum = 0;
            for (int i = 0; i < input.Length; i++)
            {
                if (input[i] == '-')
                {
                    if ((i < input.Length - 1) && (char.IsDigit(input[i + 1])))
                    {
                        StringBuilder sb = new();
                        i++;
                        while (i < input.Length && char.IsDigit(input[i]))
                            sb.Append(input[i++]);
                        sum -= Int32.Parse(sb.ToString());
                    }
                }

                else if (char.IsDigit(input[i]))
                {
                    StringBuilder sb = new();
                    sb.Append(input[i++]);
                    while (i < input.Length && char.IsDigit(input[i]))
                        sb.Append(input[i++]);
                    sum += Int32.Parse(sb.ToString());
                }
            }

            Console.WriteLine($"Part One Sum: {sum}");
        }

        private static int ParseJsonObject(ref Utf8JsonReader reader)
        {
            int sum = 0;
            while (reader.Read())
            {
                JsonTokenType type = reader.TokenType;
                switch (type)
                {
                    case JsonTokenType.StartObject:
                        sum += ParseJsonObject(ref reader);
                        break;
                    case JsonTokenType.Number:
                        sum += reader.GetInt32();
                        break;
                    case JsonTokenType.String:
                        string? text = reader.GetString();
                        if (text == "red")
                        {
                            while (reader.Read())
                            {
                                JsonTokenType tokenType = reader.TokenType;
                                switch (tokenType)
                                { 
                                    case JsonTokenType.StartObject:
                                        ParseJsonObject(ref reader);
                                        break;
                                    case JsonTokenType.StartArray:
                                        ParseJsonArray(ref reader);
                                        break;
                                    case JsonTokenType.EndObject:
                                        return 0; //Always return 0 regardless of what children return as we found "red" in the object value.
                                }
                            }
                        }
                        break;
                    case JsonTokenType.StartArray:
                        sum += ParseJsonArray(ref reader);
                        break;
                    case JsonTokenType.EndObject:
                        return sum;
                }
            }
            return sum; 
        }

        private static int ParseJsonArray(ref Utf8JsonReader reader) 
        {
            int sum = 0;
            while (reader.Read())
            {
                JsonTokenType type = reader.TokenType;
                switch (type)
                {
                    case JsonTokenType.StartObject:
                        sum += ParseJsonObject(ref reader);
                        break;
                    case JsonTokenType.StartArray:
                        sum += ParseJsonArray(ref reader);
                        break;
                    case JsonTokenType.Number:
                        sum += reader.GetInt32();
                        break;
                    case JsonTokenType.EndArray:
                        return sum;
                }
            }
            return sum;
        }

        private static void ProcessPartTwo(ref Utf8JsonReader reader)
        {
            int sum = 0;
            while (reader.Read())
            {
                JsonTokenType type = reader.TokenType; 
                switch(type)
                {
                    case JsonTokenType.StartArray:
                        sum += ParseJsonArray(ref reader);
                        break;
                    default:
                        break;
                }
            }

            Console.WriteLine($"Part Two Sum: {sum}");
        }
    }
}

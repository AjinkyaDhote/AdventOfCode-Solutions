//--- Day 12: JSAbacusFramework.io ---

using System.Diagnostics.CodeAnalysis;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;


namespace AOC_2015
{
    public class Root
    {
        public List<object>? MyArray { get; set; }
    }

    public static class Day12
    {
        private static ReadOnlySpan<byte> Utf8Bom => new byte[] { 0xEF, 0xBB, 0xBF };
        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day12\Input.txt");
            var input = Utility.ReadToEnd(path);
            //ProcessPartOne(input);

            ReadOnlySpan<byte> jsonReadOnlySpan = File.ReadAllBytes(Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day12\Input.txt"));
            
            // Read past the UTF-8 BOM bytes if a BOM exists.
            if (jsonReadOnlySpan.StartsWith(Utf8Bom))
            {
                jsonReadOnlySpan = jsonReadOnlySpan.Slice(Utf8Bom.Length);
            }

            var reader = new Utf8JsonReader(jsonReadOnlySpan);
            ProcessPartTwo(reader);
            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static int ProcessString(string str)
        {
            int sum = 0;

            for(int i = 0; i < str.Length; i++)
            {
                if (str[i] == '{')
                    sum += ProcessString(new string(str.Substring(str[i])));
            }

            return sum;

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

            Console.WriteLine($"Sum: {sum}");
        }

        private static int ParseJsonObject(ref Utf8JsonReader reader, bool skip = false)
        {
            if (skip)
            {
                while (reader.TokenType != JsonTokenType.EndObject) 
                    reader.Read();
                return 0;
            }

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
                            sum = 0;
                            while (reader.Read())
                            {
                                JsonTokenType tokenType = reader.TokenType;
                                switch (tokenType)
                                { 
                                    case JsonTokenType.StartObject:
                                        ParseJsonObject(ref reader, true);
                                        break;
                                    case JsonTokenType.StartArray:
                                        ParseJsonArray(ref reader, true);
                                        break;
                                    case JsonTokenType.EndObject:
                                        return 0;
                                    case JsonTokenType.PropertyName:
                                        string propertyName = reader.GetString();
                                        break;
                                    case JsonTokenType.String:
                                        string str = reader.GetString();
                                        break;
                                    case JsonTokenType.Number:
                                        int num = reader.GetInt32();
                                        break;
                                }
                            }
                            return sum;
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

        private static int ParseJsonArray(ref Utf8JsonReader reader, bool skip = false) 
        {
            if (skip)
            {
                while(reader.Read() && reader.TokenType != JsonTokenType.EndArray)
                    reader.Read();
                return 0;
            }

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
                    case JsonTokenType.String:
                        string? text = reader.GetString();
                        if (text == "red")
                        {
                            reader.Skip();
                        }
                        break;
                    case JsonTokenType.EndArray:
                        return sum;
                }
            }

            return sum;
        }

        private static void ProcessPartTwo(Utf8JsonReader reader)
        {
            int sum = 0;
            while (reader.Read())
            {
                JsonTokenType type = reader.TokenType; 
                switch(type)
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
                    default:
                        break;
                }
            }

            Console.WriteLine(sum);
        }
    }
}

//---Day 15: Day 15: Science for Hungry People ---
namespace AOC_2015
{
    /*Sprinkles: capacity 2, durability 0, flavor -2, texture 0, calories 3
    Butterscotch: capacity 0, durability 5, flavor -3, texture 0, calories 3
    Chocolate: capacity 0, durability 0, flavor 5, texture -1, calories 8
    Candy: capacity 0, durability -1, flavor 0, texture 5, calories 8*/

    public static class Day15
    {
        public struct Ingredient
        {
            string name;
            public int capacity;
            public int durability;
            public int flavor;
            public int texture;
            public int calories;
            public int quantity { get; set; }

            public Ingredient(string _name, int c, int d, int f, int t, int ca)
            {
                name = _name;
                capacity = c;
                durability = d;
                flavor = f;
                texture = t;
                calories = ca;
                quantity = 0;
            }
        }

        public static void Solve()
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();

            var path = Path.Combine(Directory.GetCurrentDirectory(), Utility.GetInputPath() + @"Day15\Example.txt");
            var input = Utility.ReadToEnd(path);
            Process(input);

            watch.Stop();
            Console.WriteLine($"Elapsed Time {watch.ElapsedMilliseconds} ms");
        }

        private static void Process(string input)
        {
            List<Ingredient> ingredients = [];
            {
                ingredients.Add(new Ingredient("Butterscotch", -1, -2, 6, 3, 8));
                ingredients.Add(new Ingredient("Cinnamon", 2, 3, -2, -1, 3));

                //ingredients.Add(new Ingredient("Sprinkles", 2, 0, -2, 0, 3));
                //ingredients.Add(new Ingredient("Butterscotch", 0, 5, -3, 0, 3));
                //ingredients.Add(new Ingredient("Chocolate", 0, 0, 5, -1, 8));
                //ingredients.Add(new Ingredient("Candy", 0, -1, 0, 5, 8));
            }

            int totalIngredients = ingredients.Count;
            int split = 100 / totalIngredients;

            int ascend = 1, descend = -1;





            int totalScore = int.MinValue;

            Console.WriteLine($"{totalScore}");
        }
    }
}

using System;

namespace LineCounter
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1 && (args.Length != 2 || args[1] != "/s"))
            {
                Console.WriteLine("Reports on line statistics for Visual Studio solutions.");
                Console.WriteLine();
                Console.WriteLine("Usage: LineCounter.exe filename [/s]");
            }
            else
            {
                bool silent = args.Length == 2;

                try
                {
                    Counter counter = new Counter(args[0]);
                    counter.Calculate();

                    if (!silent)
                    {
                        foreach (string s in counter.Warnings)
                            Console.WriteLine("Warning: " + s);

                        Console.WriteLine("Projects    : " + counter.Projects);
                        Console.WriteLine("Files       : " + counter.Files);
                        Console.WriteLine("Directories : " + counter.Directories);
                        Console.WriteLine("Total Lines : " + counter.TotalLines);
                        Console.WriteLine("Code Lines  : " + counter.CodeLines);
                        Console.WriteLine("Comments    : " + counter.Comments);
                        Console.WriteLine("Blank Lines : " + counter.BlankLines);
                    }
                }
                catch (Exception e)
                {
                    if (!silent)
                        Console.WriteLine("Error: " + e.Message);
                }
            }
        }
    }
}

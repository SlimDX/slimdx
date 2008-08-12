using System;

namespace LineCounter
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Reports on line statistics for Visual Studio solutions.");
                Console.WriteLine();
                Console.WriteLine("Usage: LineCounter.exe filename");
            }
            else
            {
                try
                {
                    Counter.Calculate(args[0]);
                }
                catch (Exception e)
                {
                    Console.WriteLine("Error: " + e.Message);
                }
            }

#if DEBUG
            Console.ReadLine();
#endif
        }
    }
}

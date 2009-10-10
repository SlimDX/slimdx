using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace WikiToMAML
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: ValueGenerator wikiFile");
                return;
            }

            if (!File.Exists(args[0]))
            {
                Console.WriteLine("Could not find target file");
                return;
            }

            StringBuilder output = new StringBuilder();
            output.AppendLine("<list class=\"bullet\">");

            bool indented = false;
            bool first = true;

            string[] lines = File.ReadAllLines(args[0]);
            foreach (string line in lines)
            {
                string l = line.Trim();
                if (string.IsNullOrEmpty(l))
                    continue;

                if (l.StartsWith("**") && !indented)
                {
                    indented = true;
                    output.AppendLine("<list class=\"bullet\">");
                }
                else if (!l.StartsWith("**") && indented)
                {
                    indented = false;
                    output.AppendLine("</listItem>");
                    output.AppendLine("</list>");
                    output.AppendLine("</listItem>");
                }
                else if (!first)
                    output.AppendLine("</listItem>");
                else
                    first = false;

                l = l.Replace('*', ' ');
                bool bold = false;

                if (l.Contains("'''"))
                    bold = true;

                l = l.Replace('\'', ' ');
                l = l.Trim();

                output.Append("<listItem>");
                if (bold)
                    output.Append("<legacyBold>");

                output.Append(l);

                if (bold)
                    output.Append("</legacyBold>");
            }

            output.AppendLine("</listItem>");
            output.AppendLine("</list>");
            output.AppendLine("</listItem>");
            output.AppendLine("</list>");

            File.WriteAllText(Path.Combine(Path.GetDirectoryName(args[0]), "output.txt"), output.ToString());
        }
    }
}

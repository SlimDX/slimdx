using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;

namespace ValueGenerator
{
    class Program
    {
        static StringBuilder output = new StringBuilder();

        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: ValueGenerator assemblyName");
                return;
            }

            if (!File.Exists(args[0]))
            {
                Console.WriteLine("Could not find target assembly");
                return;
            }

            Assembly assembly = Assembly.LoadFile(args[0]);

            var types = from type in assembly.GetTypes()
                        where type.IsValueType && type.IsVisible &&
                              !type.IsSpecialName && !type.IsEnum &&
                              type.GetMethod("GetHashCode", BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly) == null
                        select type;

            foreach (var type in types)
                ProcessType(type);

            File.WriteAllText("results.txt", output.ToString());
        }

        static void ProcessType(Type type)
        {
            string template = File.ReadAllText("template.txt");
            template = template.Replace("$Name", type.Name);

            StringBuilder getHashCodeImpl = new StringBuilder();
            getHashCodeImpl.Append("return ");
            var properties = type.GetProperties(BindingFlags.DeclaredOnly | BindingFlags.Public | BindingFlags.Instance);
            foreach (var property in properties)
            {
                getHashCodeImpl.Append(property.Name);

                if (property.PropertyType.IsValueType)
                    getHashCodeImpl.Append(".GetHashCode()");
                else
                    getHashCodeImpl.Append("->GetHashCode()");

                if (property == properties.Last())
                    getHashCodeImpl.Append(";");
                else
                    getHashCodeImpl.Append(" + ");
            }

            StringBuilder equalsImpl = new StringBuilder();
            equalsImpl.Append("return ( ");
            foreach (var property in properties)
            {
                equalsImpl.Append(property.Name);
                equalsImpl.Append(" == value.");
                equalsImpl.Append(property.Name);

                if (property == properties.Last())
                    equalsImpl.Append(" );");
                else
                    equalsImpl.Append(" && ");
            }

            template = template.Replace("$GetHashCodeImpl", getHashCodeImpl.ToString());
            template = template.Replace("$EqualsImpl", equalsImpl.ToString());

            output.Append(template);
            output.AppendLine();
            output.AppendLine();
        }
    }
}

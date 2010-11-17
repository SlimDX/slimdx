// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Text.RegularExpressions;
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        public CppIncludeGroup group;
        public CSharpGenerator gen;
    
        /// <summary>
        /// Run the XIDL To CSharp generator
        /// </summary>
        public void Run(string[] args)
        {
            string checkOkFile = ".slimdx_generator_ok";
            var creationTimeForGeneratorAssembly = File.GetLastWriteTime(Assembly.GetExecutingAssembly().Location);

            string fileNameXIDL = "directx.xidl";
            string optionParser = "/o:" + fileNameXIDL;

            List<string> newArgs = new List<string>();
            newArgs.Add(optionParser);
            newArgs.AddRange(args);


            // Run the parser
            Parser.Program parser = new Parser.Program();


            if (parser.IsParserAlreadyUpToDate(optionParser) && File.Exists(checkOkFile) && File.GetLastWriteTime(checkOkFile) == creationTimeForGeneratorAssembly)
            {
                Console.WriteLine("Don't need to generate files again. Last run was successfull");
                return;
            }
           
            // Run the parser, only if necessary
            group = parser.Run(newArgs.ToArray());

            // Instanciate the generator
            gen = new CSharpGenerator(group);

            // For all methods "GetXXX", convert parameters with [None] attribute and pointer to [Out] attribute
            // TODO remove this and apply one-to-one mapping

            //// Dump potential invalid "Get|Is" methods that don't have the [Out] attribute on their output paremeters
            //// Run this and inspect the method_patched.txt file
            //StreamWriter methodGetWithWrongSignature = new StreamWriter("method_patched.txt");
            //group.DumpGetMethods(".*", methodGetWithWrongSignature);
            //methodGetWithWrongSignature.Close();
            //return;

            //  Global Rename

            // -----------------------------------------------------------------------
            // MapWin32 should be call before any other mapping
            // -----------------------------------------------------------------------
            MapWin32();

            // Then order is not important (only for MapDirect3DCommon and MapD3DCompiler)

            MapDirectSound();
            MapXAPO();
            MapXAudio2();

            /*MapX3DAudio();

            MapXInput();

            MapDirectInput();

            MapXACT3();*/
           

            MapDXGI();

            MapDirect3DCommon();        // MapDirect3DCommon() should be called before MapD3DCompiler
            MapD3DCompiler();           // because D3DCreateBlob from D3DCompiler is moved to D3DCommon

            MapDirect3D9();
            MapDirect3D10AndDirect3D11();

            MapDirect2D1();
            MapDirectWrite();

            gen.GeneratedPath = @"..\..\..\";

            gen.Generate();

            File.WriteAllText(checkOkFile,"");
            File.SetLastWriteTime(checkOkFile, creationTimeForGeneratorAssembly);
            // gen.Dump("SlimDX.csv");

            // DumpEnumItems("match_enums.txt", "DirectSound");

            DumpStats();
        }

        public void DumpStats()
        {
            Dictionary<string,int> stats = new Dictionary<string, int>();
            stats["interfaces"] = 0;
            stats["methods"] = 0;
            stats["parameters"] = 0;
            stats["enums"] = 0;
            stats["structs"] = 0;
            stats["fields"] = 0;
            stats["enumitems"] = 0;           
            stats["functions"] = 0;

            foreach (var assembly in gen.Assemblies)
            {
                foreach (var nameSpace in assembly.Items)
                // Enums, Structs, Interface, FunctionGroup
                foreach (var item in nameSpace.Items)
                {
                    if (item is CSharpInterface)
                        stats["interfaces"]++;
                    else if (item is CSharpStruct)
                        stats["structs"]++;
                    else if (item is CSharpEnum)
                        stats["enums"]++;

                    foreach (var subitem in item.Items)
                    {
                        if (subitem is CSharpFunction)
                        {
                            stats["functions"]++;
                            stats["parameters"] += subitem.Items.Count;
                        }
                        else if (subitem is CSharpMethod)
                        {
                            stats["methods"]++;
                            stats["parameters"] += subitem.Items.Count;
                        }
                        else if (subitem is CSharpEnum.Item)
                        {
                            stats["enumitems"]++;
                        } 
                        else if (subitem is CSharpField)
                        {
                            stats["fields"]++;
                        }
                    }                    
                }
            }

            Console.WriteLine("Generator statistics:");
            foreach (var stat in stats)
                Console.WriteLine("\tNumber of {0} : {1}", stat.Key, stat.Value);
        }

        ///// <summary>
        ///// Used to match SlimDX Enum with SlimDX Enum after a 1st pass in order to :
        ///// - get the correct name for each enum items
        ///// - get the correct type for each enum
        ///// </summary>
        ///// <param name="fileName"></param>
        ///// <param name="nameSpace"></param>
        //public void DumpEnumItems(string fileName, string nameSpace)
        //{
        //    StreamWriter log = new StreamWriter(fileName, false, Encoding.ASCII);

        //    var assemblySlimDX = typeof(SlimDX.Direct3D9.Device).Assembly;

        //    foreach (var assembly in gen.Assemblies)
        //    {
        //        foreach (var ns in assembly.Namespaces)
        //        {
        //            if (ns.Name == "SlimDX." + nameSpace)
        //            {
        //                foreach (var cSharpEnum in ns.Enums)
        //                {
        //                    Type slimdxType = assemblySlimDX.GetType("SlimDX." + nameSpace + "." + cSharpEnum.Name);

        //                    if (slimdxType != null)
        //                    {
        //                        string[] slimDXEnumNames = Enum.GetNames(slimdxType);
        //                        Array slimDXEnumValues = Enum.GetValues(slimdxType);

        //                        Type typeInSlimDX = slimdxType.GetEnumUnderlyingType();
        //                        if (cSharpEnum.Type != typeInSlimDX)
        //                        {
        //                            string typeEnumInSlimDX = "";
        //                            if (typeInSlimDX == typeof(short))
        //                                typeEnumInSlimDX = "short";
        //                            else if (typeInSlimDX == typeof(byte))
        //                                typeEnumInSlimDX = "byte";
        //                            else if (typeInSlimDX == typeof(int))
        //                                typeEnumInSlimDX = "int";
        //                            else
        //                            {
        //                                log.WriteLine("// Unable to determine type from SlimDX for enum {0} with type {1} ", cSharpEnum.CppElement.Name, typeInSlimDX);
        //                            }

        //                            log.WriteLine("group.TagTypeName<CppEnum>(@\"^{0}$\",\"{1}\");", cSharpEnum.CppElement.Name, typeEnumInSlimDX);
        //                        }

        //                        bool isSlimFlag = typeInSlimDX.GetCustomAttributes(typeof (System.FlagsAttribute), false).Length > 0;

        //                        if (cSharpEnum.IsFlag != isSlimFlag)
        //                        {
        //                            log.WriteLine("// Warning Enums [{0}] have different Flags SlimDX [{1}] != SlimDX [{2}]", cSharpEnum.Name, isSlimFlag, cSharpEnum.IsFlag);
        //                        }

        //                        int i = 0;
        //                        foreach (var enumItem in cSharpEnum.EnumItems)
        //                        {
        //                            try
        //                            {
        //                                int value = Evaluator.EvalToInteger(string.IsNullOrEmpty(enumItem.Value) ? "" + i : enumItem.Value);

        //                                bool moreThanOne = false;
        //                                for (int j = 0; j < slimDXEnumValues.Length; j++)
        //                                {
        //                                    if ((int)slimDXEnumValues.GetValue(j) == value)
        //                                    {
        //                                        string name = slimDXEnumNames[j];
        //                                        if (!string.IsNullOrEmpty(name) && name != enumItem.Name)
        //                                        {
        //                                            log.WriteLine("group.TagName<CppEnumItem>(@\"^{0}$\",\"{1}\");" + ((moreThanOne) ? "// << DUPLICATE CHECK" : ""), enumItem.CppElementName, name);
        //                                            moreThanOne = true;
        //                                        }
        //                                    }
        //                                }
        //                            }
        //                            catch (Exception ex)
        //                            {
        //                                // Console.WriteLine(ex);
        //                            }
        //                            i++;
        //                        }
        //                    }
        //                    else
        //                    {
        //                        Console.WriteLine("Enum not found {0}", "SlimDX.Direct3D9." + cSharpEnum.Name);
        //                    }

        //                }
        //            }
        //        }
        //    }
        //    log.Close();
        //}

        /// <summary>
        /// Main SlimDX.Generator
        /// </summary>
        /// <param name="args">Command line args.</param>
        private static void Main(string[] args)
        {
            try
            {
                Program program = new Program();
                program.Run(args);
            }
            catch (Exception ex)
            {
                // Print friendly error parsable by Visual Studio in order to display them in the Error List
                StringReader reader = new StringReader(ex.ToString());

                Regex regex = new Regex(@"^\s*at\s+([^\)]+)\)\s+in\s+(.*):line\s+(\d+)");

                // Rewrite the exception in order to have it mapping well in VisualStudio

                // Write the exception as is
                Console.Out.WriteLine(ex);

                // And write the exception parsable by Visual Studio
                List<string> exceptionLines = new List<string>();
                string line = null;
                while ((line= reader.ReadLine()) != null) {
                    Match match = regex.Match(line);
                    if (match.Success)
                    {
                        string methodLocation = match.Groups[1].Value;
                        string fileName = match.Groups[2].Value;
                        string lineNumber = match.Groups[3].Value;
                        Console.Out.WriteLine("{0}({1},1): error CS9999: at {2})", fileName, lineNumber, methodLocation );
                    }
                    else
                    {
                        Console.Out.WriteLine("Generator(1,1): error CS9999: {0}", line);
                    }
                    Console.Out.Flush();
                }
                Environment.ExitCode = 1;
            }
        }
    }
}
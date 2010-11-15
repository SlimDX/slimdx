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
using System.Globalization;
using System.IO;
using System.Text;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    internal partial class Program
    {
        public CppIncludeGroup group;
        public CSharpGenerator gen;

    
        /// <summary>
        /// Run the XIDL To CSharp generator
        /// </summary>
        public void Run()
        {
            string fileNameXIDL = "directx.xidl";

            if (!File.Exists(fileNameXIDL))
            {
                Console.WriteLine("File {0} not found. You must run HeaderToXIDL before running XIDLToCSharp");
                Environment.Exit(1);
            }

            // Instantiate main objects
            group = CppIncludeGroup.Read(fileNameXIDL);
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
            group.TagName<CppEnum>(@"^D3D\d?\d?(.+)", "$1", false);
            group.TagName<CppEnum>(@"^D3DX\d?\d?(.+)", "$1", false);
            group.TagName<CppStruct>(@"^D3D\d?\d?(.+)", "$1", false);
            group.TagName<CppStruct>(@"^D3DX\d?\d?(.+)", "$1", false);
            group.TagName<CppFunction>(@"^D3D\d?\d?(.+)", "$1", false);
            group.TagName<CppFunction>(@"^D3DX\d?\d?(.+)", "$1", false);
            group.TagName<CppInterface>(@"^ID3D\d?\d?(.+)", "$1", false);
            group.TagName<CppInterface>(@"^ID3DX\d?\d?(.+)", "$1", false);

            // -----------------------------------------------------------------------
            // Mapping order is important!!!
            // -----------------------------------------------------------------------
            MapWin32();

            MapDirectSound();

            MapXAudio2();

            MapXAPO();

            MapDXGI();

            MapDirect3DCommon();
            MapD3DCompiler();

            MapDirect3D9();
            MapDirect3D10AndDirect3D11();
            
            MapDirect2D1();
            MapDirectWrite();

						gen.GeneratedPath = @"..\..\..\";

            gen.Generate();

            gen.Dump("slimdx2.csv");

            // DumpEnumItems("match_enums.txt", "DirectSound");
        }

        ///// <summary>
        ///// Used to match SlimDX Enum with SlimDX2 Enum after a 1st pass in order to :
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
        //            if (ns.Name == "SlimDX2." + nameSpace)
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
        //                            log.WriteLine("// Warning Enums [{0}] have different Flags SlimDX [{1}] != SlimDX2 [{2}]", cSharpEnum.Name, isSlimFlag, cSharpEnum.IsFlag);
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
        /// Main XIDLToCSharp
        /// </summary>
        /// <param name="args">Command line args.</param>
        private unsafe static void Main(string[] args)
        {
            Program program = new Program();
            program.Run();
        }
    }
}
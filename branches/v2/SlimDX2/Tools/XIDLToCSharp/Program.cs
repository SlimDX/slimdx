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
using System.IO;
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
            group.ModifyToGetMethods(".*");
            
            // -----------------------------------------------------------------------
            // Mapping order is important!!!
            // -----------------------------------------------------------------------
            MapWin32();

            MapDXGI();

            MapDirect3DCommon();
            MapD3DCompiler();

            MapDirect3D9();
            MapDirect3D10AndDirect3D11();
            
            MapDirect2D1();
            MapDirectWrite();

            // -----------------------------------------------------------------------
            // Garbage collector on prefix
            // -----------------------------------------------------------------------
            // Last Global Rename on 
            gen.RenameType(@"^ID3DX(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3D(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3DX(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3D(.+)", "$1", false, TypeContext.Root);

            // Rename all types (interface, methods..) that are ending with Desc, Desc1

            // Global Prefix Rename
            gen.RenameTypePart("^D3D", "");

            gen.GeneratedPath = @"..\..\..\Sources\";

            gen.Generate();
        }

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
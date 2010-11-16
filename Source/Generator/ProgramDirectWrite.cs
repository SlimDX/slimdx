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
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        /// <summary>
        /// Map DirectWrite API
        /// </summary>
        public void MapDirectWrite()
        {
            // Global namespace for Direct2D1
            string assemblyName = Global.Name + ".Direct2D1";
            string namespaceName = Global.Name + ".DirectWrite";

            foreach (var includeName in new[] { "dcommon", "dwrite" })
            {
                gen.MapIncludeToNamespace(includeName, assemblyName, namespaceName, "DirectWrite");
                group.FindContext.Add(includeName);                
            }

            // Global Rename
            group.TagName<CppEnum>(@"^DWRITE(.+)", "$1", false);
            group.TagName<CppStruct>(@"^DWRITE(.+)", "$1", false);
            
            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Enumerations
            // --------------------------------------------------------------------------------------------------------

            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Structures
            // --------------------------------------------------------------------------------------------------------

            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^IDWrite(.+)", "$1", false);

            group.TagVisibility<CppMethod>(@"^IDWriteGdiInterop::.*?LOGFONT$", Visibility.Internal);
            group.TagCallback(@"^IDWritePixelSnapping$");
            group.TagCallback(@"^IDWriteTextRenderer$");

            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppFunction>(@"^DWrite(.+)", "$1", false);
            CSharpFunctionGroup dwriteFunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "DWrite");
            group.TagFunction("^DWriteCreateFactory", "dwrite.dll", dwriteFunctionGroup);

            group.FindContext.Clear();
        }
    }
}
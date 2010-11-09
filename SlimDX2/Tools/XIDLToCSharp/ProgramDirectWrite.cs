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
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    internal partial class Program
    {


        public unsafe void MapDirectWrite()
        {

            gen.MapIncludeToNamespace("dcommon", Global.Name + ".DirectWrite", Global.Name + ".Direct2D1", "DirectWrite");
            gen.MapIncludeToNamespace("dwrite", Global.Name + ".DirectWrite", Global.Name + ".Direct2D1", "DirectWrite");
            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Enumerations
            // --------------------------------------------------------------------------------------------------------

            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Structures
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^DWRITE(.+)", "$1", false, TypeContext.Root);

            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Interfaces
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^IDWrite(.+)", "$1", false, TypeContext.Root);

            group.TagVisibility<CppMethod>(@"^IDWriteGdiInterop::.*?LOGFONT$", Visibility.Internal);
            group.TagCallback(@"^IDWritePixelSnapping$");
            group.TagCallback(@"^IDWriteTextRenderer$");

            // --------------------------------------------------------------------------------------------------------
            // DirectWrite Functions
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^DWrite(.+)", "$1", false, TypeContext.Root);
            CSharpFunctionGroup dwriteFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct2D1", Global.Name + ".DirectWrite", "DWrite");
            group.TagFunction("^DWriteCreateFactory", "dwrite.dll", dwriteFunctionGroup);
        }


    }
}
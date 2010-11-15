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
        public unsafe void MapDirect2D1()
        {

            gen.MapIncludeToNamespace("d2d1", Global.Name + ".Direct2D1");

            group.TagName<CppEnum>(@"^D2D1(.*)","$1",false);
            group.TagName<CppStruct>(@"^D2D1(.*)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // D2D1 Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppEnumItem>(@"^D2D1_FEATURE_LEVEL_(.*)", @"Level_$1");
            group.TagName<CppEnumItem>(@"^D2D1_GAMMA_2_2", @"StandardRgb");
            group.TagName<CppEnumItem>(@"^D2D1_GAMMA_1_0", @"Linear");

            // --------------------------------------------------------------------------------------------------------
            // D2D1 Structures
            // --------------------------------------------------------------------------------------------------------
            gen.MapCppTypeToCSharpType("D2D_SIZE_F", TypeSystemDrawingSizeF);
            gen.MapCppTypeToCSharpType("D2D_SIZE_U", TypeSystemDrawingSize);
            gen.MapCppTypeToCSharpType("D2D_RECT_U", TypeSlimDX2Rectangle);
            gen.MapCppTypeToCSharpType("D2D_RECT_F", TypeSlimDX2RectangleF);
            gen.MapCppTypeToCSharpType("D2D_POINT_2F", TypeSystemDrawingPointF);
            gen.MapCppTypeToCSharpType("D2D_POINT_2U", TypeSystemDrawingPoint);
            gen.MapCppTypeToCSharpType("D2D_COLOR_F", TypeSlimMathColor4);

            // Use Direct2D1.Matrix3x2 struct
            var matrix3x2Type = new CSharpStruct();
            matrix3x2Type.Name = Global.Name + ".Direct2D1.Matrix3x2";
            matrix3x2Type.SizeOf = 6 * 4;
            gen.MapCppTypeToCSharpType("D2D_MATRIX_3X2_F", matrix3x2Type);

            // --------------------------------------------------------------------------------------------------------
            // D2D1 Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^ID2D1(.+)", "$1", false);

            // Remove methods using WIC
            group.Remove<CppMethod>(@"^ID2D(\d+)RenderTarget::CreateBitmapFromWicBitmap$");
            group.Remove<CppMethod>(@"^ID2D(\d+)Factory::CreateWicBitmapRenderTarget$");

            // Tag Internal for all Create methods
            group.TagVisibility<CppMethod>(@"^ID2D(\d+)Factory::Create.*$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID2D(\d+)RenderTarget::Create.*$", Visibility.Internal);

            group.TagVisibility<CppMethod>(@"^ID2D(\d+)Mesh::Open$", Visibility.Internal, null, "Open_");

            // Set parameter as pure "In"
            group.TagParameter(@"^ID2D(\d+)RenderTarget::CreateSharedBitmap::data$", CppAttribute.In);

            // Tag D2D1 Sink interface as dual-callback interfaces
            group.TagCallback(@"ID2D(\d+).*Sink$", true);

            // --------------------------------------------------------------------------------------------------------
            // D2D1 Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppFunction>(@"^D2D1(.+)", "$1", false);
            CSharpFunctionGroup d2d1FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct2D1", Global.Name + ".Direct2D1", "D2D1");
            group.TagFunction("^D2D1.*", "d2d1.dll", d2d1FunctionGroup);
        }
    }
}
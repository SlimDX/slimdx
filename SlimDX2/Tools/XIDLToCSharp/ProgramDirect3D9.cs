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

        public unsafe void MapDirect3D9()
        {
            CSharpFunctionGroup d3d9FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D9", Global.Name + ".Direct3D9", "D3D9");
            CSharpFunctionGroup d3dx9FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D9", Global.Name + ".Direct3D9", "D3DX9");

            gen.MapIncludeToNamespace("d3d9", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3d9caps", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3d9types", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9anim", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9core", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9effect", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9mesh", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9shader", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9shape", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9tex", Global.Name + ".Direct3D9");
            gen.MapIncludeToNamespace("d3dx9xof", Global.Name + ".Direct3D9");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.Modify<CppEnum>(@"^_MAX_FVF_DECL_SIZE$", Modifiers.Remove);

            gen.RenameType(@"^D3DMULTISAMPLE_NONE$", "None");
            gen.RenameType(@"^D3DMULTISAMPLE_NONMASKABLE$", "NonMaskable");
            gen.RenameType(@"^D3DMULTISAMPLE_2_SAMPLES$", "TwoSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_3_SAMPLES$", "ThreeSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_4_SAMPLES$", "FourSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_5_SAMPLES$", "FiveSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_6_SAMPLES$", "SixSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_7_SAMPLES$", "SevenSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_8_SAMPLES$", "EightSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_9_SAMPLES$", "NineSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_10_SAMPLES$", "TenSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_11_SAMPLES$", "ElevenSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_12_SAMPLES$", "TwelveSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_13_SAMPLES$", "ThirteenSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_14_SAMPLES$", "FourteenSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_15_SAMPLES$", "FifteenSamples");
            gen.RenameType(@"^D3DMULTISAMPLE_16_SAMPLES$", "SixteenSamples");

            gen.RenameType(@"^D3DAUTHENTICATEDCHANNEL_D3D9$", "Direct3D9", true);
            gen.RenameType(@"^D3DDISPLAYROTATION_(.*)$", "ROTATION_$1");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Structures
            // --------------------------------------------------------------------------------------------------------
            gen.MapCppTypeToCSharpType("D3DCOLORVALUE", TypeSlimMathColor4);
            gen.MapCppTypeToCSharpType("D3DXCOLOR", TypeSlimMathColor4);
            gen.MapCppTypeToCSharpType("D3DXMATRIX", TypeSlimMathMatrix);
            gen.MapCppTypeToCSharpType("D3DMATRIX", TypeSlimMathMatrix);
            gen.MapCppTypeToCSharpType("D3DXVECTOR2", TypeSlimMathVector2);
            gen.MapCppTypeToCSharpType("D3DVECTOR", TypeSlimMathVector3);
            gen.MapCppTypeToCSharpType("D3DXVECTOR3", TypeSlimMathVector3);
            gen.MapCppTypeToCSharpType("D3DXVECTOR4", TypeSlimMathVector4);
            gen.MapCppTypeToCSharpType("D3DXQUATERNION", TypeSlimMathQuaternion);
            gen.MapCppTypeToCSharpType("D3DXPLANE", TypeSlimMathPlane);

            gen.MapCppTypeToCSharpType("D3DCOLOR", typeof(int));   // TODO: use real ColorRGBA8
            gen.MapCppTypeToCSharpType("D3DXFLOAT16", typeof(int)); // TODO TEMP!!!!!!
            gen.MapCppTypeToCSharpType("D3DXVECTOR2_16F", typeof(int)); // TODO TEMP!!!!!!
            gen.MapCppTypeToCSharpType("D3DXVECTOR3_16F", typeof(int)); // TODO TEMP!!!!!!
            gen.MapCppTypeToCSharpType("D3DXVECTOR4_16F", typeof(int)); // TODO TEMP!!!!!!



            group.Modify<CppStruct>(@"^D3D_OMAC$", Modifiers.Remove);

            gen.MapCppTypeToCSharpType("LPD3DXSHPRTSIMCB", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("LPD3DXUVATLASCB", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("LPD3DXIMTSIGNALCALLBACK", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("LPD3DXFILL2D", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("LPD3DXFILL3D", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("LPGLYPHMETRICSFLOAT", typeof(IntPtr));
            gen.MapCppTypeToCSharpType("D3D_OMAC", typeof(Guid));
            gen.MapCppTypeToCSharpType("D3DRECT", TypeSystemDrawingSize);     

            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Interfaces
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^GetDC$", "GetDisplayDeviceContext");
            gen.RenameType(@"^IDirect3D9$", "Direct3D9", true);
            gen.RenameType(@"^IDirect3D9Ex$", "Direct3D9Ex", true);
            gen.RenameType(@"^IDirect3D9Ex(.+)", "$1");
            gen.RenameType(@"^IDirect3D(.+)9$", "$1");
            gen.RenameType(@"^IDirect3D(.+)9$", "$1");
            gen.RenameType(@"^IDirect3D(.+)", "$1", false, TypeContext.Root);


            // --------------------------------------------------------------------------------------------------------
            // Direct3D9 Functions
            // --------------------------------------------------------------------------------------------------------
            string d3dx9DLLName = string.Format("d3dx9_{0}.dll", group.FindFirst<CppMacroDefinition>("D3DX_SDK_VERSION").StripStringValue);
            group.TagFunction("^D3D9.*", "d3d9.dll", d3d9FunctionGroup);
            group.TagFunction("^Direct3D.*", "d3d9.dll", d3d9FunctionGroup);
            group.TagFunction("^D3DX9.*", d3dx9DLLName, d3dx9FunctionGroup);
            group.TagFunction("^D3DX[^0-9].*", d3dx9DLLName, d3dx9FunctionGroup);
            group.TagFunction("^D3DPERF.*", d3dx9DLLName, d3dx9FunctionGroup);
            

            // Add constant from macro definitions
            gen.AddConstantFromMacroToCSharpType("D3D_SDK_VERSION", Global.Name + ".Direct3D9.D3D9", "int");



        }
    }
}
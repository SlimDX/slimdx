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

namespace SlimDX.Generator
{
    internal partial class Program
    {
        public CSharpFunctionGroup D3DCommonFunctionGroup;
        public string D3DCompilerDLLName;


        public unsafe void MapDirect3DCommon()
        {
            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SVC_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SVF_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SVT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SIF_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_SIT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_CT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_NAME_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_INCLUDE_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_RETURN_TYPE_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_OUTPUT_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_DOMAIN_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_PARTITIONING_.*");
            group.Remove<CppEnumItem>(@"^D3D(\d+)_REGISTER_COMPONENT_.*");

            group.TagName<CppEnum>(@"^D3D_PRIMITIVE$", @"InputPrimitive");
            group.TagName<CppEnumItem>(@"^D3D_FEATURE_LEVEL_(.*)", @"Level_$1", true);
            group.TagName<CppEnumItem>(@"^D3D_PRIMITIVE_TOPOLOGY_(\d+)_CONTROL_POINT_PATCHLIST", "PatchListWith$1ControlPoints");
            group.TagName<CppEnumItem>(@"^D3D_PRIMITIVE_(\d+)_CONTROL_POINT_PATCH", "PatchWith$1ControlPoints");

            group.TagName<CppEnumItem>(@"^D3D_SVC_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SVF_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SVT_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SIF_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_SIT_(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D_CT_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3D_NAME$", "ParameterName");
            group.TagName<CppEnum>(@"^D3D_NAME_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3DCOMPILER_STRIP_FLAGS$", "StripFlags");

            group.TagName<CppEnum>(@"^D3D_INCLUDE_TYPE$", "IncludeType");
            group.TagName<CppEnumItem>(@"^D3D_INCLUDE_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_RETURN_TYPE_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_TESSELLATOR_OUTPUT_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_TESSELLATOR_DOMAIN_(.*)", "$1", false);

            group.TagName<CppEnumItem>(@"^D3D_TESSELLATOR_PARTITIONING_(.*)", "$1", false);

            group.TagName<CppEnum>(@"^D3D_REGISTER_COMPONENT_TYPE$", "RegisterComponentType");
            group.TagName<CppEnumItem>(@"^D3D_REGISTER_COMPONENT_(.*)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Interfaces
            // --------------------------------------------------------------------------------------------------------
            // Those interfaces are only used as callback
            group.TagCallback(@"^ID3DInclude$");

            // --------------------------------------------------------------------------------------------------------
            // D3DCommon Interfaces
            // --------------------------------------------------------------------------------------------------------
            D3DCommonFunctionGroup = gen.CreateFunctionGroup(Global.Name, Global.Name + ".Direct3D", "D3DCommon");
            D3DCompilerDLLName = group.FindFirst<CppMacroDefinition>("D3DCOMPILER_DLL_A").StripStringValue;
        }
    }
}
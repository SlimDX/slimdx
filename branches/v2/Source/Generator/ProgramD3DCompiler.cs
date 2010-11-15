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

        public unsafe void MapD3DCompiler()
        {
            gen.MapIncludeToNamespace("d3dcompiler", Global.Name + ".D3DCompiler");

            // Move some D3DCommon types to D3DCompiler
            gen.MapTypeToNamespace("^D3D_PRIMITIVE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_CBUFFER_TYPE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_RESOURCE_RETURN_TYPE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_CBUFFER_FLAGS$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_INPUT_TYPE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_FLAGS$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_CLASS$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_FLAG$S", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_TYPE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_TESSELLATOR_DOMAIN$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_TESSELLATOR_PARTITIONING$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_TESSELLATOR_OUTPUT_PRIMITIVE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_SHADER_INPUT_FLAGS$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_NAME$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_REGISTER_COMPONENT_TYPE$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^ID3DInclude$", Global.Name + ".D3DCompiler");
            gen.MapTypeToNamespace("^D3D_INCLUDE_TYPE$", Global.Name + ".D3DCompiler");

            // Create enums from macros before Global Rename
            group.CreateEnumFromMacros(@"^D3DCOMPILE_[^E][^F].*", "D3DCOMPILE_SHADER_FLAGS");
            group.CreateEnumFromMacros(@"^D3DCOMPILE_EFFECT_.*", "D3DCOMPILE_EFFECT_FLAGS");
            group.CreateEnumFromMacros(@"^D3D_DISASM_.*", "D3DCOMPILE_DISASM_FLAGS");
           
            // Global Rename
            group.TagName<CppEnum>(@"^D3DCOMPILE_(.+)", "$1", false);
            group.TagName<CppEnum>(@"^D3DCOMPILER_(.+)", "$1", false);
            group.TagName<CppStruct>(@"^D3DCOMPILE_(.+)", "$1", false);
            group.TagName<CppStruct>(@"^D3DCOMPILER_(.+)", "$1", false);

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.Remove<CppEnumItem>(@"D3D(\d+)_PRIMITIVE_TOPOLOGY_.*");
            group.Remove<CppEnumItem>(@"D3D(\d+)_PRIMITIVE_.*");
            //group.ModifyAll(".*", Modifiers.RenameType("D3D11_PRIMITIVE_TOPOLOGY", "D3D_PRIMITIVE_TOPOLOGY"));
            //group.ModifyAll(".*", Modifiers.RenameType("D3D10_SHADER_MACRO", "D3D_SHADER_MACRO"));

            group.Remove<CppEnumItem>(@"D3D(\d+)_SRV_DIMENSION_.*");
            group.Remove<CppEnumItem>(@"D3D(\d+_1)_SRV_DIMENSION_.*");

            group.TagName<CppMacroDefinition>(@"^D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS$", "AllowSlowOperations");

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagParameter(@"^ID3D(\d+)ShaderReflectionConstantBuffer::GetDesc::pDesc", CppAttribute.Out);

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppField>(@"^D3D_SHADER_DATA::pBytecode$", "BytecodePtr");

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Functions
            // --------------------------------------------------------------------------------------------------------
            CSharpFunctionGroup d3dFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".D3DCompiler", Global.Name + ".D3DCompiler", "D3D");

            // Map All D3D(Compiler) functions to D3D Function Group
            group.TagFunction(@"^D3D[^1].*", D3DCompilerDLLName, d3dFunctionGroup);
            // Override last Tag to move D3DCreateBlob to D3DCommon
            group.TagFunction(@"^D3DCreateBlob$", D3DCompilerDLLName, D3DCommonFunctionGroup);

            group.TagTypeAndName<CppParameter>(@"^D3DCompile.*?::Flags1$", "D3DCOMPILE_SHADER_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DCompile.*?::Flags2$", "D3DCOMPILE_EFFECT_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DDisassemble::Flags$", "D3DCOMPILE_DISASM_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DStripShader::uStripFlags$", "D3DCOMPILER_STRIP_FLAGS");

            // pDefines is an array of Macro (and not just In)
            group.TagParameter("^D3DCompile::pDefines", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);
            group.TagParameter("^D3DPreprocess::pDefines", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);
        }
    }
}
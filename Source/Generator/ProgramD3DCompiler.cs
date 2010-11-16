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
using SlimDX.XIDL;

namespace SlimDX.Generator
{
    internal partial class Program
    {
        /// <summary>
        /// Map D3DCompiler API
        /// </summary>
        public void MapD3DCompiler()
        {
            // Global namespace for D3DCompiler
            string assemblyName = Global.Name + ".D3DCompiler";
            string namespaceName = assemblyName;

            gen.MapIncludeToNamespace("d3dcompiler", assemblyName, namespaceName);
            gen.MapIncludeToNamespace("d3d11shader", assemblyName, namespaceName);

            // Move some D3DCommon types to D3DCompiler
            group.FindContext.Add("d3dcommon");
            gen.MapTypeToNamespace("^D3D_PRIMITIVE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_CBUFFER_TYPE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_RESOURCE_RETURN_TYPE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_SHADER_CBUFFER_FLAGS$", assemblyName, namespaceName);
            group.Remove<CppEnumItem>(@"^D3D10_CBF_USERPACKED$");
            gen.MapTypeToNamespace("^D3D_SHADER_INPUT_TYPE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_FLAGS$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_CLASS$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_FLAG$S", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_SHADER_VARIABLE_TYPE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_TESSELLATOR_DOMAIN$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_TESSELLATOR_PARTITIONING$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_TESSELLATOR_OUTPUT_PRIMITIVE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_SHADER_INPUT_FLAGS$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_NAME$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_REGISTER_COMPONENT_TYPE$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^ID3DInclude$", assemblyName, namespaceName);
            gen.MapTypeToNamespace("^D3D_INCLUDE_TYPE$", assemblyName, namespaceName);
            group.FindContext.Clear();
            
            // Start working only on d3d11shader
            group.FindContext.Add("d3dcompiler");
            group.FindContext.Add("d3d11shader");

            // Create enums from macros before Global Rename
            group.CreateEnumFromMacros(@"^D3DCOMPILE_[^E][^F].*", "D3DCOMPILE_SHADER_FLAGS");
            group.CreateEnumFromMacros(@"^D3DCOMPILE_EFFECT_.*", "D3DCOMPILE_EFFECT_FLAGS");
            group.CreateEnumFromMacros(@"^D3D_DISASM_.*", "D3DCOMPILE_DISASM_FLAGS");
           
            // Global Rename

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppEnum>(@"^D3D(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D(.*)", "$1", false);
            group.TagName<CppEnum>(@"^D3DCOMPILE_(.+)", "$1", false);
            group.TagName<CppEnum>(@"^D3DCOMPILER_(.+)", "$1", false);


            group.TagName<CppEnum>(@"^D3D11(.*)", "$1", false);
            group.TagName<CppEnumItem>(@"^D3D11(.*)", "$1", false);

            //group.ModifyAll(".*", Modifiers.RenameType("D3D11_PRIMITIVE_TOPOLOGY", "D3D_PRIMITIVE_TOPOLOGY"));
            //group.ModifyAll(".*", Modifiers.RenameType("D3D10_SHADER_MACRO", "D3D_SHADER_MACRO"));

            group.TagName<CppMacroDefinition>(@"^D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS$", "AllowSlowOperations");

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^ID3D(.*)", "$1", false);
            group.TagName<CppInterface>(@"^ID3D11(.*)", "$1", false);
            group.TagParameter(@"^ID3D(\d+)ShaderReflectionConstantBuffer::GetDesc::pDesc", CppAttribute.Out);

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppStruct>(@"^D3D(.*)", "$1", false);
            group.TagName<CppStruct>(@"^D3D11(.*)", "$1", false);
            group.TagName<CppStruct>(@"^D3DCOMPILE_(.+)", "$1", false);
            group.TagName<CppStruct>(@"^D3DCOMPILER_(.+)", "$1", false);
            
            group.TagName<CppField>(@"^D3D_SHADER_DATA::pBytecode$", "BytecodePtr");

            // --------------------------------------------------------------------------------------------------------
            // D3DCompiler Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppFunction>(@"^D3D(.*)", "$1", false);
            CSharpFunctionGroup d3dFunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "D3D");

            string d3dCompilerDllName = group.FindFirst<CppMacroDefinition>("D3DCOMPILER_DLL_A").StripStringValue;

            // Map All D3D(Compiler) functions to D3D Compiler Function Group
            group.TagFunction(@"^D3D[^1].*", d3dCompilerDllName, d3dFunctionGroup);
            // Override last Tag to move D3DCreateBlob to D3DCommon
            group.TagFunction(@"^D3DCreateBlob$", d3dCompilerDllName, D3DCommonFunctionGroup);

            group.TagTypeAndName<CppParameter>(@"^D3DCompile.*?::Flags1$", "D3DCOMPILE_SHADER_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DCompile.*?::Flags2$", "D3DCOMPILE_EFFECT_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DDisassemble::Flags$", "D3DCOMPILE_DISASM_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DStripShader::uStripFlags$", "D3DCOMPILER_STRIP_FLAGS");

            // pDefines is an array of Macro (and not just In)
            group.TagParameter("^D3DCompile::pDefines", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);
            group.TagParameter("^D3DPreprocess::pDefines", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);

            group.FindContext.Clear();
        }
    }
}
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
using System.Linq;
using SlimDX2.Tools.XIDL;

namespace SlimDX2.Tools.XIDLToCSharp
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            CppIncludeGroup group = CppIncludeGroup.Read("directx.xidl");

            group.Modify<CppParameter>("^D3DX11.*?::pDefines",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Buffer |
                                                                    CppAttribute.Optional));

            // Modify device Flags for D3D11CreateDevice to use D3D11_CREATE_DEVICE_FLAG
            group.Modify<CppParameter>("^D3D11CreateDevice.*?::Flags$", Modifiers.Type("D3D11_CREATE_DEVICE_FLAG"));

            // ppFactory on CreateDXGIFactory.* should be Attribute.Out
            group.Modify<CppParameter>("^CreateDXGIFactory.*?::ppFactory$",
                                       Modifiers.ParameterAttribute(CppAttribute.Out));

            // pDefines is an array of Macro (and not just In)
            group.Modify<CppParameter>("^D3DCompile::pDefines",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Buffer |
                                                                    CppAttribute.Optional));
            group.Modify<CppParameter>("^D3DPreprocess::pDefines",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Buffer |
                                                                    CppAttribute.Optional));

            // SwapChain description is mandatory In and not optional
            group.Modify<CppParameter>("^D3D11CreateDeviceAndSwapChain::pSwapChainDesc",
                                       Modifiers.ParameterAttribute(CppAttribute.In));

            // Remove all enums ending with _FORCE_DWORD, FORCE_UINT
            group.Modify<CppEnumItem>("^.*_FORCE_DWORD$", Modifiers.Remove);
            group.Modify<CppEnumItem>("^.*_FORCE_UINT$", Modifiers.Remove);

            // D3DCompiler

            group.Modify<CppParameter>(@"^ID3D(\d+)Device::CreateTexture[0-9]D::pInitialData$",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Buffer |
                                                                    CppAttribute.Optional));

            group.Modify<CppEnumItem>(@"D3D(\d+)_PRIMITIVE_TOPOLOGY_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"D3D(\d+)_PRIMITIVE_.*", Modifiers.Remove);
            group.ModifyAll(".*", Modifiers.RenameType("D3D11_PRIMITIVE_TOPOLOGY", "D3D_PRIMITIVE_TOPOLOGY"));

            group.Modify<CppEnumItem>(@"D3D(\d+)_SRV_DIMENSION_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"D3D(\d+_1)_SRV_DIMENSION_.*", Modifiers.Remove);

            group.TagTypeName<CppField>(@"^D3D_SHADER_DATA::pBytecode$", null, "BytecodePtr");

            group.ModifyAll("^D3D10_CBF_USERPACKED$", Modifiers.Remove);

            group.ModifyAll(@"^D3DX11_ERR$", Modifiers.Remove);

            group.Modify<CppParameter>(@"^D3DCompile.*?::Flags1$", Modifiers.Type("D3DCOMPILE_SHADER_FLAGS"));
            group.Modify<CppParameter>(@"^D3DCompile.*?::Flags2$", Modifiers.Type("D3DCOMPILE_EFFECT_FLAGS"));
            group.Modify<CppParameter>(@"^D3DDisassemble::Flags$", Modifiers.Type("D3DCOMPILE_DISASM_FLAGS"));
            group.Modify<CppParameter>(@"^D3DStripShader::uStripFlags$", Modifiers.Type("D3DCOMPILER_STRIP_FLAGS"));

            // D3DX11/D3DX10
            group.Modify<CppParameter>(@"^D3DX(\d+).*?::Flags1$", Modifiers.Type("D3DCOMPILE_SHADER_FLAGS"));
            group.Modify<CppParameter>(@"^D3DX(\d+).*?::Flags2$", Modifiers.Type("D3DCOMPILE_EFFECT_FLAGS"));

            group.Modify<CppParameter>(@"^D3DX(\d+)ComputeNormalMap::Flags$", Modifiers.Type("D3DX$1_NORMALMAP_FLAG"));
            group.Modify<CppParameter>(@"^D3DX(\d+)ComputeNormalMap::Channel$", Modifiers.Type("D3DX$1_CHANNEL_FLAG"));

            group.Modify<CppFunction>(@"^D3DX(\d+).*A$", Modifiers.Remove);

            // Remove duplicate D3DX function to D3DCompiler
            group.Modify<CppFunction>(@"^D3DX(\d+)Compile.*$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3DX(\d+)PreprocessShader.*$", Modifiers.Remove);

            // Remove all async functions as they would be much more easier to implement in C#
            group.Modify<CppFunction>(@"^D3DX(\d+)CreateAsync.*$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3DX(\d+)CreateThreadPump.*$", Modifiers.Remove);

            //group.Modify<CppField>(@"^D3D(\d+)_BUFFER_DESC::ByteWidth$", Modifiers.Name("SizeInBytes"));

            // Remove Array from RenderTargetView
            group.Modify<CppParameter>(@"^ID3D(\d+)DeviceContext::ClearRenderTargetView::ColorRGBA$",
                                       Modifiers.Type("SHARPDX_COLOR4", "*", false, null));

            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromFileW::ppTexture",
                                       Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromResourceW::ppTexture",
                                       Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromMemory::ppTexture",
                                       Modifiers.ParameterAttribute(CppAttribute.Out));

            group.Modify<CppParameter>(@"^D3DX(\d+)SaveTextureToMemory::ppDestBuf",
                                       Modifiers.ParameterAttribute(CppAttribute.Out));

            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromFileW::pLoadInfo",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Optional));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromResourceW::pLoadInfo",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Optional));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromMemory::pLoadInfo",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Optional));

            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromFileW$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromResourceW$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromMemory$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)SaveTextureToFile$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)SaveTextureToMemory$", Visibility.Internal);

            //group.Modify<CppFunction>(@"^(D3DX(\d+)11.*)W$", Modifiers.Name("$1"));

            // D3DCommon
            group.Modify<CppEnumItem>(@"^D3D(\d+)_SVC_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_SVF_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_SVT_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_SIF_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_SIT_.*", Modifiers.Remove);
            ;
            group.Modify<CppEnumItem>(@"^D3D(\d+)_CT_.*", Modifiers.Remove);

            group.Modify<CppEnumItem>(@"^D3D(\d+)_NAME_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_INCLUDE_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_RETURN_TYPE_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_OUTPUT_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_DOMAIN_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_TESSELLATOR_PARTITIONING_.*", Modifiers.Remove);
            group.Modify<CppEnumItem>(@"^D3D(\d+)_REGISTER_COMPONENT_.*", Modifiers.Remove);

            // DXGI
            group.Modify<CppParameter>(@"^IDXGISwapChain::Present::Flags$", Modifiers.Type("DXGI_PRESENT_FLAGS"));
            group.Modify<CppParameter>(@"^IDXGIFactory::MakeWindowAssociation::Flags$", Modifiers.Type("DXGI_MWA_FLAGS"));

            group.TagTypeName<CppField>(@"^DXGI_SWAP_CHAIN_DESC::Flags$", "DXGI_SWAP_CHAIN_FLAG");

            // Remove DXGI_DISPLAY_COLOR_SPACE type and all typedefs
            group.Modify<CppStruct>("DXGI_DISPLAY_COLOR_SPACE", Modifiers.Remove);

            // --------------------------------------------------------------------------------------------------------
            // D3D(\d+) Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)ClassInstance::GetInstanceName$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)ClassInstance::GetTypeName$", Visibility.Internal);

            // Prepare For Mapping, using tag
            // Hide all Create.* methods in Device
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)Device::Create.*$", Visibility.Internal);
            // Hide GetImmediateContext and force to no property
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)Device::GetImmediateContext$", Visibility.Internal, true);

            // DeviceContext
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetVertexBuffers$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetTargets$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetRenderTargetsAndUnorderedAccessViews$",
                                       Visibility.Internal);

            // Mark all stage SetShader methods internals
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetViewports$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetScissorRects$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::IASetVertexBuffers$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetShader$",
                                       Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetShaderResources$",
                                       Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetSamplers$",
                                       Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetShader$",
                                       Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetConstantBuffers$",
                                       Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetShaderResources$",
                                       Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetSamplers$",
                                       Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetConstantBuffers$",
                                       Visibility.Internal | Visibility.Override);

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::Map$", Visibility.Internal);
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::Unmap$", "UnmapSubresource");
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::UpdateSubresource$", Visibility.Internal);
            group.Modify<CppParameter>(@"^ID3D(\d+)DeviceContext::Map::MapFlags$", Modifiers.Type("D3D$1_MAP_FLAG"));

            group.Modify<CppParameter>(@"^ID3D(\d+)DeviceContext::GetData::GetDataFlags$",
                                       Modifiers.Type("D3D$1_ASYNC_GETDATA_FLAG"));
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::GetData$", Visibility.Internal, null,
                                       "GetDataInternal");

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::FinishCommandList$", Visibility.Internal, null,
                                       "FinishCommandListInternal");

            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::GetResourceMinLOD$", "GetMinimumLod");
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::SetResourceMinLOD$", "SetMinimumLod");

            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::ClearUnorderedAccessViewFloat$",
                                       "ClearUnorderedAccessView");
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::ClearUnorderedAccessViewUint$",
                                       "ClearUnorderedAccessView");

            group.Modify<CppParameter>(@"^ID3D(\d+)DeviceContext::ClearDepthStencilView::ClearFlags$",
                                       Modifiers.Type("D3D11_CLEAR_FLAG"));

            // --------------------------------------------------------------------------------------------------------
            // D3D(\d+) Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagVisibility<CppStruct>(@"^D3D(\d+)_SUBRESOURCE_DATA$", Visibility.Internal);
            group.TagVisibility<CppStruct>(@"^D3D(\d+)_MAPPED_SUBRESOURCE$", Visibility.Internal);

            // Change Some Field type in structs (using existing enums)
            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeName<CppField>(@"^D3D(\d+)_FEATURE_DATA_FORMAT_SUPPORT::OutFormatSupport$", "D3D$1_FORMAT_SUPPORT2");
            group.TagTypeName<CppField>(@"^D3D(\d+)_FEATURE_DATA_FORMAT_SUPPORT2::OutFormatSupport2$", "D3D$1_FORMAT_SUPPORT2");

            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_INFO::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG");

            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::CpuAccessFlags", "D3D$1_CPU_ACCESS_FLAG");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::Filter", "D3DX$1_FILTER_FLAG");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::MipFilter", "D3DX$1_FILTER_FLAG");

            group.TagTypeName<CppField>(@"^D3DX(\d+)_TEXTURE_LOAD_INFO::Filter", "D3DX$1_FILTER_FLAG");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_TEXTURE_LOAD_INFO::MipFilter", "D3DX$1_FILTER_FLAG");

            group.TagTypeName<CppField>(@"^D3D(\d+)_DEPTH_STENCIL_VIEW_DESC::Flags", "D3D$1_DSV_FLAG");

            group.TagTypeName<CppField>(@"^DXGI_SWAP_CHAIN_DESC::Flags", "DXGI_SWAP_CHAIN_FLAG");

            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_DESC::Flags", "D3DCOMPILE_SHADER_FLAGS");

            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_DESC::Version", "D3D$1_SHADER_VERSION_TYPE");

            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_DESC::ByteWidth", null, "SizeInBytes");
            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_DESC::MiscFlags", null, "OptionFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::MiscFlags", null, "OptionFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::MiscFlags", null, "OptionFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::MiscFlags", null, "OptionFlags");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_INFO::MiscFlags", null, "OptionFlags");
            group.TagTypeName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::MiscFlags", null, "OptionFlags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_DESC::MiscFlags", null, "OptionFlags");

            group.TagTypeName<CppField>(@"^D3D(\d+)_SUBRESOURCE_DATA::pSysMem$", null, "DataPointer");
            group.TagTypeName<CppField>(@"^D3D(\d+)_SUBRESOURCE_DATA::SysMemPitch$", null, "Pitch");
            group.TagTypeName<CppField>(@"^D3D(\d+)_SUBRESOURCE_DATA::SysMemSlicePitch$", null, "SlicePitch");

            group.TagTypeName<CppField>(@"^D3D(\d+)_QUERY_DESC::MiscFlags", "D3D$1_QUERY_MISC_FLAG", "QueryFlags");

            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFEREX_SRV::Flags", "D3D$1_BUFFEREX_SRV_FLAG");
            group.TagTypeName<CppField>(@"^D3D(\d+)_BUFFER_UAV::Flags", "D3D$1_BUFFER_UAV_FLAG");

            group.TagTypeName<CppField>(@"^DXGI_ADAPTER_DESC1::Flags", "DXGI_ADAPTER_FLAG");

            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_VARIABLE_DESC::uFlags", "D3D_SHADER_VARIABLE_FLAGS", "Flags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_INPUT_BIND_DESC::uFlags", "D3D_SHADER_INPUT_FLAGS", "Flags");

            // --------------------------------------------------------------------------------------------------------
            // D3D(\d+) Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagEnumFlags(@"^D3D(\d+)_FORMAT_SUPPORT$");
            group.TagEnumFlags(@"^D3D(\d+)_FORMAT_SUPPORT2$");

            CSharpGenerator gen = new CSharpGenerator(group);


            // Create IUnknown object
            var comObject = new CSharpInterface(new CppInterface() {Name = "IUnknown"});
            comObject.Name = Global.Name + ".ComObject";
            comObject.Add(new CSharpMethod(new CppMethod() {Name = "QueryInterface"}));
            comObject.Add(new CSharpMethod(new CppMethod() {Name = "AddRef"}));
            comObject.Add(new CSharpMethod(new CppMethod() {Name = "Release"}));

            // Global object
            gen.MapCppTypeToCSharpType(comObject.CppElement.Name, comObject);

            // Namespace mapping
            gen.MapIncludeToNamespace("dxgi", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("dxgiformat", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("dxgitype", Global.Name + ".DXGI");
            gen.MapIncludeToNamespace("d3dcommon", Global.Name + ".Direct3D", Global.Name);
            gen.MapIncludeToNamespace("d3d11", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11core", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11tex", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11async", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3d11shader", Global.Name + ".D3DCompiler");
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

            //gen.MapTypeToNamespace("^D3DCreateBlob$", Global.Name + ".Direct3D", Global.Name);
            //gen.MapTypeToNamespace("^D3D_SHADER_MACRO$", Global.Name + ".D3DCompiler");

            gen.MapCppTypeToCSharpType("INT", typeof (int));
            gen.MapCppTypeToCSharpType("LONG", typeof (int));
            gen.MapCppTypeToCSharpType("DWORD", typeof (int)); // old uint

            // fort UINT UINT32 to int easier under C#
            gen.MapCppTypeToCSharpType("UINT", typeof (int));
            gen.MapCppTypeToCSharpType("UINT32", typeof (int));

            gen.MapCppTypeToCSharpType("CHAR", typeof (byte));
            gen.MapCppTypeToCSharpType("BYTE", typeof (byte));
            gen.MapCppTypeToCSharpType("LPCSTR", typeof (string));
            gen.MapCppTypeToCSharpType("LPSTR", typeof (string));
            gen.MapCppTypeToCSharpType("FLOAT", typeof (float));
            gen.MapCppTypeToCSharpType("BOOL", typeof (bool));
            gen.MapCppTypeToCSharpType("UINT8", typeof (byte));
            gen.MapCppTypeToCSharpType("UINT64", typeof (long));
            gen.MapCppTypeToCSharpType("LARGE_INTEGER", typeof (ulong));
            gen.MapCppTypeToCSharpType("SIZE_T", typeof (IntPtr));
            gen.MapCppTypeToCSharpType("HANDLE", typeof (IntPtr));
            gen.MapCppTypeToCSharpType("HMODULE", typeof (IntPtr));
            gen.MapCppTypeToCSharpType("HMONITOR", typeof (IntPtr));
            gen.MapCppTypeToCSharpType("HWND", typeof (IntPtr));
            gen.MapCppTypeToCSharpType("REFIID", typeof (Guid), true);
            gen.MapCppTypeToCSharpType("REFGUID", typeof (Guid), true);
            gen.MapCppTypeToCSharpType("LUID", typeof (long));
            gen.MapCppTypeToCSharpType("WCHAR", typeof (char));
            var rectType = new CSharpStruct();
            rectType.Name = Global.Name + ".Rectangle";
            rectType.SizeOf = 4*4;
            gen.MapCppTypeToCSharpType("RECT", rectType); //Global.Name + ".Rectangle", 4 * 4, false, true);
            var color4Type = new CSharpStruct();
            color4Type.Name = "SlimMath.Color4";
            color4Type.SizeOf = 4*4;
            gen.MapCppTypeToCSharpType("SHARPDX_COLOR4", color4Type); // Global.Name + ".Color4"
            gen.MapCppTypeToCSharpType("HRESULT", typeof (int));

            // General 
            //gen.RemoveType(@"^.*_FORCE_DWORD$");      // Remove all enums ending with _FORCE_DWORD, FORCE_UINT
            //gen.RemoveType(@"^.*_FORCE_UINT$");      

            // DXGI
            gen.KeepUnderscoreForType(@"^DXGI_FORMAT_.*");

            gen.RenameType(@"^IDXGIObject$", "DXGIObject", true);

            gen.RenameType(@"^DXGI_MODE_ROTATION$", "DisplayModeRotation");
            gen.RenameType(@"^DXGI_MODE_SCALING$", "DisplayModeScaling");
            gen.RenameType(@"^DXGI_MODE_SCANLINE_ORDER$", "DisplayModeScanlineOrder");

            // ReCreate enums from macro definitions
            gen.CreateEnumFromMacros(@"^DXGI_PRESENT_.*", "DXGI_PRESENT_FLAGS");
            gen.CreateEnumFromMacros(@"^DXGI_USAGE_.*", "DXGI_USAGE");
            gen.CreateEnumFromMacros(@"^DXGI_RESOURCE_.*", "DXGI_RESOURCE_PRIORITY");
            gen.CreateEnumFromMacros(@"^DXGI_MAP_.*", "DXGI_MAP_FLAGS");
            gen.CreateEnumFromMacros(@"^DXGI_ENUM_MODES_.*", "DXGI_ENUM_MODES_FLAGS");
            gen.CreateEnumFromMacros(@"^DXGI_MWA_.*", "DXGI_MWA_FLAGS");

            gen.RenameType("^DXGI_ERROR$", "DXGIError", true, TypeContext.Root);
            gen.RenameType("^DXGI_STATUS$", "DXGIStatus", true, TypeContext.Root);

            gen.CreateEnumFromMacros(@"^DXGI_ERROR_.*", "DXGI_ERROR");
            gen.CreateEnumFromMacros(@"^DXGI_STATUS_.*", "DXGI_STATUS");

            gen.RenameType(@"^DXGI_ENUM_MODES_FLAGS$", "DisplayModeEnumerationFlags");
            gen.RenameType(@"^DXGI_MWA_FLAGS$", "WindowAssociationFlags");
            gen.RenameType(@"^DXGI_MWA_NO_WINDOW_CHANGES$", "IgnoreAll");
            gen.RenameType(@"^DXGI_MWA_NO_ALT_ENTER$", "IgnoreAltEnter");
            gen.RenameType(@"^DXGI_MWA_NO_PRINT_SCREEN$", "IgnorePrintScreen");

            // D3DCompiler
            gen.CreateEnumFromMacros(@"^D3DCOMPILE_[^E][^F].*", "D3DCOMPILE_SHADER_FLAGS");
            gen.CreateEnumFromMacros(@"^D3DCOMPILE_EFFECT_.*", "D3DCOMPILE_EFFECT_FLAGS");
            gen.CreateEnumFromMacros(@"^D3D_DISASM_.*", "D3DCOMPILE_DISASM_FLAGS");

            gen.RenameType(@"^D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS$", "AllowSlowOperations");
            gen.RenameType(@"^D3D11_SHADER_BUFFER_DESC$", "ConstantBufferDescription");


            // D3D10/D3D11
            //gen.AddNoteEnumItem("D3D11_FORMAT_SUPPORT2");
            gen.AddNoteEnumItem("D3D11_COLOR_WRITE_ENABLE");

            gen.RenameType(@"^D3D(\d+)_CREATE_DEVICE_FLAG$", "DeviceCreationFlags");
            gen.RenameType(@"^D3D(\d+)_CREATE_DEVICE_(.*)$", "$2");

            gen.RenameType(@"^D3D(\d+)_QUERY_MISC_FLAG$", "QueryFlags");
            gen.RenameType(@"^D3D(\d+)_QUERY$", "QueryType");
            gen.RenameType(@"^D3D(\d+)_COUNTER$", "CounterKind");
            gen.RenameType(@"^D3D(\d+)_BLEND$", "BlendOption");
            gen.RenameType(@"^D3D(\d+)_ASYNC_GETDATA_FLAG$", "AsynchronousFlags");
            gen.RenameType(@"^D3D(\d+)_ASYNC_GETDATA_DONOTFLUSH$", "DoNotFlush");

            gen.RenameType(@"^D3D(\d+)_BLEND_DESC$", "BlendStateDescription");
            gen.RenameType(@"^D3D(\d+)_DEPTH_STENCIL_DESC$", "DepthStencilStateDescription");
            gen.RenameType(@"^D3D(\d+)_RASTERIZER_DESC$", "RasterizerStateDescription");
            gen.RenameType(@"^D3D(\d+)_SAMPLER_DESC$", "SamplerStateDescription");

            gen.RenameType(@"^D3D(\d+)_QUERY_DATA_SO_STATISTICS$", "StreamOutputStatistics");
            gen.RenameType(@"^D3D(\d+)_SO_DECLARATION_ENTRY$", "StreamOutputElement");
            gen.RenameType(@"^D3D(\d+)_INPUT_ELEMENT_DESC", "InputElement");

            gen.RenameType(@"^D3D(\d+)_MAP$", "MapMode");

            gen.RenameType(@"^D3D11_FORMAT_SUPPORT2$", "ComputeShaderFormatSupport");
            gen.RenameType(@"^D3D11_FORMAT_SUPPORT2_UAV_(.*)$", "$1");

            gen.RenameType(@"^D3D(\d+)_BIND_FLAG$", "BindFlags");
            gen.RenameType(@"^D3D(\d+)_BIND_(.*)", "$2");

            gen.RenameType(@"^D3D(\d+)_MAP$", "MapMode");
            gen.RenameType(@"^D3D(\d+)_MAP_FLAG$", "MapFlags");

            gen.RenameType(@"^D3D(\d+)_MAP_FLAG_(.*)", "$2");
            gen.RenameType(@"^D3D(\d+)_MAP_(.*)", "$2");

            gen.RenameType(@"^D3D(\d+)_BUFFER_UAV_FLAG$", "UnorderedAccessViewBufferFlags");
            gen.RenameType(@"^D3D(\d+)_BUFFER_UAV_FLAG_(.*)$", "$2");

            gen.RenameType(@"^D3D(\d+)_COLOR_WRITE_ENABLE$", "ColorWriteMaskFlags");
            gen.RenameType(@"^D3D(\d+)_COLOR_WRITE_ENABLE_(.*)$", "$2");

            gen.RenameType(@"^D3D(\d+)_CPU_ACCESS_FLAG$", "CpuAccessFlags");
            gen.RenameType(@"^D3D(\d+)_CPU_ACCESS_(.*)$", "$2");

            gen.RenameType(@"^D3D(\d+)_USAGE$", "ResourceUsage");
            gen.RenameType(@"^D3D(\d+)_USAGE_(.*)$", "$2");

            gen.RenameType(@"^D3D(\d+)_RESOURCE_MISC_FLAG$", "ResourceOptionFlags");
            gen.RenameType(@"^D3D(\d+)_RESOURCE_MISC_(.*)", "$2");

            gen.RenameType(@"^D3D(\d+)_CLEAR_FLAG", "DepthStencilClearFlags");
            gen.RenameType(@"^D3D(\d+)_CLEAR_(.*)", "$2");

            gen.RenameType(@"^D3D(\d+)_DSV_FLAG$", "DepthStencilViewFlags");
            gen.RenameType(@"^D3D(\d+)_DSV_(.*)", "$2");

            gen.RenameType(@"^D3D11_FEATURE_FORMAT_SUPPORT2$", "ComputeShaders");
            gen.RenameType(@"^D3D11_FEATURE_DOUBLES$", "ShaderDoubles");

            gen.RenameType(@"^D3D(\d+)_BOX$", "ResourceRegion");

            // Move structure inner type (SRV,RTV,DSV,UAV)
            gen.RenameType(@"^D3D11_(.*)_SRV$", "$1_Resource");
            gen.MoveStructToInner(@"^D3D11_(.*)_SRV$", "D3D11_SHADER_RESOURCE_VIEW_DESC");

            gen.RenameType(@"^D3D11_(.*)_RTV$", "$1_Resource");
            gen.MoveStructToInner(@"^D3D11_(.*)_RTV$", "D3D11_RENDER_TARGET_VIEW_DESC");

            gen.RenameType(@"^D3D11_(.*)_DSV$", "$1_Resource");
            gen.MoveStructToInner(@"^D3D11_(.*)_DSV$", "D3D11_DEPTH_STENCIL_VIEW_DESC");

            gen.RenameType(@"^D3D11_(.*)_UAV$", "$1_Resource");
            gen.MoveStructToInner(@"^D3D11_(.*)_UAV$", "D3D11_UNORDERED_ACCESS_VIEW_DESC");

            // D3DX10/D3DX11
            gen.RenameType(@"^D3DX(\d+)_CHANNEL_FLAG$", "ChannelFlags");
            gen.RenameType(@"^D3DX(\d+)_CHANNEL_(.*)$", "$2");

            gen.RenameType(@"^D3DX(\d+)_FILTER_FLAG$", "FilterFlags");
            gen.RenameType(@"^D3DX(\d+)_FILTER_(.*)$", "$2");

            gen.RenameType(@"^D3DX(\d+)_IFF_(.*)$", "$2");

            gen.RenameType(@"^D3DX(\d+)_NORMALMAP_FLAG$", "NormalMapFlags");
            gen.RenameType(@"^D3DX(\d+)_NORMALMAP_(.*)", "$2");

            gen.RenameType(@"^D3DX(\d+)_SAVE_TEXTURE_FLAG$", "SaveTextureFlags");
            gen.RenameType(@"^D3DX(\d+)_STF_USEINPUTBLOB$", "UseInputBlob");
            gen.RenameType(@"^D3DX(\d+)_STF_(.*)", "$2");

            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::IA(.*)", "InputAssemblerStage", "InputAssembler", "$1");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::VS(.*)", "VertexShaderStage", "VertexShader", "$1",
                                            "CommonShaderStage<VertexShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::PS(.*)", "PixelShaderStage", "PixelShader", "$1",
                                            "CommonShaderStage<PixelShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::GS(.*)", "GeometryShaderStage", "GeometryShader", "$1",
                                            "CommonShaderStage<GeometryShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::SO(.*)", "StreamOutputStage", "StreamOutput", "$1");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::DS(.*)", "DomainShaderStage", "DomainShader", "$1",
                                            "CommonShaderStage<DomainShader>");
            ;
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::HS(.*)", "HullShaderStage", "HullShader", "$1",
                                            "CommonShaderStage<HullShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::RS(.*)", "RasterizerStage", "Rasterizer", "$1");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::OM(.*)", "OutputMergerStage", "OutputMerger", "$1");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::CS(.*)", "ComputeShaderStage", "ComputeShader", "$1",
                                            "CommonShaderStage<ComputeShader>");

            //            gen.RenameType(@"D3D(\d++)_COMPARISON_FUNC", "Comparison");

            gen.RenameType(@"^D3DX\d+(.*)W", "$1");

            // d3dcommon
            gen.RenameType(@"^D3D_PRIMITIVE$", @"InputPrimitive");
            gen.RenameType(@"^D3D_FEATURE_LEVEL_(.*)", @"Level_$1", true);
            gen.RenameType(@"^D3D_PRIMITIVE_TOPOLOGY_(\d+)_CONTROL_POINT_PATCHLIST", "PatchListWith$1ControlPoints");
            gen.RenameType(@"^D3D_PRIMITIVE_(\d+)_CONTROL_POINT_PATCH", "PatchWith$1ControlPoints");

            gen.RenameType(@"^D3D_SVC_(.*)", "$1");
            gen.RenameType(@"^D3D_SVF_(.*)", "$1");
            gen.RenameType(@"^D3D_SVT_(.*)", "$1");
            gen.RenameType(@"^D3D_SIF_(.*)", "$1");
            gen.RenameType(@"^D3D_SIT_(.*)", "$1");
            gen.RenameType(@"^D3D_CT_(.*)", "$1");

            //gen.RemoveType(@"^D3D_NAME$");
            gen.RenameType(@"^D3D_NAME$", "ParameterName");
            gen.RenameType(@"^D3D_NAME_(.*)", "$1");

            gen.RenameType(@"^D3DCOMPILER_STRIP_FLAGS$", "StripFlags");

            gen.RenameType(@"^D3D_INCLUDE_TYPE$", "IncludeType");
            gen.RenameType(@"^D3D_INCLUDE_(.*)", "$1");

            gen.RenameType(@"^D3D_RETURN_TYPE_(.*)", "$1");


            gen.RenameType(@"^D3D_TESSELLATOR_OUTPUT_(.*)", "$1");

            gen.RenameType(@"^D3D_TESSELLATOR_DOMAIN_(.*)", "$1");

            gen.RenameType(@"^D3D_TESSELLATOR_PARTITIONING_(.*)", "$1");

            gen.RenameType(@"^D3D_REGISTER_COMPONENT_TYPE$", "RegisterComponentType");
            gen.RenameType(@"^D3D_REGISTER_COMPONENT_(.*)", "$1");

            gen.ChangeMethodParamAttribute("ID3D11ShaderReflectionConstantBuffer::GetDesc::pDesc", CppAttribute.Out);

            // Global

            gen.RenameType(@"^IDXGI(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^DXGI(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3D11(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3D11(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3DX11(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3DX11(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3D10(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3D10(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3DX10(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3DX10(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3DCOMPILE(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3D(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3D(.+)", "$1", false, TypeContext.Root);

            // Rename all types (interface, methods..) that are ending with Desc, Desc1
            gen.RenameType(@"^(.*)Desc$", "$1Description");
            gen.RenameType(@"^(.*)Desc1$", "$1Description1");
            gen.RenameType(@"^GetType$", "GetTypeInfo", true);

            // Global Prefix Rename
            gen.RenameTypePart("^DXGI", "");
            gen.RenameTypePart("^D3D10", "");
            gen.RenameTypePart("^D3D11", "");
            gen.RenameTypePart("^D3DX11", "");
            gen.RenameTypePart("^D3DCOMPILE", "");
            gen.RenameTypePart("^D3D", "");

            // For DXGI Format
            gen.RenameTypePart(@"^(R(\d).*)", "$1");
            gen.RenameTypePart(@"^(B(\d).*)", "$1");
            gen.RenameTypePart(@"^(G(\d).*)", "$1");
            gen.RenameTypePart(@"^(A(\d).*)", "$1");
            gen.RenameTypePart(@"^(X(\d).*)", "$1");
            gen.RenameTypePart(@"^(BC(\d).*)", "$1");
            //gen.RenameTypePart(@"^(\d+)$", "_$1");

            // Expand sub part between underscore
            gen.RenameTypePart("^DESC$", "Description");
            gen.RenameTypePart("^CBUFFER$", "ConstantBuffer");
            gen.RenameTypePart("^TBUFFER$", "TextureBuffer");
            gen.RenameTypePart("^BUFFEREX$", "ExtendedBuffer");
            gen.RenameTypePart("^FUNC$", "Function");
            gen.RenameTypePart("^FLAG$", "Flags");
            gen.RenameTypePart("^SRV$", "ShaderResourceView");
            gen.RenameTypePart("^DSV$", "DepthStencilView");
            gen.RenameTypePart("^RTV$", "RenderTargetView");
            gen.RenameTypePart("^UAV$", "UnorderedAccessView");
            gen.RenameTypePart("^TEXTURE1D$", "Texture1D");
            gen.RenameTypePart("^TEXTURE2D$", "Texture2D");
            gen.RenameTypePart("^TEXTURE3D$", "Texture3D");
            gen.RenameTypePart("^TEX1D$", "Texture1D");
            gen.RenameTypePart("^TEX2D$", "Texture2D");
            gen.RenameTypePart("^TEX3D$", "Texture3D");
            gen.RenameTypePart("^TEXCUBE$", "TextureCube");
            gen.RenameTypePart("^TEX2DMS$", "Texture2DMultisampled");
            gen.RenameTypePart("^RWTEXTURE1D$", "RWTexture1D");
            gen.RenameTypePart("^RWTEXTURE2D$", "RWTexture2D");
            gen.RenameTypePart("^RWTEXTURE3D$", "RWTexture3D");
            gen.RenameTypePart("^RWTEXTURE1DARRAY$", "RWTexture1DArray");
            gen.RenameTypePart("^RWTEXTURE2DARRAY$", "RWTexture2DArray");
            gen.RenameTypePart("^TEXTURE1DARRAY$", "Texture1DArray");
            gen.RenameTypePart("^TEXTURE2DARRAY$", "Texture2DArray");
            gen.RenameTypePart("^TEXTURE3DARRAY$", "Texture3DArray");
            gen.RenameTypePart("^TEXTURE2DMS$", "Texture2DMultisampled");
            gen.RenameTypePart("^TEXTURE2DMSARRAY$", "Texture2DMultisampledArray");
            gen.RenameTypePart("^RWBUFFER$", "RWBuffer");
            gen.RenameTypePart("^RWBYTEADDRESS$", "RWByteAddress");
            gen.RenameTypePart("^UINT8$", "UInt8");
            gen.RenameTypePart("^UINT$", "UInt");
            gen.RenameTypePart("^SINT$", "SInt");
            gen.RenameTypePart("^UNORM$", "UNorm");
            gen.RenameTypePart("^SNORM$", "SNorm");
            gen.RenameTypePart("^SRGB$", "SRgb");
            gen.RenameTypePart("^ADJ$", "WithAdjency");
            gen.RenameTypePart("^IA$", "InputAssembly");
            gen.RenameTypePart("^SO$", "StreamOutput");
            gen.RenameTypePart("^OP$", "Operation");
            gen.RenameTypePart("^INV$", "Inverse");
            gen.RenameTypePart("^SRC$", "Source");
            gen.RenameTypePart("^SRC1$", "SecondarySource");
            gen.RenameTypePart("^SAT$", "Saturate");
            gen.RenameTypePart("^DEST$", "Destination");
            gen.RenameTypePart("^REV$", "Reverse");
            gen.RenameTypePart("^MAX$", "Maximum");
            gen.RenameTypePart("^MIN$", "Minimum");
            gen.RenameTypePart("^INCR$", "Increment");
            gen.RenameTypePart("^DECR$", "Decrement");
            gen.RenameTypePart("^SRGB$", "StandardRgb");
            gen.RenameTypePart("^STENCILOP$", "StencilOperation");
            gen.RenameTypePart("^SUBRESOURCE$", "SubResource");
            gen.RenameTypePart("^CBF$", "ConstantBuffer");
            gen.RenameTypePart("^INFO$", "Information");
            gen.RenameTypePart("^DESC1$", "Description1");
            gen.RenameTypePart("^DISASM$", "Disassembly");

            gen.MapCppTypeToCSharpType("DXGI_RGB", "SlimMath.Color3", 3*4, false, true);

            // Those interfaces are only used as callback
            gen.MakeCallbackInterface("ID3DInclude");
            gen.MakeCallbackInterface("ID3DX11DataLoader");
            gen.MakeCallbackInterface("ID3DX11DataProcessor");

            // Function group
            var d3dCommonFunctionGroup = gen.CreateFunctionGroup(Global.Name, Global.Name + ".Direct3D", "D3DCommon");
            var dxgiFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".DXGI", Global.Name + ".DXGI", "DXGI");
            var d3dFunctionGroup = gen.CreateFunctionGroup(Global.Name + ".D3DCompiler", Global.Name + ".D3DCompiler",
                                                           "D3D");
            var d3d11FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D11", Global.Name + ".Direct3D11",
                                                             "D3D11");
            var d3dx11FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D11", Global.Name + ".Direct3D11",
                                                              "D3DX11");

            // Mark visibility to internal assembly
            d3dCommonFunctionGroup.Visibility = Visibility.PublicProtected;
            dxgiFunctionGroup.Visibility = Visibility.PublicProtected;
            d3dFunctionGroup.Visibility = Visibility.PublicProtected;
            d3d11FunctionGroup.Visibility = Visibility.PublicProtected;
            d3dx11FunctionGroup.Visibility = Visibility.PublicProtected;

            // Map All DXGI functions to DXGI Function Group
            gen.MapFunctionToFunctionGroup("^CreateDXGIFactory.*", "dxgi.dll", dxgiFunctionGroup);

            // Map All D3D11 functions to D3D11 Function Group
            gen.MapFunctionToFunctionGroup(@"^D3D11.*", "d3d11.dll", d3d11FunctionGroup);

            // Map All D3DX11 functions to D3DX11 Function Group
            gen.MapFunctionToFunctionGroup(@"^D3DX11.*",
                                           group.Find<CppMacroDefinition>("D3DX11_DLL_A").FirstOrDefault().
                                               StripStringValue, d3dx11FunctionGroup);

            // Map All D3D11 functions to D3D11 Function Group
            string d3dCompilerDll =
                group.Find<CppMacroDefinition>("D3DCOMPILER_DLL_A").FirstOrDefault().StripStringValue;
            gen.MapFunctionToFunctionGroup(@"^D3DCreateBlob$", d3dCompilerDll, d3dCommonFunctionGroup);

            // Map All D3D(Compiler) functions to D3D Function Group
            gen.MapFunctionToFunctionGroup(@"^D3D.*", d3dCompilerDll, d3dFunctionGroup);


            gen.MapCppTypeToCppType("D3D10_SHADER_MACRO", "D3D_SHADER_MACRO");

            // Change method parameters (Flags parameter for D3D11CreateDevice.* should be D3D11_CREATE_DEVICE_FLAG)
            //gen.ChangeMethodParamTypeToCppType("D3D11CreateDevice.*::Flags", "D3D11_CREATE_DEVICE_FLAG");
            //gen.ChangeMethodParamAttribute("CreateDXGIFactory.*::ppFactory", CppAttribute.Out);


            //gen.ChangeMethodParamAttribute("D3DCompile::pDefines", CppAttribute.In|CppAttribute.Buffer|CppAttribute.Optional);
            //gen.ChangeMethodParamAttribute("D3DPreprocess::pDefines", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);
            //gen.ChangeMethodParamAttribute("D3D11CreateDeviceAndSwapChain::pSwapChainDesc", CppAttribute.In);

            // Add constant from macro definitions
            gen.AddConstantFromMacroToCSharpType("D3D11_SDK_VERSION", Global.Name + ".Direct3D11.D3D11", "int");

            gen.GeneratedPath = @"..\..\..\Sources\";

            gen.Generate();
        }
    }
}
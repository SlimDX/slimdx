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

        private string[] d3d10Includes = new string[] {"d3d10", 
                                                       "d3d10_1",
                                                       "d3d10_1shader",
                                                       "d3d10effect",
                                                       "d3d10misc", 
                                                       "d3d10sdklayers",
                                                       "d3d10shader",
                                                       "d3dx10", 
                                                       "d3dx10core", 
                                                       "d3dx10tex", 
                                                       "d3dx10async"};

        private string[] d3d11Includes = new string[]
                                             {
                                                 "d3d11",
                                                 "d3dx11",
                                                 "d3dx11core",
                                                 "d3dx11tex",
                                                 "d3dx11async"
                                             };
        
        
        /// <summary>
        /// Maps the Direct3D10 and Direct3D11 API
        /// </summary>
        public void MapDirect3D10AndDirect3D11()
        {
            // The following part is not common to Direct3D10 and Direct3D11
            group.FindContext.AddRange(d3d10Includes);
            group.FindContext.AddRange(d3d11Includes);

            // Global Rename
            group.TagName<CppEnum>(@"^D3D(\d+)(.*)", "$2", false);
            group.TagName<CppEnum>(@"^D3DX(\d+)(.*)", "$2", false);
            group.TagName<CppStruct>(@"^D3D(\d+)(.*)", "$2", false);
            group.TagName<CppStruct>(@"^D3DX(\d+)(.*)", "$2", false);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagEnumFlags(@"^D3D(\d+)_FORMAT_SUPPORT$");
            group.TagEnumFlags(@"^D3D(\d+)_FORMAT_SUPPORT2$");

            // Add None = 0 for enum D3D11_COLOR_WRITE_ENABLE
            foreach (var enumToAdd in group.Find<CppEnum>(@"^D3D(\d+)_COLOR_WRITE_ENABLE$")) 
                enumToAdd.Add(new CppEnumItem() { Name = "None", Value = "0"});
            group.TagEnumFlags(@"^D3D(\d+)_COLOR_WRITE_ENABLE$");

            // D3D10/D3D11
            group.TagName<CppEnum>(@"^D3D(\d+)_CREATE_DEVICE_FLAG$", "DeviceCreationFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_CREATE_DEVICE_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_QUERY_MISC_FLAG$", "QueryFlags");
            group.TagName<CppEnum>(@"^D3D(\d+)_QUERY$", "QueryType");
            group.TagName<CppEnum>(@"^D3D(\d+)_COUNTER$", "CounterKind");
            group.TagName<CppEnum>(@"^D3D(\d+)_BLEND$", "BlendOption");
            group.TagName<CppEnum>(@"^D3D(\d+)_ASYNC_GETDATA_FLAG$", "AsynchronousFlags");
            group.TagName<CppEnum>(@"^D3D(\d+)_ASYNC_GETDATA_DONOTFLUSH$", "DoNotFlush");

            group.TagName<CppEnum>(@"^D3D(\d+)_MAP$", "MapMode");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_MAP_FLAG$", "MapFlags");

            group.TagName<CppEnum>(@"^D3D(\d+)_BIND_FLAG$", "BindFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_BIND_(.*)", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_MAP_FLAG_(.*)", "$2", false);
            group.TagName<CppEnumItem>(@"^D3D(\d+)_MAP_(.*)", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_BUFFER_UAV_FLAG$", "UnorderedAccessViewBufferFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_BUFFER_UAV_FLAG_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_COLOR_WRITE_ENABLE$", "ColorWriteMaskFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_COLOR_WRITE_ENABLE_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_CPU_ACCESS_FLAG$", "CpuAccessFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_CPU_ACCESS_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_USAGE$", "ResourceUsage");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_USAGE_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_RESOURCE_MISC_FLAG$", "ResourceOptionFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_RESOURCE_MISC_(.*)", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_CLEAR_FLAG$", "DepthStencilClearFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_CLEAR_(.*)", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_DSV_FLAG$", "DepthStencilViewFlags");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_DSV_(.*)", "$2", false);

            // D3DX10/D3DX11
            group.TagName<CppEnum>(@"^D3DX(\d+)_CHANNEL_FLAG$", "ChannelFlags");
            group.TagName<CppEnumItem>(@"^D3DX(\d+)_CHANNEL_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3DX(\d+)_FILTER_FLAG$", "FilterFlags");
            group.TagName<CppEnumItem>(@"^D3DX(\d+)_FILTER_(.*)$", "$2", false);
            group.TagName<CppEnumItem>(@"^D3DX(\d+)_IFF_(.*)$", "$2", false);

            group.TagName<CppEnum>(@"^D3DX(\d+)_NORMALMAP_FLAG$", "NormalMapFlags");
            group.TagName<CppEnumItem>(@"^D3DX(\d+)_NORMALMAP_(.*)", "$2", false);

            group.TagName<CppEnum>(@"^D3DX(\d+)_SAVE_TEXTURE_FLAG$", "SaveTextureFlags");
            group.TagName<CppEnum>(@"^D3DX(\d+)_STF_USEINPUTBLOB$", "UseInputBlob");
            group.TagName<CppEnumItem>(@"^D3DX(\d+)_STF_(.*)", "$2", false);

            group.TagName<CppEnum>(@"^D3D(\d+)_SHADER_DEBUG_REGTYPE$", "ShaderDebugRegisterType");
            group.TagName<CppEnumItem>(@"^D3D(\d+)_SHADER_DEBUG_REG_(.+)$", "$2", false);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppStruct>(@"^D3D(\d+)_BOX$", "ResourceRegion");

            group.TagName<CppStruct>(@"^D3D(\d+)_BLEND_DESC$", "BlendStateDescription");
            group.TagName<CppStruct>(@"^D3D(\d+)_DEPTH_STENCIL_DESC$", "DepthStencilStateDescription");
            group.TagName<CppStruct>(@"^D3D(\d+)_RASTERIZER_DESC$", "RasterizerStateDescription");
            group.TagName<CppStruct>(@"^D3D(\d+)_SAMPLER_DESC$", "SamplerStateDescription");

            group.TagName<CppStruct>(@"^D3D(\d+)_QUERY_DATA_SO_STATISTICS$", "StreamOutputStatistics");
            group.TagName<CppStruct>(@"^D3D(\d+)_SO_DECLARATION_ENTRY$", "StreamOutputElement");
            group.TagName<CppStruct>(@"^D3D(\d+)_INPUT_ELEMENT_DESC", "InputElement");

            group.TagVisibility<CppStruct>(@"^D3D(\d+)_SUBRESOURCE_DATA$", Visibility.Internal);
            group.TagVisibility<CppStruct>(@"^D3D(\d+)_MAPPED_SUBRESOURCE$", Visibility.Internal);

            // Move structure inner type (SRV,RTV,DSV,UAV)
            group.TagName<CppStruct>(@"^D3D(\d+)_(.*)_SRV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_SRV$", "D3D$1_SHADER_RESOURCE_VIEW_DESC");

            group.TagName<CppStruct>(@"^D3D(\d+)_(.*)_SRV1$", "$2_Resource1");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_SRV1$", "D3D$1_SHADER_RESOURCE_VIEW_DESC1");

            group.TagName<CppStruct>(@"^D3D(\d+)_(.*)_RTV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_RTV$", "D3D$1_RENDER_TARGET_VIEW_DESC");

            group.TagName<CppStruct>(@"^D3D(\d+)_(.*)_DSV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_DSV$", "D3D$1_DEPTH_STENCIL_VIEW_DESC");

            group.TagName<CppStruct>(@"^D3D(\d+)_(.*)_UAV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_UAV$", "D3D$1_UNORDERED_ACCESS_VIEW_DESC");

            group.TagName<CppStruct>(@"^D3D(\d+)_PASS_DESC$", "EffectPassDescription");
            group.TagName<CppStruct>(@"^D3D(\d+)_PASS_SHADER_DESC$", "EffectPassShaderDescription");
            group.TagName<CppStruct>(@"^D3D(\d+)_TECHNIQUE_DESC$", "EffectTechniqueDescription");

            // Change Some Field type in structs (using existing enums)
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_BUFFER_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_BUFFER_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_BUFFER_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::CPUAccessFlags", "D3D$1_CPU_ACCESS_FLAG", "CpuAccessFlags");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG", "OptionFlags");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_FEATURE_DATA_FORMAT_SUPPORT::OutFormatSupport$", "D3D$1_FORMAT_SUPPORT2");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_FEATURE_DATA_FORMAT_SUPPORT2::OutFormatSupport2$", "D3D$1_FORMAT_SUPPORT2");

            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_IMAGE_INFO::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG");

            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::BindFlags", "D3D$1_BIND_FLAG");
            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::CpuAccessFlags", "D3D$1_CPU_ACCESS_FLAG");
            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::MiscFlags", "D3D$1_RESOURCE_MISC_FLAG");
            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::Filter", "D3DX$1_FILTER_FLAG");
            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::MipFilter", "D3DX$1_FILTER_FLAG");

            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_TEXTURE_LOAD_INFO::Filter", "D3DX$1_FILTER_FLAG");
            group.TagTypeAndName<CppField>(@"^D3DX(\d+)_TEXTURE_LOAD_INFO::MipFilter", "D3DX$1_FILTER_FLAG");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_DEPTH_STENCIL_VIEW_DESC::Flags", "D3D$1_DSV_FLAG");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_SHADER_DESC::Flags", "D3DCOMPILE_SHADER_FLAGS");

            group.TagName<CppField>(@"^D3D(\d+)_BUFFER_DESC::ByteWidth", "SizeInBytes");
            group.TagName<CppField>(@"^D3D(\d+)_BUFFER_DESC::MiscFlags", "OptionFlags");
            group.TagName<CppField>(@"^D3D(\d+)_TEXTURE1D_DESC::MiscFlags", "OptionFlags");
            group.TagName<CppField>(@"^D3D(\d+)_TEXTURE2D_DESC::MiscFlags", "OptionFlags");
            group.TagName<CppField>(@"^D3D(\d+)_TEXTURE3D_DESC::MiscFlags", "OptionFlags");
            group.TagName<CppField>(@"^D3DX(\d+)_IMAGE_INFO::MiscFlags", "OptionFlags");
            group.TagName<CppField>(@"^D3DX(\d+)_IMAGE_LOAD_INFO::MiscFlags", "OptionFlags");
            group.TagName<CppField>(@"^D3D(\d+)_BUFFER_DESC::MiscFlags", "OptionFlags");

            group.TagName<CppField>(@"^D3D(\d+)_SUBRESOURCE_DATA::pSysMem$", "DataPointer");
            group.TagName<CppField>(@"^D3D(\d+)_SUBRESOURCE_DATA::SysMemPitch$", "Pitch");
            group.TagName<CppField>(@"^D3D(\d+)_SUBRESOURCE_DATA::SysMemSlicePitch$", "SlicePitch");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_QUERY_DESC::MiscFlags", "D3D$1_QUERY_MISC_FLAG", "QueryFlags");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_BUFFEREX_SRV::Flags", "D3D$1_BUFFEREX_SRV_FLAG");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_BUFFER_UAV::Flags", "D3D$1_BUFFER_UAV_FLAG");

            group.TagTypeAndName<CppField>(@"^D3D(\d+)_SHADER_VARIABLE_DESC::uFlags", "D3D_SHADER_VARIABLE_FLAGS", "Flags");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_SHADER_INPUT_BIND_DESC::uFlags", "D3D_SHADER_INPUT_FLAGS", "Flags");

            group.TagName<CppField>(@"^D3D(\d+)_QUERY_DATA_PIPELINE_STATISTICS::(.*)s", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_SHADER_DESC::(.*[^g])s$", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_SHADER_BUFFER_DESC::Variables$", "VariableCount");
            group.TagTypeAndName<CppField>(@"^D3D(\d+)_SHADER_BUFFER_DESC::uFlags$", "D3D_SHADER_CBUFFER_FLAGS", "Flags");
            group.TagName<CppField>(@"^D3D(\d+)_SHADER_TYPE_DESC::(.*[^g])s$", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_EFFECT_DESC::(.*[^g])s$", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_TECHNIQUE_DESC::(.*[^g])s$", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_PASS_DESC::(.*[^g])s$", "$2Count");

            // Rename all Num(Elmenent)s by ElementCount
            group.TagName<CppField>(@"^D3DX?(\d+).*::Num(.*)s$", "$2Count");

            group.TagVisibility<CppField>(@"^D3D(\d+)_PASS_DESC::pIAInputSignature", Visibility.Internal);
            group.TagVisibility<CppField>(@"^D3D(\d+)_PASS_DESC::IAInputSignatureSize", Visibility.Internal);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)ClassInstance::GetInstanceName$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)ClassInstance::GetTypeName$", Visibility.Internal);

            // Hide all Create.* methods in Device
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)Device::Create.*$", Visibility.Internal);
            // Hide GetImmediateContext and force to no property
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)Device::GetImmediateContext$", Visibility.Internal, true);

            // ID3DxxDevice
            group.TagParameter(@"^ID3D(\d+)Device::CreateTexture[0-9]D::pInitialData$",
                                       CppAttribute.In | CppAttribute.Buffer
                                                                    | CppAttribute.Optional);

            // Device / DeviceContext
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetVertexBuffers$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetTargets$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetRenderTargetsAndUnorderedAccessViews$", Visibility.Internal);

            var param = group.FindFirst<CppParameter>(@"^ID3D(\d+)DeviceContext::ClearRenderTargetView::ColorRGBA$");
            param.Type = "SLIMDX_COLOR4";
            param.IsArray = false;
            param.Specifier = "*";

            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::IA(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::VS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::PS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::GS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::SO(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::DS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::HS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::RS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::OM(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D\d+DeviceContext::CS(.*)$", "$1");

            // Mark all stage SetShader methods internals
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetViewports$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetScissorRects$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::IASetVertexBuffers$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetShader$", Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetShaderResources$", Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetSamplers$", Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetShader$", Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]SetConstantBuffers$", Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetShaderResources$", Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetSamplers$", Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetConstantBuffers$", Visibility.Internal | Visibility.Override);

            // Force pNumClassInstance to be inout but not optional
            group.TagParameter(@"^ID3D(\d+)DeviceContext::[A-Z][A-Z]GetShader::pNumClassInstances$", CppAttribute.InOut);

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::Map$", Visibility.Internal);
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::Unmap$", "UnmapSubresource");
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::UpdateSubresource$", Visibility.Internal);

            //group.TagParameter(@"^ID3D(\d+)DeviceContext::Map::MapFlags$", Modifiers.Type("D3D$1_MAP_FLAG"));
            group.TagTypeAndName<CppParameter>(@"^ID3D(\d+)DeviceContext::Map::MapFlags$", "D3D$1_MAP_FLAG");

            group.TagTypeAndName<CppParameter>(@"^ID3D(\d+)DeviceContext::GetData::GetDataFlags$", "D3D$1_ASYNC_GETDATA_FLAG");
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::GetData$", Visibility.Internal, null, "GetDataInternal");

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::FinishCommandList$", Visibility.Internal, null, "FinishCommandListInternal");

            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::GetResourceMinLOD$", "GetMinimumLod");
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::SetResourceMinLOD$", "SetMinimumLod");

            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::ClearUnorderedAccessViewFloat$", "ClearUnorderedAccessView");
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::ClearUnorderedAccessViewUint$", "ClearUnorderedAccessView");

            group.TagTypeAndName<CppParameter>(@"^ID3D(\d+)DeviceContext::ClearDepthStencilView::ClearFlags$", "D3D11_CLEAR_FLAG");

            // Remove TheadPump interfaces as they don't make sense in .NET
            group.Remove<CppInterface>(@"^ID3DX(\d+)ThreadPump$");
            group.Remove<CppInterface>(@"^ID3DX(\d+)DataLoader$");
            group.Remove<CppInterface>(@"^ID3DX(\d+)DataProcessor$");

            // Patch Effects Interfaces
            group.TagParameter(@"^ID3D(\d+)ShaderReflectionType::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflectionVariable::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflectionConstantBuffer::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection::GetResourceBindingDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection::GetInputParameterDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection::GetOutputParameterDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)StateBlock::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectType::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVariable::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectScalarVariable::GetFloat::pValue$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectScalarVariable::GetFloatArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectScalarVariable::GetInt::pValue$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectScalarVariable::GetIntArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectScalarVariable::GetBool::pValue$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectScalarVariable::GetBoolArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVectorVariable::GetBoolVector::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVectorVariable::GetIntVector::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVectorVariable::GetFloatVector::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVectorVariable::GetBoolVectorArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVectorVariable::GetIntVectorArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectVectorVariable::GetFloatVectorArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectMatrixVariable::GetMatrix::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectMatrixVariable::GetMatrixArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectMatrixVariable::GetMatrixTranspose::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectMatrixVariable::GetMatrixTransposeArray::pData$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectStringVariable::GetStringArray::ppStrings$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderResourceVariable::GetResource::ppResource$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderResourceVariable::GetResourceArray::ppResources$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectRenderTargetViewVariable::GetRenderTarget::ppResource$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectRenderTargetViewVariable::GetRenderTargetArray::ppResources$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectDepthStencilViewVariable::GetDepthStencil::ppResource$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectDepthStencilViewVariable::GetDepthStencilArray::ppResources$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectConstantBuffer::GetConstantBuffer::ppConstantBuffer$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectConstantBuffer::GetTextureBuffer::ppTextureBuffer$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderVariable::GetShaderDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderVariable::GetVertexShader::ppVS$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderVariable::GetGeometryShader::ppGS$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderVariable::GetPixelShader::ppPS$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderVariable::GetInputSignatureElementDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectShaderVariable::GetOutputSignatureElementDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectBlendVariable::GetBlendState::ppBlendState$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectBlendVariable::GetBackingStore::pBlendDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectDepthStencilVariable::GetDepthStencilState::ppDepthStencilState$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectDepthStencilVariable::GetBackingStore::pDepthStencilDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectRasterizerVariable::GetRasterizerState::ppRasterizerState$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectRasterizerVariable::GetBackingStore::pRasterizerDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectSamplerVariable::GetSampler::ppSampler$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectSamplerVariable::GetBackingStore::pSamplerDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectPass::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectPass::GetVertexShaderDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectPass::GetGeometryShaderDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectPass::GetPixelShaderDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)EffectTechnique::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)Effect::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)Effect::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetResourceBindingDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetInputParameterDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetOutputParameterDesc::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetMovInstructionCount::pCount$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetMovcInstructionCount::pCount$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetConversionInstructionCount::pCount$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetBitwiseInstructionCount::pCount$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::GetGSInputPrimitive::pPrim$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::IsLevel9Shader::pbLevel9Shader$", CppAttribute.Out);
            group.TagParameter(@"^ID3D(\d+)ShaderReflection1::IsSampleFrequencyShader::pbSampleFrequency$", CppAttribute.Out);

            group.TagTypeAndName<CppParameter>(@"^ID3DX(\d*)Sprite::Begin::flags", "D3DX$1_SPRITE_FLAG");

            group.TagTypeAndName<CppParameter>(@"^ID3D(\d+).*::Map::MapFlags", "D3D$1_MAP_FLAG");

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)EffectPass::Apply$", Visibility.Internal);

            group.TagVisibility<CppMethod>(@"^ID3DX(\d*)Font::GetTextMetrics.*$", Visibility.Internal);


            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppFunction>(@"^D3DX\d+(.*)W", "$1", false);

            group.TagTypeAndName<CppParameter>(@"^D3D(\d+)CreateDevice.*?::Flags$", "D3D$1_CREATE_DEVICE_FLAG");
            group.TagTypeAndName<CppParameter>(@"^D3DX(\d+).*?::Flags1$", "D3DCOMPILE_SHADER_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DX(\d+).*?::Flags2$", "D3DCOMPILE_EFFECT_FLAGS");
            group.TagTypeAndName<CppParameter>(@"^D3DX(\d+)ComputeNormalMap::Flags$", "D3DX$1_NORMALMAP_FLAG");
            group.TagTypeAndName<CppParameter>(@"^D3DX(\d+)ComputeNormalMap::Channel$", "D3DX$1_CHANNEL_FLAG");

            group.TagParameter(@"^D3DX(\d+)CreateTextureFromFileW::ppTexture", CppAttribute.Out);
            group.TagParameter(@"^D3DX(\d+)CreateTextureFromResourceW::ppTexture", CppAttribute.Out);
            group.TagParameter(@"^D3DX(\d+)CreateTextureFromMemory::ppTexture", CppAttribute.Out);
            group.TagParameter(@"^D3DX(\d+)SaveTextureToMemory::ppDestBuf", CppAttribute.Out);
            group.TagParameter(@"^D3DX(\d+)CreateTextureFromFileW::pLoadInfo", CppAttribute.In | CppAttribute.Optional);
            group.TagParameter(@"^D3DX(\d+)CreateTextureFromResourceW::pLoadInfo", CppAttribute.In | CppAttribute.Optional);
            group.TagParameter(@"^D3DX(\d+)CreateTextureFromMemory::pLoadInfo", CppAttribute.In | CppAttribute.Optional);
            group.TagParameter(@"^D3DX(\d+).*?::pDefines", CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional);
            group.TagParameter(@"^D3D(\d+)CreateDeviceAndSwapChain::pSwapChainDesc", CppAttribute.In);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromFileW$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromResourceW$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromMemory$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)SaveTextureToFile$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)SaveTextureToMemory$", Visibility.Internal);

            // Remove all functions unsing ASCII strings
            group.Remove<CppFunction>(@"^D3DX(\d+).*A$");
            group.TagName<CppFunction>(@"^D3DX(\d+)(.+)W$", "$2", false);

            // Remove duplicate D3DX function to D3DCompiler
            group.Remove<CppFunction>(@"^D3DX(\d+)Compile.*$");
            group.Remove<CppFunction>(@"^D3DX(\d+)PreprocessShader.*$");

            // Remove all async functions as they would be much more easier to implement in C#
            group.Remove<CppFunction>(@"^D3DX(\d+)CreateAsync.*$");
            group.Remove<CppFunction>(@"^D3DX(\d+)CreateThreadPump.*$");

            group.FindContext.Clear();

            // Map specific part
            MapDirect3D10();
            MapDirect3D11();
        }




        /// <summary>
        /// Maps the Direct3D10 API
        /// </summary>
        public void MapDirect3D10()
        {
            // Global namespace for D3DCompiler
            string assemblyName = Global.Name + ".Direct3D10";
            string namespaceName = assemblyName;

            // Include to Assembly/Namespace assocation
            foreach (var includeName in d3d10Includes)
                gen.MapIncludeToNamespace(includeName, assemblyName, namespaceName);

            group.FindContext.AddRange(d3d10Includes);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppEnum>(@"^D3D10_FEATURE_LEVEL1$", "FeatureLevel");
            group.TagName<CppEnumItem>(@"^D3D10_FEATURE_LEVEL_(.*)", @"Level_$1", true);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppStruct>(@"^D3DX10_SPRITE", "SpriteType");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_SCOPE_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_SCOPEVAR_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_INPUT_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_VAR_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_TOKEN_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_OUTPUTVAR$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_OUTPUTREG_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_INST_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_FILE_INFO$");
            group.Remove<CppStruct>(@"^D3D10_SHADER_DEBUG_INFO$");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^ID3D10(.+)", "$1", false);
            group.TagName<CppInterface>(@"^ID3DX10(.+)", "$1", false);

            // Remove all methods using ASCII encoding
            group.Remove<CppMethod>(@"^ID3DX10Font::.*A$");
            group.Remove<CppStruct>(@"^D3DX10_FONT_DESCA$");

            // Rename all methods using WideChar encoding
            group.TagName<CppMethod>(@"^ID3DX10Font::GetTextMetricsW$", "GetTextMetrics");
            group.TagName<CppMethod>(@"^ID3DX10Font::PreloadTextW$", "PreloadText");
            group.TagName<CppMethod>(@"^ID3DX10Font::DrawTextW$", "DrawText");
            //group.TagName<CppMethod>(@"^ID3DX10Font::GetDC$", "GetDeviceContext");

            group.TagName<CppMethod>(@"^ID3D10Device::IA(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D10Device::VS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D10Device::PS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D10Device::GS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D10Device::SO(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D10Device::RS(.*)$", "$1");
            group.TagName<CppMethod>(@"^ID3D10Device::OM(.*)$", "$1");

            gen.MoveMethodsToInnerInterface("ID3D10Device::IA(.*)", "InputAssemblerStage", "InputAssembler");
            gen.MoveMethodsToInnerInterface("ID3D10Device::VS(.*)", "VertexShaderStage", "VertexShader", "CommonShaderStage<VertexShader>");
            gen.MoveMethodsToInnerInterface("ID3D10Device::PS(.*)", "PixelShaderStage", "PixelShader", "CommonShaderStage<PixelShader>");
            gen.MoveMethodsToInnerInterface("ID3D10Device::GS(.*)", "GeometryShaderStage", "GeometryShader", "CommonShaderStage<GeometryShader>");
            gen.MoveMethodsToInnerInterface("ID3D10Device::SO(.*)", "StreamOutputStage", "StreamOutput");
            gen.MoveMethodsToInnerInterface("ID3D10Device::RS(.*)", "RasterizerStage", "Rasterizer");
            gen.MoveMethodsToInnerInterface("ID3D10Device::OM(.*)", "OutputMergerStage", "OutputMerger");


            // Mark all stage methods internals
            var param = group.FindFirst<CppParameter>(@"^ID3D10Device::ClearRenderTargetView::ColorRGBA$");
            param.Type = "SLIMDX_COLOR4";
            param.IsArray = false;
            param.Specifier = "*";

            group.TagVisibility<CppMethod>(@"^ID3D10DeviceContext::SetViewports$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::SetScissorRects$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::IASetVertexBuffers$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]SetShader$", null, true, "Set");
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]SetShaderResources$", Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]SetSamplers$", Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]GetShader$", null, true, "Get");
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]SetConstantBuffers$", Visibility.Public | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]GetShaderResources$", Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]GetSamplers$", Visibility.Internal | Visibility.Override);
            group.TagVisibility<CppMethod>(@"^ID3D10Device::[A-Z][A-Z]GetConstantBuffers$", Visibility.Internal | Visibility.Override);

            // Patch Out parameters
            group.TagParameter(@"^ID3DX10Sprite::GetViewTransform::pViewTransform$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Sprite::GetProjectionTransform::pProjectionTransform$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Sprite::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetDevice::ppDevice$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetDescA::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetDescW::pDesc$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetTextMetricsA::pTextMetrics$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetTextMetricsW::pTextMetrics$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetGlyphData::ppTexture$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetGlyphData::pBlackBox$", CppAttribute.Out);
            group.TagParameter(@"^ID3DX10Font::GetGlyphData::pCellInc$", CppAttribute.Out);

            // Replace all existing reference to ID3DX11ThreadPump type to void (making all pointers to be void*)
            //group.ModifyAll(".*", Modifiers.RenameType("ID3DX10ThreadPump", "void"));
            gen.MapCppTypeToCSharpType("ID3DX10ThreadPump", typeof(IntPtr));

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Functions
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppFunction>(@"^D3D10(.+)", "$1", false);
            group.TagName<CppFunction>(@"^D3DX10(.+)$", "$1", false);
            group.TagName<CppFunction>(@"^D3DX10(.+)W$", "$1", false);

            group.TagParameter(@"^D3D10CreateDevice1?::ppDevice", CppAttribute.Out);
            group.TagParameter(@"^D3D10CreateDeviceAndSwapChain1?::ppDevice", CppAttribute.Out);
            group.TagParameter(@"^D3D10CreateDeviceAndSwapChain1?::ppSwapChain", CppAttribute.Out);
            group.TagParameter(@"^D3D10CreateEffectFromMemory::ppEffect", CppAttribute.Out);
            group.Remove<CppFunction>(@"^D3D10CreateBlob$");
            group.Remove<CppFunction>(@"^D3D10CompileShader$");
            group.Remove<CppFunction>(@"^D3D10DisassembleShader$");
            group.Remove<CppFunction>(@"^D3D10ReflectShader$");
            group.Remove<CppFunction>(@"^D3D10PreprocessShader$");
            group.Remove<CppFunction>(@"^D3D10GetInputSignatureBlob$");
            group.Remove<CppFunction>(@"^D3D10GetOutputSignatureBlob$");
            group.Remove<CppFunction>(@"^D3D10GetInputAndOutputSignatureBlob$");
            group.Remove<CppFunction>(@"^D3D10GetShaderDebugInfo$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskUnion$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskIntersect$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskDifference$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskEnableCapture$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskDisableCapture$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskEnableAll$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskDisableAll$");
            group.Remove<CppFunction>(@"^D3D10StateBlockMaskGetSetting$");
            group.Remove<CppFunction>(@"^D3D10CreateStateBlock$");
            group.Remove<CppFunction>(@"^D3D10CompileEffectFromMemory$");
            group.Remove<CppFunction>(@"^D3D10DisassembleEffect$");

            group.Remove<CppInterface>(@"^ID3D10Debug$");
           
            CSharpFunctionGroup d3d10FunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "D3D10");
            CSharpFunctionGroup d3dx10FunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "D3DX10");
            string d3dx10DLLName = group.FindFirst<CppMacroDefinition>("D3DX10_DLL_A").StripStringValue;

            // Map All D3D11 functions to D3D11 Function Group
            group.TagFunction(@"^D3D10.*", "d3d10.dll", d3d10FunctionGroup);
            group.TagFunction(@"^D3D10.*1", "d3d10_1.dll", d3d10FunctionGroup);

            // Map All D3DX11 functions to D3DX11 Function Group
            group.TagFunction(@"^D3DX10.*", d3dx10DLLName, d3dx10FunctionGroup);

            gen.AddConstantFromMacroToCSharpType("^D3D10_SDK_VERSION$", namespaceName + "." + d3d10FunctionGroup.Name, "int", "SdkVersion");
            gen.AddConstantFromMacroToCSharpType("^D3D10_1_SDK_VERSION$", namespaceName + "." + d3d10FunctionGroup.Name, "int", "SdkVersion1");

            group.FindContext.Clear();

            // SubPart renaming
            // gen.RenameTypePart("^D3D10", "");        
        }

        /// <summary>
        /// Maps the Direct3D11 API
        /// </summary>
        public unsafe void MapDirect3D11()
        {
            // Global namespace for D3DCompiler
            string assemblyName = Global.Name + ".Direct3D11";
            string namespaceName = assemblyName;

            // Include to Assembly/Namespace assocation
            foreach (var includeName in d3d11Includes)
                gen.MapIncludeToNamespace(includeName, assemblyName, namespaceName);

            group.FindContext.AddRange(d3d11Includes);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppEnumItem>(@"^D3D11_FEATURE_FORMAT_SUPPORT2$", "ComputeShaders");
            group.TagName<CppEnumItem>(@"^D3D11_FEATURE_DOUBLES$", "ShaderDoubles");
            group.Remove<CppEnumItem>(@"^_D3DX11_ERR$");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppStruct>(@"^D3D11_SHADER_BUFFER_DESC$", "ConstantBufferDescription");
            group.TagTypeAndName<CppField>(@"^D3D11_SHADER_DESC::Version", "D3D11_SHADER_VERSION_TYPE");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Interfaces
            // --------------------------------------------------------------------------------------------------------
            group.TagName<CppInterface>(@"^ID3D11(.+)", "$1", false);
            group.TagName<CppInterface>(@"^ID3DX11(.+)", "$1", false);

            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::IA(.*)", "InputAssemblerStage", "InputAssembler");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::VS(.*)", "VertexShaderStage", "VertexShader", "CommonShaderStage<VertexShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::PS(.*)", "PixelShaderStage", "PixelShader", "CommonShaderStage<PixelShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::GS(.*)", "GeometryShaderStage", "GeometryShader", "CommonShaderStage<GeometryShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::SO(.*)", "StreamOutputStage", "StreamOutput");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::DS(.*)", "DomainShaderStage", "DomainShader", "CommonShaderStage<DomainShader>");
            ;
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::HS(.*)", "HullShaderStage", "HullShader", "CommonShaderStage<HullShader>");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::RS(.*)", "RasterizerStage", "Rasterizer");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::OM(.*)", "OutputMergerStage", "OutputMerger");
            gen.MoveMethodsToInnerInterface("ID3D11DeviceContext::CS(.*)", "ComputeShaderStage", "ComputeShader", "CommonShaderStage<ComputeShader>");

            // Replace all existing reference to ID3DX11ThreadPump type to void (making all pointers to be void*)
            //            group.ModifyAll(".*", Modifiers.RenameType("ID3DX11ThreadPump", "void"));
            gen.MapCppTypeToCSharpType("ID3DX11ThreadPump", typeof(IntPtr));

            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Functions
            // --------------------------------------------------------------------------------------------------------
            CSharpFunctionGroup d3d11FunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "D3D11");
            CSharpFunctionGroup d3dx11FunctionGroup = gen.CreateFunctionGroup(assemblyName, namespaceName, "D3DX11");
            string d3dx11DLLName = group.FindFirst<CppMacroDefinition>("D3DX11_DLL_A").StripStringValue;

            gen.AddConstantFromMacroToCSharpType("^D3D11_SDK_VERSION$", namespaceName + "." + d3d11FunctionGroup.Name, "int", "SdkVersion");
            group.TagName<CppFunction>(@"^D3D11(.+)", "$1", false);
            group.TagName<CppFunction>(@"^D3DX11(.+)$", "$1", false);
            group.TagName<CppFunction>(@"^D3DX11(.+)W$", "$1", false);


            group.TagFunction(@"^D3D11.*", "d3d11.dll", d3d11FunctionGroup);
            group.TagFunction(@"^D3DX11.*", d3dx11DLLName, d3dx11FunctionGroup);

            group.FindContext.Clear();
            //gen.RenameTypePart("^D3D11", "");
            //gen.RenameTypePart("^D3DX11", "");
        }
    }
}

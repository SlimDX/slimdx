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

        /// <summary>
        /// Maps the Direct3D10 and Direct3D11 API
        /// </summary>
        public void MapDirect3D10AndDirect3D11()
        {
            // The following part is not common to Direct3D10 and Direct3D11

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Enumerations
            // --------------------------------------------------------------------------------------------------------
            group.TagEnumFlags(@"^D3D(\d+)_FORMAT_SUPPORT$");
            group.TagEnumFlags(@"^D3D(\d+)_FORMAT_SUPPORT2$");
            group.ModifyAll(@"^D3DX11_ERR$", Modifiers.Remove);
            group.ModifyAll("^D3D10_CBF_USERPACKED$", Modifiers.Remove);
            group.Modify<CppEnum>(@"^D3D10_FEATURE_LEVEL1$", Modifiers.Remove);

            group.ModifyAll(".*", Modifiers.RenameType("D3D10_FEATURE_LEVEL1", "D3D_FEATURE_LEVEL"));

            // Add None = 0 for enum D3D11_COLOR_WRITE_ENABLE
            group.Modify<CppEnum>(@"^D3D(\d+)_COLOR_WRITE_ENABLE$", Modifiers.EnumAdd("None", "0"));
            group.TagEnumFlags(@"^D3D(\d+)_COLOR_WRITE_ENABLE$");


            // D3D10/D3D11
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
            gen.RenameType(@"^D3D(\d+)_(.*)_SRV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_SRV$", "D3D$1_SHADER_RESOURCE_VIEW_DESC");

            gen.RenameType(@"^D3D(\d+)_(.*)_SRV1$", "$2_Resource1");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_SRV1$", "D3D$1_SHADER_RESOURCE_VIEW_DESC1");

            gen.RenameType(@"^D3D(\d+)_(.*)_RTV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_RTV$", "D3D$1_RENDER_TARGET_VIEW_DESC");

            gen.RenameType(@"^D3D(\d+)_(.*)_DSV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_DSV$", "D3D$1_DEPTH_STENCIL_VIEW_DESC");

            gen.RenameType(@"^D3D(\d+)_(.*)_UAV$", "$2_Resource");
            gen.MoveStructToInner(@"^D3D(\d+)_(.*)_UAV$", "D3D$1_UNORDERED_ACCESS_VIEW_DESC");

            gen.RenameType(@"^D3D(\d+)_PASS_DESC$", "EffectPassDescription");
            gen.RenameType(@"^D3D(\d+)_PASS_SHADER_DESC$", "EffectPassShaderDescription");
            gen.RenameType(@"^D3D(\d+)_TECHNIQUE_DESC$", "EffectTechniqueDescription");

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

            gen.RenameType(@"^D3D(\d+)_SHADER_DEBUG_REGTYPE$", "ShaderDebugRegisterType");
            gen.RenameType(@"^D3D(\d+)_SHADER_DEBUG_REG_(.+)$", "$2");
            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Structures
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

            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_DESC::Flags", "D3DCOMPILE_SHADER_FLAGS");

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

            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_VARIABLE_DESC::uFlags", "D3D_SHADER_VARIABLE_FLAGS", "Flags");
            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_INPUT_BIND_DESC::uFlags", "D3D_SHADER_INPUT_FLAGS", "Flags");

            group.TagName<CppField>(@"^D3D(\d+)_QUERY_DATA_PIPELINE_STATISTICS::(.*)s", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_SHADER_DESC::(.*[^g])s$", "$2Count");
            group.TagName<CppField>(@"^D3D(\d+)_SHADER_BUFFER_DESC::Variables$", "VariableCount");
            group.TagTypeName<CppField>(@"^D3D(\d+)_SHADER_BUFFER_DESC::uFlags$", "D3D_SHADER_CBUFFER_FLAGS", "Flags");
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
            group.Modify<CppParameter>(@"^ID3D(\d+)Device::CreateTexture[0-9]D::pInitialData$",
                                       Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Buffer
                                                                    | CppAttribute.Optional));

            // Device / DeviceContext
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetVertexBuffers$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetTargets$", Visibility.Internal);
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::SetRenderTargetsAndUnorderedAccessViews$", Visibility.Internal);

            group.Modify<CppParameter>(@"^ID3D(\d+)DeviceContext::ClearRenderTargetView::ColorRGBA$", Modifiers.Type("SLIMDX_COLOR4", "*", false, null));

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

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::Map$", Visibility.Internal);
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::Unmap$", "UnmapSubresource");
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::UpdateSubresource$", Visibility.Internal);

            //group.Modify<CppParameter>(@"^ID3D(\d+)DeviceContext::Map::MapFlags$", Modifiers.Type("D3D$1_MAP_FLAG"));
            group.TagTypeName<CppParameter>(@"^ID3D(\d+)DeviceContext::Map::MapFlags$", "D3D$1_MAP_FLAG");

            group.TagTypeName<CppParameter>(@"^ID3D(\d+)DeviceContext::GetData::GetDataFlags$", "D3D$1_ASYNC_GETDATA_FLAG");
            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::GetData$", Visibility.Internal, null, "GetDataInternal");

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)DeviceContext::FinishCommandList$", Visibility.Internal, null, "FinishCommandListInternal");

            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::GetResourceMinLOD$", "GetMinimumLod");
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::SetResourceMinLOD$", "SetMinimumLod");

            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::ClearUnorderedAccessViewFloat$", "ClearUnorderedAccessView");
            group.TagName<CppMethod>(@"^ID3D(\d+)DeviceContext::ClearUnorderedAccessViewUint$", "ClearUnorderedAccessView");

            group.TagTypeName<CppParameter>(@"^ID3D(\d+)DeviceContext::ClearDepthStencilView::ClearFlags$", "D3D11_CLEAR_FLAG");

            // Remove TheadPump interfaces as they don't make sense in .NET
            group.Modify<CppInterface>(@"^ID3DX(\d+)ThreadPump$", Modifiers.Remove);
            group.Modify<CppInterface>(@"^ID3DX(\d+)DataLoader$", Modifiers.Remove);
            group.Modify<CppInterface>(@"^ID3DX(\d+)DataProcessor$", Modifiers.Remove);

            // Effects Interfaces
            group.Modify<CppParameter>(@"^ID3D(\d+)ShaderReflectionVariable::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)ShaderReflection1?::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)ShaderReflection1?:GetResourceBindingDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)ShaderReflection1?::GetInputParameterDescription::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)ShaderReflection1?::GetOutputParameterDescription::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)ShaderReflection1?::GetResourceBindingDescByName::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectType::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectVariable::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectConstantBuffer::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectShaderVariable::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectShaderVariable::GetShaderDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectShaderVariable::GetInputSignatureElementDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectShaderVariable::GetOutputSignatureElementDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectBlendVariable::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectRasterizerVariable::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectSamplerVariable::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectPass::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectPass::ComputeStateBlockMask::pStateBlockMask", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectTechnique::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)EffectTechnique::ComputeStateBlockMask::pStateBlockMask", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3D(\d+)Effect::GetDesc::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3DX(\d+)Font::GetDescW::pDesc", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^ID3DX?(\d*).*::GetDevice::ppDevice$", Modifiers.ParameterAttribute(CppAttribute.Out));

            group.TagTypeName<CppParameter>(@"^ID3DX(\d*)Sprite::Begin::flags", "D3DX$1_SPRITE_FLAG");

            group.TagTypeName<CppParameter>(@"^ID3D(\d+).*::Map::MapFlags", "D3D$1_MAP_FLAG");

            group.TagVisibility<CppMethod>(@"^ID3D(\d+)EffectPass::Apply$", Visibility.Internal);

            group.TagVisibility<CppMethod>(@"^ID3DX(\d*)Font::GetTextMetrics.*$", Visibility.Internal);


            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 / Direct3D11 Functions
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^D3DX\d+(.*)W", "$1");

            group.TagTypeName<CppParameter>(@"^D3D(\d+)CreateDevice.*?::Flags$", "D3D$1_CREATE_DEVICE_FLAG");
            group.TagTypeName<CppParameter>(@"^D3DX(\d+).*?::Flags1$", "D3DCOMPILE_SHADER_FLAGS");
            group.TagTypeName<CppParameter>(@"^D3DX(\d+).*?::Flags2$", "D3DCOMPILE_EFFECT_FLAGS");
            group.TagTypeName<CppParameter>(@"^D3DX(\d+)ComputeNormalMap::Flags$", "D3DX$1_NORMALMAP_FLAG");
            group.TagTypeName<CppParameter>(@"^D3DX(\d+)ComputeNormalMap::Channel$", "D3DX$1_CHANNEL_FLAG");

            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromFileW::ppTexture", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromResourceW::ppTexture", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromMemory::ppTexture", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3DX(\d+)SaveTextureToMemory::ppDestBuf", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromFileW::pLoadInfo", Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Optional));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromResourceW::pLoadInfo", Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Optional));
            group.Modify<CppParameter>(@"^D3DX(\d+)CreateTextureFromMemory::pLoadInfo", Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Optional));
            group.Modify<CppParameter>(@"^D3DX(\d+).*?::pDefines", Modifiers.ParameterAttribute(CppAttribute.In | CppAttribute.Buffer | CppAttribute.Optional));
            group.Modify<CppParameter>(@"^D3D(\d+)CreateDeviceAndSwapChain::pSwapChainDesc", Modifiers.ParameterAttribute(CppAttribute.In));
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromFileW$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromResourceW$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)CreateTextureFromMemory$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)SaveTextureToFile$", Visibility.Internal);
            group.TagVisibility<CppFunction>(@"^D3DX(\d+)SaveTextureToMemory$", Visibility.Internal);

            // Remove all functions unsing ASCII strings
            group.Modify<CppFunction>(@"^D3DX(\d+).*A$", Modifiers.Remove);

            // Remove duplicate D3DX function to D3DCompiler
            group.Modify<CppFunction>(@"^D3DX(\d+)Compile.*$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3DX(\d+)PreprocessShader.*$", Modifiers.Remove);

            // Remove all async functions as they would be much more easier to implement in C#
            group.Modify<CppFunction>(@"^D3DX(\d+)CreateAsync.*$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3DX(\d+)CreateThreadPump.*$", Modifiers.Remove);


            // Map specific part
            MapDirect3D10();
            MapDirect3D11();
        }

        /// <summary>
        /// Maps the Direct3D10 API
        /// </summary>
        public unsafe void MapDirect3D10()
        {
            // Include to Assembly/Namespace assocation
            gen.MapIncludeToNamespace("d3d10", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3d10_1", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3d10_1shader", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3d10effect", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3d10misc", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3d10sdklayers", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3d10shader", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3dx10", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3dx10core", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3dx10tex", Global.Name + ".Direct3D10");
            gen.MapIncludeToNamespace("d3dx10async", Global.Name + ".Direct3D10");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Enumerations
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^D3DX10_SPRITE", "SpriteType");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Structures
            // --------------------------------------------------------------------------------------------------------
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_SCOPE_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_SCOPEVAR_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_INPUT_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_VAR_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_TOKEN_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_OUTPUTVAR$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_OUTPUTREG_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_INST_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_FILE_INFO$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3D10_SHADER_DEBUG_INFO$", Modifiers.Remove);

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Interfaces
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^ID3D10(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3DX10(.+)", "$1", false, TypeContext.Root);

            gen.MoveMethodsToInnerInterface("ID3D10Device::IA(.*)", "InputAssemblerStage", "InputAssembler", "$1");
            gen.MoveMethodsToInnerInterface("ID3D10Device::VS(.*)", "VertexShaderStage", "VertexShader", "$1",
                                            "CommonShaderStage<VertexShader>");
            gen.MoveMethodsToInnerInterface("ID3D10Device::PS(.*)", "PixelShaderStage", "PixelShader", "$1",
                                            "CommonShaderStage<PixelShader>");
            gen.MoveMethodsToInnerInterface("ID3D10Device::GS(.*)", "GeometryShaderStage", "GeometryShader", "$1",
                                            "CommonShaderStage<GeometryShader>");
            gen.MoveMethodsToInnerInterface("ID3D10Device::SO(.*)", "StreamOutputStage", "StreamOutput", "$1");
            gen.MoveMethodsToInnerInterface("ID3D10Device::RS(.*)", "RasterizerStage", "Rasterizer", "$1");
            gen.MoveMethodsToInnerInterface("ID3D10Device::OM(.*)", "OutputMergerStage", "OutputMerger", "$1");

            // Remove all methods using ASCII encoding
            group.Modify<CppMethod>(@"^ID3DX10Font::.*A$", Modifiers.Remove);
            group.Modify<CppStruct>(@"^D3DX10_FONT_DESCA$", Modifiers.Remove);

            // Rename all methods using WideChar encoding
            group.TagName<CppMethod>(@"^ID3DX10Font::GetTextMetricsW$", "GetTextMetrics");
            group.TagName<CppMethod>(@"^ID3DX10Font::PreloadTextW$", "PreloadText");
            group.TagName<CppMethod>(@"^ID3DX10Font::DrawTextW$", "DrawText");
            //group.TagName<CppMethod>(@"^ID3DX10Font::GetDC$", "GetDeviceContext");

            // Mark all stage methods internals
            group.Modify<CppParameter>(@"^ID3D10Device::ClearRenderTargetView::ColorRGBA$", Modifiers.Type("SLIMDX_COLOR4", "*", false, null));
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


            // Replace all existing reference to ID3DX11ThreadPump type to void (making all pointers to be void*)
            group.ModifyAll(".*", Modifiers.RenameType("ID3DX10ThreadPump", "void"));

            // --------------------------------------------------------------------------------------------------------
            // Direct3D10 Functions
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^D3D10(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3DX10(.+)", "$1", false, TypeContext.Root);

            group.Modify<CppParameter>(@"^D3D10CreateDevice1?::ppDevice", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3D10CreateDeviceAndSwapChain1?::ppDevice", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3D10CreateDeviceAndSwapChain1?::ppSwapChain", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppParameter>(@"^D3D10CreateEffectFromMemory::ppEffect", Modifiers.ParameterAttribute(CppAttribute.Out));
            group.Modify<CppFunction>(@"^D3D10CreateBlob$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10CompileShader$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10DisassembleShader$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10ReflectShader$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10PreprocessShader$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10GetInputSignatureBlob$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10GetOutputSignatureBlob$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10GetInputAndOutputSignatureBlob$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10GetShaderDebugInfo$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskUnion$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskIntersect$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskDifference$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskEnableCapture$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskDisableCapture$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskEnableAll$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskDisableAll$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10StateBlockMaskGetSetting$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10CreateStateBlock$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10CompileEffectFromMemory$", Modifiers.Remove);
            group.Modify<CppFunction>(@"^D3D10DisassembleEffect$", Modifiers.Remove);

            group.Modify<CppInterface>(@"^ID3D10Debug$", Modifiers.Remove);


            CSharpFunctionGroup d3d10FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D10", Global.Name + ".Direct3D10", "D3D10");
            CSharpFunctionGroup d3dx10FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D10", Global.Name + ".Direct3D10", "D3DX10");
            string d3dx10DLLName = group.FindFirst<CppMacroDefinition>("D3DX10_DLL_A").StripStringValue;

            // Map All D3D11 functions to D3D11 Function Group
            group.TagFunction(@"^D3D10.*", "d3d10.dll", d3d10FunctionGroup);
            group.TagFunction(@"^D3D10.*1", "d3d10_1.dll", d3d10FunctionGroup);

            // Map All D3DX11 functions to D3DX11 Function Group
            group.TagFunction(@"^D3DX10.*", d3dx10DLLName, d3dx10FunctionGroup);

            gen.AddConstantFromMacroToCSharpType("D3D10_SDK_VERSION", Global.Name + ".Direct3D10.D3D10", "int");
            gen.AddConstantFromMacroToCSharpType("D3D10_1_SDK_VERSION", Global.Name + ".Direct3D10.D3D10", "int", "SdkVersion1");

            // SubPart renaming
            gen.RenameTypePart("^D3D10", "");        
        }

        /// <summary>
        /// Maps the Direct3D11 API
        /// </summary>
        public unsafe void MapDirect3D11()
        {
            gen.MapIncludeToNamespace("d3d11", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11core", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11tex", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3dx11async", Global.Name + ".Direct3D11");
            gen.MapIncludeToNamespace("d3d11shader", Global.Name + ".D3DCompiler");
            gen.MapIncludeToNamespace("d3dcompiler", Global.Name + ".D3DCompiler");


            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Enumerations
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS$", "AllowSlowOperations");
            gen.RenameType(@"^D3D11_SHADER_BUFFER_DESC$", "ConstantBufferDescription");

            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Structures
            // --------------------------------------------------------------------------------------------------------
            group.TagTypeName<CppField>(@"^D3D11_SHADER_DESC::Version", "D3D11_SHADER_VERSION_TYPE");


            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Interfaces
            // --------------------------------------------------------------------------------------------------------
            gen.RenameType(@"^ID3D11(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^ID3DX11(.+)", "$1", false, TypeContext.Root);        

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

            // Replace all existing reference to ID3DX11ThreadPump type to void (making all pointers to be void*)
            group.ModifyAll(".*", Modifiers.RenameType("ID3DX11ThreadPump", "void"));
            
            // --------------------------------------------------------------------------------------------------------
            // Direct3D11 Functions
            // --------------------------------------------------------------------------------------------------------
            gen.AddConstantFromMacroToCSharpType("D3D11_SDK_VERSION", Global.Name + ".Direct3D11.D3D11", "int");
            gen.RenameType(@"^D3D11(.+)", "$1", false, TypeContext.Root);
            gen.RenameType(@"^D3DX11(.+)", "$1", false, TypeContext.Root);

            CSharpFunctionGroup d3d11FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D11", Global.Name + ".Direct3D11", "D3D11");
            CSharpFunctionGroup d3dx11FunctionGroup = gen.CreateFunctionGroup(Global.Name + ".Direct3D11", Global.Name + ".Direct3D11", "D3DX11");
            string d3dx11DLLName = group.FindFirst<CppMacroDefinition>("D3DX11_DLL_A").StripStringValue;

            group.TagFunction(@"^D3D11.*", "d3d11.dll", d3d11FunctionGroup);
            group.TagFunction(@"^D3DX11.*", d3dx11DLLName, d3dx11FunctionGroup);

            gen.RenameTypePart("^D3D11", "");
            gen.RenameTypePart("^D3DX11", "");
        }
    }
}

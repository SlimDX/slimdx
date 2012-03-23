using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using Buffer = SlimDX.Direct3D11.Buffer;
using SlimMath;
using SlimDX.DXGI;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// A helper class to save and restore the rendering state for a device context.
    /// </summary>
    /// <remarks>
    /// This class saves the following bits of state from the device context:
    /// <list type="bullet">
    /// <item><description>Primitive Topology</description></item>
    /// <item><description>Input Layout</description></item>
    /// <item><description>Blend State (including the blend factor and sample mask)</description></item>
    /// <item><description>Depth-Stencil State (including the reference value)</description></item>
    /// <item><description>Rasterizer State</description></item>
    /// <item><description>Pixel shader sampler states</description></item>
    /// <item><description>Vertex shader</description></item>
    /// <item><description>Pixel shader</description></item>
    /// <item><description>Geometry shader (if supported)</description></item>
    /// <item><description>Hull shader (if supported)</description></item>
    /// <item><description>Domain shader (if supported)</description></item>
    /// <item><description>Any class instances set for any of the shaders</description></item>
    /// <item><description>Any set constant buffers for the vertex or geometry shaders</description></item>
    /// <item><description>Any shader resources set for the pixel or geometry shaders</description></item>
    /// <item><description>Any set vertex buffer bindings</description></item>
    /// <item><description>Index buffer (including the format and current offset)</description></item>
    /// </list>
    /// </remarks>
    public class StateSaver : IDisposable
    {
        FeatureLevel featureLevel;
        DeviceContext context;
        PrimitiveTopology primitiveTopology;
        InputLayout inputLayout;
        BlendState blendState;
        Color4 blendFactor;
        int blendSampleMask;
        DepthStencilState depthStencilState;
        int depthStencilReference;
        RasterizerState rasterizerState;
        VertexShader vertexShader;
        PixelShader pixelShader;
        GeometryShader geometryShader;
        HullShader hullShader;
        DomainShader domainShader;
        ClassInstance[] vsInstances;
        ClassInstance[] psInstances;
        ClassInstance[] gsInstances;
        ClassInstance[] hsInstances;
        ClassInstance[] dsInstances;
        Buffer[] vsConstantBuffers;
        Buffer[] gsConstantBuffers;
        SamplerState[] samplerStates;
        ShaderResourceView[] psResources;
        ShaderResourceView[] gsResources;
        VertexBufferBinding[] vertexBuffers;
        Buffer indexBuffer;
        Format indexFormat;
        int indexOffset;
        bool saveState;

        /// <summary>
        /// Initializes a new instance of the <see cref="StateSaver"/> class.
        /// </summary>
        /// <param name="context">The context for which to save state.</param>
        /// <param name="saveState">if set to <c>true</c>, save the current state. This parameter exists to make it easy to dynamically use the state saver in a using-block.</param>
        public StateSaver(DeviceContext context, bool saveState = true)
        {
            if (!saveState)
                return;

            this.saveState = saveState;
            this.context = context;
            featureLevel = context.Device.FeatureLevel;

            primitiveTopology = context.InputAssembler.PrimitiveTopology;
            inputLayout = context.InputAssembler.InputLayout;
            rasterizerState = context.Rasterizer.State;
            vertexShader = context.VertexShader.Get(256, out vsInstances);
            vsConstantBuffers = context.VertexShader.GetConstantBuffers(0, 1);
            pixelShader = context.PixelShader.Get(256, out psInstances);
            psResources = context.PixelShader.GetShaderResources(0, 1);
            samplerStates = context.PixelShader.GetSamplers(0, 1);

            context.OutputMerger.GetBlendState(ref blendState, ref blendFactor, ref blendSampleMask);
            context.OutputMerger.GetDepthStencilState(ref depthStencilState, ref depthStencilReference);

            if (featureLevel >= FeatureLevel.Level_10_0)
            {
                geometryShader = context.GeometryShader.Get(256, out gsInstances);
                gsConstantBuffers = context.GeometryShader.GetConstantBuffers(0, 1);
                gsResources = context.GeometryShader.GetShaderResources(0, 1);

                if (featureLevel >= FeatureLevel.Level_11_0)
                {
                    hullShader = context.HullShader.Get(256, out hsInstances);
                    domainShader = context.DomainShader.Get(256, out dsInstances);
                }
            }

            vertexBuffers = context.InputAssembler.GetVertexBuffers(0, 1);
            context.InputAssembler.GetIndexBuffer(out indexBuffer, out indexFormat, out indexOffset);
        }

        /// <summary>
        /// Restores the previously saved state.
        /// </summary>
        public void Dispose()
        {
            if (!saveState)
                return;

            context.InputAssembler.PrimitiveTopology = primitiveTopology;
            context.InputAssembler.InputLayout = inputLayout;
            context.Rasterizer.State = rasterizerState;
            context.VertexShader.Set(vertexShader, vsInstances);
            context.VertexShader.SetConstantBuffers(vsConstantBuffers, 0, 1);
            context.PixelShader.Set(pixelShader, psInstances);
            context.PixelShader.SetSamplers(samplerStates, 0, 1);
            context.PixelShader.SetShaderResources(psResources, 0, 1);

            context.OutputMerger.SetBlendState(blendState, blendFactor, blendSampleMask);
            context.OutputMerger.SetDepthStencilState(depthStencilState, depthStencilReference);

            if (featureLevel >= FeatureLevel.Level_10_0)
            {
                context.GeometryShader.Set(geometryShader, gsInstances);
                context.GeometryShader.SetConstantBuffers(gsConstantBuffers, 0, 1);
                context.GeometryShader.SetShaderResources(gsResources, 0, 1);

                if (featureLevel >= FeatureLevel.Level_11_0)
                {
                    context.HullShader.Set(hullShader, hsInstances);
                    context.DomainShader.Set(domainShader, dsInstances);
                }
            }

            context.InputAssembler.SetVertexBuffers(0, vertexBuffers);
            context.InputAssembler.SetIndexBuffer(indexBuffer, indexFormat, indexOffset);
        }
    }
}

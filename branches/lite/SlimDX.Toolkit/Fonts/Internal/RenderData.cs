using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using Buffer = SlimDX.Direct3D11.Buffer;
using Device = SlimDX.Direct3D11.Device;
using MapFlags = SlimDX.Direct3D11.MapFlags;
using System.Drawing;
using SlimMath;
using SlimDX.D3DCompiler;
using SlimDX.DXGI;
using System.Runtime.InteropServices;

namespace SlimDX.Toolkit
{
    class RenderData : IDisposable
    {
        [StructLayout(LayoutKind.Sequential)]
        struct ShaderConstants
        {
            public static readonly int SizeInBytes = Marshal.SizeOf(typeof(ShaderConstants));

            public Matrix Transform;
            public RectangleF ClipRect;
        }

        HashSet<IDisposable> resources = new HashSet<IDisposable>();    // I'm lazy
        Device device;
        FeatureLevel featureLevel;
        VertexShader simpleVertexShader;
        VertexShader clippingVertexShader;
        PixelShader simplePixelShader;
        PixelShader clippingPixelShader;
        InputLayout inputLayout;
        ConstantBuffer<ShaderConstants> constantBuffer;
        BlendState blendState;
        SamplerState samplerState;
        DepthStencilState depthStencilState;
        RasterizerState rasterizerState;

        public RenderData(Device device, bool anisotropicFiltering)
        {
            this.device = device;
            featureLevel = device.FeatureLevel;

            CreateQuadShaders();
            CreatePixelShaders();
            CreateConstantBuffer();
            CreateRenderStates(anisotropicFiltering);
        }

        public void Dispose()
        {
            foreach (var resource in resources)
                resource.Dispose();
            resources.Clear();
        }

        public void SetStates(DeviceContext context, TextOptions flags)
        {
            // quads constructed on the CPU
            context.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
            context.InputAssembler.InputLayout = inputLayout;
            context.VertexShader.Set((flags & TextOptions.ClipRect) != 0 ? clippingVertexShader : simpleVertexShader);
            context.PixelShader.Set((flags & TextOptions.ClipRect) != 0 ? clippingPixelShader : simplePixelShader);
            context.VertexShader.SetConstantBuffer(constantBuffer.Buffer, 0);

            // clear out unused shaders
            if (featureLevel >= FeatureLevel.Level_10_0)
                context.GeometryShader.Set(null);

            if (featureLevel >= FeatureLevel.Level_11_0)
            {
                context.DomainShader.Set(null);
                context.HullShader.Set(null);
            }

            // set render states
            context.OutputMerger.SetBlendState(blendState, new Color4(0), -1);
            context.OutputMerger.SetDepthStencilState(depthStencilState, 0);
            context.Rasterizer.State = rasterizerState;
            context.PixelShader.SetSampler(samplerState, 0);
        }

        public unsafe void UpdateShaderConstants(DeviceContext context, RectangleF* clipRect, Matrix* transform)
        {
            var constants = new ShaderConstants();
            if (transform != null)
                constants.Transform = *transform;
            else
            {
                float w = 512.0f;
                float h = 512.0f;

                var vp = context.Rasterizer.GetViewport();
                if (vp.Width >= 1.0f && vp.Height >= 1.0f)
                {
                    w = vp.Width;
                    h = vp.Height;
                }

                constants.Transform = Matrix.OrthoOffCenterLH(0.0f, w, h, 0.0f, 0.0f, 1.0f);
            }

            if (clipRect != null)
            {
                constants.ClipRect = *clipRect;
                constants.ClipRect.X *= -1;
                constants.ClipRect.Y *= -1;
            }
            else
            {
                constants.ClipRect.X = float.MaxValue;
                constants.ClipRect.Y = float.MaxValue;
                constants.ClipRect.Width = float.MaxValue;
                constants.ClipRect.Height = float.MaxValue;
            }

            constantBuffer.SetData(context, ref constants);
        }

        void CreateQuadShaders()
        {
            // compile vertex shaders
            using (var bytecode = ShaderBytecode.Compile(FontShaders.SimpleVertexShader, "VS", device.VertexShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
            {
                simpleVertexShader = new VertexShader(device, bytecode);
                inputLayout = new InputLayout(device, bytecode, new[] {
                    new InputElement("POSITION", 0, Format.R32G32B32A32_Float, 0),
                    new InputElement("GLYPHCOLOR", 0, Format.R8G8B8A8_UNorm, 0)
                });
            }

            using (var bytecode = ShaderBytecode.Compile(FontShaders.ClippingVertexShader, "VS", device.VertexShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
                clippingVertexShader = new VertexShader(device, bytecode);

            resources.Add(simpleVertexShader);
            resources.Add(inputLayout);
            resources.Add(clippingVertexShader);
        }

        void CreatePixelShaders()
        {
            // compile pixel shaders
            using (var bytecode = ShaderBytecode.Compile(FontShaders.SimplePixelShader, "PS", device.PixelShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
                simplePixelShader = new PixelShader(device, bytecode);

            using (var bytecode = ShaderBytecode.Compile(FontShaders.ClippingPixelShader, "PS", device.PixelShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
                clippingPixelShader = new PixelShader(device, bytecode);

            resources.Add(simplePixelShader);
            resources.Add(clippingPixelShader);
        }

        void CreateConstantBuffer()
        {
            constantBuffer = new ConstantBuffer<ShaderConstants>(device);
            resources.Add(constantBuffer);
        }

        void CreateRenderStates(bool anisotropicFiltering)
        {
            var blendDesc = new BlendStateDescription();
            for (int i = 0; i < 4; i++)
            {
                blendDesc.RenderTargets[i] = new RenderTargetBlendDescription
                {
                    BlendEnable = true,
                    SourceBlend = BlendOption.One,
                    DestinationBlend = BlendOption.InverseSourceAlpha,
                    BlendOperation = BlendOperation.Add,
                    SourceBlendAlpha = BlendOption.One,
                    DestinationBlendAlpha = BlendOption.Zero,
                    BlendOperationAlpha = BlendOperation.Add,
                    RenderTargetWriteMask = ColorWriteMaskFlags.All
                };
            }

            blendState = BlendState.FromDescription(device, blendDesc);
            samplerState = SamplerState.FromDescription(device, new SamplerDescription
            {
                AddressU = TextureAddressMode.Clamp,
                AddressV = TextureAddressMode.Clamp,
                AddressW = TextureAddressMode.Clamp,
                MaximumLod = float.MaxValue,
                Filter = anisotropicFiltering ? Filter.Anisotropic : Filter.MinMagMipLinear,
                MaximumAnisotropy = anisotropicFiltering ? featureLevel >= FeatureLevel.Level_9_2 ? 5 : 2 : 0
            });

            rasterizerState = RasterizerState.FromDescription(device, new RasterizerStateDescription
            {
                FillMode = FillMode.Solid,
                CullMode = CullMode.None,
                IsFrontCounterclockwise = false,
                IsDepthClipEnabled = true
            });

            depthStencilState = DepthStencilState.FromDescription(device, new DepthStencilStateDescription
            {
                IsDepthEnabled = false
            });

            resources.Add(blendState);
            resources.Add(samplerState);
            resources.Add(rasterizerState);
            resources.Add(depthStencilState);
        }
    }
}

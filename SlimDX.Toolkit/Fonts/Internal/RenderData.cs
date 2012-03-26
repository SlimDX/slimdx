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
    /// <summary>
    /// Contains D3D resources used for rendering fonts. Shared between fonts.
    /// </summary>
    class RenderData : IDisposable
    {
        const string ResourcePath = "SlimDX.Toolkit.Shaders.Compiled.";

        [StructLayout(LayoutKind.Sequential)]
        struct ShaderConstants
        {
            public Matrix Transform;
            public RectangleF ClipRect;
        }

        FeatureLevel featureLevel;
        VertexShader simpleVertexShader;
        VertexShader clippingVertexShader;
        PixelShader simplePixelShader;
        PixelShader clippingPixelShader;
        InputLayout inputLayout;
        ConstantBuffer<ShaderConstants> constantBuffer;
        CommonStates states;
        bool disposed;

        public RenderData(Device device)
        {
            featureLevel = device.FeatureLevel;

            // compile vertex shaders
            using (var bytecode = ShaderBytecode.LoadResource(typeof(RenderData).Assembly, ResourcePath + "SimpleFontEffect_VS.fxo"))
            {
                simpleVertexShader = new VertexShader(device, bytecode);
                inputLayout = new InputLayout(device, bytecode, new[] {
                    new InputElement("POSITION", 0, Format.R32G32B32A32_Float, 0),
                    new InputElement("GLYPHCOLOR", 0, Format.R8G8B8A8_UNorm, 0)
                });
            }

            using (var bytecode = ShaderBytecode.LoadResource(typeof(RenderData).Assembly, ResourcePath + "ClippingFontEffect_VS.fxo"))
                clippingVertexShader = new VertexShader(device, bytecode);

            // compile pixel shaders
            using (var bytecode = ShaderBytecode.LoadResource(typeof(RenderData).Assembly, ResourcePath + "SimpleFontEffect_PS.fxo"))
                simplePixelShader = new PixelShader(device, bytecode);

            using (var bytecode = ShaderBytecode.LoadResource(typeof(RenderData).Assembly, ResourcePath + "ClippingFontEffect_PS.fxo"))
                clippingPixelShader = new PixelShader(device, bytecode);

            constantBuffer = new ConstantBuffer<ShaderConstants>(device);
            states = new CommonStates(device);
        }

        public void Dispose()
        {
            if (disposed)
                return;

            disposed = true;

            simpleVertexShader.Dispose();
            clippingVertexShader.Dispose();
            simplePixelShader.Dispose();
            clippingPixelShader.Dispose();
            inputLayout.Dispose();
            constantBuffer.Dispose();
            states.Dispose();
        }

        public void SetStates(DeviceContext context, bool anisotropicFiltering, TextOptions flags)
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
            context.OutputMerger.SetBlendState(states.AlphaBlend, new Color4(0), -1);
            context.OutputMerger.SetDepthStencilState(states.DepthNone, 0);
            context.Rasterizer.State = states.CullNone;
            context.PixelShader.SetSampler(anisotropicFiltering ? states.AnisotropicClamp : states.LinearClamp, 0);
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
    }
}

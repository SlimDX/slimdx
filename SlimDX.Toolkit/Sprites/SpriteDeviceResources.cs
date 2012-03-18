using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;
using Buffer = SlimDX.Direct3D11.Buffer;
using SlimDX.D3DCompiler;

namespace SlimDX.Toolkit
{
    class SpriteDeviceResources : IDisposable
    {
        public VertexShader VertexShader;
        public PixelShader PixelShader;
        public InputLayout InputLayout;
        public Buffer IndexBuffer;

        public SpriteDeviceResources(Device device)
        {
            using (var bytecode = ShaderBytecode.Compile(SpriteShaders.VertexShader, "VS", device.VertexShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
            {
                VertexShader = new VertexShader(device, bytecode);
            }
        }

        public void Dispose()
        {
        }
    }
}

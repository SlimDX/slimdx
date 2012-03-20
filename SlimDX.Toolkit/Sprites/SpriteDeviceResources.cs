using System;
using SlimDX.D3DCompiler;
using SlimDX.Direct3D11;
using SlimDX.Toolkit.VertexTypes;
using Buffer = SlimDX.Direct3D11.Buffer;

namespace SlimDX.Toolkit
{
    // contains shared resources that are associated with a particular device
    class SpriteDeviceResources : IDisposable
    {
        public VertexShader VertexShader;
        public PixelShader PixelShader;
        public InputLayout InputLayout;
        public Buffer IndexBuffer;
        public CommonStates States;

        public SpriteDeviceResources(Device device, int maxBatchSize)
        {
            // create the vertex shader and input layout
            using (var bytecode = ShaderBytecode.Compile(SpriteShaders.VertexShader, "VS", device.VertexShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
            {
                VertexShader = new VertexShader(device, bytecode);
                InputLayout = new InputLayout(device, bytecode, InputElementFactory.DemandCreate(typeof(VertexPositionColorTexture)));
            }

            // create the pixel shader
            using (var bytecode = ShaderBytecode.Compile(SpriteShaders.PixelShader, "PS", device.PixelShaderProfile, ShaderFlags.OptimizationLevel3, EffectFlags.None))
                PixelShader = new PixelShader(device, bytecode);

            // generate indices for simple quads
            int size = maxBatchSize * SpriteBatch.IndicesPerSprite * sizeof(short);
            var indices = new DataStream(size, true, true);
            for (short i = 0; i < maxBatchSize * SpriteBatch.VerticesPerSprite; i += SpriteBatch.VerticesPerSprite)
            {
                indices.Write(i);
                indices.Write(i + 1);
                indices.Write(i + 2);

                indices.Write(i + 1);
                indices.Write(i + 3);
                indices.Write(i + 2);
            }

            // create the index buffer
            indices.Position = 0;
            IndexBuffer = new Buffer(device, indices, new BufferDescription
            {
                SizeInBytes = size,
                BindFlags = BindFlags.IndexBuffer,
                Usage = ResourceUsage.Default
            });

            States = new CommonStates(device);
        }

        public void Dispose()
        {
            VertexShader.Dispose();
            PixelShader.Dispose();
            InputLayout.Dispose();
            IndexBuffer.Dispose();
            States.Dispose();
        }
    }
}

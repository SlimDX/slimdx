using System;
using SlimDX.Direct3D11;
using SlimDX.Toolkit.VertexTypes;
using SlimMath;
using Buffer = SlimDX.Direct3D11.Buffer;

namespace SlimDX.Toolkit
{
    // contains shared resources that are associated with a particular device context
    class SpriteContextResources : IDisposable
    {
        const int VerticesPerSprite = 4;

        public bool InImmediateMode;
        public int VertexBufferPosition;
        public Buffer VertexBuffer;
        public ConstantBuffer<Matrix> ConstantBuffer;

        public SpriteContextResources(DeviceContext context, int maxBatchSize)
        {
            // create a dynamic write-only constant buffer for the sprite transform
            ConstantBuffer = new ConstantBuffer<Matrix>(context.Device);

            // create a dynamic write-only vertex buffer for the sprite vertices, limited by maxBatchSize
            VertexBuffer = new Buffer(context.Device, new BufferDescription
            {
                SizeInBytes = VertexPositionColorTexture.SizeInBytes * maxBatchSize * VerticesPerSprite,
                BindFlags = BindFlags.VertexBuffer,
                Usage = ResourceUsage.Dynamic,
                CpuAccessFlags = CpuAccessFlags.Write
            });
        }

        public void Dispose()
        {
            VertexBuffer.Dispose();
            ConstantBuffer.Dispose();
        }
    }
}

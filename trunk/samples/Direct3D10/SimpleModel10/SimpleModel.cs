using System;
using SlimDX;
using SlimDX.Direct3D10;
using SlimDX.DXGI;
using SlimDX.SampleFramework;
using Buffer=SlimDX.Direct3D10.Buffer;
using Device=SlimDX.Direct3D10.Device;
using PrimitiveTopology=SlimDX.Direct3D10.PrimitiveTopology;

namespace SimpleModel10 {
    class SimpleMesh : IDisposable {
        public SimpleMesh(Device device, MeshData meshData) {
            this.device = device;

            using (var data = new DataStream(meshData.Indices.ToArray(), true, false)) {
                indices = new Buffer(device, data, new BufferDescription(meshData.Indices.Count * 4, ResourceUsage.Default, BindFlags.IndexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None));
                indexCount = meshData.Indices.Count;
            }

            using (var data = new DataStream(meshData.Positions.ToArray(), true, false)) {
                vertices = new Buffer(device, data, new BufferDescription(meshData.Positions.Count * 4 * 3, ResourceUsage.Default, BindFlags.VertexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None));
            }
            using (var data = new DataStream(meshData.Normals.ToArray(), true, false)) {
                normals = new Buffer(device, data, new BufferDescription(meshData.Normals.Count * 4 * 3, ResourceUsage.Default, BindFlags.VertexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None));
            }

            using (var data = new DataStream(meshData.TextureCoordinates.ToArray(), true, false)) {
                texCoords = new Buffer(device, data, new BufferDescription(meshData.TextureCoordinates.Count * 4 * 2, ResourceUsage.Default, BindFlags.VertexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None));
            }

            Elements = new[] {
                new InputElement("POSITION", 0, Format.R32G32B32_Float, 0, 0), 
                new InputElement("NORMAL", 0, Format.R32G32B32_Float, 0, 1), 
                new InputElement("TEXCOORD", 0, Format.R32G32_Float, 0, 2)
            };
        }

        public void Draw() {
            device.InputAssembler.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
            device.InputAssembler.SetIndexBuffer(indices, Format.R32_UInt, 0);
            device.InputAssembler.SetVertexBuffers(0, new[] {
                new VertexBufferBinding(vertices, 12, 0),
                new VertexBufferBinding(normals, 12, 0),
                new VertexBufferBinding(texCoords, 8, 0)
            });

            device.DrawIndexed(indexCount, 0, 0);

            device.InputAssembler.SetIndexBuffer(null, Format.Unknown, 0);
            device.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding[3]);
        }

        public void Dispose() {
            indices.Dispose();
            normals.Dispose();
            vertices.Dispose();
            texCoords.Dispose();
        }

        public InputElement[] Elements { get; private set; }

        private readonly Device device;
        private readonly Buffer indices;
        private readonly int indexCount;
        private readonly Buffer normals;
        private readonly Buffer vertices;
        private readonly Buffer texCoords;
    }
}

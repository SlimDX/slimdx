using System;
using System.Collections.Generic;
using SlimDX.Direct3D11;
using SlimDX.DXGI;
using SlimMath;
using Buffer = SlimDX.Direct3D11.Buffer;
using Device = SlimDX.Direct3D11.Device;
using MapFlags = SlimDX.Direct3D11.MapFlags;
using System.Runtime.InteropServices;
using System.Drawing;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Handles the drawing of glyphs to textured quads.
    /// </summary>
    class VertexDrawer : IDisposable
    {
        static SharedResourcePool<Device, RenderData> sharedRenderData = new SharedResourcePool<Device, RenderData>();

        [StructLayout(LayoutKind.Sequential)]
        struct QuadVertex
        {
            public static readonly int SizeInBytes = Marshal.SizeOf(typeof(QuadVertex));

            public Vector2 Position;
            public Vector2 TexCoords;
            public int Color;
        }

        ISharedResource<RenderData> renderData;
        Buffer vertexBuffer;
        Buffer indexBuffer;
        int bufferSize = 4096 * 16;
        int maxIndexCount;

        public VertexDrawer(Device device, int vertexBufferSize)
        {
            if (vertexBufferSize >= 1024)
            {
                if (device.FeatureLevel < FeatureLevel.Level_9_2)
                    vertexBufferSize = Math.Min(vertexBufferSize, 512 * 1024);
                bufferSize = vertexBufferSize;
            }

            maxIndexCount = (bufferSize * 3) / (2 * QuadVertex.SizeInBytes);
            if (maxIndexCount < 64)
                maxIndexCount = 64;

            vertexBuffer = new Buffer(device, new BufferDescription
            {
                SizeInBytes = bufferSize,
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.VertexBuffer,
                CpuAccessFlags = CpuAccessFlags.Write
            });

            using (var indices = new DataStream(sizeof(short) * maxIndexCount, true, true))
            {
                for (int i = 0; i < maxIndexCount / 6; i++)
                {
                    indices.Write((short)(i * 4));
                    indices.Write((short)(i * 4 + 1));
                    indices.Write((short)(i * 4 + 2));
                    indices.Write((short)(i * 4 + 1));
                    indices.Write((short)(i * 4 + 3));
                    indices.Write((short)(i * 4 + 2));
                }

                indices.Position = 0;
                indexBuffer = new Buffer(device, indices, new BufferDescription
                {
                    SizeInBytes = sizeof(short) * maxIndexCount,
                    Usage = ResourceUsage.Immutable,
                    BindFlags = BindFlags.IndexBuffer
                });
            }

            renderData = sharedRenderData.DemandCreate(device, () => new RenderData(device));
        }

        public void Dispose()
        {
            if (vertexBuffer != null)
                vertexBuffer.Dispose();
            if (indexBuffer != null)
                indexBuffer.Dispose();
            if (renderData != null)
                renderData.Release();

            vertexBuffer = null;
            indexBuffer = null;
            renderData = null;
        }

        public unsafe void DrawVertices(DeviceContext context, GlyphAtlas glyphAtlas, IList<Glyph> glyphs, bool anisotropic, RectangleF* clipBounds, Matrix* transformMatrix, TextOptions flags)
        {
            // set states and shaders
            if ((flags & TextOptions.StatePrepared) == 0)
                renderData.Resource.SetStates(context, anisotropic, flags);
            if ((flags & TextOptions.ConstantsPrepared) == 0)
                renderData.Resource.UpdateShaderConstants(context, clipBounds, transformMatrix);

            if ((flags & TextOptions.BuffersPrepared) == 0)
            {
                context.InputAssembler.SetIndexBuffer(indexBuffer, Format.R16_UInt, 0);
                context.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, QuadVertex.SizeInBytes, 0));
            }

            int maxVertexCount = bufferSize / QuadVertex.SizeInBytes;
            if (maxVertexCount > 4 * (maxIndexCount / 6))
                maxVertexCount = 4 * (maxIndexCount / 6);
            if (maxVertexCount % 4 != 0)
                maxVertexCount -= (maxVertexCount % 4);

            int current = 0;
            int total = glyphs.Count;

            // draw every glyph as a 2-tri quad
            while (current < total)
            {
                var data = context.MapSubresource(vertexBuffer, MapMode.WriteDiscard, MapFlags.None).Data;

                // figure out the number of vertices we can draw in this "pass" (limited by the size of the vertex buffer)
                int count = Math.Min(total - current, maxVertexCount / 4);
                for (int i = 0; i < count; i++)
                {
                    var glyph = glyphs[current + i];
                    var output = new QuadVertex();
                    output.Color = glyph.Color;
                    output.Position = glyph.Position + new Vector2(glyph.PositionOffsets.Left, glyph.PositionOffsets.Top);
                    output.TexCoords = new Vector2(glyph.TextureCoordinates.Left, glyph.TextureCoordinates.Top);
                    data.Write(output);

                    output.Position.X = glyph.Position.X + glyph.PositionOffsets.Right;
                    output.TexCoords.X = glyph.TextureCoordinates.Right;
                    data.Write(output);

                    output.Position.Y = glyph.Position.Y + glyph.PositionOffsets.Bottom;
                    output.TexCoords.Y = glyph.TextureCoordinates.Bottom;
                    data.Write(output);

                    output.Position.X = glyph.Position.X + glyph.PositionOffsets.Left;
                    output.TexCoords.X = glyph.TextureCoordinates.Left;
                    data.Write(output);
                }

                context.UnmapSubresource(vertexBuffer, 0);

                // now draw the vertices (one draw call per sheet)
                int currentSheet = -1;
                int sheetCount = 0;
                int drawn = 0;

                for (int i = 0; i < count; i++)
                {
                    int sheet = glyphs[current + i].SheetIndex;
                    if (sheet != currentSheet)
                    {
                        if (sheetCount != 0)
                        {
                            glyphAtlas.BindSheet(context, currentSheet);
                            context.DrawIndexed(sheetCount * 6, 0, drawn);
                            drawn += sheetCount * 4;
                        }

                        sheetCount = 0;
                        currentSheet = sheet;
                    }

                    sheetCount++;
                }

                current += count;
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using SlimMath;
using SlimDX.Direct3D11;
using Buffer = SlimDX.Direct3D11.Buffer;
using Device = SlimDX.Direct3D11.Device;
using MapFlags = SlimDX.Direct3D11.MapFlags;
using SlimDX.DXGI;

namespace SlimDX.Toolkit.Fonts
{
    [StructLayout(LayoutKind.Sequential)]
    struct QuadVertex
    {
        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(QuadVertex));

        public Vector2 Position;
        public Vector2 TexCoords;
        public int Color;
    }

    class VertexDrawer : IDisposable
    {
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

            CreateBuffers(device);
        }

        public void Dispose()
        {
            if (vertexBuffer != null)
                vertexBuffer.Dispose();

            if (indexBuffer != null)
                indexBuffer.Dispose();

            vertexBuffer = null;
            indexBuffer = null;
        }

        public void DrawVertices(DeviceContext context, GlyphAtlas glyphAtlas, VertexData vertexData, TextOptions flags)
        {
            int stride = 0;
            if ((flags & TextOptions.NoGeometryShader) == 0)
                stride = GlyphVertex.SizeInBytes;
            else
            {
                stride = QuadVertex.SizeInBytes;
                if ((flags & TextOptions.BuffersPrepared) == 0)
                    context.InputAssembler.SetIndexBuffer(indexBuffer, Format.R16_UInt, 0);
            }

            if ((flags & TextOptions.BuffersPrepared) == 0)
                context.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, stride, 0));

            if ((flags & TextOptions.NoGeometryShader) == 0)
                DrawVertices(context, glyphAtlas, vertexData);
            else
                DrawQuads(context, glyphAtlas, vertexData);
        }

        void DrawVertices(DeviceContext context, GlyphAtlas glyphAtlas, VertexData vertexData)
        {
            int total = vertexData.Vertices.Length;
            if (vertexData.VertexCounts.Length == 0 || total == 0)
                return;

            int maxVertexCount = bufferSize / GlyphVertex.SizeInBytes;
            int currentSheet = 0;
            int activeSheet = int.MaxValue;
            int currentVertex = 0;
            int nextSheet = vertexData.VertexCounts[0];

            // draw all vertices
            while (currentVertex < total)
            {
                // fill the vertex buffer
                int count = Math.Min(total - currentVertex, maxVertexCount);
                var box = context.MapSubresource(vertexBuffer, MapMode.WriteDiscard, MapFlags.None);
                box.Data.WriteRange(vertexData.Vertices, currentVertex, count);
                context.UnmapSubresource(vertexBuffer, 0);

                // draw all glyphs in the buffer
                int drawnVertices = 0;
                while (drawnVertices < count)
                {
                    while (currentVertex >= nextSheet)
                    {
                        currentSheet++;
                        nextSheet += vertexData.VertexCounts[currentSheet];
                    }

                    // bind sheet shaders
                    if (currentSheet != activeSheet)
                    {
                        glyphAtlas.BindSheet(context, currentSheet, 0);
                        activeSheet = currentSheet;
                    }

                    int drawCount = Math.Min(count - drawnVertices, nextSheet - currentVertex);
                    context.Draw(drawCount, drawnVertices);

                    drawnVertices += drawCount;
                    currentVertex += drawCount;
                }
            }
        }

        void DrawQuads(DeviceContext context, GlyphAtlas glyphAtlas, VertexData vertexData)
        {
            int total = vertexData.Vertices.Length;
            if (vertexData.VertexCounts.Length == 0 || total == 0)
                return;

            int maxVertexCount = bufferSize / QuadVertex.SizeInBytes;
            if (maxVertexCount > 4 * (maxIndexCount / 6))
                maxVertexCount = 4 * (maxIndexCount / 6);
            if (maxVertexCount % 4 != 0)
                maxVertexCount -= (maxVertexCount % 4);

            GlyphCoords[] sheetCoords = null;
            int currentSheet = 0;
            int activeSheet = int.MaxValue;
            int currentVertex = 0;
            int nextSheet = vertexData.VertexCounts[0];

            // draw all vertices
            while (currentVertex < total)
            {
                // fill the vertex buffer
                int count = Math.Min((total - currentVertex) * 4, maxVertexCount);
                var box = context.MapSubresource(vertexBuffer, MapMode.WriteDiscard, MapFlags.None);

                // convert to quads
                int savedCurrentSheet = currentSheet;
                int savedActiveSheet = activeSheet;
                int savedNextSheetStart = nextSheet;
                int savedCurrentVertex = currentVertex;

                int drawnVertices = 0;
                while (drawnVertices < count)
                {
                    while (currentVertex >= nextSheet)
                    {
                        currentSheet++;
                        nextSheet += vertexData.VertexCounts[currentSheet];
                    }

                    // bind sheet shaders
                    if (currentSheet != activeSheet)
                    {
                        sheetCoords = glyphAtlas.GetGlyphCoords(currentSheet);
                        activeSheet = currentSheet;
                    }

                    int drawCount = Math.Min(count - drawnVertices, (nextSheet - currentVertex) * 4);
                    for (int i = 0; i < drawCount / 4; i++)
                    {
                        var vertex = vertexData.Vertices[currentVertex + i];
                        var coords = sheetCoords[vertex.GlyphIndex];

                        var output = new QuadVertex();
                        output.Color = vertex.Color;
                        output.Position = vertex.Position + new Vector2(coords.PositionLeft, coords.PositionTop);
                        output.TexCoords = new Vector2(coords.TexCoordLeft, coords.TexCoordTop);
                        box.Data.Write(output);

                        output.Position.X = vertex.Position.X + coords.PositionRight;
                        output.TexCoords.X = coords.TexCoordRight;
                        box.Data.Write(output);

                        output.Position.Y = vertex.Position.Y + coords.PositionBottom;
                        output.TexCoords.Y = coords.TexCoordBottom;
                        box.Data.Write(output);

                        output.Position.X = vertex.Position.X + coords.PositionLeft;
                        output.TexCoords.X = coords.TexCoordLeft;
                        box.Data.Write(output);
                    }

                    drawnVertices += drawCount;
                    currentVertex += drawCount / 4;
                }

                context.UnmapSubresource(vertexBuffer, 0);

                // draw all glyphs in the buffer
                currentSheet = savedCurrentSheet;
                activeSheet = savedActiveSheet;
                nextSheet = savedNextSheetStart;
                currentVertex = savedCurrentVertex;
                drawnVertices = 0;

                while (drawnVertices < count)
                {
                    while (currentVertex >= nextSheet)
                    {
                        currentSheet++;
                        nextSheet += vertexData.VertexCounts[currentSheet];
                    }

                    // bind sheet shaders
                    if (currentSheet != activeSheet)
                    {
                        glyphAtlas.BindSheet(context, currentSheet, TextOptions.NoGeometryShader);
                        activeSheet = currentSheet;
                    }

                    int drawCount = Math.Min(count - drawnVertices, (nextSheet - currentVertex) * 4);
                    context.DrawIndexed((drawCount / 2) * 3, 0, drawnVertices);

                    drawnVertices += drawCount;
                    currentVertex += drawCount / 4;
                }
            }
        }

        void CreateBuffers(Device device)
        {
            vertexBuffer = new Buffer(device, new BufferDescription
            {
                SizeInBytes = bufferSize,
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.VertexBuffer,
                CpuAccessFlags = CpuAccessFlags.Write
            });

            var indices = new DataStream(sizeof(short) * maxIndexCount, true, true);
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

            indices.Dispose();
        }
    }
}

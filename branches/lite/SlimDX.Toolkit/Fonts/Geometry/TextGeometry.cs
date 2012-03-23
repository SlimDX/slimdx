using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Toolkit.Fonts
{
    /// <summary>
    /// Maintains the geometry for a set of glyphs.
    /// </summary>
    class TextGeometry
    {
        List<GlyphVertex> vertices = new List<GlyphVertex>();
        GlyphVertex[] sortedVertices;
        int[] vertexCounts;
        int maxSheetIndex;
        bool sorted;

        public void Clear()
        {
            vertices.Clear();
            maxSheetIndex = 0;
            sorted = false;
        }

        public void AddVertex(GlyphVertex vertex)
        {
            vertices.Add(vertex);
            maxSheetIndex = Math.Max(maxSheetIndex, vertex.GlyphIndex >> 16);
            sorted = false;
        }

        public VertexData GetGlyphVertices()
        {
            var result = new VertexData();
            if (vertices.Count == 0)
                return result;

            int sheetCount = maxSheetIndex + 1;
            if (!sorted)
            {
                // sort the vertices and keep track of counts for each sheet
                sortedVertices = new GlyphVertex[vertices.Count];
                vertexCounts = new int[sheetCount];
                var indices = new int[sheetCount];
                foreach (var vertex in vertices)
                    vertexCounts[vertex.GlyphIndex >> 16]++;

                int currentIndex = 0;
                for (int i = 0; i < sheetCount; i++)
                {
                    indices[i] = currentIndex;
                    currentIndex += vertexCounts[i];
                }

                foreach (var vertex in vertices)
                {
                    int sheetIndex = vertex.GlyphIndex >> 16;
                    int index = indices[sheetIndex];
                    sortedVertices[index] = vertex;
                    sortedVertices[index].GlyphIndex &= 0xffff;

                    indices[sheetIndex]++;
                }

                sorted = true;
            }

            result.VertexCounts = vertexCounts;
            result.Vertices = sortedVertices;

            return result;
        }
    }
}

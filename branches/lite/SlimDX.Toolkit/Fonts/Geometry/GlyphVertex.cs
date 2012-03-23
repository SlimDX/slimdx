using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimMath;
using System.Runtime.InteropServices;

namespace SlimDX.Toolkit.Fonts
{
    struct GlyphVertex
    {
        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(GlyphVertex));

        public Vector2 Position;
        public int GlyphIndex;
        public int Color;
    }

    struct VertexData
    {
        public int[] VertexCounts;
        public GlyphVertex[] Vertices;
    }
}

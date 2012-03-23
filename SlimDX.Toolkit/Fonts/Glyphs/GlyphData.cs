using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SlimDX.Toolkit.Fonts
{
    struct GlyphBounds
    {
        public float OffsetX;
        public float OffsetY;
        public int Width;
        public int Height;
    }

    struct GlyphCoords
    {
        public static readonly int SizeInBytes = Marshal.SizeOf(typeof(GlyphCoords));

        public float TexCoordLeft;
        public float TexCoordTop;
        public float TexCoordRight;
        public float TexCoordBottom;
        public float PositionLeft;
        public float PositionTop;
        public float PositionRight;
        public float PositionBottom;
    };

    class GlyphImageData
    {
        public GlyphBounds Metrics;
        public IntPtr GlyphPixels;
        public int RowPitch;
        public int PixelStride;
    };
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using SlimMath;
using SlimDX.Direct3D11;

namespace SlimDX.Toolkit
{
    // 80-byte sprite structure. The padding is to maintain a 16-byte alignment.
    [StructLayout(LayoutKind.Sequential, Size = 80)]
    struct SpriteInfo
    {
        public Vector4 Source;
        public Vector4 Destination;
        public Color4 Color;
        public Vector4 OriginRotationDepth;
        public int Texture;
        public int Flags;
    }
}

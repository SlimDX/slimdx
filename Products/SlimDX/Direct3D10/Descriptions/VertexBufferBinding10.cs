using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public struct VertexBufferBinding10 {
        public VertexBufferBinding10(IBuffer10 buffer, int stride, int offset) {
            VertexBuffer = buffer;
            Stride = stride;
            Offset = offset;
        }

        public IBuffer10 VertexBuffer;
        public int Stride;
        public int Offset;
    }
}

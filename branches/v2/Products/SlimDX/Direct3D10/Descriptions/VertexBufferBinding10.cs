using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public struct VertexBufferBinding {
        public VertexBufferBinding(IBuffer buffer, int stride, int offset) {
            VertexBuffer = buffer;
            Stride = stride;
            Offset = offset;
        }

        public IBuffer VertexBuffer;
        public int Stride;
        public int Offset;
    }
}

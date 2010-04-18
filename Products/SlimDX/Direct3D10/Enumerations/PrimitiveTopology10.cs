using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public enum PrimitiveTopology {
        Undefined                   = 0,
        PointList                   = 1,
        LineList                    = 2,
        LineStrip                   = 3,
        TriangleList                = 4,
        TriangleStrip               = 5,
        LineListWithAdjacency       = 10,
        LineStripWithAdjacency      = 11,
        TriangleListWithAdjacency   = 12,
        TriangleStripWithAdjacency  = 13
    }
}

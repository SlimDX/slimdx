using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public enum InputClassification {
        VertexData = 0,
        InstanceData = 1
    }

    public struct InputElement {
        public string Name;
        public int Index;
        public DXGI.Format Format;
        public int Slot;
        public int AlignedByteOffset;
        public InputClassification InputClassification;
        public int InstanceDataStep;
    }
}

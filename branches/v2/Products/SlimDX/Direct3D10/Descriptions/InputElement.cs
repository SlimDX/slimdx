using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public enum InputClassification10 {
        VertexData = 0,
        InstanceData = 1
    }

    public struct InputElement10 {
        public string Name;
        public int Index;
        public DXGI.Format Format;
        public int Slot;
        public int AlignedByteOffset;
        public InputClassification10 InputClassification;
        public int InstanceDataStep;
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    public struct EffectPassDescription10 {
        public string Name { get; set; }
        public int Annotations { get; set; }
        public ShaderSignature10 ShaderSignature { get; set; }
        public int StencilRef { get; set; }
        public int SampleMask { get; set; }
        public float BlendFactorR { get; set; }
        public float BlendFactorG { get; set; }
        public float BlendFactorB { get; set; }
        public float BlendFactorA { get; set; }
    }

    public struct ShaderSignature10 {
        public IntPtr Signature { get; set; }
        public int SignatureLength { get; set; }
    }
}

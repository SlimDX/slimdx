using System;

namespace SlimDX.Direct3D10 {
    [Flags]
    public enum EffectFlags10 {
        None = 0,
        ChildEffect = (1 << 0),
        AllowSlowOps = (1 << 1),
        SingleThreaded = (1 << 3)
    };
}
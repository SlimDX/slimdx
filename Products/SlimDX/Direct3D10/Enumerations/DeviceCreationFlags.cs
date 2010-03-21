using System;

namespace SlimDX.Direct3D10 {
    [Flags]
    public enum DeviceCreationFlags : int {
       SingleThreaded = 0x1,
       Debug = 0x2,
       SwitchToReference = 0x4,
       PreventInternalThreadingOptimizations = 0x8,
       AllowNullFromMap = 0x10,
       BgraSupport = 0x20,
       StrictValidation = 0x200,
    }
}

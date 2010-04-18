using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.Direct3D10 {
    [Flags]
    public enum OptionFlags {
        None                = 0x00,
        GenerateMipmaps     = 0x01,
        Shared              = 0x02,
        TextureCube         = 0x04,
        SharedKeyedMutex    = 0x10,
        GdiCompatible       = 0x20
    }
}

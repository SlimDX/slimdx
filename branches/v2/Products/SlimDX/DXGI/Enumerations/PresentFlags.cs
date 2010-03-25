using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SlimDX.DXGI {
    public enum PresentFlags : int {
        None,
        Test = 0x1,
        DoNotSequence = 0x2,
        Restart = 0x4
    }
}

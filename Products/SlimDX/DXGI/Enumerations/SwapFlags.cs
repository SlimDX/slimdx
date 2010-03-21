using System;

namespace SlimDX.DXGI {
    /// <summary>
    ///
    /// </summary>
    [Flags]
    public enum SwapChainFlags : int {
        /// <summary>
        /// 
        /// </summary>
        None = 0,

        /// <summary>
        /// 
        /// </summary>
        NonPreRotated = 1,

        /// <summary>
        /// 
        /// </summary>
        AllowModeSwitch = 2,

        /// <summary>
        /// 
        /// </summary>
        GdiCompatible = 4,
    }
}

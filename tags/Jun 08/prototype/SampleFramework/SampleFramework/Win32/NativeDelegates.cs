using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Provides a delegate for low leve keyboard procedures.
    /// </summary>
    /// <param name="nCode">The hook code.</param>
    /// <param name="wParam">The first generic parameter.</param>
    /// <param name="lParam">The second generic parameter.</param>
    /// <returns>The next hook in the chain.</returns>
    delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);
}

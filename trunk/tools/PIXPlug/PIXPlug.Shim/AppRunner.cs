using System;
using System.Collections.Generic;
using System.Text;

namespace PIXPlug.Shim
{
    public static class AppRunner
    {
        public static int Start(string path)
        {
            return AppDomain.CurrentDomain.ExecuteAssembly(path);
        }
    }
}

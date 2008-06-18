using System;
using System.Collections.Generic;
using System.Text;
using SampleFramework;
using SlimDX.Direct3D9;
using System.Drawing;
using SlimDX;
using System.Windows.Forms;

namespace SimpleLighting
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            using (SimpleLighting sample = new SimpleLighting())
                sample.Run();
        }
    }
    
}

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace SampleFramework.Particles
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Particles part = new Particles();

            part.Run();
        }
    }
}

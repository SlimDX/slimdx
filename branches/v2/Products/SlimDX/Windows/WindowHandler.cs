using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SlimDX.Windows
{
    class WindowHandler : NativeWindow
    {
        MessageHandler wndproc;

        public delegate bool MessageHandler(ref Message m);

        public WindowHandler(MessageHandler messageHandler)
        {
            wndproc = messageHandler;
        }

        protected override void WndProc(ref Message m)
        {
            if (!wndproc(ref m))
                base.WndProc(ref m);
        }
    }
}

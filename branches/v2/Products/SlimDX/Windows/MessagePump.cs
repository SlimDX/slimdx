using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SlimDX.Windows
{
    public delegate void MessageLoop();

    public static class MessagePump
    {
        public static int Run(IWin32Window window, MessageLoop messageLoop)
        {
            if (window == null)
                throw new ArgumentNullException("window");
            if (messageLoop == null)
                throw new ArgumentNullException("messageLoop");

            IntPtr handle = window.Handle;
            if (window.Handle == IntPtr.Zero || !NativeMethods.IsWindow(handle))
                throw new InvalidOperationException("Window handle not yet created.");

            var msg = new NativeMessage();
            NativeMethods.ShowWindow(handle, Win32Interop.SW_SHOWNORMAL);

            while (NativeMethods.IsWindow(handle))
            {
                if (NativeMethods.PeekMessage(out msg, handle, 0, 0, Win32Interop.PM_REMOVE))
                {
                    if (msg.msg == WindowMessages.WM_QUIT)
                    {
                        NativeMethods.DestroyWindow(handle);
                        break;
                    }

                    NativeMethods.TranslateMessage(ref msg);
                    NativeMethods.DispatchMessage(ref msg);
                }
                else
                    messageLoop();
            }

            GC.KeepAlive(window);
            return msg.wParam.ToInt32();
        }

        public static void Exit()
        {
            Exit(0);
        }

        public static void Exit(int exitCode)
        {
            NativeMethods.PostQuitMessage(exitCode);
        }
    }
}

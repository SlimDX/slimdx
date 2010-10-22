// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Runtime.InteropServices;
using System.Security;
using System.Windows.Forms;

namespace SlimDX2.Windows
{
    public delegate void MainLoop();

    public sealed class MessagePump
    {
        private MessagePump()
        {
        }

        public static void Run(MainLoop mainLoop)
        {
            Application.Idle += new EventHandler(new IdleHandler(mainLoop).OnIdle);
            Application.Run();
        }

        public static void Run(ApplicationContext context, MainLoop mainLoop)
        {
            Application.Idle += new EventHandler(new IdleHandler(mainLoop).OnIdle);
            Application.Run(context);
        }

        public static void Run(Form form, MainLoop mainLoop)
        {
            Application.Idle += new EventHandler(new IdleHandler(mainLoop).OnIdle);
            Application.Run(form);
        }

        public static bool IsApplicationIdle
        {
            get
            {
                NativeMessage msg;
                return (bool) (PeekMessage(out msg, IntPtr.Zero, 0, 0, 0) == 0);
            }
        }

        private class IdleHandler
        {
            private MainLoop loopDelegate;

            public IdleHandler(MainLoop mainLoop)
            {
                this.loopDelegate = mainLoop;
            }

            public void OnIdle(object sender, EventArgs e)
            {
                while (IsApplicationIdle)
                    this.loopDelegate();
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct NativeMessage
        {
            public IntPtr handle;
            public uint msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint time;
            public System.Drawing.Point p;
        }

        [DllImport("user32.dll", EntryPoint = "PeekMessage"), SuppressUnmanagedCodeSecurity]
        private static extern byte PeekMessage(out NativeMessage lpMsg, IntPtr hWnd, int wMsgFilterMin,
                                               int wMsgFilterMax, int wRemoveMsg);
    }
}
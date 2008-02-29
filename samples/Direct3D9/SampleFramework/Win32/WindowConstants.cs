/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Collections.Generic;
using System.Text;

namespace SampleFramework
{
    static class WindowConstants
    {
        #region Constants

        public const uint ES_CONTINUOUS = 0x80000000;
        public const uint ES_DISPLAY_REQUIRED = 0x00000002;
        public const uint ES_SYSTEM_REQUIRED = 0x00000001;
        public const uint ES_USER_PRESENT = 0x00000004;

        public const int WPF_RESTORETOMAXIMIZED = 2;
        public const int MONITOR_DEFAULTTOPRIMARY = 1;
        public const int WM_KEYDOWN = 0x100;
        public const int WM_KEYUP = 0x101;
        public const int VK_LWIN = 0x5B;
        public const int VK_RWIN = 0x5C;

        public const int WM_SIZE = 0x5;
        public const int WM_ACTIVATEAPP = 0x001C;
        public const int SIZE_MINIMIZED = 1;
        public const int SIZE_MAXIMIZED = 2;
        public const int SIZE_RESTORED = 0;

        public const int GWL_WNDPROC = -4;
        public const int GWL_HINSTANCE = -6;
        public const int GWL_HWNDPARENT = -8;
        public const int GWL_STYLE = -16;
        public const int GWL_EXSTYLE = -20;
        public const int GWL_USERDATA = -21;
        public const int GWL_ID = -12;

        public const uint SWP_NOSIZE = 0x0001;
        public const uint SWP_NOMOVE = 0x0002;
        public const uint SWP_NOZORDER = 0x0004;
        public const uint SWP_NOREDRAW = 0x0008;
        public const uint SWP_NOACTIVATE = 0x0010;
        public const uint SWP_FRAMECHANGED = 0x0020;
        public const uint SWP_SHOWWINDOW = 0x0040;
        public const uint SWP_HIDEWINDOW = 0x0080;
        public const uint SWP_NOCOPYBITS = 0x0100;
        public const uint SWP_NOOWNERZORDER = 0x0200;
        public const uint SWP_NOSENDCHANGING = 0x0400;

        public const long WS_OVERLAPPED = 0x00000000;
        public const long WS_POPUP = 0x80000000;
        public const long WS_CHILD = 0x40000000;
        public const long WS_MINIMIZE = 0x20000000;
        public const long WS_VISIBLE = 0x10000000;
        public const long WS_DISABLED = 0x08000000;
        public const long WS_CLIPSIBLINGS = 0x04000000;
        public const long WS_CLIPCHILDREN = 0x02000000;
        public const long WS_MAXIMIZE = 0x01000000;
        public const long WS_CAPTION = 0x00C00000;
        public const long WS_BORDER = 0x00800000;
        public const long WS_DLGFRAME = 0x00400000;
        public const long WS_VSCROLL = 0x00200000;
        public const long WS_HSCROLL = 0x00100000;
        public const long WS_SYSMENU = 0x00080000;
        public const long WS_THICKFRAME = 0x00040000;
        public const long WS_GROUP = 0x00020000;
        public const long WS_TABSTOP = 0x00010000;
        public const long WS_MINIMIZEBOX = 0x00020000;
        public const long WS_MAXIMIZEBOX = 0x00010000;
        public const long WS_TILED = WS_OVERLAPPED;
        public const long WS_ICONIC = WS_MINIMIZE;
        public const long WS_SIZEBOX = WS_THICKFRAME;
        public const long WS_TILEDWINDOW = WS_OVERLAPPEDWINDOW;
        public const long WS_OVERLAPPEDWINDOW = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
        public const long WS_POPUPWINDOW = (WS_POPUP | WS_BORDER | WS_SYSMENU);
        public const long WS_CHILDWINDOW = WS_CHILD;
        public const long WS_EX_DLGMODALFRAME = 0x00000001;
        public const long WS_EX_NOPARENTNOTIFY = 0x00000004;
        public const long WS_EX_TOPMOST = 0x00000008;
        public const long WS_EX_ACCEPTFILES = 0x00000010;
        public const long WS_EX_TRANSPARENT = 0x00000020;
        public const long WS_EX_MDICHILD = 0x00000040;
        public const long WS_EX_TOOLWINDOW = 0x00000080;
        public const long WS_EX_WINDOWEDGE = 0x00000100;
        public const long WS_EX_CLIENTEDGE = 0x00000200;
        public const long WS_EX_CONTEXTHELP = 0x00000400;
        public const long WS_EX_RIGHT = 0x00001000;
        public const long WS_EX_LEFT = 0x00000000;
        public const long WS_EX_RTLREADING = 0x00002000;
        public const long WS_EX_LTRREADING = 0x00000000;
        public const long WS_EX_LEFTSCROLLBAR = 0x00004000;
        public const long WS_EX_RIGHTSCROLLBAR = 0x00000000;
        public const long WS_EX_CONTROLPARENT = 0x00010000;
        public const long WS_EX_STATICEDGE = 0x00020000;
        public const long WS_EX_APPWINDOW = 0x00040000;
        public const long WS_EX_OVERLAPPEDWINDOW = (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE);
        public const long WS_EX_PALETTEWINDOW = (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
        public const long WS_EX_LAYERED = 0x00080000;
        public const long WS_EX_NOINHERITLAYOUT = 0x00100000;
        public const long WS_EX_LAYOUTRTL = 0x00400000;
        public const long WS_EX_COMPOSITED = 0x02000000;
        public const long WS_EX_NOACTIVATE = 0x08000000;

        #endregion

        #region Statics

        public static readonly IntPtr HWND_TOPMOST = new IntPtr(-1);
        public static readonly IntPtr HWND_NOTOPMOST = new IntPtr(-2);

        #endregion
    }
}

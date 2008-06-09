using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Contains constants for Window operations.
    /// </summary>
    static class WindowConstants
    {
        /// <summary>
        /// A key was pressed.
        /// </summary>
        public static readonly IntPtr WM_KEYDOWN = new IntPtr(0x100);

        /// <summary>
        /// A key was released.
        /// </summary>
        public static readonly IntPtr WM_KEYUP = new IntPtr(0x101);

        /// <summary>
        /// A window's size is changing.
        /// </summary>
        public const int WM_SIZE = 0x5;

        /// <summary>
        /// A system command was sent to the window.
        /// </summary>
        public const int WM_SYSCOMMAND = 0x112;

        /// <summary>
        /// The application is being activated or deactivated.
        /// </summary>
        public const int WM_ACTIVATEAPP = 0x001C;

        /// <summary>
        /// A power broadcast message is being sent.
        /// </summary>
        public const int WM_POWERBROADCAST = 0x0218;

        /// <summary>
        /// Screensaver is about to activate.
        /// </summary>
        public const int SC_SCREENSAVE = 0xF140;

        /// <summary>
        /// Monitor is about to power cycle.
        /// </summary>
        public const int SC_MONITORPOWER = 0xF170;

        /// <summary>
        /// Represents the left Windows key.
        /// </summary>
        public const int VK_LWIN = 0x5B;

        /// <summary>
        /// Represents the right Windows key.
        /// </summary>
        public const int VK_RWIN = 0x5C;

        /// <summary>
        /// The window is being minimized.
        /// </summary>
        public static readonly IntPtr SIZE_MINIMIZED = new IntPtr(1);

        /// <summary>
        /// The window is being maximized.
        /// </summary>
        public static readonly IntPtr SIZE_MAXIMIZED = new IntPtr(2);

        /// <summary>
        /// The window is being restored.
        /// </summary>
        public static readonly IntPtr SIZE_RESTORED = new IntPtr(0);

        /// <summary>
        /// The system is going into suspended mode.
        /// </summary>
        public static readonly IntPtr PBT_APMQUERYSUSPEND = new IntPtr(0x0000);

        /// <summary>
        /// The system is coming out of suspended mode.
        /// </summary>
        public static readonly IntPtr PBT_APMRESUMESUSPEND = new IntPtr(0x0007);

        /// <summary>
        /// The window is being restored to a maximized state.
        /// </summary>
        public const int WPF_RESTORETOMAXIMIZED = 2;

        /// <summary>
        /// Restore the window.
        /// </summary>
        public const int SW_RESTORE = 9;

        /// <summary>
        /// Show the window, but in a minimized state.
        /// </summary>
        public const int SW_SHOWMINIMIZED = 2;

        /// <summary>
        /// Maximize the window.
        /// </summary>
        public const int SW_MAXIMIZE = 3;

        /// <summary>
        /// Show the window.
        /// </summary>
        public const int SW_SHOW = 5;

        /// <summary>
        /// Minimize the window.
        /// </summary>
        public const int SW_MINIMIZE = 6;

        /// <summary>
        /// Specifies the style setting of a window.
        /// </summary>
        public const int GWL_STYLE = -16;

        /// <summary>
        /// Specifies the extended style setting of a window.
        /// </summary>
        public const int GWL_EXSTYLE = -20;

        /// <summary>
        /// The window is maximized.
        /// </summary>
        public const long WS_MAXIMIZE = 0x01000000;

        /// <summary>
        /// The window is minimized.
        /// </summary>
        public const long WS_MINIMIZE = 0x20000000;

        /// <summary>
        /// The window is a popup window.
        /// </summary>
        public const long WS_POPUP = 0x80000000;

        /// <summary>
        /// The window has a system menu.
        /// </summary>
        public const long WS_SYSMENU = 0x00080000;

        /// <summary>
        /// The window is a topmost window.
        /// </summary>
        public const long WS_EX_TOPMOST = 0x00000008;

        /// <summary>
        /// Don't change the window's size.
        /// </summary>
        public const uint SWP_NOSIZE = 0x0001;

        /// <summary>
        /// Don't change the window's position.
        /// </summary>
        public const uint SWP_NOMOVE = 0x0002;

        /// <summary>
        /// Don't change the window's Z-order.
        /// </summary>
        public const uint SWP_NOZORDER = 0x0004;

        /// <summary>
        /// Don't redraw the window.
        /// </summary>
        public const uint SWP_NOREDRAW = 0x0008;

        /// <summary>
        /// The thread is continuously active.
        /// </summary>
        public const uint ES_CONTINUOUS = 0x80000000;

        /// <summary>
        /// The thread requires a display.
        /// </summary>
        public const uint ES_DISPLAY_REQUIRED = 0x00000002;
    }
}

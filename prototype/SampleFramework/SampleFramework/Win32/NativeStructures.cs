using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;

namespace SampleFramework
{
    /// <summary>
    /// Represents the unmanaged RECT type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct NativeRectangle
    {
        /// <summary>
        /// The left bound of the rectangle.
        /// </summary>
        public int left;

        /// <summary>
        /// The top bound of the rectangle.
        /// </summary>
        public int top;

        /// <summary>
        /// The right bound of the rectangle.
        /// </summary>
        public int right;

        /// <summary>
        /// The bottom bound of the rectangle.
        /// </summary>
        public int bottom;
    }

    /// <summary>
    /// Represents the unmanaged MSG type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct NativeMessage
    {
        /// <summary>
        /// The window handle.
        /// </summary>
        public IntPtr hWnd;

        /// <summary>
        /// The message ID.
        /// </summary>
        public uint msg;

        /// <summary>
        /// The first generic parameter.
        /// </summary>
        public IntPtr wParam;

        /// <summary>
        /// The second generic parameter.
        /// </summary>
        public IntPtr lParam;

        /// <summary>
        /// The timing of the message.
        /// </summary>
        public uint time;

        /// <summary>
        /// A context dependent point.
        /// </summary>
        public Point p;
    }

    /// <summary>
    /// Represents the unmanaged KBDLLHOOKSTRUCT type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct KBDLLHOOKSTRUCT
    {
        /// <summary>
        /// The keyboard key code.
        /// </summary>
        public int vkCode;

        /// <summary>
        /// The scan code of the key.
        /// </summary>
        public int scanCode;

        /// <summary>
        /// Keyboard flags.
        /// </summary>
        public int flags;

        /// <summary>
        /// Key event time.
        /// </summary>
        public int time;

        /// <summary>
        /// Extra info about the event.
        /// </summary>
        public IntPtr dwExtraInfo;
    }

    /// <summary>
    /// Represents the unmanaged FILTERKEYS type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct FILTERKEYS
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public int cbSize;

        /// <summary>
        /// The filter keys flags.
        /// </summary>
        public int dwFlags;
    }

    /// <summary>
    /// Represents the unmanaged STICKYKEYS type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct STICKYKEYS
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public int cbSize;

        /// <summary>
        /// The sticky keys flags.
        /// </summary>
        public int dwFlags;
    }

    /// <summary>
    /// Represents the unmanaged TOGGLEKEYS type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct TOGGLEKEYS
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public int cbSize;

        /// <summary>
        /// The toggle keys flags.
        /// </summary>
        public int dwFlags;
    }

    /// <summary>
    /// Represents the unmanaged WINDOWPLACEMENT type.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    struct WINDOWPLACEMENT
    {
        /// <summary>
        /// The size of the structure, in bytes.
        /// </summary>
        public int length;

        /// <summary>
        /// Window placement flags.
        /// </summary>
        public int flags;

        /// <summary>
        /// The ShowWindow flag.
        /// </summary>
        public int showCmd;

        /// <summary>
        /// The minimum point of the window.
        /// </summary>
        public Point ptMinPosition;

        /// <summary>
        /// The maximum point of the window.
        /// </summary>
        public Point ptMaxPosition;

        /// <summary>
        /// The restored position of the window.
        /// </summary>
        public NativeRectangle rcNormalPosition;

        /// <summary>
        /// Gets the size of the structure, in bytes.
        /// </summary>
        public static int Length
        {
            get { return Marshal.SizeOf(typeof(WINDOWPLACEMENT)); }
        }
    }
}

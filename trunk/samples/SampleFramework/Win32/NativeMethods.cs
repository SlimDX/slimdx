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
using System.Drawing;
using System.Runtime.InteropServices;
using System.Security;

namespace SampleFramework
{
    /// <summary>
    /// Contains imported native methods.
    /// </summary>
    static class NativeMethods
    {
        /// <summary>
        /// Peeks at the next message in the queue.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="hwnd">The window handle.</param>
        /// <param name="messageFilterMin">The message filter minimum.</param>
        /// <param name="messageFilterMax">The message filter maximum.</param>
        /// <param name="flags">The flags.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out NativeMessage message, IntPtr hwnd, uint messageFilterMin, uint messageFilterMax, uint flags);

        /// <summary>
        /// Gets a window's client rectangle.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="lpRect">The client rectangle.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool GetClientRect(IntPtr hWnd, out NativeRectangle lpRect);

        /// <summary>
        /// Gets a window's outer rectangle.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="lpRect">The outer rectangle.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool GetWindowRect(IntPtr hWnd, out NativeRectangle lpRect);

        /// <summary>
        /// Gets a window's placement information.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="lpwndpl">The placement information.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetWindowPlacement(IntPtr hWnd, ref WINDOWPLACEMENT lpwndpl);

        /// <summary>
        /// Sets a window's placement information.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="lpwndpl">The placement information.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetWindowPlacement(IntPtr hWnd, ref WINDOWPLACEMENT lpwndpl);

        /// <summary>
        /// Sets a window style.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="nIndex">Index of the style.</param>
        /// <param name="dwNewLong">The new style value.</param>
        /// <returns>The old style value.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern uint SetWindowLong(IntPtr hWnd, int nIndex, uint dwNewLong);

        /// <summary>
        /// Gets a window style.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="nIndex">Index of the style.</param>
        /// <returns>The style value.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern uint GetWindowLong(IntPtr hWnd, int nIndex);

        /// <summary>
        /// Determines whether the specified window is iconic.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <returns>
        /// <c>true</c> if the specified window is iconic; otherwise, <c>false</c>.
        /// </returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool IsIconic(IntPtr hWnd);

        /// <summary>
        /// Determines whether the specified window is zoomed.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <returns>
        /// <c>true</c> if the specified window is zoomed; otherwise, <c>false</c>.
        /// </returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool IsZoomed(IntPtr hWnd);

        /// <summary>
        /// Shows the window.
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="nCmdShow">Show flags.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        /// <summary>
        /// Adjusts a window rectangle.
        /// </summary>
        /// <param name="lpRect">The rectangle.</param>
        /// <param name="dwStyle">Style flags..</param>
        /// <param name="bMenu">if set to <c>true</c>, include the menu in calculations as well.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool AdjustWindowRect(ref NativeRectangle lpRect, uint dwStyle, [MarshalAs(UnmanagedType.Bool)]bool bMenu);

        /// <summary>
        /// Sets the state of the thread execution.
        /// </summary>
        /// <param name="esFlags">The execution flags.</param>
        /// <returns>The thread execution state.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        public static extern uint SetThreadExecutionState(uint esFlags);

        /// <summary>
        /// Sets a window's position..
        /// </summary>
        /// <param name="hWnd">The window handle.</param>
        /// <param name="hWndInsertAfter">The Z-order for the window.</param>
        /// <param name="X">The X position.</param>
        /// <param name="Y">The Y position.</param>
        /// <param name="cx">The width.</param>
        /// <param name="cy">The height.</param>
        /// <param name="uFlags">Show flags.</param>
        /// <returns><c>true</c> on success; otherwise, <c>false</c>.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint uFlags);

        /// <summary>
        /// Gets the monitor in which the specified Window resides.
        /// </summary>
        /// <param name="hwnd">The window handle.</param>
        /// <param name="dwFlags">The monitor flags.</param>
        /// <returns>A handle to the monitor.</returns>
        [SuppressUnmanagedCodeSecurityAttribute]
        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = false)]
        public static extern IntPtr MonitorFromWindow(IntPtr hwnd, uint dwFlags);

        /// <summary>
        /// Gets the client rectangle of a window.
        /// </summary>
        /// <param name="handle">The handle of the window.</param>
        /// <returns>The window's client rectangle.</returns>
        public static Rectangle GetClientRectangle(IntPtr handle)
        {
            // grab the native rectangle
            NativeRectangle rect;
            if (!GetClientRect(handle, out rect))
                return Rectangle.Empty;

            // return the converted rectangle
            return Rectangle.FromLTRB(rect.left, rect.top, rect.right, rect.bottom);
        }

        /// <summary>
        /// Gets the outer rectangle of a window.
        /// </summary>
        /// <param name="handle">The handle of the window.</param>
        /// <returns>The window's outer rectangle.</returns>
        public static Rectangle GetWindowRectangle(IntPtr handle)
        {
            // grab the native rectangle
            NativeRectangle rect;
            if (!GetWindowRect(handle, out rect))
                return Rectangle.Empty;

            // return the converted rectangle
            return Rectangle.FromLTRB(rect.left, rect.top, rect.right, rect.bottom);
        }
    }
}

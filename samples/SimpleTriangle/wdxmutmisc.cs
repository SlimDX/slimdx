//--------------------------------------------------------------------------------------
// File: WDXMUTMisc.cs
//
// Shortcut and helper functions for using Managed DirectX for Whidbey Code
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
using System;
using System.IO;
using System.Collections;
using System.Runtime.InteropServices;
using SlimDX;
using SlimDX.Direct3D9;

//stripped down version of wdxmutmisc.cs

namespace SimpleTriangle
{
    #region Native Methods
    /// <summary>
    /// Will hold native methods which are interop'd
    /// </summary>
    public class NativeMethods
    {
        #region Win32 User Messages / Structures

        /// <summary>Window messages</summary>
        public enum WindowMessage : uint
        {
            // Misc messages
            Destroy = 0x0002,
            Close = 0x0010,
            Quit = 0x0012,
            Paint = 0x000F,
            SetCursor = 0x0020,
            ActivateApplication = 0x001C,
            EnterMenuLoop = 0x0211,
            ExitMenuLoop = 0x0212,
            NonClientHitTest = 0x0084,
            PowerBroadcast = 0x0218,
            SystemCommand = 0x0112,
            GetMinMax = 0x0024,

            // Keyboard messages
            KeyDown = 0x0100,
            KeyUp = 0x0101,
            Character = 0x0102,
            SystemKeyDown = 0x0104,
            SystemKeyUp = 0x0105,
            SystemCharacter = 0x0106,

            // Mouse messages
            MouseMove = 0x0200,
            LeftButtonDown = 0x0201,
            LeftButtonUp = 0x0202,
            LeftButtonDoubleClick = 0x0203,
            RightButtonDown = 0x0204,
            RightButtonUp = 0x0205,
            RightButtonDoubleClick = 0x0206,
            MiddleButtonDown = 0x0207,
            MiddleButtonUp = 0x0208,
            MiddleButtonDoubleClick = 0x0209,
            MouseWheel = 0x020a,
            XButtonDown = 0x020B,
            XButtonUp = 0x020c,
            XButtonDoubleClick = 0x020d,
            MouseFirst = LeftButtonDown, // Skip mouse move, it happens a lot and there is another message for that
            MouseLast = XButtonDoubleClick,

            // Sizing
            EnterSizeMove = 0x0231,
            ExitSizeMove = 0x0232,
            Size = 0x0005,

        }

        /// <summary>Mouse buttons</summary>
        public enum MouseButtons
        {
            Left = 0x0001,
            Right = 0x0002,
            Middle = 0x0010,
            Side1 = 0x0020,
            Side2 = 0x0040,
        }

        /// <summary>Windows Message</summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public WindowMessage msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint time;
            public System.Drawing.Point p;
        }

        /// <summary>MinMax Info structure</summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct MinMaxInformation
        {
            public System.Drawing.Point reserved;
            public System.Drawing.Point MaxSize;
            public System.Drawing.Point MaxPosition;
            public System.Drawing.Point MinTrackSize;
            public System.Drawing.Point MaxTrackSize;
        }

        /// <summary>Monitor Info structure</summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct MonitorInformation
        {
            public uint Size; // Size of this structure
            public System.Drawing.Rectangle MonitorRectangle;
            public System.Drawing.Rectangle WorkRectangle;
            public uint Flags; // Possible flags
        }
        #endregion

        #region Windows API calls
        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [System.Runtime.InteropServices.DllImport("winmm.dll")]
        public static extern IntPtr timeBeginPeriod(uint period);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("kernel32")]
        public static extern bool QueryPerformanceFrequency(ref long PerformanceFrequency);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("kernel32")]
        public static extern bool QueryPerformanceCounter(ref long PerformanceCount);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool GetMonitorInfo(IntPtr hWnd, ref MonitorInformation info);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr MonitorFromWindow(IntPtr hWnd, uint flags);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern short GetAsyncKeyState(uint key);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr SetCapture(IntPtr handle);

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool ReleaseCapture();

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern int GetCaretBlinkTime();

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool PeekMessage(out Message msg, IntPtr hWnd, uint messageFilterMin, uint messageFilterMax, uint flags);
        #endregion

        #region Class Methods
        private NativeMethods() { } // No creation
        /// <summary>Returns the low word</summary>
        public static short LoWord(uint l)
        {
            return (short)(l & 0xffff);
        }
        /// <summary>Returns the high word</summary>
        public static short HiWord(uint l)
        {
            return (short)(l >> 16);
        }

        /// <summary>Makes two shorts into a long</summary>
        public static uint MakeUInt32(short l, short r)
        {
            return (uint)((l & 0xffff) | ((r & 0xffff) << 16));
        }

        /// <summary>Is this key down right now</summary>
        public static bool IsKeyDown(System.Windows.Forms.Keys key)
        {
            return (GetAsyncKeyState((int)System.Windows.Forms.Keys.ShiftKey) & 0x8000) != 0;
        }
        #endregion
    }

    #endregion

    #region Timer
    class FrameworkTimer
    {
        #region Instance Data
        private static bool isUsingQPF;
        private static bool isTimerStopped;
        private static long ticksPerSecond;
        private static long stopTime;
        private static long lastElapsedTime;
        private static long baseTime;
        #endregion

        #region Creation
        private FrameworkTimer() { } // No creation
        /// <summary>
        /// Static creation routine
        /// </summary>
        static FrameworkTimer()
        {
            isTimerStopped = true;
            ticksPerSecond = 0;
            stopTime = 0;
            lastElapsedTime = 0;
            baseTime = 0;
            // Use QueryPerformanceFrequency to get frequency of the timer
            isUsingQPF = NativeMethods.QueryPerformanceFrequency(ref ticksPerSecond);
        }
        #endregion

        /// <summary>
        /// Resets the timer
        /// </summary>
        public static void Reset()
        {
            if (!isUsingQPF)
                return; // Nothing to do

            // Get either the current time or the stop time
            long time = 0;
            if (stopTime != 0)
                time = stopTime;
            else
                NativeMethods.QueryPerformanceCounter(ref time);

            baseTime = time;
            lastElapsedTime = time;
            stopTime = 0;
            isTimerStopped = false;
        }

        /// <summary>
        /// Starts the timer
        /// </summary>
        public static void Start()
        {
            if (!isUsingQPF)
                return; // Nothing to do

            // Get either the current time or the stop time
            long time = 0;
            if (stopTime != 0)
                time = stopTime;
            else
                NativeMethods.QueryPerformanceCounter(ref time);

            if (isTimerStopped)
                baseTime += (time - stopTime);
            stopTime = 0;
            lastElapsedTime = time;
            isTimerStopped = false;
        }

        /// <summary>
        /// Stop (or pause) the timer
        /// </summary>
        public static void Stop()
        {
            if (!isUsingQPF)
                return; // Nothing to do

            if (!isTimerStopped)
            {
                // Get either the current time or the stop time
                long time = 0;
                if (stopTime != 0)
                    time = stopTime;
                else
                    NativeMethods.QueryPerformanceCounter(ref time);

                stopTime = time;
                lastElapsedTime = time;
                isTimerStopped = true;
            }
        }

        /// <summary>
        /// Advance the timer a tenth of a second
        /// </summary>
        public static void Advance()
        {
            if (!isUsingQPF)
                return; // Nothing to do

            stopTime += ticksPerSecond / 10;
        }

        /// <summary>
        /// Get the absolute system time
        /// </summary>
        public static double GetAbsoluteTime()
        {
            if (!isUsingQPF)
                return -1.0; // Nothing to do

            // Get either the current time or the stop time
            long time = 0;
            if (stopTime != 0)
                time = stopTime;
            else
                NativeMethods.QueryPerformanceCounter(ref time);

            double absolueTime = time / (double)ticksPerSecond;
            return absolueTime;
        }

        /// <summary>
        /// Get the current time
        /// </summary>
        public static double GetTime()
        {
            if (!isUsingQPF)
                return -1.0; // Nothing to do

            // Get either the current time or the stop time
            long time = 0;
            if (stopTime != 0)
                time = stopTime;
            else
                NativeMethods.QueryPerformanceCounter(ref time);

            double appTime = (double)(time - baseTime) / (double)ticksPerSecond;
            return appTime;
        }

        /// <summary>
        /// get the time that elapsed between GetElapsedTime() calls
        /// </summary>
        public static double GetElapsedTime()
        {
            if (!isUsingQPF)
                return -1.0; // Nothing to do

            // Get either the current time or the stop time
            long time = 0;
            if (stopTime != 0)
                time = stopTime;
            else
                NativeMethods.QueryPerformanceCounter(ref time);

            double elapsedTime = (double)(time - lastElapsedTime) / (double)ticksPerSecond;
            lastElapsedTime = time;
            return elapsedTime;
        }

        /// <summary>
        /// Returns true if timer stopped
        /// </summary>
        public static bool IsStopped
        {
            get { return isTimerStopped; }
        }
    }
    #endregion
}
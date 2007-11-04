//-----------------------------------------------------------------------------
// File: RenderForm.cs
//
// Desc: This is our form used for rendering and handling window messages.
//-----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Matrices
{
    public partial class RenderForm : Form
    {
        /// <summary>
        /// Native methods which are interop'd
        /// </summary>
        #region Win32 Message structure and Message Callback

        /// <summary>Windows Message</summary>
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public UInt32 msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public UInt32 time;
            public System.Drawing.Point p;
        };

        [System.Security.SuppressUnmanagedCodeSecurity] // We won't use this maliciously
        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        public static extern bool PeekMessage(out Message msg, IntPtr hWnd, UInt32 msgFilterMin, UInt32 msgFilterMax, UInt32 flags);

        #endregion

        public RenderForm()
        {
            InitializeComponent();
            this.ClientSize = new Size(800, 600);
            this.Text = "SlimDX - D3D9 Tutorial 03: Matrices";
        }

        public void PrepareMainLoop()
        {
            Application.Idle += new EventHandler(Application_Idle);
        }

        private bool AppStillIdle
        {
            get
            {
                Message msg;
                return !PeekMessage(out msg, IntPtr.Zero, 0, 0, 0);
            }
        }

        //This is our actual loop function
        private void Application_Idle(object sender, EventArgs e)
        {
            while (AppStillIdle)
            {
                Program.MainLoop();
            }
        }
    }
}
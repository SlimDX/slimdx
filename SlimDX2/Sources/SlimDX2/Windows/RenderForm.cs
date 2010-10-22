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
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace SlimDX2.Windows
{
    public class RenderForm : Form
    {
        private const int WM_SIZE = 0x0005;
        private const int SIZE_RESTORED = 0;
        private const int SIZE_MINIMIZED = 1;
        private const int SIZE_MAXIMIZED = 2;
        private const int SIZE_MAXSHOW = 3;
        private const int SIZE_MAXHIDE = 4;
        private const int WM_ACTIVATEAPP = 0x001C;
        private const int WM_POWERBROADCAST = 0x0218;
        private const int WM_MENUCHAR = 0x0120;
        private const int WM_SYSCOMMAND = 0x0112;
        private const uint PBT_APMRESUMESUSPEND = 7;
        private const uint PBT_APMQUERYSUSPEND = 0;
        private const int SC_MONITORPOWER = 0xF170;
        private const int SC_SCREENSAVE = 0xF140;
        private const int MNC_CLOSE = 1;
        private System.Drawing.Size cachedSize;
        private bool maximized;
        private bool minimized;
        //private DisplayMonitor monitor;
        private bool sizeMove;


        public RenderForm()
        {
            Construct("SlimDX2");
        }

        public RenderForm(String text)
        {
            Construct(text);
        }

        public event EventHandler<EventArgs> AppActivated;
        public event EventHandler<EventArgs> AppDeactivated;
        public event EventHandler<EventArgs> MonitorChanged;
        public event EventHandler<EventArgs> PauseRendering;
        public event EventHandler<EventArgs> ResumeRendering;
        public event EventHandler<CancelEventArgs> Screensaver;
        public event EventHandler<EventArgs> SystemResume;
        public event EventHandler<EventArgs> SystemSuspend;
        public event EventHandler<EventArgs> UserResized;

        private void Construct(String text)
        {
            Text = text;
            ClientSize = new System.Drawing.Size(800, 600);
            MinimumSize = new System.Drawing.Size(200, 200);

            ResizeRedraw = true;
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint, true);

            //Icon = SlimDX.Resources.BlackIcon;
        }

        protected override void OnResizeBegin(EventArgs e)
        {
            base.OnResizeBegin(e);

            sizeMove = true;
            cachedSize = Size;
            OnPauseRendering(e);
        }

        protected override void OnResizeEnd(EventArgs e)
        {
            base.OnResizeEnd(e);

            OnUserResized(e);
            UpdateScreen();

            sizeMove = false;
            OnResumeRendering(e);
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            cachedSize = Size;
            UpdateScreen();
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
        }

        private void OnPauseRendering(EventArgs e)
        {
            if (PauseRendering != null)
                PauseRendering(this, e);
        }

        private void OnResumeRendering(EventArgs e)
        {
            if (ResumeRendering != null)
                ResumeRendering(this, e);
        }

        private void OnUserResized(EventArgs e)
        {
            if (UserResized != null)
                UserResized(this, e);
        }

        private void OnMonitorChanged(EventArgs e)
        {
            if (MonitorChanged != null)
                MonitorChanged(this, e);
        }

        private void OnAppActivated(EventArgs e)
        {
            if (AppActivated != null)
                AppActivated(this, e);
        }

        private void OnAppDeactivated(EventArgs e)
        {
            if (AppDeactivated != null)
                AppDeactivated(this, e);
        }

        private void OnSystemSuspend(EventArgs e)
        {
            if (SystemSuspend != null)
                SystemSuspend(this, e);
        }

        private void OnSystemResume(EventArgs e)
        {
            if (SystemResume != null)
                SystemResume(this, e);
        }

        private void OnScreensaver(CancelEventArgs e)
        {
            if (Screensaver != null)
                Screensaver(this, e);
        }

        [DllImport("user32.dll")]
        private static extern bool GetClientRect(IntPtr hWnd, out Rectangle lpRect);

        protected override void WndProc(ref Message m)
        {
            long wparam = m.WParam.ToInt64();

            switch (m.Msg)
            {
                case WM_SIZE:
                    if (wparam == SIZE_MINIMIZED)
                    {
                        minimized = true;
                        maximized = false;
                        OnPauseRendering(EventArgs.Empty);
                    }
                    else
                    {
                        Rectangle rect;

                        GetClientRect(m.HWnd, out rect);
                        if (rect.Bottom - rect.Top == 0)
                        {
                            // Rapidly clicking the task bar to minimize and restore a window
                            // can cause a WM_SIZE message with SIZE_RESTORED when 
                            // the window has actually become minimized due to rapid change
                            // so just ignore this message
                        }
                        else if (wparam == SIZE_MAXIMIZED)
                        {
                            if (minimized)
                                OnResumeRendering(EventArgs.Empty);

                            minimized = false;
                            maximized = true;

                            OnUserResized(EventArgs.Empty);
                            UpdateScreen();
                        }
                        else if (wparam == SIZE_RESTORED)
                        {
                            if (minimized)
                                OnResumeRendering(EventArgs.Empty);

                            minimized = false;
                            maximized = false;

                            if (!sizeMove && Size != cachedSize)
                            {
                                OnUserResized(EventArgs.Empty);
                                UpdateScreen();
                                cachedSize = Size;
                            }
                        }
                    }
                    break;
                case WM_ACTIVATEAPP:
                    if (wparam != 0)
                        OnAppActivated(EventArgs.Empty);
                    else
                        OnAppDeactivated(EventArgs.Empty);
                    break;
                case WM_POWERBROADCAST:
                    if (wparam == PBT_APMQUERYSUSPEND)
                    {
                        OnSystemSuspend(EventArgs.Empty);
                        m.Result = new IntPtr(1);
                        return;
                    }
                    else if (wparam == PBT_APMRESUMESUSPEND)
                    {
                        OnSystemResume(EventArgs.Empty);
                        m.Result = new IntPtr(1);
                        return;
                    }
                    break;
                case WM_MENUCHAR:
                    m.Result = new IntPtr(MNC_CLOSE << 16); // IntPtr(MAKELRESULT(0, MNC_CLOSE));
                    return;
                case WM_SYSCOMMAND:
                    wparam &= 0xFFF0;
                    if (wparam == SC_MONITORPOWER || wparam == SC_SCREENSAVE)
                    {
                        var e = new CancelEventArgs();
                        OnScreensaver(e);
                        if (e.Cancel)
                        {
                            m.Result = IntPtr.Zero;
                            return;
                        }
                    }
                    break;
            }

            base.WndProc(ref m);
        }

        private void UpdateScreen()
        {
            //DisplayMonitor current = DisplayMonitor.FromWindow(Handle);
            //if (monitor != null && monitor->DeviceName != current->DeviceName)
            //{
            //    monitor = current;
            //    OnMonitorChanged(System.EventArgs.Empty);
            //}

            //monitor = current;
        }
    }
}
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
using System.Windows.Forms;
using System.Security.Permissions;

namespace SampleFramework
{
    /// <summary>
    /// A Windows Form designed to work well with Direct3D.
    /// </summary>
    public class Window : Form
    {
        #region Variables

        bool active;

        #endregion

        #region Events

        /// <summary>
        /// Occurs when the window is minimized.
        /// </summary>
        public event EventHandler SizeMinimized;

        /// <summary>
        /// Occurs when the window is maximized.
        /// </summary>
        public event EventHandler SizeMaximized;

        /// <summary>
        /// Occurs when the window is restored.
        /// </summary>
        public event EventHandler SizeRestored;

        /// <summary>
        /// Occurs when the active state of the window is changed.
        /// </summary>
        public event EventHandler ActiveChanged;

        #endregion

        #region Properties

        /// <summary>
        /// Gets a value indicating whether this <see cref="Window"/> is active.
        /// </summary>
        /// <value><c>true</c> if active; otherwise, <c>false</c>.</value>
        public bool Active
        {
            get { return active; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="Window"/> class.
        /// </summary>
        public Window()
        {
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Raises the <see cref="E:ActiveChanged"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnActiveChanged(EventArgs e)
        {
            if (ActiveChanged != null)
                ActiveChanged(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:SizeMinimized"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnSizeMinimized(EventArgs e)
        {
            if (SizeMinimized != null)
                SizeMinimized(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:SizeMaximized"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnSizeMaximized(EventArgs e)
        {
            if (SizeMaximized != null)
                SizeMaximized(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:SizeRestored"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnSizeRestored(EventArgs e)
        {
            if (SizeRestored != null)
                SizeRestored(this, e);
        }

        #endregion

        #region Window Procedure

        /// <summary>
        /// Handles Windows messages.
        /// </summary>
        /// <param name="m">The message details.</param>
        [SecurityPermission(SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.UnmanagedCode)]
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == WindowConstants.WM_SIZE)
            {
                if (m.WParam.ToInt32() == WindowConstants.SIZE_MINIMIZED)
                    OnSizeMinimized(EventArgs.Empty);
                else
                {
                    NativeRectangle rect;
                    NativeMethods.GetClientRect(m.HWnd, out rect);
                    if (rect.top == 0 && rect.bottom == 0)
                    {
                        // rapidly clicking the task bar to minimize and restore a window
                        // can cause a WM_SIZE message with SIZE_RESTORED when 
                        // the window has actually become minimized due to rapid change
                        // so just ignore this message
                    }
                    else if (m.WParam.ToInt32() == WindowConstants.SIZE_MAXIMIZED)
                        OnSizeMaximized(EventArgs.Empty);
                    else if (m.WParam.ToInt32() == WindowConstants.SIZE_RESTORED)
                        OnSizeRestored(EventArgs.Empty);
                }
            }
            else if (m.Msg == WindowConstants.WM_ACTIVATEAPP)
            {
                if (m.WParam.ToInt32() == 1 && !active)
                {
                    active = true;
                    OnActiveChanged(EventArgs.Empty);
                }
                else if (m.WParam.ToInt32() == 0 && active)
                {
                    active = false;
                    OnActiveChanged(EventArgs.Empty);
                }
            }

            base.WndProc(ref m);
        }

        #endregion
    }
}

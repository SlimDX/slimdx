using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace SampleFramework
{
    public class Window : Form
    {
        #region Variables

        bool active;

        #endregion

        #region Events

        public event EventHandler SizeMinimized;
        public event EventHandler SizeMaximized;
        public event EventHandler SizeRestored;
        public event EventHandler ActiveChanged;

        #endregion

        #region Properties

        public bool Active
        {
            get { return active; }
        }

        #endregion

        #region Constructor

        public Window()
        {
        }

        #endregion

        #region Event Handlers

        protected virtual void OnActiveChanged(EventArgs e)
        {
            if (ActiveChanged != null)
                ActiveChanged(this, e);
        }

        protected virtual void OnSizeMinimized(EventArgs e)
        {
            if (SizeMinimized != null)
                SizeMinimized(this, e);
        }

        protected virtual void OnSizeMaximized(EventArgs e)
        {
            if (SizeMaximized != null)
                SizeMaximized(this, e);
        }

        protected virtual void OnSizeRestored(EventArgs e)
        {
            if (SizeRestored != null)
                SizeRestored(this, e);
        }

        #endregion

        #region Window Procedure

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

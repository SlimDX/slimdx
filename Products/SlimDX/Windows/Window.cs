using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace SlimDX.Windows
{
    public class Window : IWin32Window
    {
        WindowHandler window;
        Rectangle bounds;
        Size clientSize;

        public event EventHandler ApplicationActivated;
        public event EventHandler ApplicationDeactivated;
        public event EventHandler Closed;
        public event EventHandler CursorChanged;
        public event EventHandler LocationChanged;
        public event EventHandler SizeChanged;
        public event EventHandler Maximized;
        public event EventHandler Minimized;
        public event EventHandler Restored;
        public event EventHandler ResizeBegin;
        public event EventHandler ResizeEnd;
        public event EventHandler SystemSuspend;
        public event EventHandler SystemResume;
        public event KeyEventHandler KeyDown;
        public event KeyEventHandler KeyUp;
        public event KeyEventHandler SystemKeyDown;
        public event KeyEventHandler SystemKeyUp;
        public event MouseEventHandler MouseDown;
        public event MouseEventHandler MouseUp;
        public event MouseEventHandler MouseDoubleClick;
        public event MouseEventHandler MouseWheel;
        public event MouseEventHandler MouseMove;
        public event PaintEventHandler Paint;

        public IntPtr Handle
        {
            get { return window.Handle; }
        }

        public Rectangle Bounds
        {
            get { return bounds; }
            set { bounds = value; UpdateBounds(); }
        }

        public Size Size
        {
            get { return bounds.Size; }
            set { bounds.Size = value; UpdateSize(); }
        }

        public Point Location
        {
            get { return bounds.Location; }
            set { bounds.Location = value; UpdatePosition(); }
        }

        public int X
        {
            get { return bounds.X; }
            set { bounds.X = value; UpdatePosition(); }
        }

        public int Y
        {
            get { return bounds.Y; }
            set { bounds.Y = value; UpdatePosition(); }
        }

        public int Width
        {
            get { return bounds.Width; }
            set { bounds.Width = value; UpdateSize(); }
        }

        public int Height
        {
            get { return bounds.Height; }
            set { bounds.Height = value; UpdateSize(); }
        }

        public Size ClientSize
        {
            get { return clientSize; }
            set { clientSize = value; UpdateClientSize(); }
        }

        public int ClientWidth
        {
            get { return clientSize.Width; }
            set { clientSize.Width = value; UpdateClientSize(); }
        }

        public int ClientHeight
        {
            get { return clientSize.Height; }
            set { clientSize.Height = value; UpdateClientSize(); }
        }

        public Window()
            : this("SlimDX", 800, 600)
        {
        }

        public Window(string title)
            : this(title, 800, 600)
        {
        }

        public Window(string title, int clientWidth, int clientHeight)
        {
            window = new WindowHandler(WndProc);

            var clientBounds = new RECT(0, 0, clientWidth, clientHeight);
            NativeMethods.AdjustWindowRectEx(ref clientBounds, Win32Interop.WS_OVERLAPPEDWINDOW, false, Win32Interop.WS_EX_OVERLAPPEDWINDOW);

            var createParams = new CreateParams()
            {
                Caption = title,
                ClassStyle = Win32Interop.CS_DBLCKS | Win32Interop.CS_HREDRAW | Win32Interop.CS_VREDRAW,
                Style = Win32Interop.WS_OVERLAPPEDWINDOW,
                ExStyle = Win32Interop.WS_EX_OVERLAPPEDWINDOW,
                X = Win32Interop.CW_USEDEFAULT,
                Y = Win32Interop.CW_USEDEFAULT,
                Width = clientBounds.Right - clientBounds.Left,
                Height = clientBounds.Bottom - clientBounds.Top,
            };

            window.CreateHandle(createParams);
            RefreshSize();
        }

        protected virtual void OnApplicationActivated(EventArgs e)
        {
            if (ApplicationActivated != null)
                ApplicationActivated(this, e);
        }

        protected virtual void OnApplicationDeactivated(EventArgs e)
        {
            if (ApplicationDeactivated != null)
                ApplicationDeactivated(this, e);
        }

        protected virtual void OnClosed(EventArgs e)
        {
            if (Closed != null)
                Closed(this, e);
        }

        protected virtual void OnCursorChanged(EventArgs e)
        {
            if (CursorChanged != null)
                CursorChanged(this, e);
        }

        protected virtual void OnLocationChanged(EventArgs e)
        {
            if (LocationChanged != null)
                LocationChanged(this, e);
        }

        protected virtual void OnSizeChanged(EventArgs e)
        {
            if (SizeChanged != null)
                SizeChanged(this, e);
        }

        protected virtual void OnMaximized(EventArgs e)
        {
            if (Maximized != null)
                Maximized(this, e);
        }

        protected virtual void OnMinimized(EventArgs e)
        {
            if (Minimized != null)
                Minimized(this, e);
        }

        protected virtual void OnRestored(EventArgs e)
        {
            if (Restored != null)
                Restored(this, e);
        }

        protected virtual void OnResizeBegin(EventArgs e)
        {
            if (ResizeBegin != null)
                ResizeBegin(this, e);
        }

        protected virtual void OnResizeEnd(EventArgs e)
        {
            if (ResizeEnd != null)
                ResizeEnd(this, e);
        }

        protected virtual void OnSystemSuspend(EventArgs e)
        {
            if (SystemSuspend != null)
                SystemSuspend(this, e);
        }

        protected virtual void OnSystemResume(EventArgs e)
        {
            if (SystemResume != null)
                SystemResume(this, e);
        }

        protected virtual void OnKeyDown(KeyEventArgs e)
        {
            if (KeyDown != null)
                KeyDown(this, e);
        }

        protected virtual void OnKeyUp(KeyEventArgs e)
        {
            if (KeyUp != null)
                KeyUp(this, e);
        }

        protected virtual void OnSystemKeyDown(KeyEventArgs e)
        {
            if (SystemKeyDown != null)
                SystemKeyDown(this, e);
        }

        protected virtual void OnSystemKeyUp(KeyEventArgs e)
        {
            if (SystemKeyUp != null)
                SystemKeyUp(this, e);
        }

        protected virtual void OnMouseDown(MouseEventArgs e)
        {
            if (MouseDown != null)
                MouseDown(this, e);
        }

        protected virtual void OnMouseUp(MouseEventArgs e)
        {
            if (MouseUp != null)
                MouseUp(this, e);
        }

        protected virtual void OnMouseDoubleClick(MouseEventArgs e)
        {
            if (MouseDoubleClick != null)
                MouseDoubleClick(this, e);
        }

        protected virtual void OnMouseWheel(MouseEventArgs e)
        {
            if (MouseWheel != null)
                MouseWheel(this, e);
        }

        protected virtual void OnMouseMove(MouseEventArgs e)
        {
            if (MouseMove != null)
                MouseMove(this, e);
        }

        protected virtual void OnPaint(PaintEventArgs e)
        {
            if (Paint != null)
                Paint(this, e);
        }

        protected virtual bool WndProc(ref Message m)
        {
            int x = Win32Interop.LOWORD(m.LParam);
            int y = Win32Interop.HIWORD(m.LParam);
            var buttons = (MouseButtons)Win32Interop.LOWORD(m.WParam);

            switch (m.Msg)
            {
                case WindowMessages.WM_LBUTTONDOWN:
                case WindowMessages.WM_MBUTTONDOWN:
                case WindowMessages.WM_RBUTTONDOWN:
                case WindowMessages.WM_XBUTTONDOWN:
                    OnMouseDown(new MouseEventArgs(buttons, 1, x, y, 0));
                    break;

                case WindowMessages.WM_LBUTTONUP:
                case WindowMessages.WM_MBUTTONUP:
                case WindowMessages.WM_RBUTTONUP:
                case WindowMessages.WM_XBUTTONUP:
                    OnMouseUp(new MouseEventArgs(buttons, 1, x, y, 0));
                    break;

                case WindowMessages.WM_LBUTTONDBLCLK:
                case WindowMessages.WM_MBUTTONDBLCLK:
                case WindowMessages.WM_RBUTTONDBLCLK:
                case WindowMessages.WM_XBUTTONDBLCLK:
                    OnMouseDoubleClick(new MouseEventArgs(buttons, 2, x, y, 0));
                    break;

                case WindowMessages.WM_MOVE:
                    bounds.X = x;
                    bounds.Y = y;
                    OnLocationChanged(EventArgs.Empty);
                    break;

                case WindowMessages.WM_SIZE:
                    RefreshSize();
                    OnSizeChanged(EventArgs.Empty);
                    break;
            }

            return false;
        }

        void RefreshSize()
        {
            RECT clientBounds = new RECT();
            NativeMethods.GetClientRect(Handle, out clientBounds);
            clientSize = new Size(clientBounds.Right - clientBounds.Left, clientBounds.Bottom - clientBounds.Top);

            NativeMethods.GetWindowRect(Handle, out clientBounds);
            bounds = clientBounds.ToRectangle();
        }

        void UpdatePosition()
        {
            NativeMethods.SetWindowPos(Handle, Win32Interop.HWND_TOP, bounds.X, bounds.Y, bounds.Width, bounds.Height, Win32Interop.SWP_NOSIZE);
        }

        void UpdateSize()
        {
            NativeMethods.SetWindowPos(Handle, Win32Interop.HWND_TOP, bounds.X, bounds.Y, bounds.Width, bounds.Height, Win32Interop.SWP_NOMOVE);
        }

        void UpdateBounds()
        {
            NativeMethods.SetWindowPos(Handle, Win32Interop.HWND_TOP, bounds.X, bounds.Y, bounds.Width, bounds.Height, 0);
        }

        void UpdateClientSize()
        {
            var clientBounds = new RECT(0, 0, clientSize.Width, clientSize.Height);
            NativeMethods.AdjustWindowRectEx(ref clientBounds, Win32Interop.WS_OVERLAPPEDWINDOW, false, Win32Interop.WS_EX_OVERLAPPEDWINDOW);

            NativeMethods.SetWindowPos(Handle, Win32Interop.HWND_TOP, bounds.X, bounds.Y, clientBounds.Right - clientBounds.Left, 
                clientBounds.Bottom - clientBounds.Top, Win32Interop.SWP_NOMOVE);
        }
    }
}

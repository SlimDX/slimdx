using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.ObjectModel;

namespace Interface
{
    #region ControlState

    /// <summary>
    /// Specifies possible control states.
    /// </summary>
    public enum ControlState
    {
        /// <summary>
        /// Normal control state.
        /// </summary>
        Normal,

        /// <summary>
        /// The control is disabled.
        /// </summary>
        Disabled,

        /// <summary>
        /// The control is hidden.
        /// </summary>
        Hidden,

        /// <summary>
        /// The control is focused.
        /// </summary>
        Focus,

        /// <summary>
        /// The mouse is over the control
        /// </summary>
        MouseOver,

        /// <summary>
        /// The control is pressed.
        /// </summary>
        Pressed
    }

    #endregion

    /// <summary>
    /// Represents a user interface element.
    /// </summary>
    public abstract class Control
    {
        #region Variables

        // variables
        bool hasFocus;
        bool isMouseDown;

        #endregion

        #region Events

        /// <summary>
        /// Occurs when the control is clicked.
        /// </summary>
        public event EventHandler Click;

        /// <summary>
        /// Occurs when the control loses focus.
        /// </summary>
        public event EventHandler LostFocus;

        /// <summary>
        /// Occurs when the control receives focus.
        /// </summary>
        public event EventHandler GotFocus;

        /// <summary>
        /// Occurs when the mouse enters the dialog.
        /// </summary>
        public event EventHandler MouseEnter;

        /// <summary>
        /// Occurs when the mouse leaves the dialog.
        /// </summary>
        public event EventHandler MouseLeave;

        /// <summary>
        /// Occurs when the control's hotkey is invoked.
        /// </summary>
        public event EventHandler HotKeyInvoked;

        /// <summary>
        /// Occurs when the mouse moves over the control.
        /// </summary>
        public event System.Windows.Forms.MouseEventHandler MouseMove;

        /// <summary>
        /// Occurs when the mouse wheel is spun.
        /// </summary>
        public event System.Windows.Forms.MouseEventHandler MouseWheel;

        /// <summary>
        /// Occurs when a mouse button is released.
        /// </summary>
        public event System.Windows.Forms.MouseEventHandler MouseUp;

        /// <summary>
        /// Occurs when a mouse button is pressed.
        /// </summary>
        public event System.Windows.Forms.MouseEventHandler MouseDown;

        /// <summary>
        /// Occurs when a key is pressed.
        /// </summary>
        public event System.Windows.Forms.KeyEventHandler KeyDown;

        /// <summary>
        /// Occurs when a key is released.
        /// </summary>
        public event System.Windows.Forms.KeyEventHandler KeyUp;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>The name.</value>
        public string Name
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the X position.
        /// </summary>
        /// <value>The X position.</value>
        public int X
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the Y position.
        /// </summary>
        /// <value>The Y position.</value>
        public int Y
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the width.
        /// </summary>
        /// <value>The width.</value>
        public int Width
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the height.
        /// </summary>
        /// <value>The height.</value>
        public int Height
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the size.
        /// </summary>
        /// <value>The size.</value>
        public Size Size
        {
            get { return new Size(Width, Height); }
            set { Width = value.Width; Height = value.Height; }
        }

        /// <summary>
        /// Gets or sets the location.
        /// </summary>
        /// <value>The location.</value>
        public Point Location
        {
            get { return new Point(X, Y); }
            set { X = value.X; Y = value.Y; }
        }

        /// <summary>
        /// Gets or sets the bounds.
        /// </summary>
        /// <value>The bounds.</value>
        public Rectangle Bounds
        {
            get { return new Rectangle(X, Y, Width, Height); }
            set { X = value.X; Y = value.Y; Width = value.Width; Height = value.Height; }
        }

        /// <summary>
        /// Gets the parent dialog.
        /// </summary>
        /// <value>The parent dialog.</value>
        public Dialog Parent
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is visible.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is visible; otherwise, <c>false</c>.
        /// </value>
        public bool IsVisible
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is enabled.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is enabled; otherwise, <c>false</c>.
        /// </value>
        public virtual bool IsEnabled
        {
            get;
            set;
        }

        /// <summary>
        /// Gets a value indicating whether this instance can have focus.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance can have focus; otherwise, <c>false</c>.
        /// </value>
        public virtual bool CanHaveFocus
        {
            get { return false; }
        }

        /// <summary>
        /// Gets a value indicating whether this instance has focus.
        /// </summary>
        /// <value><c>true</c> if this instance has focus; otherwise, <c>false</c>.</value>
        public bool HasFocus
        {
            get { return hasFocus; }
            set
            {
                // avoid unecessary changes
                if (hasFocus == value)
                    return;

                // update the value
                hasFocus = value;

                // check if we now have the focus
                if (hasFocus && Parent != null && Parent.FocusControl != this)
                {
                    // update the state
                    Parent.ClearFocus();
                    Parent.FocusControl = this;
                }
            }
        }

        /// <summary>
        /// Gets or sets the hotkey.
        /// </summary>
        /// <value>The hotkey.</value>
        public Keys HotKey
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets user defined data associated with the control.
        /// </summary>
        /// <value>The user defined data associated with the control.</value>
        public object Tag
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the drawing elements.
        /// </summary>
        /// <value>The drawing elements.</value>
        protected Collection<DrawingElement> DrawingElements
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets a value indicating whether the mouse is over the control.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if the mouse is over the control; otherwise, <c>false</c>.
        /// </value>
        public bool IsMouseOver
        {
            get;
            private set;
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="Control"/> class.
        /// </summary>
        protected Control()
        {
            // create the collection
            DrawingElements = new Collection<DrawingElement>();

            // set default values
            IsVisible = true;
            IsEnabled = true;
        }

        #endregion

        #region Methods

        /// <summary>
        /// Determines whether the control contains the specified point.
        /// </summary>
        /// <param name="point">The point.</param>
        /// <returns>
        /// 	<c>true</c> if the control contains the specified point; otherwise, <c>false</c>.
        /// </returns>
        protected internal virtual bool ContainsPoint(Point point)
        {
            // default is to just check the bounds
            return Bounds.Contains(point);
        }

        /// <summary>
        /// Updates the control.
        /// </summary>
        /// <param name="elapsedTime">The elapsed time.</param>
        protected internal virtual void Update(float elapsedTime)
        {
        }

        /// <summary>
        /// Renders the control.
        /// </summary>
        protected internal virtual void Render()
        {
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Raises the <see cref="E:LostFocus"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnLostFocus(EventArgs e)
        {
            // update the state
            HasFocus = false;

            // raise the event
            if (LostFocus != null)
                LostFocus(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:GotFocus"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnGotFocus(EventArgs e)
        {
            // update the state
            HasFocus = true;

            // raise the event
            if (GotFocus != null)
                GotFocus(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:Click"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnClick(EventArgs e)
        {
            // raise the event
            if (Click != null)
                Click(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:MouseEnter"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnMouseEnter(EventArgs e)
        {
            // raise the event
            if (MouseEnter != null)
                MouseEnter(this, e);

            // mouse is over
            IsMouseOver = true;
        }

        /// <summary>
        /// Raises the <see cref="E:MouseLeave"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnMouseLeave(EventArgs e)
        {
            // raise the event
            if (MouseLeave != null)
                MouseLeave(this, e);

            // mouse is not over
            IsMouseOver = false;
        }

        /// <summary>
        /// Raises the <see cref="E:MouseDown"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnMouseDown(System.Windows.Forms.MouseEventArgs e)
        {
            // raise the event
            if (MouseDown != null)
                MouseDown(this, e);

            // the mouse is now down
            if (e.Button == MouseButtons.Left)
                isMouseDown = true;
        }

        /// <summary>
        /// Raises the <see cref="E:MouseUp"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnMouseUp(System.Windows.Forms.MouseEventArgs e)
        {
            // raise the event
            if (MouseUp != null)
                MouseUp(this, e);

            // if the mouse was down, we just got a click
            if (isMouseDown && e.Button == MouseButtons.Left)
            {
                // raise the event
                OnClick(EventArgs.Empty);
                isMouseDown = false;
            }
        }

        /// <summary>
        /// Raises the <see cref="E:MouseWheel"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnMouseWheel(System.Windows.Forms.MouseEventArgs e)
        {
            // raise the event
            if (MouseWheel != null)
                MouseWheel(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:MouseMove"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnMouseMove(System.Windows.Forms.MouseEventArgs e)
        {
            // raise the event
            if (MouseMove != null)
                MouseMove(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:KeyDown"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnKeyDown(System.Windows.Forms.KeyEventArgs e)
        {
            // raise the event
            if (KeyDown != null)
                KeyDown(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:KeyUp"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnKeyUp(System.Windows.Forms.KeyEventArgs e)
        {
            // raise the event
            if (KeyUp != null)
                KeyUp(this, e);
        }

        /// <summary>
        /// Raises the <see cref="E:HotKeyInvoked"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal virtual void OnHotKeyInvoked(EventArgs e)
        {
            // raise the event
            if (HotKeyInvoked != null)
                HotKeyInvoked(this, e);
        }

        #endregion
    }
}

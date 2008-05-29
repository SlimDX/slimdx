using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using SlimDX;
using SlimDX.Direct3D9;

namespace Interface
{
    /// <summary>
    /// Represents a user interface form.
    /// </summary>
    public class Dialog
    {
        #region Variables

        // variables
        bool isModal;
        Control mouseOverControl;

        #endregion

        #region Events

        /// <summary>
        /// Occurs when the dialog is clicked.
        /// </summary>
        public event EventHandler Click;

        /// <summary>
        /// Occurs when the mouse enters the dialog.
        /// </summary>
        public event EventHandler MouseEnter;

        /// <summary>
        /// Occurs when the mouse leaves the dialog.
        /// </summary>
        public event EventHandler MouseLeave;

        /// <summary>
        /// Occurs when the mouse moves over the dialog.
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
        /// Gets the focused control.
        /// </summary>
        /// <value>The focused control.</value>
        public Control FocusControl
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the color of the top left corner.
        /// </summary>
        /// <value>The color of the top left corner.</value>
        public Color4 TopLeftColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the color of the top right corner.
        /// </summary>
        /// <value>The color of the top right corner.</value>
        public Color4 TopRightColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the color of the bottom left corner.
        /// </summary>
        /// <value>The color of the bottom left corner.</value>
        public Color4 BottomLeftColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the color of the bottom right corner.
        /// </summary>
        /// <value>The color of the bottom right corner.</value>
        public Color4 BottomRightColor
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the parent manager.
        /// </summary>
        /// <value>The parent manager.</value>
        public InterfaceManager Parent
        {
            get;
            internal set;
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
        public bool IsEnabled
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is modal.
        /// </summary>
        /// <value><c>true</c> if this instance is modal; otherwise, <c>false</c>.</value>
        public bool IsModal
        {
            get { return isModal; }
            set
            {
                // avoid unecessary changes
                if (isModal == value)
                    return;

                // update the value
                isModal = value;

                // check if we are now modal
                if (isModal)
                {
                    // update the state
                    Parent.ModalDialog.IsModal = false;
                    Parent.ModalDialog = this;
                }
            }
        }

        /// <summary>
        /// Gets the controls associated with the dialog.
        /// </summary>
        /// <value>The controls.</value>
        public ControlCollection Controls
        {
            get;
            private set;
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="Dialog"/> class.
        /// </summary>
        /// <param name="parent">The parent manager.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="parent"/> is <c>null</c>.</exception>
        public Dialog(InterfaceManager parent)
        {
            // error checking
            if (parent == null)
                throw new ArgumentNullException("parent");

            // store the parent
            Parent = parent;

            // create the collection
            Controls = new ControlCollection(this);

            // default values
            IsVisible = true;
            IsEnabled = true;
            TopLeftColor = new Color4(0);
            TopRightColor = new Color4(0);
            BottomLeftColor = new Color4(0);
            BottomRightColor = new Color4(0);
            Width = 500;
            Height = 500;
        }

        #endregion

        #region Methods

        /// <summary>
        /// Cycles the focus between controls.
        /// </summary>
        public void CycleFocus()
        {
            // get the set of visible controls
            List<Control> validControls = Controls.Where(c => c.IsVisible && c.IsEnabled && c.CanHaveFocus).ToList();
            if (validControls.Count == 0)
                return;

            // check if we have only one item
            if (validControls.Count == 1)
            {
                // if the control isn't focused, focus it now
                if (FocusControl == null)
                {
                    // focus in
                    FocusControl = validControls[0];
                    FocusControl.OnGotFocus(EventArgs.Empty);
                }
                return;
            }

            // otherwise, cycle the current control forward one
            int index = 0;
            if (FocusControl != null)
                index = validControls.IndexOf(FocusControl) + 1;

            // clear the focus
            ClearFocus();

            // check for wrap-around
            if (index >= validControls.Count)
                index = 0;

            // focus on the correct control
            Control control = validControls[index];
            FocusControl = control;
            control.OnGotFocus(EventArgs.Empty);
        }

        /// <summary>
        /// Draws a rectangle.
        /// </summary>
        /// <param name="rectangle">The rectangle.</param>
        /// <param name="color">The color.</param>
        public void DrawRectangle(Rectangle rectangle, Color4 color)
        {
            // offset the rectangle
            rectangle.Offset(X, Y);

            // build up the vertices
            ScreenVertex[] vertices = new ScreenVertex[] {
                new ScreenVertex((float)rectangle.Left - 0.5f, (float)rectangle.Top - 0.5f, 0.5f, 1.0f, (int)color, 0, 0),
                new ScreenVertex((float)rectangle.Right - 0.5f, (float)rectangle.Top - 0.5f, 0.5f, 1.0f, (int)color, 0, 0),
                new ScreenVertex((float)rectangle.Right - 0.5f, (float)rectangle.Bottom - 0.5f, 0.5f, 1.0f, (int)color, 0, 0),
                new ScreenVertex((float)rectangle.Left - 0.5f, (float)rectangle.Bottom - 0.5f, 0.5f, 1.0f, (int)color, 0, 0)};
        
            // flush the sprite
            Parent.Sprite.Flush();
            VertexDeclaration store = Parent.Device.VertexDeclaration;

            // set states
            Parent.Device.VertexFormat = ScreenVertex.Format;
            Parent.Device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.SelectArg2);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.SelectArg2);

            // draw the vertices
            Parent.Device.DrawUserPrimitives(PrimitiveType.TriangleFan, 0, 2, vertices);

            // reset the state
            Parent.Device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.Modulate);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.Modulate);
            Parent.Device.VertexDeclaration = store;
        }

        /// <summary>
        /// Draws a polyline.
        /// </summary>
        /// <param name="points">The polyline points.</param>
        /// <param name="color">The color.</param>
        public void DrawPolyline(Point[] points, Color4 color)
        {
            // build up the vertices
            ScreenVertex[] vertices = new ScreenVertex[points.Length];
            for (int i = 0; i < points.Length; i++)
                vertices[i] = new ScreenVertex((float)points[i].X + X, (float)points[i].Y + Y, 0.5f, 1.0f, (int)color, 0, 0);

            // flush the sprite
            Parent.Sprite.Flush();
            VertexDeclaration store = Parent.Device.VertexDeclaration;

            // set states
            Parent.Device.VertexFormat = ScreenVertex.Format;
            Parent.Device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.SelectArg2);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.SelectArg2);

            // draw the vertices
            Parent.Device.DrawUserPrimitives(PrimitiveType.LineStrip, vertices.Length, 2, vertices);

            // reset the state
            Parent.Device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.Modulate);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.Modulate);
            Parent.Device.VertexDeclaration = store;
        }

        /// <summary>
        /// Draws a sprite.
        /// </summary>
        /// <param name="element">The drawing element.</param>
        /// <param name="destinationRectangle">The destination rectangle.</param>
        public void DrawSprite(DrawingElement element, Rectangle destinationRectangle)
        {
            // offset the rectangle
            destinationRectangle.Offset(X, Y);

            // figure out the scaling
            float scaleX = (float)destinationRectangle.Width / element.TextureRectangle.Width;
            float scaleY = (float)destinationRectangle.Height / element.TextureRectangle.Height;

            // figure out the position
            Vector3 position = new Vector3((float)destinationRectangle.Left, (float)destinationRectangle.Top, 0.0f);
            position.X /= scaleX;
            position.Y /= scaleY;

            // draw the sprite
            Parent.Sprite.Transform = Matrix.Scaling(scaleX, scaleY, 1.0f);
            Parent.Sprite.Draw(Parent.Texture, element.TextureRectangle, Vector3.Zero, position, element.TextureColor.CurrentColor);
        }

        /// <summary>
        /// Calculates a text rectangle.
        /// </summary>
        /// <param name="text">The text.</param>
        /// <param name="element">The drawing element.</param>
        /// <returns>The bounding rectangle for the text.</returns>
        public Rectangle CalculateTextRectangle(string text, DrawingElement element)
        {
            // setup the format
            DrawTextFormat format = element.TextFormat | DrawTextFormat.CalcRect;

            // grab the font
            SlimDX.Direct3D9.Font font = element.CachedFont == null ? Parent.DefaultFont.Font : element.CachedFont.Font;

            // calculate the dimensions
            return font.MeasureString(null, text, format);
        }

        /// <summary>
        /// Draws a string of text.
        /// </summary>
        /// <param name="text">The text.</param>
        /// <param name="element">The drawing element.</param>
        /// <param name="destinationRectangle">The destination rectangle.</param>
        public void DrawText(string text, DrawingElement element, Rectangle destinationRectangle)
        {
            // call the overload
            DrawText(text, element, destinationRectangle, false);
        }

        /// <summary>
        /// Draws a string of text.
        /// </summary>
        /// <param name="text">The text.</param>
        /// <param name="element">The drawing element.</param>
        /// <param name="destinationRectangle">The destination rectangle.</param>
        /// <param name="shadow">if set to <c>true</c>, draw a shadow as well.</param>
        public void DrawText(string text, DrawingElement element, Rectangle destinationRectangle, bool shadow)
        {
            // don't draw fully transparent layers
            if (element.FontColor.CurrentColor.Alpha == 0)
                return;

            // offset the rectangle
            destinationRectangle.Offset(X, Y);

            // reset the transform
            Parent.Sprite.Transform = Matrix.Identity;

            // grab the font
            SlimDX.Direct3D9.Font font = element.CachedFont == null ? Parent.DefaultFont.Font : element.CachedFont.Font;

            // check if we should draw a shadow
            if (shadow)
            {
                // draw the shadow
                Rectangle shadowRect = destinationRectangle;
                destinationRectangle.Offset(1, 1);
                font.DrawString(Parent.Sprite, text, shadowRect, element.TextFormat, new Color4(element.FontColor.CurrentColor.Alpha, 0, 0, 0));
            }

            // draw the text
            font.DrawString(Parent.Sprite, text, destinationRectangle, element.TextFormat, element.FontColor.CurrentColor);
        }

        /// <summary>
        /// Brings the dialog to the front.
        /// </summary>
        public void BringToFront()
        {
            // pop this dialog up to the top of the list
            Parent.Dialogs.Remove(this);
            Parent.Dialogs.Add(this);
        }

        /// <summary>
        /// Sends the dialog to the background.
        /// </summary>
        public void SendToBack()
        {
            // move the dialog up to the first spot in the collection
            Parent.Dialogs.Remove(this);
            Parent.Dialogs.Insert(0, this);
        }

        /// <summary>
        /// Clears the focus from any controls.
        /// </summary>
        public void ClearFocus()
        {
            // check if we have a focus control
            if (FocusControl != null)
            {
                // clear the focus
                if (FocusControl.HasFocus)
                    FocusControl.OnLostFocus(EventArgs.Empty);
                FocusControl = null;
            }
        }

        /// <summary>
        /// Updates the dialog.
        /// </summary>
        /// <param name="elapsedTime">The elapsed time.</param>
        public void Update(float elapsedTime)
        {
            // update each control
            foreach (Control control in Controls)
                control.Update(elapsedTime);
        }

        /// <summary>
        /// Renders the dialog.
        /// </summary>
        public void Render()
        {
            // make sure we are visible
            if (!IsVisible)
                return;

            // check if we have a background
            if (TopLeftColor.Alpha != 0 || TopRightColor.Alpha != 0 || BottomLeftColor.Alpha != 0 || BottomRightColor.Alpha != 0)
            {
                // set texture stage states
                Parent.Device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.SelectArg2);
                Parent.Device.SetTextureStageState(0, TextureStage.ColorArg2, TextureArgument.Diffuse);
                Parent.Device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.SelectArg1);
                Parent.Device.SetTextureStageState(0, TextureStage.AlphaArg1, TextureArgument.Diffuse);

                // build up the vertices
                UntexturedScreenVertex[] vertices = new UntexturedScreenVertex[] {
                    new UntexturedScreenVertex((float)X,           (float)Y,          0.5f, 1.0f, (int)TopLeftColor),
                    new UntexturedScreenVertex((float)X + Width,   (float)Y,          0.5f, 1.0f, (int)TopRightColor),
                    new UntexturedScreenVertex((float)X + Width,   (float)Y + Height, 0.5f, 1.0f, (int)BottomRightColor),
                    new UntexturedScreenVertex((float)X,           (float)Y + Height, 0.5f, 1.0f, (int)BottomLeftColor) };
            
                // set the declaration and render
                Parent.Device.VertexFormat = UntexturedScreenVertex.Format;
                Parent.Device.DrawUserPrimitives(PrimitiveType.TriangleFan, 0, 2, vertices);
            }

            // set texture stage states
            Parent.Device.SetTextureStageState(0, TextureStage.ColorOperation, TextureOperation.Modulate);
            Parent.Device.SetTextureStageState(0, TextureStage.ColorArg1, TextureArgument.Texture);
            Parent.Device.SetTextureStageState(0, TextureStage.ColorArg2, TextureArgument.Diffuse);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaOperation, TextureOperation.Modulate);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaArg1, TextureArgument.Texture);
            Parent.Device.SetTextureStageState(0, TextureStage.AlphaArg2, TextureArgument.Diffuse);

            // start sprite drawing
            Parent.Sprite.Begin(SpriteFlags.DoNotSaveState);

            // draw all of the controls
            foreach (Control control in Controls)
                control.Render();

            // end sprite drawing
            Parent.Sprite.End();
        }

        /// <summary>
        /// Closes the dialog.
        /// </summary>
        public void Close()
        {
            // hide, disable, and remove from parent
            IsEnabled = false;
            IsVisible = false;
            Parent.Dialogs.Remove(this);
        }

        #endregion

        #region Event Handlers

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

            // make sure the mouse over control is still valid
            if (mouseOverControl != null && (!mouseOverControl.IsEnabled || !mouseOverControl.IsVisible))
                mouseOverControl = null;

            // check if we have a focus control that can handle this
            if (FocusControl != null)
            {
                // check if the mouse is still over the focus control
                if (FocusControl.ContainsPoint(e.Location))
                {
                    // handle it
                    FocusControl.OnMouseDown(new System.Windows.Forms.MouseEventArgs(
                        e.Button, e.Clicks, e.X - FocusControl.X, e.Y - FocusControl.Y, e.Delta));
                    return;
                }
                else
                {
                    // otherwise, this is no longer the focus control
                    FocusControl.OnLostFocus(EventArgs.Empty);
                    FocusControl = null;
                }
            }

            // otherwise, check to see if a new control now has the focus
            if (mouseOverControl != null)
            {
                // check if this control can receive focus
                if (mouseOverControl.CanHaveFocus)
                    mouseOverControl.OnGotFocus(EventArgs.Empty);

                // let it handle the message regardless
                mouseOverControl.OnMouseDown(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverControl.X, e.Y - mouseOverControl.Y, e.Delta));
            }
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
            OnClick(EventArgs.Empty);

            // make sure the mouse over control is still valid
            if (mouseOverControl != null && (!mouseOverControl.IsEnabled || !mouseOverControl.IsVisible))
                mouseOverControl = null;

            // otherwise, check to see if control has the mouse over it
            if (mouseOverControl != null)
                mouseOverControl.OnMouseUp(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverControl.X, e.Y - mouseOverControl.Y, e.Delta));
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

            // make sure the mouse over control is still valid
            if (mouseOverControl != null && (!mouseOverControl.IsEnabled || !mouseOverControl.IsVisible))
                mouseOverControl = null;

            // if we have a mouse over control stored already, see if the mouse has left it yet
            if (mouseOverControl != null)
            {
                // check if the mouse is still over, or if it has left
                if (mouseOverControl.ContainsPoint(e.Location))
                {
                    // we found the right control already
                    mouseOverControl.OnMouseMove(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverControl.X, e.Y - mouseOverControl.Y, e.Delta));
                    return;
                }
                else
                {
                    // the mouse has left
                    mouseOverControl.OnMouseLeave(EventArgs.Empty);
                    mouseOverControl = null;
                }
            }

            // otherwise, check to see if the mouse is now over another control
            for (int i = Controls.Count - 1; i >= 0; i--)
            {
                // make sure the dialog is both visible and enabled
                if (!Controls[i].IsVisible || !Controls[i].IsEnabled)
                    continue;

                // check to see if the mouse has entered this dialog
                if (Controls[i].ContainsPoint(e.Location))
                {
                    // yes it has, update the state accordingly
                    mouseOverControl = Controls[i];
                    Controls[i].OnMouseEnter(EventArgs.Empty);
                    Controls[i].OnMouseMove(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverControl.X, e.Y - mouseOverControl.Y, e.Delta));
                    break;
                }
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

            // check if we have a focused control that can handle this
            if (FocusControl != null)
            {
                // handle it
                FocusControl.OnMouseWheel(new System.Windows.Forms.MouseEventArgs(
                        e.Button, e.Clicks, e.X - FocusControl.X, e.Y - FocusControl.Y, e.Delta));
                return;
            }

            // make sure the mouse over control is still valid
            if (mouseOverControl != null && (!mouseOverControl.IsEnabled || !mouseOverControl.IsVisible))
                mouseOverControl = null;

            // if we have a mouse over control, let it know that the mouse wheel just moved
            if (mouseOverControl != null)
                mouseOverControl.OnMouseWheel(new System.Windows.Forms.MouseEventArgs(
                    e.Button, e.Clicks, e.X - mouseOverControl.X, e.Y - mouseOverControl.Y, e.Delta));
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

            // check if we have a focused control that can handle this
            if (FocusControl != null)
                FocusControl.OnKeyDown(e);
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

            // check if we have a focused control that can handle this
            if (FocusControl != null)
            {
                // handle it
                FocusControl.OnKeyDown(e);
                if (e.Handled)
                    return;
            }

            // if we have the tab key, cycle the focus
            if (e.KeyCode == System.Windows.Forms.Keys.Tab)
                CycleFocus();

            // otherwise, see if a control has a corresponding hotkey
            foreach (Control control in Controls)
                if (control.HotKey == e.KeyCode)
                    control.OnHotKeyInvoked(EventArgs.Empty);
        }

        #endregion
    }
}

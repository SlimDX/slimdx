using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using SlimDX.Direct3D9;

namespace Interface
{
    /// <summary>
    /// Represents a check box control.
    /// </summary>
    public class CheckBox : TextControl
    {
        #region Variables

        // variables
        bool pressed;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="CheckBox"/> is checked.
        /// </summary>
        /// <value><c>true</c> if checked; otherwise, <c>false</c>.</value>
        public virtual bool Checked
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
        public override bool CanHaveFocus
        {
            get { return IsVisible && IsEnabled; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="CheckBox"/> class.
        /// </summary>
        public CheckBox()
        {
            // set default values
            Padding = new System.Windows.Forms.Padding(0, 5, 0, 5);

            // create the box element
            DrawingElement box = new DrawingElement();
            box.TextureRectangle = new Rectangle(0, 54, 27, 27);
            box.TextFormat = DrawTextFormat.Left | DrawTextFormat.VerticalCenter;
            box.FontColor.States[(int)ControlState.Disabled] = Color.FromArgb(200, 200, 200, 200);
            box.TextureColor.States[(int)ControlState.Normal] = Color.FromArgb(150, 255, 255, 255);
            box.TextureColor.States[(int)ControlState.Focus] = Color.FromArgb(200, 255, 255, 255);
            box.TextureColor.States[(int)ControlState.Pressed] = Color.FromArgb(255, 255, 255, 255);

            // create the check element
            DrawingElement check = new DrawingElement();
            check.TextureRectangle = new Rectangle(27, 54, 27, 27);

            // add the elements
            DrawingElements.Add(box);
            DrawingElements.Add(check);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="CheckBox"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public CheckBox(DrawingElement[] elements)
        {
            // set default values
            Padding = new System.Windows.Forms.Padding(0, 5, 0, 5);

            // add the items
            DrawingElements.AddRange(elements);
        }

        #endregion

        #region Methods

        /// <summary>
        /// Gets the preferred size of the control.
        /// </summary>
        /// <returns>The preferred size of the control.</returns>
        protected override Size GetPreferredSize()
        {
            // calculate the preferred size
            Size size = base.GetPreferredSize();
            size.Width += (int)(1.25f * Height);

            // return the desired size
            return size;
        }

        /// <summary>
        /// Updates the control.
        /// </summary>
        /// <param name="elapsedTime">The elapsed time.</param>
        protected internal override void Update(float elapsedTime)
        {
            // call the base method
            base.Update(elapsedTime);

            // determine the destination state
            ControlState state = ControlState.Normal;
            if (!IsVisible)
                state = ControlState.Hidden;
            else if (!IsEnabled)
                state = ControlState.Disabled;
            else if (pressed)
                state = ControlState.Pressed;
            else if (IsMouseOver)
                state = ControlState.MouseOver;
            else if (HasFocus)
                state = ControlState.Focus;

            // figure out the rate
            float rate = (state == ControlState.Pressed) ? 0.0f : 0.8f;

            // blend the colors
            DrawingElements[0].TextureColor.Blend(state, elapsedTime, rate);
            DrawingElements[0].FontColor.Blend(state, elapsedTime, rate);

            // if we aren't checked, don't show the check mark
            if (!Checked)
                state = ControlState.Hidden;

            // blend the colors
            DrawingElements[1].TextureColor.Blend(state, elapsedTime, rate);
        }

        /// <summary>
        /// Renders the control.
        /// </summary>
        protected internal override void Render()
        {
            // call the base method
            base.Render();

            // create the rectangles
            Rectangle buttonRectangle = new Rectangle(X, Y, Height, Height);
            Rectangle textRectangle = new Rectangle(X + (int)(1.25f * Height), Y, Width, Height);

            // draw the base element
            Parent.DrawSprite(DrawingElements[0], buttonRectangle);
            Parent.DrawText(Text, DrawingElements[0], textRectangle, true);

            // draw the check
            Parent.DrawSprite(DrawingElements[1], buttonRectangle);
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Raises the <see cref="E:Click"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnClick(EventArgs e)
        {
            // update the checked state
            Checked = !Checked;

            // call the base method
            base.OnClick(e);
        }

        /// <summary>
        /// Raises the <see cref="E:HotKeyInvoked"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnHotKeyInvoked(EventArgs e)
        {
            // call the base method
            base.OnHotKeyInvoked(e);

            // request focus
            HasFocus = true;

            // send the click event
            OnClick(EventArgs.Empty);
        }

        /// <summary>
        /// Raises the <see cref="E:MouseDown"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal override void OnMouseDown(System.Windows.Forms.MouseEventArgs e)
        {
            // call the base method
            base.OnMouseDown(e);

            // pressed
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                // update state
                HasFocus = true;
                pressed = true;
            }
        }

        /// <summary>
        /// Raises the <see cref="E:MouseUp"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal override void OnMouseUp(System.Windows.Forms.MouseEventArgs e)
        {
            // call the base method
            base.OnMouseUp(e);

            // not pressed
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                pressed = false;
        }

        /// <summary>
        /// Raises the <see cref="E:MouseLeave"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnMouseLeave(EventArgs e)
        {
            // call the base method
            base.OnMouseLeave(e);

            // mouse left
            pressed = false;
        }

        #endregion
    }
}

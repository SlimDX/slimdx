using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using SlimDX;

namespace Interface
{
    /// <summary>
    /// Represents a clickable button.
    /// </summary>
    public class Button : TextControl
    {
        #region Properties

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

        /// <summary>
        /// Gets or sets a value indicating whether the button should pulse when it has the focus.
        /// </summary>
        /// <value><c>true</c> if the button should pulse when it has the focus; otherwise, <c>false</c>.</value>
        public bool PulseOnFocus
        {
            get;
            set;
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="Button"/> class.
        /// </summary>
        public Button()
        {
            // set default values
            PulseOnFocus = true;
            Padding = new System.Windows.Forms.Padding(15, 5, 15, 5);

            // create the fill layer element
            DrawingElement fill = new DrawingElement();
            fill.TextureRectangle = new Rectangle(0, 0, 136, 54);
            fill.TextureColor.States[(int)ControlState.Normal] = Color.FromArgb(150, 255, 255, 255);
            fill.TextureColor.States[(int)ControlState.Pressed] = Color.FromArgb(200, 255, 255, 255);
            fill.FontColor.States[(int)ControlState.MouseOver] = Color.FromArgb(255, 0, 0, 0);

            // create the main layer element
            DrawingElement main = new DrawingElement();
            main.TextureRectangle = new Rectangle(136, 0, 116, 54);
            main.TextureColor = new BlendColor(Color.FromArgb(0, 255, 255, 255));
            main.TextureColor.States[(int)ControlState.MouseOver] = Color.FromArgb(160, 255, 255, 255);
            main.TextureColor.States[(int)ControlState.Pressed] = Color.FromArgb(60, 0, 0, 0);
            main.TextureColor.States[(int)ControlState.Focus] = Color.FromArgb(30, 255, 255, 255);
            main.FontColor.States[(int)ControlState.MouseOver] = Color.FromArgb(255, 0, 0, 0);

            // add the items
            DrawingElements.Add(fill);
            DrawingElements.Add(main);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Button"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public Button(DrawingElement[] elements)
        {
            // set default values
            PulseOnFocus = true;
            Padding = new System.Windows.Forms.Padding(15, 5, 15, 5);

            // add the items
            DrawingElements.AddRange(elements);
        }

        #endregion

        #region Methods

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
            else if (IsPressed)
                state = ControlState.Pressed;
            else if (IsMouseOver)
                state = ControlState.MouseOver;
            else if (HasFocus)
                state = ControlState.Focus;

            // figure out the rate
            float rate = (state == ControlState.Pressed) ? 0.0f : 0.8f;

            // blend the fonts
            DrawingElements[0].FontColor.Blend(state, elapsedTime, rate);
            DrawingElements[1].FontColor.Blend(state, elapsedTime, rate);

            // check if we need to pulse or blend
            if (state == ControlState.Focus && PulseOnFocus)
            {
                // pulse
                DrawingElements[0].TextureColor.Pulse(ControlState.Normal, ControlState.Focus, elapsedTime);
                DrawingElements[1].TextureColor.Pulse(ControlState.Normal, ControlState.Focus, elapsedTime);
            }
            else
            {
                // blend
                DrawingElements[0].TextureColor.Blend(state, elapsedTime, rate);
                DrawingElements[1].TextureColor.Blend(state, elapsedTime, rate);
            }
        }

        /// <summary>
        /// Renders the control.
        /// </summary>
        protected internal override void Render()
        {
            // call the base method
            base.Render();

            // calculate the offset
            int offsetX = 0;
            int offsetY = 0;
            if (IsPressed)
            {
                offsetX = 1;
                offsetY = 2;
            }
            else if (IsMouseOver)
            {
                offsetX = -1;
                offsetY = -2;
            }

            // get the rectangle
            Rectangle bounds = Bounds;
            bounds.Offset(offsetX, offsetY);

            // draw the fill layer
            Parent.DrawSprite(DrawingElements[0], bounds);
            Parent.DrawText(Text, DrawingElements[0], bounds);

            // draw the main layer
            Parent.DrawSprite(DrawingElements[1], bounds);
            Parent.DrawText(Text, DrawingElements[1], bounds);
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Raises the <see cref="E:HotKeyInvoked"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnHotKeyInvoked(EventArgs e)
        {
            // call the base method
            base.OnHotKeyInvoked(e);

            // send the click event
            OnClick(EventArgs.Empty);
        }

        /// <summary>
        /// Raises the <see cref="E:Click"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnClick(EventArgs e)
        {
            // request focus
            HasFocus = true;

            // call the base method
            base.OnClick(e);
        }

        #endregion
    }
}

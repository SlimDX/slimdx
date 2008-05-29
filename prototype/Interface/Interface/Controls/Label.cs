using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX;
using System.Drawing;

namespace Interface
{
    /// <summary>
    /// Represents a text label.
    /// </summary>
    public class Label : TextControl
    {
        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="Label"/> class.
        /// </summary>
        public Label()
        {
            // set default drawing elements
            DrawingElement element = new DrawingElement();
            element.FontColor.States[(int)ControlState.Disabled] = Color.FromArgb(200, 200, 200, 200);
            DrawingElements.Add(element);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Label"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public Label(DrawingElement[] elements)
        {
            // add the elements
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

            // figure out the desired state
            ControlState state = ControlState.Normal;
            if (!IsEnabled)
                state = ControlState.Disabled;

            // blend the color
            DrawingElements[0].FontColor.Blend(state, elapsedTime);
        }

        /// <summary>
        /// Renders the control.
        /// </summary>
        protected internal override void Render()
        {
            // call the base method
            base.Render();

            // draw the text
            Parent.DrawText(Text, DrawingElements[0], Bounds, true);
        }

        #endregion
    }
}

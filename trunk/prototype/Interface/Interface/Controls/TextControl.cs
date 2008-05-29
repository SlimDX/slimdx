using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX;
using System.Windows.Forms;
using System.Drawing;

namespace Interface
{
    /// <summary>
    /// Provides a base class for controls that display static text.
    /// </summary>
    public abstract class TextControl : Control
    {
        #region Properties

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        /// <value>The text.</value>
        public string Text
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the color of the text.
        /// </summary>
        /// <value>The color of the text.</value>
        public Color4 TextColor
        {
            get { return DrawingElements[0].FontColor.States[(int)ControlState.Normal]; }
            set { DrawingElements[0].FontColor.States[(int)ControlState.Normal] = value; }
        }

        /// <summary>
        /// Gets or sets the font.
        /// </summary>
        /// <value>The font.</value>
        public CachedFont Font
        {
            get { return DrawingElements[0].CachedFont; }
            set { DrawingElements[0].CachedFont = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the control should automatically size to its contents.
        /// </summary>
        /// <value><c>true</c> if the control should automatically size to its contents; otherwise, <c>false</c>.</value>
        public bool AutoSize
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the padding between the text and the outward bounds of the control.
        /// </summary>
        /// <value>The padding between the text and the outward bounds of the control.</value>
        public Padding Padding
        {
            get;
            set;
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="TextControl"/> class.
        /// </summary>
        protected TextControl()
        {
            // set initial values
            AutoSize = true;
        }

        #endregion

        #region Methods

        /// <summary>
        /// Gets the preferred size of the control.
        /// </summary>
        /// <returns>The preferred size of the control.</returns>
        protected virtual Size GetPreferredSize()
        {
            // return the size of the text
            return Parent.CalculateTextRectangle(Text, DrawingElements[0]).Size;
        }

        /// <summary>
        /// Updates the control.
        /// </summary>
        /// <param name="elapsedTime">The elapsed time.</param>
        protected internal override void Update(float elapsedTime)
        {
            // call the base method
            base.Update(elapsedTime);

            // check if we need to autosize
            Size size = GetPreferredSize();
            if (AutoSize && size != Size.Empty)
            {
                // resize
                Size = size;
                Width += Padding.Horizontal;
                Height += Padding.Vertical;
            }
        }

        #endregion
    }
}

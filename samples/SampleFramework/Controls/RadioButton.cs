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
using System.Drawing;

namespace SampleFramework
{
    /// <summary>
    /// Represents a radio button control.
    /// </summary>
    public class RadioButton : CheckBox
    {
        /// <summary>
        /// Gets or sets the radio group.
        /// </summary>
        /// <value>The radio group.</value>
        public int Group
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="CheckBox"/> is checked.
        /// </summary>
        /// <value><c>true</c> if checked; otherwise, <c>false</c>.</value>
        public override bool Checked
        {
            get { return base.Checked; }
            set
            {
                // avoid unecessary changes
                if (value == base.Checked)
                    return;

                // update the value
                base.Checked = value;

                // clear any other radio buttons with the same group
                UpdateRadioButtons();
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="RadioButton"/> class.
        /// </summary>
        public RadioButton()
        {
            // update the base elements
            DrawingElements[0].TextureRectangle = new Rectangle(54, 54, 27, 27);
            DrawingElements[1].TextureRectangle = new Rectangle(81, 54, 27, 27);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="RadioButton"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public RadioButton(DrawingElement[] elements)
            : base(elements)
        {
        }

        /// <summary>
        /// Raises the <see cref="E:Click"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnClick(EventArgs e)
        {
            // don't let clicks make the checked state false
            Checked = false;

            // call the base method
            base.OnClick(e);
        }

        /// <summary>
        /// Updates the radio buttons.
        /// </summary>
        void UpdateRadioButtons()
        {
            // if we are checked, uncheck all other radio buttons with the same group
            if (Checked && Parent != null)
            {
                // grab the other radio buttons
                foreach (Control control in Parent.Controls)
                {
                    // only select radio buttons
                    RadioButton button = control as RadioButton;
                    if (button != null && button != this && button.Group == Group)
                        button.Checked = false;
                }
            }
        }
    }
}

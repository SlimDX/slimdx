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
using System.Drawing;

namespace SampleFramework
{
    /// <summary>
    /// Represents a text label.
    /// </summary>
    public class Label : TextControl
    {
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
            // add the items
            foreach (DrawingElement element in elements)
                DrawingElements.Add(element);
        }

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
    }
}

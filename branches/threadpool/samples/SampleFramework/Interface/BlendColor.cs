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
using SlimDX;

namespace SampleFramework
{
    /// <summary>
    /// Represents a blendable color.
    /// </summary>
    public class BlendColor : ICloneable
    {
        // constants
        const float cutoff = (float)Math.PI * 1000.0f;

        // variables
        float storedTime;

        /// <summary>
        /// Gets the possible states associated with the color.
        /// </summary>
        /// <value>The states.</value>
        public Color4[] States
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the current blended color.
        /// </summary>
        /// <value>The current blended color.</value>
        public Color4 CurrentColor
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="BlendColor"/> class.
        /// </summary>
        public BlendColor()
            : this(Color.FromArgb(255, 255, 255, 255))
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="BlendColor"/> class.
        /// </summary>
        /// <param name="normalValue">The value.</param>
        public BlendColor(Color4 normalValue)
        {
            // set default states
            States = new Color4[6];
            for (int i = 0; i < 6; i++)
                States[i] = normalValue;
            States[(int)ControlState.Disabled] = Color.FromArgb(200, 128, 128, 128);
            States[(int)ControlState.Hidden] = Color.FromArgb(0, 0, 0, 0);

            // set the initial color value
            CurrentColor = States[(int)ControlState.Hidden];
        }

        /// <summary>
        /// Blends the color to the specified state.
        /// </summary>
        /// <param name="state">The desired state.</param>
        /// <param name="elapsedTime">The time elapsed since the last update.</param>
        public void Blend(ControlState state, float elapsedTime)
        {
            // call the overload
            Blend(state, elapsedTime, 0.7f);
        }

        /// <summary>
        /// Blends the color to the specified state.
        /// </summary>
        /// <param name="state">The desired state.</param>
        /// <param name="elapsedTime">The time elapsed since the last update.</param>
        /// <param name="rate">The blend rate.</param>
        public void Blend(ControlState state, float elapsedTime, float rate)
        {
            // calculate the new color value
            storedTime = (float)Math.PI / 3;
            Color4 destinationColor = States[(int)state];
            CurrentColor = Color4.Lerp(CurrentColor, destinationColor, 1.0f - (float)Math.Pow(rate, 30 * elapsedTime));
        }

        /// <summary>
        /// Pulses between the specified states.
        /// </summary>
        /// <param name="startState">The start state.</param>
        /// <param name="endState">The end state.</param>
        /// <param name="elapsedTime">The elapsed time.</param>
        public void Pulse(ControlState startState, ControlState endState, float elapsedTime)
        {
            // update the time
            storedTime += elapsedTime;
            if (storedTime > cutoff)
                storedTime -= cutoff;

            // calculate the new color value
            Color4 startColor = States[(int)startState];
            Color4 destinationColor = States[(int)endState];
            CurrentColor = Color4.Lerp(startColor, destinationColor, (float)Math.Abs(Math.Sin(storedTime)));
        }

        /// <summary>
        /// Sets the color to the specified state.
        /// </summary>
        /// <param name="state">The state.</param>
        public void SetColor(ControlState state)
        {
            // set the color
            CurrentColor = States[(int)state];
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        public BlendColor Clone()
        {
            // clone each member
            BlendColor result = new BlendColor();
            result.CurrentColor = CurrentColor;
            for (int i = 0; i < 6; i++)
                result.States[i] = States[i];

            // return the result
            return result;
        }

        /// <summary>
        /// Creates a new object that is a copy of the current instance.
        /// </summary>
        /// <returns>
        /// A new object that is a copy of this instance.
        /// </returns>
        object ICloneable.Clone()
        {
            // call the overload
            return Clone();
        }
    }
}

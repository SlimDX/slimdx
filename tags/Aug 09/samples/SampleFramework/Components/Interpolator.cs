/*
* Copyright (c) 2007-2009 SlimDX Group
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

namespace SampleFramework
{
    /// <summary>
    /// A delegate that represents an interpolation function.
    /// </summary>
    /// <param name="currentValue">The current interpolated value.</param>
    /// <returns>The new interpolated value.</returns>
    public delegate float InterpolationFunction(float currentValue);

    /// <summary>
    /// Implements an interpolator.
    /// </summary>
    public class Interpolator
    {
        InterpolationFunction function;
        Predicate<float> predicate;
        bool finished;

        /// <summary>
        /// Occurs when the interpolator has finished processing.
        /// </summary>
        public event EventHandler Finished;

        /// <summary>
        /// Gets or sets the value.
        /// </summary>
        /// <value>The value.</value>
        public float Value
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="Interpolator"/> is finished.
        /// </summary>
        /// <value><c>true</c> if finished; otherwise, <c>false</c>.</value>
        public bool IsFinished
        {
            get { return finished; }
            set
            {
                if (finished == value)
                    return;

                finished = value;
                OnFinished(EventArgs.Empty);
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Interpolator"/> class.
        /// </summary>
        /// <param name="function">The function.</param>
        public Interpolator(InterpolationFunction function)
        {
            this.function = function;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Interpolator"/> class.
        /// </summary>
        /// <param name="function">The function.</param>
        /// <param name="startValue">The start value.</param>
        public Interpolator(InterpolationFunction function, float startValue)
        {
            this.function = function;
            Value = startValue;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Interpolator"/> class.
        /// </summary>
        /// <param name="function">The function.</param>
        /// <param name="startValue">The start value.</param>
        /// <param name="predicate">The predicate.</param>
        public Interpolator(InterpolationFunction function, float startValue, Predicate<float> predicate)
        {
            this.function = function;
            this.predicate = predicate;
            Value = startValue;
        }

        /// <summary>
        /// Updates the interpolator.
        /// </summary>
        public void Update()
        {
            Value = function(Value);

            if (predicate != null && predicate(Value))
                IsFinished = true;
        }

        /// <summary>
        /// Raises the <see cref="E:Finished"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnFinished(EventArgs e)
        {
            if (Finished != null)
                Finished(this, e);
        }
    }
}

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
    /// A delegate that represents a trigger activation function.
    /// </summary>
    /// <returns><c>true</c> if the trigger should activate; otherwise, <c>false</c>.</returns>
    public delegate bool TriggerActivation();

    /// <summary>
    /// Represents a trigger linking an action with a condition.
    /// </summary>
    public class Trigger
    {
        /// <summary>
        /// Occurs when the trigger is activated.
        /// </summary>
        public event EventHandler Activated;

        /// <summary>
        /// Gets the number of times the trigger has been activated.
        /// </summary>
        /// <value>The hit count.</value>
        public int HitCount
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="Trigger"/> should repeat, or if it should
        /// be removed after the first activation.
        /// </summary>
        /// <value><c>true</c> if the trigger should repeat; otherwise, <c>false</c>.</value>
        public bool Repeat
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the duration from the time the trigger is created until it is activated.
        /// </summary>
        /// <value>The duration.</value>
        public float Duration
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the start time.
        /// </summary>
        /// <value>The start time.</value>
        public float StartTime
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the activation predicate.
        /// </summary>
        /// <value>The activation predicate.</value>
        /// <remarks>
        /// This function will be called once per frame to see if the trigger
        /// should activate.
        /// </remarks>
        public TriggerActivation ActivationPredicate
        {
            get;
            set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Trigger"/> class.
        /// </summary>
        public Trigger()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Trigger"/> class.
        /// </summary>
        /// <param name="duration">The duration.</param>
        public Trigger(float duration)
        {
            Duration = duration;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="Trigger"/> class.
        /// </summary>
        /// <param name="activationPredicate">The activation predicate.</param>
        public Trigger(TriggerActivation activationPredicate)
        {
            ActivationPredicate = activationPredicate;
        }

        /// <summary>
        /// Activates the trigger.
        /// </summary>
        public void Activate()
        {
            HitCount++;

            OnActivated(EventArgs.Empty);
        }

        /// <summary>
        /// Raises the <see cref="E:Activated"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected virtual void OnActivated(EventArgs e)
        {
            if (Activated != null)
                Activated(this, e);
        }
    }
}

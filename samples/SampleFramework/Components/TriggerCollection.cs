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
using System.Collections.ObjectModel;

namespace SampleFramework
{
    /// <summary>
    /// Implements a collection of triggers.
    /// </summary>
    public class TriggerCollection : Collection<Trigger>
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TriggerCollection"/> class.
        /// </summary>
        public TriggerCollection()
        {
        }

        /// <summary>
        /// Updates the triggers in the collection.
        /// </summary>
        /// <param name="gameTime">The game time.</param>
        public void Update(GameTime gameTime)
        {
            // process each trigger
            for( int i = Items.Count - 1; i >= 0; i-- )
            {
                // check if the trigger has a predicate that is allowing us to proceed
                Trigger trigger = Items[i];
                if (trigger.ActivationPredicate != null && trigger.ActivationPredicate())
                {
                    // activate the trigger
                    trigger.Activate();
                    if (!trigger.Repeat)
                        RemoveAt(i);
                }
                else
                {
                    // set the start time if it doesn't yet have one
                    if (trigger.StartTime == 0)
                        trigger.StartTime = gameTime.TotalGameTime;
                    else if (gameTime.TotalGameTime - trigger.StartTime > trigger.Duration)
                    {
                        // activate the trigger
                        trigger.Activate();
                        if (!trigger.Repeat)
                            RemoveAt(i);
                        else
                            trigger.StartTime = gameTime.TotalGameTime;
                    }
                }
            }
        }
    }
}

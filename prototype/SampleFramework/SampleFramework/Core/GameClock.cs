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
using System.Diagnostics;

namespace SampleFramework
{
    /// <summary>
    /// Provides methods to manage the game clock.
    /// </summary>
    class GameClock
    {
        // variables
        long baseRealTime;
        long lastRealTime;
        bool lastRealTimeValid;
        int suspendCount;
        long suspendStartTime;
        long timeLostToSuspension;
        TimeSpan currentTimeBase;
        TimeSpan currentTimeOffset;

        /// <summary>
        /// Gets the current time.
        /// </summary>
        /// <value>The current time.</value>
        public TimeSpan CurrentTime
        {
            get { return currentTimeBase + currentTimeOffset; }
        }

        /// <summary>
        /// Gets the elapsed time.
        /// </summary>
        /// <value>The elapsed time.</value>
        public TimeSpan ElapsedTime
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the elapsed adjusted time.
        /// </summary>
        /// <value>The elapsed adjusted time.</value>
        public TimeSpan ElapsedAdjustedTime
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the frequency of the clock.
        /// </summary>
        /// <value>The clock frequency.</value>
        public static long Frequency
        {
            get { return Stopwatch.Frequency; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GameClock"/> class.
        /// </summary>
        public GameClock()
        {
            // reset the timer
            Reset();
        }

        /// <summary>
        /// Resets the clock.
        /// </summary>
        public void Reset()
        {
            // reset values
            currentTimeBase = TimeSpan.Zero;
            currentTimeOffset = TimeSpan.Zero;
            baseRealTime = Stopwatch.GetTimestamp();
            lastRealTimeValid = false;
        }

        /// <summary>
        /// Suspends the clock.
        /// </summary>
        public void Suspend()
        {
            // update the suspend state
            suspendCount++;
            if (suspendCount == 1)
                suspendStartTime = Stopwatch.GetTimestamp();
        }

        /// <summary>
        /// Resumes a previously suspended clock.
        /// </summary>
        public void Resume()
        {
            // check to see if we can start the clock again
            suspendCount--;
            if (suspendCount <= 0)
            {
                // reset the state
                timeLostToSuspension += Stopwatch.GetTimestamp() - suspendStartTime;
                suspendStartTime = 0;
            }
        }

        /// <summary>
        /// Steps the clock forward one frame.
        /// </summary>
        public void Step()
        {
            // grab the current timestamp
            long counter = Stopwatch.GetTimestamp();

            // check if we don't have a valid real time
            if (!lastRealTimeValid)
            {
                // store the real time
                lastRealTime = counter;
                lastRealTimeValid = true;
            }

            try
            {
                // get the current offset
                currentTimeOffset = CounterToTimeSpan(counter - baseRealTime);
            }
            catch (OverflowException)
            {
                // update the base value and try again to adjust for overflow
                currentTimeBase += currentTimeOffset;
                baseRealTime = lastRealTime;

                try
                {
                    // get the current offset
                    currentTimeOffset = CounterToTimeSpan(counter - baseRealTime);
                }
                catch (OverflowException)
                {
                    // account for overflow
                    baseRealTime = counter;
                    currentTimeOffset = TimeSpan.Zero;
                }
            }

            try
            {
                // get the current elapsed time
                ElapsedTime = CounterToTimeSpan(counter - lastRealTime);
            }
            catch (OverflowException)
            {
                // we couldn't get a valid elapsed time
                ElapsedTime = TimeSpan.Zero;
            }

            try
            {
                // get the adjusted time
                ElapsedAdjustedTime = CounterToTimeSpan(counter - (lastRealTime + timeLostToSuspension));
                timeLostToSuspension = 0;
            }
            catch (OverflowException)
            {
                // we couldn't get a valid adjusted time
                ElapsedAdjustedTime = TimeSpan.Zero;
            }

            // store the current real time
            lastRealTime = counter;
        }

        /// <summary>
        /// Converts the current counter value to a time span.
        /// </summary>
        /// <param name="delta">The counter delta.</param>
        /// <returns>The equivalent time span.</returns>
        static TimeSpan CounterToTimeSpan(long delta)
        {
            // return the correct value
            return TimeSpan.FromTicks((delta * 10000000) / Frequency);
        }
    }
}

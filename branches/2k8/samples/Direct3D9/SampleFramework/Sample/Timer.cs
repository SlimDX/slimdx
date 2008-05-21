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
using System.Collections.Generic;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Handles high performance timing operations.
    /// </summary>
    public class Timer
    {
        #region Variables

        bool stopped = true;
        long ticksPerSecond;
        long lastElapsedTime;
        long baseTime;
        long stopTime;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets a value indicating whether the timer is stopped.
        /// </summary>
        /// <value>
        /// <c>true</c> if the timer is stopped; otherwise, <c>false</c>.
        /// </value>
        public bool IsStopped
        {
            get { return stopped; }
            set
            {
                // start or stop the timer
                if (value)
                    Start();
                else
                    Stop();
            }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="Timer"/> class.
        /// </summary>
        public Timer()
        {
            NativeMethods.QueryPerformanceFrequency(out ticksPerSecond);
        }

        #endregion

        #region Methods

        /// <summary>
        /// Starts the timer.
        /// </summary>
        public void Start()
        {
            long time;
            NativeMethods.QueryPerformanceCounter(out time);

            if (stopped)
                baseTime += time - stopTime;

            stopTime = 0;
            lastElapsedTime = time;
            stopped = false;
        }

        /// <summary>
        /// Stops the timer.
        /// </summary>
        public void Stop()
        {
            if (!stopped)
            {
                long time;
                NativeMethods.QueryPerformanceCounter(out time);

                stopTime = time;
                lastElapsedTime = time;
                stopped = true;
            }
        }

        /// <summary>
        /// Resets the timer.
        /// </summary>
        public void Reset()
        {
            long time = GetAdjustedCurrentTime();

            baseTime = time;
            lastElapsedTime = time;
            stopTime = 0;
            stopped = false;
        }

        /// <summary>
        /// Advances the timer by one millisecond.
        /// </summary>
        public void Advance()
        {
            stopTime += ticksPerSecond / 1000;
        }

        /// <summary>
        /// Gets the absolute time.
        /// </summary>
        /// <returns>The absolute time.</returns>
        public double GetAbsoluteTime()
        {
            long time;
            NativeMethods.QueryPerformanceCounter(out time);

            return time / (double)ticksPerSecond;
        }

        /// <summary>
        /// Gets the current time.
        /// </summary>
        /// <returns>The current time.</returns>
        public double GetTime()
        {
            long time = GetAdjustedCurrentTime();

            return (double)(time - baseTime) / (double)ticksPerSecond;
        }

        /// <summary>
        /// Gets the amount of time that has elapsed since the last GetElapsedTime call.
        /// </summary>
        /// <returns>The amount of time that has elapsed.</returns>
        public double GetElapsedTime()
        {
            long time = GetAdjustedCurrentTime();

            double elapsed = (double)(time - lastElapsedTime) / (double)ticksPerSecond;
            lastElapsedTime = time;

            if (elapsed < 0.0)
                elapsed = 0.0;

            return elapsed;
        }

        #endregion

        #region Helpers

        long GetAdjustedCurrentTime()
        {
            long time;
            if (stopTime != 0)
                time = stopTime;
            else
                NativeMethods.QueryPerformanceCounter(out time);

            return time;
        }

        #endregion
    }
}

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

namespace SampleFramework
{
    /// <summary>
    /// Contains the current timing state of the game.
    /// </summary>
    public class GameTime
    {
        /// <summary>
        /// Gets the current frames-per-second measure.
        /// </summary>
        /// <value>The current frames-per-second measure.</value>
        public float FramesPerSecond
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the elapsed game time, in seconds.
        /// </summary>
        /// <value>The elapsed game time.</value>
        public float ElapsedGameTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the elapsed real time, in seconds.
        /// </summary>
        /// <value>The elapsed real time.</value>
        public float ElapsedRealTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the total game time, in seconds.
        /// </summary>
        /// <value>The total game time.</value>
        public float TotalGameTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the total real time, in seconds.
        /// </summary>
        /// <value>The total real time.</value>
        public float TotalRealTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets a value indicating whether the game is running slowly.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if the game is running slowly; otherwise, <c>false</c>.
        /// </value>
        public bool IsRunningSlowly
        {
            get;
            internal set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GameTime"/> class.
        /// </summary>
        public GameTime()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GameTime"/> class.
        /// </summary>
        /// <param name="totalRealTime">The total real time.</param>
        /// <param name="elapsedRealTime">The elapsed real time.</param>
        /// <param name="totalGameTime">The total game time.</param>
        /// <param name="elapsedGameTime">The elapsed game time.</param>
        public GameTime(float totalRealTime, float elapsedRealTime, float totalGameTime, float elapsedGameTime)
            : this(totalRealTime, elapsedRealTime, totalGameTime, elapsedGameTime, false)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GameTime"/> class.
        /// </summary>
        /// <param name="totalRealTime">The total real time.</param>
        /// <param name="elapsedRealTime">The elapsed real time.</param>
        /// <param name="totalGameTime">The total game time.</param>
        /// <param name="elapsedGameTime">The elapsed game time.</param>
        /// <param name="isRunningSlowly">if set to <c>true</c>, the game is running slowly.</param>
        public GameTime(float totalRealTime, float elapsedRealTime, float totalGameTime, float elapsedGameTime, bool isRunningSlowly)
        {
            // store variables
            TotalRealTime = totalRealTime;
            ElapsedRealTime = elapsedRealTime;
            TotalGameTime = totalGameTime;
            ElapsedGameTime = elapsedGameTime;
            IsRunningSlowly = isRunningSlowly;
        }
    }
}

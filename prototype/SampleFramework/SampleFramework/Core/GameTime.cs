using System;

namespace SampleFramework
{
    /// <summary>
    /// Contains the current timing state of the game.
    /// </summary>
    public class GameTime
    {
        /// <summary>
        /// Gets the elapsed game time.
        /// </summary>
        /// <value>The elapsed game time.</value>
        public TimeSpan ElapsedGameTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the elapsed real time.
        /// </summary>
        /// <value>The elapsed real time.</value>
        public TimeSpan ElapsedRealTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the total game time.
        /// </summary>
        /// <value>The total game time.</value>
        public TimeSpan TotalGameTime
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the total real time.
        /// </summary>
        /// <value>The total real time.</value>
        public TimeSpan TotalRealTime
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
        public GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, TimeSpan totalGameTime, TimeSpan elapsedGameTime)
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
        public GameTime(TimeSpan totalRealTime, TimeSpan elapsedRealTime, TimeSpan totalGameTime, TimeSpan elapsedGameTime, bool isRunningSlowly)
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

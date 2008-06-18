using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Thrown when no available graphics device fits the given device preferences.
    /// </summary>
    public class NoCompatibleDevicesException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="NoCompatibleDevicesException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        public NoCompatibleDevicesException(string message)
            : base(message)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="NoCompatibleDevicesException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="innerException">The inner exception.</param>
        public NoCompatibleDevicesException(string message, Exception innerException)
            : base(message, innerException)
        {
        }
    }
}

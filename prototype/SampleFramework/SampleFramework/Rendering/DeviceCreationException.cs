using System;

namespace SampleFramework
{
    /// <summary>
    /// Thrown when a graphics device cannot be created.
    /// </summary>
    public class DeviceCreationException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceCreationException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        public DeviceCreationException(string message)
            : base(message)
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DeviceCreationException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="innerException">The inner exception.</param>
        public DeviceCreationException(string message, Exception innerException)
            : base(message, innerException)
        {
        }
    }
}

namespace SlimDX.Direct3D10 {
    /// <summary>
    /// Indicates how a resource is to be mapped for access (reading and writing) by the CPU.
    /// </summary>
    public enum MapMode : int {
        /// <summary>
        /// The resource is mapped for reading.
        /// </summary>
        Read = 1,

        /// <summary>
        /// The resource is mapped for writing.
        /// </summary>
        Write = 2,

        /// <summary>
        /// The resource is mapped for both reading and writing.
        /// </summary>
        ReadWrite = 3,

        /// <summary>
        /// The resource is mapped for writing with the previous contents of the resource undefined.
        /// </summary>
        WriteDiscard = 4,

        /// <summary>
        /// The resource is mapped for writing, but the existing contents of the resource may not be
        /// overwritten. This value is only valid for vertex and index buffers.
        /// </summary>
        WriteNoOverwrite = 5,
    }
}

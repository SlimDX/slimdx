using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Buffer = SlimDX.Direct3D11.Buffer;
using SlimDX.Direct3D11;
using System.Runtime.InteropServices;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Provides a wrapper around a constant buffer structure.
    /// </summary>
    /// <typeparam name="T">The type that will act as the constant buffer. Its size must be a multiple of 16 bytes.</typeparam>
    public class ConstantBuffer<T> : IDisposable where T : struct
    {
        /// <summary>
        /// The underlying Direct3D buffer.
        /// </summary>
        public Buffer Buffer
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ConstantBuffer&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="device">The device used to create the constant buffer.</param>
        /// <exception cref="InvalidOperationException">Thrown if the constant buffer type is not a multiple of 16 bytes.</exception>
        public ConstantBuffer(Device device)
        {
            int size = Marshal.SizeOf(typeof(T));
            if (size % 16 != 0)
                throw new InvalidOperationException("Constant buffer sizes must be a multiple of 16 bytes.");

            Buffer = new Buffer(device, new BufferDescription
            {
                SizeInBytes = size,
                Usage = ResourceUsage.Dynamic,
                BindFlags = BindFlags.ConstantBuffer,
                CpuAccessFlags = CpuAccessFlags.Write
            });
        }

        /// <summary>
        /// Writes new data into the constant buffer.
        /// </summary>
        /// <param name="context">The rendering context.</param>
        /// <param name="data">The data to update.</param>
        public void SetData(DeviceContext context, ref T data)
        {
            var box = context.MapSubresource(Buffer, MapMode.WriteDiscard, MapFlags.None);
            box.Data.Write(data);

            context.UnmapSubresource(Buffer, 0);
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (Buffer != null)
            {
                Buffer.Dispose();
                Buffer = null;
            }
        }
    }
}

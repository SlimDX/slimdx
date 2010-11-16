// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
using System;
using System.Runtime.InteropServices;

namespace SlimDX.Direct3D11
{
    public partial class DeviceContext
    {
        /// <summary>
        ///   Constructs a new deferred context <see cref = "T:SlimDX.Direct3D11.DeviceContext" />.
        /// </summary>
        /// <param name = "device">The device with which to associate the state object.</param>
        /// <returns>The newly created object.</returns>
        public DeviceContext(Device device)
            : base(IntPtr.Zero)
        {
            DeviceContext temp;
            device.CreateDeferredContext(0, out temp);
            NativePointer = temp.NativePointer;
        }

        /// <summary>
        ///   Create a command list and record graphics commands into it.
        /// </summary>
        /// <param name = "restoreState">A flag indicating whether the immediate context state is saved (prior) and restored (after) the execution of a command list.</param>
        /// <returns>The created command list containing the queued rendering commands.</returns>
        public CommandList FinishCommandList(bool restoreState)
        {
            CommandList temp;
            FinishCommandListInternal(restoreState, out temp);
            return temp;
        }

        /// <summary>
        ///   Gets data from the GPU asynchronously.
        /// </summary>
        /// <param name = "data">The asynchronous data provider.</param>
        /// <returns>The data retrieved from the GPU.</returns>
        public DataStream GetData(Asynchronous data)
        {
            return GetData(data, AsynchronousFlags.None);
        }

        /// <summary>
        ///   Gets data from the GPU asynchronously.
        /// </summary>
        /// <param name = "data">The asynchronous data provider.</param>
        /// <returns>The data retrieved from the GPU.</returns>
        public T GetData<T>(Asynchronous data) where T : struct
        {
            return GetData<T>(data, AsynchronousFlags.None);
        }

        /// <summary>
        ///   Gets data from the GPU asynchronously.
        /// </summary>
        /// <param name = "data">The asynchronous data provider.</param>
        /// <param name = "flags">Flags specifying how the command should operate.</param>
        /// <returns>The data retrieved from the GPU.</returns>
        public DataStream GetData(Asynchronous data, AsynchronousFlags flags)
        {
            DataStream result = new DataStream(data.DataSize, true, true);
            GetDataInternal(data, result.DataPointer, (int) result.Length, flags);
            return result;
        }

        /// <summary>
        ///   Gets data from the GPU asynchronously.
        /// </summary>
        /// <param name = "data">The asynchronous data provider.</param>
        /// <param name = "flags">Flags specifying how the command should operate.</param>
        /// <returns>The data retrieved from the GPU.</returns>
        public T GetData<T>(Asynchronous data, AsynchronousFlags flags) where T : struct
        {
            unsafe
            {
                int size = Marshal.SizeOf(typeof (T));
                // TODO, verify if stackalloc is a good place to store async data
                byte* pBuffer = stackalloc byte[size];
                DataStream stream = new DataStream(pBuffer, size, true, true, false);

                GetDataInternal(data, stream.DataPointer, size, flags);

                return stream.Read<T>();
            }
        }

        /// <summary>
        ///   Maps a GPU resource into CPU-accessible memory.
        /// </summary>
        /// <param name = "resource">The resource to map.</param>
        /// <param name = "subresource">Index of the subresource to map.</param>
        /// <param name = "sizeInBytes">Size, in bytes, of the data to retrieve.</param>
        /// <param name = "mode">Specifies the CPU's read and write permissions for the resource. </param>
        /// <param name = "flags">Flags that specify what the CPU should do when the GPU is busy.</param>
        /// <returns>The mapped resource data.</returns>
        public DataBox MapSubresource(Resource resource, int subresource, int sizeInBytes, MapMode mode, MapFlags flags)
        {
            unsafe
            {
                MappedSubResource mappedSubResource;
                Map(resource, subresource, mode, flags, out mappedSubResource);
                return new DataBox(mappedSubResource.RowPitch, mappedSubResource.DepthPitch,
                                   new DataStream((void*) mappedSubResource.PData, sizeInBytes, true, true, false));
            }
        }

        /// <summary>
        ///   Copies data from the CPU to to a non-mappable subresource region.
        /// </summary>
        /// <param name = "source">The source data.</param>
        /// <param name = "resource">The destination resource.</param>
        /// <param name = "subresource">The destination subresource.</param>
        public void UpdateSubresource(DataBox source, Resource resource, int subresource)
        {
            UpdateSubresource(resource, subresource, null, source.Data.DataPointer, source.RowPitch, source.SlicePitch);
        }

        /// <summary>
        ///   Copies data from the CPU to to a non-mappable subresource region.
        /// </summary>
        /// <param name = "source">The source data.</param>
        /// <param name = "resource">The destination resource.</param>
        /// <param name = "subresource">The destination subresource.</param>
        /// <param name = "region">The destination region within the resource.</param>
        public void UpdateSubresource(DataBox source, Resource resource, int subresource, ResourceRegion region)
        {
            UpdateSubresource(resource, subresource, region, source.Data.DataPointer, source.RowPitch, source.SlicePitch);
        }
    }
}
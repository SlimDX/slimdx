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
using SlimDX2.Direct3D;
using SlimDX2.DXGI;

namespace SlimDX2.Direct3D10
{
    public partial class Device
    {
        /// <summary>
        ///   Constructor for a D3D10 Device. See <see cref = "SlimDX2.Direct3D10.D3D10.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "driverType"></param>
        public Device(DriverType driverType)
            : this(driverType, DeviceCreationFlags.None)
        {
        }

        /// <summary>
        ///   Constructor for a D3D10 Device. See <see cref = "SlimDX2.Direct3D10.D3D10.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "adapter"></param>
        public Device(Adapter adapter)
            : this(adapter, DeviceCreationFlags.None)
        {
        }

        /// <summary>
        ///   Constructor for a D3D10 Device. See <see cref = "SlimDX2.Direct3D10.D3D10.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "driverType"></param>
        /// <param name = "flags"></param>
        public Device(DriverType driverType, DeviceCreationFlags flags)
        {
            CreateDevice(null, DriverType.Hardware, flags);
        }

        /// <summary>
        ///   Constructor for a D3D10 Device. See <see cref = "SlimDX2.Direct3D10.D3D10.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "adapter"></param>
        /// <param name = "flags"></param>
        public Device(Adapter adapter, DeviceCreationFlags flags)
        {
            CreateDevice(adapter, DriverType.Hardware, flags);
        }


        /// <summary>
        ///   Internal CreateDevice
        /// </summary>
        /// <param name = "adapter"></param>
        /// <param name = "driverType"></param>
        /// <param name = "flags"></param>
        /// <param name = "featureLevels"></param>
        private void CreateDevice(Adapter adapter, DriverType driverType, DeviceCreationFlags flags)
        {
            Device device;
            D3D10.CreateDevice(adapter, driverType, IntPtr.Zero, flags, D3D10.SdkVersion, out device);
            NativePointer = device.NativePointer;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D10.Device" /> class along with a new <see cref = "T:SlimDX.DXGI.SwapChain" /> used for rendering.
        /// </summary>
        /// <param name = "driverType">The type of device to create.</param>
        /// <param name = "flags">A list of runtime layers to enable.</param>
        /// <param name = "swapChainDescription">Details used to create the swap chain.</param>
        /// <param name = "device">When the method completes, contains the created device instance.</param>
        /// <param name = "swapChain">When the method completes, contains the created swap chain instance.</param>
        /// <returns>A <see cref = "T:SlimDX.Result" /> object describing the result of the operation.</returns>
        public static Result CreateWithSwapChain(DriverType driverType, DeviceCreationFlags flags,
                                                 SwapChainDescription swapChainDescription, out Device device,
                                                 out SwapChain swapChain)
        {
            return CreateWithSwapChain(null, driverType, flags, swapChainDescription, out device, out swapChain);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D10.Device" /> class along with a new <see cref = "T:SlimDX.DXGI.SwapChain" /> used for rendering.
        /// </summary>
        /// <param name = "adapter">The video adapter on which the device should be created.</param>
        /// <param name = "flags">A list of runtime layers to enable.</param>
        /// <param name = "swapChainDescription">Details used to create the swap chain.</param>
        /// <param name = "device">When the method completes, contains the created device instance.</param>
        /// <param name = "swapChain">When the method completes, contains the created swap chain instance.</param>
        /// <returns>A <see cref = "T:SlimDX.Result" /> object describing the result of the operation.</returns>
        public static Result CreateWithSwapChain(Adapter adapter, DeviceCreationFlags flags,
                                                 SwapChainDescription swapChainDescription, out Device device,
                                                 out SwapChain swapChain)
        {
            return CreateWithSwapChain(adapter, DriverType.Hardware, flags, swapChainDescription, out device, out swapChain);
        }


        /// <summary>
        ///   This overload has been deprecated. Use one of the alternatives that does not take both an adapter and a driver type.
        /// </summary>
        internal static Result CreateWithSwapChain(Adapter adapter, DriverType driverType, DeviceCreationFlags flags, SwapChainDescription swapChainDescription, out Device device, out SwapChain swapChain)
        {
            FeatureLevel selectedLevel;

            Result result = D3D10.CreateDeviceAndSwapChain(adapter, driverType, IntPtr.Zero, flags, D3D10.SdkVersion,
                                                           ref swapChainDescription, out swapChain, out device);

            return result;
        }

    }
}
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
using SlimDX.Direct3D;
using SlimDX.DXGI;

namespace SlimDX.Direct3D11
{
    public partial class Device
    {
        private DeviceContext _immediateContext;

        /// <summary>
        ///   Constructor for a D3D11 Device. See <see cref = "SlimDX.Direct3D11.D3D11.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "driverType"></param>
        public Device(DriverType driverType)
            : this(driverType, DeviceCreationFlags.None)
        {
        }

        /// <summary>
        ///   Constructor for a D3D11 Device. See <see cref = "SlimDX.Direct3D11.D3D11.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "adapter"></param>
        public Device(Adapter adapter)
            : this(adapter, DeviceCreationFlags.None)
        {
        }

        /// <summary>
        ///   Constructor for a D3D11 Device. See <see cref = "SlimDX.Direct3D11.D3D11.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "driverType"></param>
        /// <param name = "flags"></param>
        public Device(DriverType driverType, DeviceCreationFlags flags)
        {
            CreateDevice(null, DriverType.Hardware, flags, null);
        }

        /// <summary>
        ///   Constructor for a D3D11 Device. See <see cref = "SlimDX.Direct3D11.D3D11.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "adapter"></param>
        /// <param name = "flags"></param>
        public Device(Adapter adapter, DeviceCreationFlags flags)
        {
            CreateDevice(adapter, DriverType.Unknown, flags, null);
        }

        /// <summary>
        ///   Constructor for a D3D11 Device. See <see cref = "SlimDX.Direct3D11.D3D11.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "driverType"></param>
        /// <param name = "flags"></param>
        /// <param name = "featureLevels"></param>
        public Device(DriverType driverType, DeviceCreationFlags flags, params FeatureLevel[] featureLevels)
        {
            CreateDevice(null, DriverType.Unknown, flags, featureLevels);
        }

        /// <summary>
        ///   Constructor for a D3D11 Device. See <see cref = "SlimDX.Direct3D11.D3D11.CreateDevice" /> for more information.
        /// </summary>
        /// <param name = "adapter"></param>
        /// <param name = "flags"></param>
        /// <param name = "featureLevels"></param>
        public Device(Adapter adapter, DeviceCreationFlags flags, params FeatureLevel[] featureLevels)
        {
            CreateDevice(adapter, DriverType.Unknown, flags, featureLevels);
        }

        /// <summary>
        ///   Internal CreateDevice
        /// </summary>
        /// <param name = "adapter"></param>
        /// <param name = "driverType"></param>
        /// <param name = "flags"></param>
        /// <param name = "featureLevels"></param>
        private void CreateDevice(Adapter adapter, DriverType driverType, DeviceCreationFlags flags,
                                  FeatureLevel[] featureLevels)
        {
            Device device;
            FeatureLevel selectedLevel;
            D3D11.CreateDevice(adapter, driverType, IntPtr.Zero, flags, featureLevels,
                               featureLevels == null ? 0 : featureLevels.Length, D3D11.SdkVersion, out device,
                               out selectedLevel, out _immediateContext);
            NativePointer = device.NativePointer;
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Device" /> class along with a new <see cref = "T:SlimDX.DXGI.SwapChain" /> used for rendering.
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
            return CreateWithSwapChain(null, driverType, flags, null, swapChainDescription, out device, out swapChain);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Device" /> class along with a new <see cref = "T:SlimDX.DXGI.SwapChain" /> used for rendering.
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
            return CreateWithSwapChain(adapter, DriverType.Unknown, flags, null, swapChainDescription, out device,
                                       out swapChain);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Device" /> class along with a new <see cref = "T:SlimDX.DXGI.SwapChain" /> used for rendering.
        /// </summary>
        /// <param name = "driverType">The type of device to create.</param>
        /// <param name = "flags">A list of runtime layers to enable.</param>
        /// <param name = "featureLevels">A list of feature levels which determine the order of feature levels to attempt to create.</param>
        /// <param name = "swapChainDescription">Details used to create the swap chain.</param>
        /// <param name = "device">When the method completes, contains the created device instance.</param>
        /// <param name = "swapChain">When the method completes, contains the created swap chain instance.</param>
        /// <returns>A <see cref = "T:SlimDX.Result" /> object describing the result of the operation.</returns>
        public static Result CreateWithSwapChain(DriverType driverType, DeviceCreationFlags flags,
                                                 FeatureLevel[] featureLevels, SwapChainDescription swapChainDescription,
                                                 out Device device, out SwapChain swapChain)
        {
            return CreateWithSwapChain(null, driverType, flags, featureLevels, swapChainDescription, out device,
                                       out swapChain);
        }

        /// <summary>
        ///   Initializes a new instance of the <see cref = "T:SlimDX.Direct3D11.Device" /> class along with a new <see cref = "T:SlimDX.DXGI.SwapChain" /> used for rendering.
        /// </summary>
        /// <param name = "adapter">The video adapter on which the device should be created.</param>
        /// <param name = "flags">A list of runtime layers to enable.</param>
        /// <param name = "featureLevels">A list of feature levels which determine the order of feature levels to attempt to create.</param>
        /// <param name = "swapChainDescription">Details used to create the swap chain.</param>
        /// <param name = "device">When the method completes, contains the created device instance.</param>
        /// <param name = "swapChain">When the method completes, contains the created swap chain instance.</param>
        /// <returns>A <see cref = "T:SlimDX.Result" /> object describing the result of the operation.</returns>
        public static Result CreateWithSwapChain(Adapter adapter, DeviceCreationFlags flags,
                                                 FeatureLevel[] featureLevels, SwapChainDescription swapChainDescription,
                                                 out Device device, out SwapChain swapChain)
        {
            return CreateWithSwapChain(adapter, DriverType.Unknown, flags, featureLevels, swapChainDescription,
                                       out device, out swapChain);
        }

        /// <summary>
        ///   This overload has been deprecated. Use one of the alternatives that does not take both an adapter and a driver type.
        /// </summary>
        [Obsolete(
            "This method is confusing because only one of the adapter/driverType parameters is valid during the call. Use one of the overloads that explicitly uses the parameter you wish to provide."
            )]
        public static Result CreateWithSwapChain(Adapter adapter, DriverType driverType, DeviceCreationFlags flags,
                                                 SwapChainDescription swapChainDescription, out Device device,
                                                 out SwapChain swapChain)
        {
            return CreateWithSwapChain(adapter, driverType, flags, null, swapChainDescription, out device, out swapChain);
        }

        /// <summary>
        ///   This overload has been deprecated. Use one of the alternatives that does not take both an adapter and a driver type.
        /// </summary>
        [Obsolete(
            "This method is confusing because only one of the adapter/driverType parameters is valid during the call. Use one of the overloads that explicitly uses the parameter you wish to provide."
            )]
        public static Result CreateWithSwapChain(Adapter adapter, DriverType driverType, DeviceCreationFlags flags,
                                                 FeatureLevel[] featureLevels, SwapChainDescription swapChainDescription,
                                                 out Device device, out SwapChain swapChain)
        {
            FeatureLevel selectedLevel;
            DeviceContext context;

            Result result = D3D11.CreateDeviceAndSwapChain(adapter, driverType, IntPtr.Zero, flags, featureLevels,
                                                           featureLevels == null ? 0 : featureLevels.Length,
                                                           D3D11.SdkVersion,
                                                           ref swapChainDescription, out swapChain, out device,
                                                           out selectedLevel, out context);

            device.ImmediateContext = context;

            return result;
        }

        /// <summary>
        ///   Get the imediate <see cref = "SlimDX.Direct3D11.DeviceContext" /> attached to this Device.
        /// </summary>
        public DeviceContext ImmediateContext
        {
            get
            {
                if (_immediateContext == null)
                {
                    GetImmediateContext(out _immediateContext);
                }
                return _immediateContext;
            }

            private set { _immediateContext = value; }
        }
    }
}
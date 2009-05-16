/*
* Copyright (c) 2007-2009 SlimDX Group
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
#pragma once

#include "Device.h"

namespace SlimDX
{
	namespace Direct3D10_1
	{
		/// <summary>
		/// Specifies possible levels of hardware acceleration features.
		/// </summary>
		/// <ummanaged>D3D10_FEATURE_LEVEL1</unmanaged>
		public enum class FeatureLevel
		{
			Level_10_0 = D3D10_FEATURE_LEVEL_10_0,
			Level_10_1 = D3D10_FEATURE_LEVEL_10_1,
			Level_9_1 = D3D10_FEATURE_LEVEL_9_1,
			Level_9_2 = D3D10_FEATURE_LEVEL_9_2,
			Level_9_3 = D3D10_FEATURE_LEVEL_9_3,
		};

		/// <summary>
		/// A virtual adapter for performing rendering operations, using Direct3D 10.1.
		///</summary>
		/// <unmanaged>ID3D10Device1</unmanaged>
		public ref class Device1 : SlimDX::Direct3D10::Device
		{
			COMOBJECT_CUSTOM(ID3D10Device1, Device1);

		public:
			property SlimDX::Direct3D10_1::FeatureLevel FeatureLevel
			{
				SlimDX::Direct3D10_1::FeatureLevel get();
			}

			/// <summary>
			/// Constructs a new Device1 object.
			/// </summary>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			/// <param name="hardwareLevel"></param>D
			Device1( SlimDX::Direct3D10::DeviceCreationFlags flags, SlimDX::Direct3D10_1::FeatureLevel hardwareLevel );
			
			/// <summary>
			/// Constructs a new Device1 object.
			/// </summary>
			/// <param name="driverType">The device driver type.</param>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			Device1( SlimDX::Direct3D10::DriverType driverType, SlimDX::Direct3D10::DeviceCreationFlags flags, SlimDX::Direct3D10_1::FeatureLevel hardwareLevel );
			
			/// <summary>
			/// Constructs a new Device object.
			/// </summary>
			/// <param name="adapter">The display adapter to associate the device with when creating a hardware device.</param>
			/// <param name="driverType">The device driver type.</param>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			Device1( SlimDX::DXGI::Adapter^ adapter, SlimDX::Direct3D10::DriverType driverType, SlimDX::Direct3D10::DeviceCreationFlags flags, SlimDX::Direct3D10_1::FeatureLevel hardwareLevel );
			
			/// <summary>
			/// Creates a new Direct3D 10.1 device and swap chain.
			/// </summary>
			/// <param name="adapter">The display adapter to associate the device with when creating a hardware device.</param>
			/// <param name="driverType">The device driver type.</param>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			/// <param name="swapChainDescription">Swap chain properties.</param>
			/// <param name="device">The newly-created device.</param>
			/// <param name="swapChain">The newly-created swap chain.</param>
			/// <returns>A result code.</returns>
			static Result CreateWithSwapChain( SlimDX::DXGI::Adapter^ adapter, SlimDX::Direct3D10::DriverType driverType, SlimDX::Direct3D10::DeviceCreationFlags flags, SlimDX::Direct3D10_1::FeatureLevel hardwareLevel, DXGI::SwapChainDescription swapChainDescription, [Out] Device1^ %device, [Out] DXGI::SwapChain^ %swapChain );
		};
	}
}

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
#pragma once

#include "../ComObject.h"

#include "../dxgi/Adapter.h"
#include "../dxgi/Enums.h"
#include "../dxgi/SwapChain.h"
#include "../dxgi/SwapChainDescription.h"
#include "../math/Color4.h"

#include "Enums.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	ref class DataBox;
	
	namespace Direct3D11
	{
		ref class Buffer;
		ref class DepthStencilView;
		ref class InputLayout;
		ref class RenderTargetView;
		ref class Resource;
		ref class ShaderResourceView;
		ref class DeviceContext;
		value class CounterCapabilities;
		value class CounterDescription;
		value class CounterMetadata;
		value class RenderTargetViewDescription;
		value class ResourceRegion;

		/// <summary>
		/// A virtual adapter for performing rendering.
		/// </summary>
		public ref class Device : ComObject
		{
			COMOBJECT(ID3D11Device, Device);

		private:
			DeviceContext^ m_ImmediateContext;
		
		public:
			/// <summary>
			/// The maximum number of multisample quality levels supported.
			/// </summary>
			literal int MultisampleCountMaximum = D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
			
			/// <summary>
			/// Gets the device's creation flags.
			/// </summary>
			property DeviceCreationFlags CreationFlags
			{
				DeviceCreationFlags get();
			}
			
			/// <summary>
			/// Gets the immediate device context.
			/// </summary>
			property DeviceContext^ ImmediateContext
			{
				DeviceContext^ get();
			}

			/// <summary>
			/// Constructs a new Device object.
			/// </summary>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			Device( DeviceCreationFlags flags );

			/// <summary>
			/// Constructs a new Device object.
			/// </summary>
			/// <param name="driverType">The device driver type.</param>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			Device( DriverType driverType, DeviceCreationFlags flags );

			/// <summary>
			/// Constructs a new Device object.
			/// </summary>
			/// <param name="adapter">The display adapter to associate the device with when creating a hardware device.</param>
			/// <param name="driverType">The device driver type.</param>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			Device( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags );

			/// <summary>
			/// Constructs a Device object from a marshalled native pointer.
			/// </summary>
			/// <param name="pointer">The native object pointer.</param>
			/// <returns>The Device object for the native object.</returns>
			static Device^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Gets information about the device's performance counters.
			/// </summary>
			/// <returns>Information about the device's performance counters.</returns>
			CounterCapabilities GetCounterCapabilities();

			/// <summary>
			/// Gets metadata (name, type, measurement units, et cetera) for a specific counter.
			/// </summary>
			/// <param name="description">The description of the counter to retrieve information about.</param>
			/// <returns>Metadata for the specified counter.</returns>
			CounterMetadata GetCounterMetadata( CounterDescription description );
			
			/// <summary>
			/// Gets information about the supported applications of a specified format.
			/// </summary>
			/// <param name="format">The format to check support for.</param>
			/// <returns>FormatSupport flags indicating usage contexts in which the specified format is supported.</returns>
			FormatSupport CheckFormatSupport( DXGI::Format format );

			/// <summary>
			/// Gets the number of quality levels supported during multisampling of resources using a specified format.
			/// </summary>
			/// <param name="format">The format to check support for.</param>
			/// <param name="sampleCount">The multisample count to check support for.</param>
			/// <returns>The number of quality levels supported. 0 if an error occured
			/// or if the format/samplecount pair is not supported.</returns>
			int CheckMultisampleQualityLevels( DXGI::Format format, int sampleCount );
			
			/// <summary>
			/// Creates a new device and swap chain.
			/// </summary>
			/// <param name="adapter">The display adapter to associate the device with when creating a hardware device.</param>
			/// <param name="driverType">The device driver type.</param>
			/// <param name="flags">Flags that indicate which device API layers to enable.</param>
			/// <param name="swapChainDescription">Swap chain properties.</param>
			/// <param name="device">The newly-created device.</param>
			/// <param name="swapChain">The newly-created swap chain.</param>
			/// <returns>A result code.</returns>
			static Result CreateWithSwapChain( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, DXGI::SwapChainDescription swapChainDescription, [Out] Device^ %device, [Out] DXGI::SwapChain^ %swapChain );
		};
	}
};
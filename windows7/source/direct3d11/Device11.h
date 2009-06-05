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

#include "Enums11.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class DeviceContext;
		value class CounterCapabilities;
		value class CounterMetadata;

		/// <summary>
		/// A virtual adapter for performing rendering.
		/// </summary>
		/// <unmanaged>ID3D11Device</unmanaged>
		public ref class Device : ComObject
		{
			COMOBJECT(ID3D11Device, Device);

		private:
			void Initialize( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, const D3D_FEATURE_LEVEL *featureLevels, int count );

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

			property Result DeviceRemovedReason
			{
				Result get();
			}

			property FeatureLevel FeatureLevel
			{
				Direct3D11::FeatureLevel get();
			}

			property DeviceContext^ ImmediateContext
			{
				DeviceContext^ get();
			}

			Device( DXGI::Adapter^ adapter );
			Device( DXGI::Adapter^ adapter, DeviceCreationFlags flags );
			Device( DXGI::Adapter^ adapter, DeviceCreationFlags flags, ... array<Direct3D11::FeatureLevel>^ featureLevels );

			Device( DriverType driverType );
			Device( DriverType driverType, DeviceCreationFlags flags );
			Device( DriverType driverType, DeviceCreationFlags flags, ... array<Direct3D11::FeatureLevel>^ featureLevels );

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
			CounterMetadata GetCounterMetadata( CounterKind counterKind );
			
			/// <summary>
			/// Gets information about the supported applications of a specified format.
			/// </summary>
			/// <param name="format">The format to check support for.</param>
			/// <returns>FormatSupport flags indicating usage contexts in which the specified format is supported.</returns>
			FormatSupport CheckFormatSupport( DXGI::Format format );

			ComputeShaderFormatSupport CheckComputeShaderFormatSupport( DXGI::Format format );
			bool CheckFeatureSupport( Feature feature );
			Result CheckThreadingSupport( [Out] bool% supportsConcurrentResources, [Out] bool% supportCommandLists );

			/// <summary>
			/// Gets the number of quality levels supported during multisampling of resources using a specified format.
			/// </summary>
			/// <param name="format">The format to check support for.</param>
			/// <param name="sampleCount">The multisample count to check support for.</param>
			/// <returns>The number of quality levels supported. 0 if an error occured
			/// or if the format/samplecount pair is not supported.</returns>
			int CheckMultisampleQualityLevels( DXGI::Format format, int sampleCount );

			static Direct3D11::FeatureLevel GetSupportedFeatureLevel();
			static Direct3D11::FeatureLevel GetSupportedFeatureLevel( array<Direct3D11::FeatureLevel>^ featureLevels );
			
			static Result CreateWithSwapChain( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, DXGI::SwapChainDescription swapChainDescription, [Out] Device^ %device, [Out] DXGI::SwapChain^ %swapChain );
			static Result CreateWithSwapChain( DXGI::Adapter^ adapter, DriverType driverType, DeviceCreationFlags flags, array<Direct3D11::FeatureLevel>^ featureLevels, DXGI::SwapChainDescription swapChainDescription, [Out] Device^ %device, [Out] DXGI::SwapChain^ %swapChain );
		};
	}
};
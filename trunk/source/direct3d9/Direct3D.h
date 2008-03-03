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

#include "../InternalHelpers.h"
#include "Enums.h"

#include "DisplayMode.h"
#include "AdapterDetails.h"
#include "Capabilities.h"
#include "AdapterInformation.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class Direct3D sealed
		{
		private:
			Direct3D() { }
			static IDirect3D9* m_Direct3D;

			static void OnExit(System::Object^ sender, System::EventArgs^ e)
			{
				SLIMDX_UNREFERENCED_PARAMETER(sender);
				SLIMDX_UNREFERENCED_PARAMETER(e);

				Terminate();
			}

		internal:
			static property IDirect3D9* InternalPointer
			{
				IDirect3D9* get() { return m_Direct3D; }
			}

		public:
			static property bool CheckWhql;
			static property AdapterCollection^ Adapters;

			static property int AdapterCount
			{
				int get() { return m_Direct3D->GetAdapterCount(); }
			}

            static void Initialize();
            static void Terminate();

			/// <summary>
			/// Tests the device to see if it supports conversion from one display format to another.
			/// </summary>
			/// <param name="adapter">Index of the adapter to use.</param>
			/// <param name="deviceType">One of the DeviceType members.</param>
			/// <param name="sourceFormat">Format to convert from.</param>
			/// <param name="targetFormat">Format to convert into.</param>
			/// <param name="result">0 if successful.  Otherwise an HRESULT error code for the function.</param>
			/// <returns>TRUE if successful, FALSE if not.</returns>
			static bool CheckDeviceFormatConversion(int adapter, DeviceType deviceType, Format sourceFormat, Format targetFormat, [Out] int% result);

			/// <summary>
			/// Tests the device to see if it supports conversion from one display format to another.
			/// </summary>
			/// <param name="adapter">Index of the adapter to use.</param>
			/// <param name="deviceType">One of the DeviceType members.</param>
			/// <param name="sourceFormat">Format to convert from.</param>
			/// <param name="targetFormat">Format to convert into.</param>
			/// <returns>TRUE if successful, FALSE if not.</returns>
			static bool CheckDeviceFormatConversion(int adapter, DeviceType deviceType, Format sourceFormat, Format targetFormat);

			static bool CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat, Usage usage, ResourceType resourceType, Format checkFormat, [Out] int% result );
			static bool CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat, Usage usage, ResourceType resourceType, Format checkFormat );

			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, Format backBufferFormat, bool windowed, [Out] int% result );
			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, Format backBufferFormat, bool windowed );

			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, Format renderTargetFormat, Format depthStencilFormat, [Out] int% result );
			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, Format renderTargetFormat, Format depthStencilFormat );

			static bool CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat, bool windowed, MultisampleType multisampleType, [Out] int% qualityLevels, [Out] int% result );
			static bool CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat, bool windowed, MultisampleType multisampleType, [Out] int% qualityLevels );
			static bool CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat, bool windowed, MultisampleType multisampleType );

            static DisplayMode GetAdapterDisplayMode( int adapter );
            static AdapterDetails^ GetAdapterIdentifier( int adapter );
            static int GetAdapterModeCount( int adapter, Format format );
            static DisplayMode EnumerateAdapterModes( int adapter, Format format, int modeIndex );
            static System::IntPtr GetAdapterMonitor( int adapter );
			static Capabilities^ GetDeviceCaps( int adapter, DeviceType deviceType );

			static bool SupportsR2VB( int adapter, DeviceType deviceType );
		};
	}
}

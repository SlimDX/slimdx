/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System::Runtime::InteropServices;

#include "Enums.h"
#include "CapsEnums.h"
#include "GraphicsException.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		[StructLayout( LayoutKind::Sequential )]
		public value class DisplayMode
		{
		public:
			int Width;
			int Height;
			int RefreshRate;
			Format Format;
		};

		public ref class AdapterDetails
		{
		internal:
			AdapterDetails( unsigned int adapter );

		public:
			initonly int Adapter;
			initonly String^ Description;
			initonly int DeviceId;
			initonly Guid DeviceIdentifier;
			initonly String^ DeviceName;
			initonly String^ DriverName;
			initonly Version^ DriverVersion;
			initonly int Revision;
			initonly int SubSystemId;
			initonly int VendorId;
			initonly int WhqlLevel;
		};

		public value class VertexShader20Caps
		{
		public:
			int Caps;
			int DynamicFlowControlDepth;
			int NumTemps;
			int StaticFlowControlDepth;
		};

		public value class PixelShader20Caps
		{
		public:
			int Caps;
			int DynamicFlowControlDepth;
			int NumTemps;
			int StaticFlowControlDepth;
			int NumInstructionSlots;
		};

		public value class Capabilities
		{
		internal:
			Capabilities( const D3DCAPS9& caps );

		public:
			//Device Info
			DeviceType DeviceType;
			int AdapterOrdinal;

			//Caps from DX7 Draw
			Caps Caps;
			Caps2 Caps2;
			Caps3 Caps3;
			int PresentInterval;

			CursorCaps CursorCaps;

			DeviceCaps DeviceCaps;

			PrimitiveMiscCaps PrimitiveMiscCaps;
			RasterCaps RasterCaps;
			CompareCaps ZCompareCaps;
			BlendCaps SourceBlendCaps;
			BlendCaps DestBlendCaps;
			CompareCaps AlphaCompareCaps;
			ShadeCaps ShadeCaps;
			TextureCaps TextureCaps;
			FilterCaps TextureFilterCaps;
			FilterCaps CubeTextureFilterCaps;
			FilterCaps VolumeTextureFilterCaps;
			TextureAddressCaps TextureAddressCaps;
			SlimDX::Direct3D9::TextureAddressCaps VolumeTextureAddressCaps;

			LineCaps LineCaps;

			int MaxTextureWidth;
			int MaxTextureHeight;
			int MaxVolumeExtent;

			int MaxTextureRepeat;
			int MaxTextureAspectRatio;
			int MaxAnisotropy;
			float MaxVertexW;

			float GuardBandLeft;
			float GuardBandTop;
			float GuardBandRight;
			float GuardBandBottom;

			float ExtentsAdjust;
			StencilCaps StencilCaps;

			VertexFormatCaps FVFCaps;
			TextureOpCaps TextureOpCaps;
			int MaxTextureBlendStages;
			int MaxSimultaneousTextures;

			VertexProcessingCaps VertexProcessingCaps;
			int MaxActiveLights;
			int MaxUserClipPlanes;
			int MaxVertexBlendMatrices;
			int MaxVertexBlendMatrixIndex;

			float MaxPointSize;

			int MaxPrimitiveCount;
			int MaxVertexIndex;
			int MaxStreams;
			int MaxStreamStride;

			initonly Version^ VertexShaderVersion;
			int MaxVertexShaderConstants;

			initonly Version^ PixelShaderVersion;
			float PixelShader1xMaxValue;

			//DX9 Specific caps
			DevCaps2 DeviceCaps2;

			float MaxNPatchTessellationLevel;

			int MasterAdapterOrdinal;
			int AdapterOrdinalInGroup;
			int NumberOfAdaptersInGroup;
			DeclTypeCaps DeclTypes;
			int NumSimultaneousRTs;
			FilterCaps StretchRectFilterCaps;
			VertexShader20Caps VS20Caps;
			PixelShader20Caps PS20Caps;
			FilterCaps VertexTextureFilterCaps;
			int MaxVShaderInstructionsExecuted;
			int MaxPShaderInstructionsExecuted;
			int MaxVertexShader30InstructionSlots;
			int MaxPixelShader30InstructionSlots;
		};

        public ref class DisplayModeList sealed : public System::Collections::IEnumerable
		{
		private:
			array<DisplayMode>^ m_Modes;

		internal:
			DisplayModeList( unsigned int adapter, Format format );

		public:
            property int Count
            {
                virtual int get() { return m_Modes->Length; }
            }

            property DisplayMode default[int]
			{
				DisplayMode get( int index )
				{
					return m_Modes[index];
				}
			}

			virtual System::Collections::IEnumerator^ GetEnumerator()
			{
                return m_Modes->GetEnumerator();
			}
		};

		public ref class AdapterInformation
		{
		internal:
			initonly int m_Adapter;

			AdapterInformation( unsigned int adapter );

		public:
			property int Adapter
			{
				int get() { return m_Adapter; }
			}

			property IntPtr Monitor { IntPtr get(); }
			property DisplayMode CurrentDisplayMode { DisplayMode get(); }
            DisplayModeList^ GetDisplayModes( Format format );
            Capabilities GetCaps( DeviceType type );

			initonly AdapterDetails^ Details;
		};

        public ref class AdapterList sealed : public System::Collections::IEnumerable
		{
		private:
            array<AdapterInformation^>^ m_Adapters;

		internal:
			AdapterList( unsigned int adapterCount );

		public:
            property int Count
            {
                virtual int get() { return m_Adapters->Length; }
            }

            property AdapterInformation^ default[int]
			{
				AdapterInformation^ get( int index )
				{
					return m_Adapters[index];
				}
			}

			virtual System::Collections::IEnumerator^ GetEnumerator()
			{
                return m_Adapters->GetEnumerator();
			}
		};

		public ref class Direct3D
		{
		private:
			static IDirect3D9* m_Direct3D;

			static void OnExit(Object^ sender,EventArgs^ e)
			{
				Terminate();
			}

		internal:
			static property IDirect3D9* InternalPointer
			{
				IDirect3D9* get() { return m_Direct3D; }
			}

		public:
			static property bool CheckWhql;
			static property AdapterList^ Adapters;

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
			static bool CheckDeviceFormatConversion(int adapter, DeviceType deviceType,
                Format sourceFormat, Format targetFormat, [Out] int% result);

			/// <summary>
			/// Tests the device to see if it supports conversion from one display format to another.
			/// </summary>
			/// <param name="adapter">Index of the adapter to use.</param>
			/// <param name="deviceType">One of the DeviceType members.</param>
			/// <param name="sourceFormat">Format to convert from.</param>
			/// <param name="targetFormat">Format to convert into.</param>
			/// <returns>TRUE if successful, FALSE if not.</returns>
			static bool CheckDeviceFormatConversion(int adapter, DeviceType deviceType,
                Format sourceFormat, Format targetFormat);

			static bool CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
				Usage usage, ResourceType resourceType, Format checkFormat, [Out] int% result );
			static bool CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
				Usage usage, ResourceType resourceType, Format checkFormat );

			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format backBufferFormat, bool windowed, [Out] int% result );
			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format backBufferFormat, bool windowed );

			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format renderTargetFormat, Format depthStencilFormat, [Out] int% result );
			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format renderTargetFormat, Format depthStencilFormat );

			static bool CheckDeviceMultiSampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
				bool windowed, MultiSampleType multiSampleType, [Out] int% qualityLevels, [Out] int% result );
			static bool CheckDeviceMultiSampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
				bool windowed, MultiSampleType multiSampleType, [Out] int% qualityLevels );
			static bool CheckDeviceMultiSampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
				bool windowed, MultiSampleType multiSampleType );

            static int GetAdapterCount();
            static DisplayMode GetAdapterDisplayMode( int adapter );
            static AdapterDetails^ GetAdapterIdentifier( int adapter );
            static int GetAdapterModeCount( int adapter, Format format );
            static DisplayMode EnumAdapterModes( int adapter, Format format, int modeIndex );
            static IntPtr GetAdapterMonitor( int adapter );
			static Capabilities GetDeviceCaps( int adapter, DeviceType deviceType );
		};
	}
}

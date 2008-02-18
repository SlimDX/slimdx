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

#include "Enums.h"
#include "CapsEnums.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D9
	{
		[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
		public value class DisplayMode
		{
		public:
			property int Width;
            property int Height;
            property int RefreshRate;
            property Format Format;
		};

		public ref class AdapterDetails
		{
		public:
			property int Adapter;
			property System::String^ Description;
			property int DeviceId;
			property System::Guid DeviceIdentifier;
			property System::String^ DeviceName;
			property System::String^ DriverName;
			property System::Version^ DriverVersion;
			property int Revision;
			property int SubsystemId;
			property int VendorId;
			property int WhqlLevel;

		internal:
			AdapterDetails( unsigned int adapter );
		};

		public value class VertexShader20Caps
		{
		public:
			property int Caps;
            property int DynamicFlowControlDepth;
            property int TempCount;
            property int StaticFlowControlDepth;
		};

		public value class PixelShader20Caps
		{
		public:
			property int Caps;
            property int DynamicFlowControlDepth;
            property int TempCount;
            property int StaticFlowControlDepth;
		};

		public value class Capabilities
		{
		public:
			property DeviceType DeviceType;
            property int AdapterOrdinal;
            property Caps Caps;
            property Caps2 Caps2;
            property Caps3 Caps3;
            property PresentInterval PresentationIntervals;
            property CursorCaps CursorCaps;
            property DeviceCaps DeviceCaps;
            property PrimitiveMiscCaps PrimitiveMiscCaps;
            property RasterCaps RasterCaps;
            property CompareCaps DepthCompareCaps;
            property BlendCaps SourceBlendCaps;
            property BlendCaps DestinationBlendCaps;
            property CompareCaps AlphaCompareCaps;
            property ShadeCaps ShadeCaps;
            property TextureCaps TextureCaps;
            property FilterCaps TextureFilterCaps;
            property FilterCaps CubeTextureFilterCaps;
            property FilterCaps VolumeTextureFilterCaps;
            property TextureAddressCaps TextureAddressCaps;
            property SlimDX::Direct3D9::TextureAddressCaps VolumeTextureAddressCaps;
            property LineCaps LineCaps;
            property int MaxTextureWidth;
            property int MaxTextureHeight;
            property int MaxVolumeExtent;
            property int MaxTextureRepeat;
            property int MaxTextureAspectRatio;
            property int MaxAnisotropy;
            property float MaxVertexW;
            property float GuardBandLeft;
            property float GuardBandTop;
            property float GuardBandRight;
            property float GuardBandBottom;
            property float ExtentsAdjust;
            property StencilCaps StencilCaps;
            property VertexFormatCaps FVFCaps;
            property TextureOperationCaps TextureOperationCaps;
            property int MaxTextureBlendStages;
            property int MaxSimultaneousTextures;
            property VertexProcessingCaps VertexProcessingCaps;
            property int MaxActiveLights;
            property int MaxUserClipPlanes;
            property int MaxVertexBlendMatrices;
            property int MaxVertexBlendMatrixIndex;
            property float MaxPointSize;
            property int MaxPrimitiveCount;
            property int MaxVertexIndex;
            property int MaxStreams;
            property int MaxStreamStride;
            property System::Version^ VertexShaderVersion;
            property int MaxVertexShaderConstants;
            property System::Version^ PixelShaderVersion;
            property float PixelShader1xMaxValue;
            property DevCaps2 DeviceCaps2;
            property float MaxNPatchTessellationLevel;
            property int MasterAdapterOrdinal;
            property int AdapterOrdinalInGroup;
            property int NumberOfAdaptersInGroup;
            property DeclarationTypeCaps DeclarationTypes;
            property int SimultaneousRTCount;
            property FilterCaps StretchRectFilterCaps;
            property VertexShader20Caps VS20Caps;
            property PixelShader20Caps PS20Caps;
            property FilterCaps VertexTextureFilterCaps;
			property int MaxVShaderInstructionsExecuted;
			property int MaxPShaderInstructionsExecuted;
			property int MaxVertexShader30InstructionSlots;
			property int MaxPixelShader30InstructionSlots;

		internal:
			Capabilities( const D3DCAPS9& caps );
		};

        public ref class DisplayModeCollection : public System::Collections::IEnumerable
		{
		private:
			array<DisplayMode>^ m_Modes;

		internal:
			DisplayModeCollection( unsigned int adapter, Format format );

		public:
            property int Count
            {
                int get() { return m_Modes->Length; }
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
		private:
			AdapterDetails^ details;

		internal:
			initonly int m_Adapter;

			AdapterInformation( unsigned int adapter );

		public:
			property int Adapter
			{
				int get() { return m_Adapter; }
			}

			property System::IntPtr Monitor { System::IntPtr get(); }
			property DisplayMode CurrentDisplayMode { DisplayMode get(); }
            DisplayModeCollection^ GetDisplayModes( Format format );
            Capabilities GetCaps( DeviceType type );
			bool SupportsR2VB( DeviceType type );

			property AdapterDetails^ Details
			{
				AdapterDetails^ get() { return details; }
			protected:
				void set( AdapterDetails^ value ) { details = value; }
			}
		};

        public ref class AdapterCollection : public System::Collections::IEnumerable
		{
		private:
            array<AdapterInformation^>^ m_Adapters;

		internal:
			AdapterCollection( unsigned int adapterCount );

		public:
            property int Count
            {
                int get() { return m_Adapters->Length; }
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

		public ref class Direct3D sealed
		{
		private:
			Direct3D() { }
			static IDirect3D9* m_Direct3D;

			static void OnExit(System::Object^ sender,System::EventArgs^ e)
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

			static bool CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
				bool windowed, MultisampleType multisampleType, [Out] int% qualityLevels, [Out] int% result );
			static bool CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
				bool windowed, MultisampleType multisampleType, [Out] int% qualityLevels );
			static bool CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
				bool windowed, MultisampleType multisampleType );

            static DisplayMode GetAdapterDisplayMode( int adapter );
            static AdapterDetails^ GetAdapterIdentifier( int adapter );
            static int GetAdapterModeCount( int adapter, Format format );
            static DisplayMode EnumAdapterModes( int adapter, Format format, int modeIndex );
            static System::IntPtr GetAdapterMonitor( int adapter );
			static Capabilities GetDeviceCaps( int adapter, DeviceType deviceType );
			
			//Extensions
			static bool SupportsR2VB( int adapter, DeviceType deviceType );
		};
	}
}

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

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

#include "CapsEnums.h"

namespace SlimDX
{
	namespace Direct3D
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

			property int Monitor { int get(); }
			property DisplayMode CurrentDisplayMode { DisplayMode get(); }
			//TODO: Enumerate display modes

			initonly AdapterDetails^ Details;
		};

		public value class VertexShaderCaps20
		{
			int Caps;
			int DynamicFlowControlDepth;
			int NumTemps;
			int StaticFlowControlDepth;
		};

		public value class PixelShaderCaps20
		{
			int Caps;
			int DynamicFlowControlDepth;
			int NumTemps;
			int StaticFlowControlDepth;
			int NumInstructionSlots;
		};

		public value class DeviceCapabilities
		{
		internal:
			DeviceCapabilities( const D3DCAPS9& caps );

		public:
			DeviceType DeviceType;
			int AdapterOrdinal;
			Caps Caps;
			Caps2 Caps2;
			Caps3 Caps3;
			int PresentationIntervals;
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
			int TextureFilterCaps;
			int CubeTextureFilterCaps;
			int VolumeTextureFilterCaps;
			int TextureAddressCaps;
			int VolumeTextureAddressCaps;
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
			int StencilCaps;
			int FVFCaps;
			int TextureOpCaps;
			int MaxTextureBlendStages;
			int MaxSimultaneousTextures;
			int VertexProcessingCaps;
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
			int MaxVertexShaderConst;
			initonly Version^ PixelShaderVersion;
			float PixelShader1xMaxValue;
			int DevCaps2;
			int MasterAdapterOrdinal;
			int AdapterOrdinalInGroup;
			int NumberOfAdaptersInGroup;
			int DeclTypes;
			int NumSimultaneousRTs;
			int StretchRectFilterCaps;
			VertexShaderCaps20 VS20Caps;
			PixelShaderCaps20 D3DPSHADERCAPS2_0;
			int VertexTextureFilterCaps;
			int MaxVShaderInstructionsExecuted;
			int MaxPShaderInstructionsExecuted;
			int MaxVertexShader30InstructionSlots;
			int MaxPixelShader30InstructionSlots;
		};

		public ref class AdapterList sealed// : public IEnumerable<AdapterInformation^>
		{
		internal:
			AdapterList( unsigned int adapterCount ) { Count = (int) adapterCount; }

		public:
			initonly int Count;

			property AdapterInformation^ default[int]
			{
				AdapterInformation^ get( int index )
				{
					if( index < 0 || index >= Count )
						throw gcnew ArgumentOutOfRangeException( "index" );

					return gcnew AdapterInformation( index );
				}
			}
		};

		public ref class Direct3D
		{
		private:
			static IDirect3D9* m_Direct3D;

		internal:
			static property IDirect3D9* InternalPointer
			{
				IDirect3D9* get() { return m_Direct3D; }
			}

		public:
			static property bool CheckWhql;
			static property AdapterList^ Adapters;

			static Direct3D()
			{
				m_Direct3D = Direct3DCreate9( D3D_SDK_VERSION );
				if( m_Direct3D == NULL )
					throw gcnew DirectXException( -1, "Could not create Direct3D instance." );

				CheckWhql = false;
				Adapters = gcnew AdapterList( m_Direct3D->GetAdapterCount() );
			}

			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format backBufferFormat, bool windowed, [Out] int% result );
			static bool CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format backBufferFormat, bool windowed );

			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format renderTargetFormat, DepthFormat depthStencilFormat, [Out] int% result );
			static bool CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
				Format renderTargetFormat, DepthFormat depthStencilFormat );

			static DeviceCapabilities GetDeviceCaps( int adapter, DeviceType deviceType );
		};
	}
}

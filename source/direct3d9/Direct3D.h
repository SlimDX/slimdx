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
		private:
			int width;
            int height;
            int refreshRate;
            Format format;

		public:
			property int Width
            {
                int get() { return width; }
                void set( int value ) { width = value; }
            }

            property int Height
            {
                int get() { return height; }
                void set( int value ) { height = value; }
            }

            property int RefreshRate
            {
                int get() { return refreshRate; }
                void set( int value ) { refreshRate = value; }
            }

			property SlimDX::Direct3D9::Format Format
            {
                SlimDX::Direct3D9::Format get() { return format; }
                void set( SlimDX::Direct3D9::Format value ) { format = value; }
            }
		};

		public ref class AdapterDetails
		{
		private:
			int adapter;
			String^ description;
			int deviceId;
			Guid deviceIdentifier;
			String^ deviceName;
			String^ driverName;
			Version^ driverVersion;
			int revision;
			int subSystemId;
			int vendorId;
			int whqlLevel;

		internal:
			AdapterDetails( unsigned int adapter );

		public:
			property int Adapter
            {
                int get() { return adapter; }
			protected:
                void set( int value ) { adapter = value; }
            }

            property String^ Description
            {
                String^ get() { return description; }
			protected:
                void set( String^ value ) { description = value; }
            }

            property int DeviceId
            {
                int get() { return deviceId; }
			protected:
                void set( int value ) { deviceId = value; }
            }

            property Guid DeviceIdentifier
            {
                Guid get() { return deviceIdentifier; }
			protected:
                void set( Guid value ) { deviceIdentifier = value; }
            }

            property String^ DeviceName
            {
                String^ get() { return deviceName; }
			protected:
                void set( String^ value ) { deviceName = value; }
            }

            property String^ DriverName
            {
                String^ get() { return driverName; }
			protected:
                void set( String^ value ) { driverName = value; }
            }

            property Version^ DriverVersion
            {
				Version^ get() { return driverVersion; }
			protected:
                void set( Version^ value ) { driverVersion = value; }
            }

            property int Revision
            {
                int get() { return revision; }
			protected:
                void set( int value ) { revision = value; }
            }

            property int SubSystemId
            {
                int get() { return subSystemId; }
			protected:
                void set( int value ) { subSystemId = value; }
            }

            property int VendorId
            {
                int get() { return vendorId; }
			protected:
                void set( int value ) { vendorId = value; }
            }

            property int WhqlLevel
            {
                int get() { return whqlLevel; }
			protected:
                void set( int value ) { whqlLevel = value; }
            }
		};

		public value class VertexShader20Caps
		{
		private:
			int caps;
            int dynamicFlowControlDepth;
            int numTemps;
            int staticFlowControlDepth;

		public:
			property int Caps
            {
                int get() { return caps; }
                void set( int value ) { caps = value; }
            }

            property int DynamicFlowControlDepth
            {
                int get() { return dynamicFlowControlDepth; }
                void set( int value ) { dynamicFlowControlDepth = value; }
            }

            property int NumTemps
            {
                int get() { return numTemps; }
                void set( int value ) { numTemps = value; }
            }

            property int StaticFlowControlDepth
            {
                int get() { return staticFlowControlDepth; }
                void set( int value ) { staticFlowControlDepth = value; }
            }
		};

		public value class PixelShader20Caps
		{
		private:
			int caps;
            int dynamicFlowControlDepth;
            int numTemps;
            int staticFlowControlDepth;

		public:
			property int Caps
            {
                int get() { return caps; }
                void set( int value ) { caps = value; }
            }

            property int DynamicFlowControlDepth
            {
                int get() { return dynamicFlowControlDepth; }
                void set( int value ) { dynamicFlowControlDepth = value; }
            }

            property int NumTemps
            {
                int get() { return numTemps; }
                void set( int value ) { numTemps = value; }
            }

            property int StaticFlowControlDepth
            {
                int get() { return staticFlowControlDepth; }
                void set( int value ) { staticFlowControlDepth = value; }
            }
		};

		public value class Capabilities
		{
		private:
			DeviceType deviceType;
            int adapterOrdinal;
            Caps caps;
            Caps2 caps2;
            Caps3 caps3;
            int presentInterval;
            CursorCaps cursorCaps;
            DeviceCaps deviceCaps;
            PrimitiveMiscCaps primitiveMiscCaps;
            RasterCaps rasterCaps;
            CompareCaps zCompareCaps;
            BlendCaps sourceBlendCaps;
            BlendCaps destBlendCaps;
            CompareCaps alphaCompareCaps;
            ShadeCaps shadeCaps;
            TextureCaps textureCaps;
            FilterCaps textureFilterCaps;
            FilterCaps cubeTextureFilterCaps;
            FilterCaps volumeTextureFilterCaps;
            TextureAddressCaps textureAddressCaps;
            SlimDX::Direct3D9::TextureAddressCaps volumeTextureAddressCaps;
            LineCaps lineCaps;
            int maxTextureWidth;
            int maxTextureHeight;
            int maxVolumeExtent;
            int maxTextureRepeat;
            int maxTextureAspectRatio;
            int maxAnisotropy;
            float maxVertexW;
            float guardBandLeft;
            float guardBandTop;
            float guardBandRight;
            float guardBandBottom;
            float extentsAdjust;
            StencilCaps stencilCaps;
            VertexFormatCaps fVFCaps;
            TextureOpCaps textureOpCaps;
            int maxTextureBlendStages;
            int maxSimultaneousTextures;
            VertexProcessingCaps vertexProcessingCaps;
            int maxActiveLights;
            int maxUserClipPlanes;
            int maxVertexBlendMatrices;
            int maxVertexBlendMatrixIndex;
            float maxPointSize;
            int maxPrimitiveCount;
            int maxVertexIndex;
            int maxStreams;
            int maxStreamStride;
            Version^ vertexShaderVersion;
            int maxVertexShaderConstants;
            Version^ pixelShaderVersion;
            float pixelShader1xMaxValue;
            DevCaps2 deviceCaps2;
            float maxNPatchTessellationLevel;
            int masterAdapterOrdinal;
            int adapterOrdinalInGroup;
            int numberOfAdaptersInGroup;
            DeclTypeCaps declTypes;
            int numSimultaneousRTs;
            FilterCaps stretchRectFilterCaps;
            VertexShader20Caps vS20Caps;
            PixelShader20Caps pS20Caps;
            FilterCaps vertexTextureFilterCaps;
			int maxVShaderInstructionsExecuted;
			int maxPShaderInstructionsExecuted;
			int maxVertexShader30InstructionSlots;
			int maxPixelShader30InstructionSlots;

		internal:
			Capabilities( const D3DCAPS9& caps );

		public:
			property SlimDX::Direct3D9::DeviceType DeviceType
            {
                SlimDX::Direct3D9::DeviceType get() { return deviceType; }
                void set( SlimDX::Direct3D9::DeviceType value ) { deviceType = value; }
            }

            property int AdapterOrdinal
            {
                int get() { return adapterOrdinal; }
                void set( int value ) { adapterOrdinal = value; }
            }

            property SlimDX::Direct3D9::Caps Caps
            {
                SlimDX::Direct3D9::Caps get() { return caps; }
                void set( SlimDX::Direct3D9::Caps value ) { caps = value; }
            }

            property SlimDX::Direct3D9::Caps2 Caps2
            {
                SlimDX::Direct3D9::Caps2 get() { return caps2; }
                void set( SlimDX::Direct3D9::Caps2 value ) { caps2 = value; }
            }

            property SlimDX::Direct3D9::Caps3 Caps3
            {
                SlimDX::Direct3D9::Caps3 get() { return caps3; }
                void set( SlimDX::Direct3D9::Caps3 value ) { caps3 = value; }
            }

            property int PresentInterval
            {
                int get() { return presentInterval; }
                void set( int value ) { presentInterval = value; }
            }

            property SlimDX::Direct3D9::CursorCaps CursorCaps
            {
                SlimDX::Direct3D9::CursorCaps get() { return cursorCaps; }
                void set( SlimDX::Direct3D9::CursorCaps value ) { cursorCaps = value; }
            }

            property SlimDX::Direct3D9::DeviceCaps DeviceCaps
            {
                SlimDX::Direct3D9::DeviceCaps get() { return deviceCaps; }
                void set( SlimDX::Direct3D9::DeviceCaps value ) { deviceCaps = value; }
            }

            property SlimDX::Direct3D9::PrimitiveMiscCaps PrimitiveMiscCaps
            {
                SlimDX::Direct3D9::PrimitiveMiscCaps get() { return primitiveMiscCaps; }
                void set( SlimDX::Direct3D9::PrimitiveMiscCaps value ) { primitiveMiscCaps = value; }
            }

            property SlimDX::Direct3D9::RasterCaps RasterCaps
            {
                SlimDX::Direct3D9::RasterCaps get() { return rasterCaps; }
                void set( SlimDX::Direct3D9::RasterCaps value ) { rasterCaps = value; }
            }

            property CompareCaps ZCompareCaps
            {
                CompareCaps get() { return zCompareCaps; }
                void set( CompareCaps value ) { zCompareCaps = value; }
            }

            property BlendCaps SourceBlendCaps
            {
                BlendCaps get() { return sourceBlendCaps; }
                void set( BlendCaps value ) { sourceBlendCaps = value; }
            }

            property BlendCaps DestBlendCaps
            {
                BlendCaps get() { return destBlendCaps; }
                void set( BlendCaps value ) { destBlendCaps = value; }
            }

            property CompareCaps AlphaCompareCaps
            {
                CompareCaps get() { return alphaCompareCaps; }
                void set( CompareCaps value ) { alphaCompareCaps = value; }
            }

            property SlimDX::Direct3D9::ShadeCaps ShadeCaps
            {
                SlimDX::Direct3D9::ShadeCaps get() { return shadeCaps; }
                void set( SlimDX::Direct3D9::ShadeCaps value ) { shadeCaps = value; }
            }

            property SlimDX::Direct3D9::TextureCaps TextureCaps
            {
                SlimDX::Direct3D9::TextureCaps get() { return textureCaps; }
                void set( SlimDX::Direct3D9::TextureCaps value ) { textureCaps = value; }
            }

            property FilterCaps TextureFilterCaps
            {
                FilterCaps get() { return textureFilterCaps; }
                void set( FilterCaps value ) { textureFilterCaps = value; }
            }

            property FilterCaps CubeTextureFilterCaps
            {
                FilterCaps get() { return cubeTextureFilterCaps; }
                void set( FilterCaps value ) { cubeTextureFilterCaps = value; }
            }

            property FilterCaps VolumeTextureFilterCaps
            {
                FilterCaps get() { return volumeTextureFilterCaps; }
                void set( FilterCaps value ) { volumeTextureFilterCaps = value; }
            }

            property SlimDX::Direct3D9::TextureAddressCaps TextureAddressCaps
            {
                SlimDX::Direct3D9::TextureAddressCaps get() { return textureAddressCaps; }
                void set( SlimDX::Direct3D9::TextureAddressCaps value ) { textureAddressCaps = value; }
            }

            property SlimDX::Direct3D9::TextureAddressCaps VolumeTextureAddressCaps
            {
                SlimDX::Direct3D9::TextureAddressCaps get() { return volumeTextureAddressCaps; }
                void set( SlimDX::Direct3D9::TextureAddressCaps value ) { volumeTextureAddressCaps = value; }
            }

            property SlimDX::Direct3D9::LineCaps LineCaps
            {
                SlimDX::Direct3D9::LineCaps get() { return lineCaps; }
                void set( SlimDX::Direct3D9::LineCaps value ) { lineCaps = value; }
            }

            property int MaxTextureWidth
            {
                int get() { return maxTextureWidth; }
                void set( int value ) { maxTextureWidth = value; }
            }

            property int MaxTextureHeight
            {
                int get() { return maxTextureHeight; }
                void set( int value ) { maxTextureHeight = value; }
            }

            property int MaxVolumeExtent
            {
                int get() { return maxVolumeExtent; }
                void set( int value ) { maxVolumeExtent = value; }
            }

            property int MaxTextureRepeat
            {
                int get() { return maxTextureRepeat; }
                void set( int value ) { maxTextureRepeat = value; }
            }

            property int MaxTextureAspectRatio
            {
                int get() { return maxTextureAspectRatio; }
                void set( int value ) { maxTextureAspectRatio = value; }
            }

            property int MaxAnisotropy
            {
                int get() { return maxAnisotropy; }
                void set( int value ) { maxAnisotropy = value; }
            }

            property float MaxVertexW
            {
                float get() { return maxVertexW; }
                void set( float value ) { maxVertexW = value; }
            }

            property float GuardBandLeft
            {
                float get() { return guardBandLeft; }
                void set( float value ) { guardBandLeft = value; }
            }

            property float GuardBandTop
            {
                float get() { return guardBandTop; }
                void set( float value ) { guardBandTop = value; }
            }

            property float GuardBandRight
            {
                float get() { return guardBandRight; }
                void set( float value ) { guardBandRight = value; }
            }

            property float GuardBandBottom
            {
                float get() { return guardBandBottom; }
                void set( float value ) { guardBandBottom = value; }
            }

            property float ExtentsAdjust
            {
                float get() { return extentsAdjust; }
                void set( float value ) { extentsAdjust = value; }
            }

            property SlimDX::Direct3D9::StencilCaps StencilCaps
            {
                SlimDX::Direct3D9::StencilCaps get() { return stencilCaps; }
                void set( SlimDX::Direct3D9::StencilCaps value ) { stencilCaps = value; }
            }

            property VertexFormatCaps FVFCaps
            {
                VertexFormatCaps get() { return fVFCaps; }
                void set( VertexFormatCaps value ) { fVFCaps = value; }
            }

            property SlimDX::Direct3D9::TextureOpCaps TextureOpCaps
            {
                SlimDX::Direct3D9::TextureOpCaps get() { return textureOpCaps; }
                void set( SlimDX::Direct3D9::TextureOpCaps value ) { textureOpCaps = value; }
            }

            property int MaxTextureBlendStages
            {
                int get() { return maxTextureBlendStages; }
                void set( int value ) { maxTextureBlendStages = value; }
            }

            property int MaxSimultaneousTextures
            {
                int get() { return maxSimultaneousTextures; }
                void set( int value ) { maxSimultaneousTextures = value; }
            }

            property SlimDX::Direct3D9::VertexProcessingCaps VertexProcessingCaps
            {
                SlimDX::Direct3D9::VertexProcessingCaps get() { return vertexProcessingCaps; }
                void set( SlimDX::Direct3D9::VertexProcessingCaps value ) { vertexProcessingCaps = value; }
            }

            property int MaxActiveLights
            {
                int get() { return maxActiveLights; }
                void set( int value ) { maxActiveLights = value; }
            }

            property int MaxUserClipPlanes
            {
                int get() { return maxUserClipPlanes; }
                void set( int value ) { maxUserClipPlanes = value; }
            }

            property int MaxVertexBlendMatrices
            {
                int get() { return maxVertexBlendMatrices; }
                void set( int value ) { maxVertexBlendMatrices = value; }
            }

            property int MaxVertexBlendMatrixIndex
            {
                int get() { return maxVertexBlendMatrixIndex; }
                void set( int value ) { maxVertexBlendMatrixIndex = value; }
            }

            property float MaxPointSize
            {
                float get() { return maxPointSize; }
                void set( float value ) { maxPointSize = value; }
            }

            property int MaxPrimitiveCount
            {
                int get() { return maxPrimitiveCount; }
                void set( int value ) { maxPrimitiveCount = value; }
            }

            property int MaxVertexIndex
            {
                int get() { return maxVertexIndex; }
                void set( int value ) { maxVertexIndex = value; }
            }

            property int MaxStreams
            {
                int get() { return maxStreams; }
                void set( int value ) { maxStreams = value; }
            }

            property int MaxStreamStride
            {
                int get() { return maxStreamStride; }
                void set( int value ) { maxStreamStride = value; }
            }

            property Version^ VertexShaderVersion
            {
               Version^ get() { return vertexShaderVersion; }
			private:
                void set( Version^ value ) { vertexShaderVersion = value; }
            }

            property int MaxVertexShaderConstants
            {
                int get() { return maxVertexShaderConstants; }
                void set( int value ) { maxVertexShaderConstants = value; }
            }

            property Version^ PixelShaderVersion
            {
                Version^ get() { return pixelShaderVersion; }
			private:
                void set( Version^ value ) { pixelShaderVersion = value; }
            }

            property float PixelShader1xMaxValue
            {
                float get() { return pixelShader1xMaxValue; }
                void set( float value ) { pixelShader1xMaxValue = value; }
            }

            property SlimDX::Direct3D9::DevCaps2 DeviceCaps2
            {
                SlimDX::Direct3D9::DevCaps2 get() { return deviceCaps2; }
                void set( SlimDX::Direct3D9::DevCaps2 value ) { deviceCaps2 = value; }
            }

            property float MaxNPatchTessellationLevel
            {
                float get() { return maxNPatchTessellationLevel; }
                void set( float value ) { maxNPatchTessellationLevel = value; }
            }

            property int MasterAdapterOrdinal
            {
                int get() { return masterAdapterOrdinal; }
                void set( int value ) { masterAdapterOrdinal = value; }
            }

            property int AdapterOrdinalInGroup
            {
                int get() { return adapterOrdinalInGroup; }
                void set( int value ) { adapterOrdinalInGroup = value; }
            }

            property int NumberOfAdaptersInGroup
            {
                int get() { return numberOfAdaptersInGroup; }
                void set( int value ) { numberOfAdaptersInGroup = value; }
            }

            property DeclTypeCaps DeclTypes
            {
                DeclTypeCaps get() { return declTypes; }
                void set( DeclTypeCaps value ) { declTypes = value; }
            }

            property int NumSimultaneousRTs
            {
                int get() { return numSimultaneousRTs; }
                void set( int value ) { numSimultaneousRTs = value; }
            }

            property FilterCaps StretchRectFilterCaps
            {
                FilterCaps get() { return stretchRectFilterCaps; }
                void set( FilterCaps value ) { stretchRectFilterCaps = value; }
            }

            property VertexShader20Caps VS20Caps
            {
                VertexShader20Caps get() { return vS20Caps; }
                void set( VertexShader20Caps value ) { vS20Caps = value; }
            }

            property PixelShader20Caps PS20Caps
            {
                PixelShader20Caps get() { return pS20Caps; }
                void set( PixelShader20Caps value ) { pS20Caps = value; }
            }

            property FilterCaps VertexTextureFilterCaps
            {
                FilterCaps get() { return vertexTextureFilterCaps; }
                void set( FilterCaps value ) { vertexTextureFilterCaps = value; }
            }

			property int MaxVShaderInstructionsExecuted
			{
				int get() { return maxVShaderInstructionsExecuted; }
				void set( int value ) { maxVShaderInstructionsExecuted; }
			}

			property int MaxPShaderInstructionsExecuted
			{
				int get() { return maxPShaderInstructionsExecuted; }
				void set( int value ) { maxPShaderInstructionsExecuted; }
			}

			property int MaxVertexShader30InstructionSlots
			{
				int get() { return maxVertexShader30InstructionSlots; }
				void set( int value ) { maxVertexShader30InstructionSlots; }
			}

			property int MaxPixelShader30InstructionSlots
			{
				int get() { return maxPixelShader30InstructionSlots; }
				void set( int value ) { maxPixelShader30InstructionSlots; }
			}
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

			property IntPtr Monitor { IntPtr get(); }
			property DisplayMode CurrentDisplayMode { DisplayMode get(); }
            DisplayModeList^ GetDisplayModes( Format format );
            Capabilities GetCaps( DeviceType type );

			property AdapterDetails^ Details
			{
				AdapterDetails^ get() { return details; }
			protected:
				void set( AdapterDetails^ value ) { details = value; }
			}
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

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

namespace SlimDX
{
	namespace Direct3D9
	{
		public value class VertexShader20Caps : System::IEquatable<VertexShader20Caps>
		{
		public:
			property int Caps;
            property int DynamicFlowControlDepth;
            property int TempCount;
            property int StaticFlowControlDepth;

			static bool operator == ( VertexShader20Caps left, VertexShader20Caps right );
			static bool operator != ( VertexShader20Caps left, VertexShader20Caps right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( VertexShader20Caps other );
			static bool Equals( VertexShader20Caps% value1, VertexShader20Caps% value2 );
		};

		public value class PixelShader20Caps : System::IEquatable<PixelShader20Caps>
		{
		public:
			property int Caps;
            property int DynamicFlowControlDepth;
            property int TempCount;
            property int StaticFlowControlDepth;

			static bool operator == ( PixelShader20Caps left, PixelShader20Caps right );
			static bool operator != ( PixelShader20Caps left, PixelShader20Caps right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( PixelShader20Caps other );
			static bool Equals( PixelShader20Caps% value1, PixelShader20Caps% value2 );
		};

		public value class Capabilities : System::IEquatable<Capabilities>
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

			static bool operator == ( Capabilities left, Capabilities right );
			static bool operator != ( Capabilities left, Capabilities right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( Capabilities other );
			static bool Equals( Capabilities% value1, Capabilities% value2 );

		internal:
			Capabilities( D3DCAPS9& caps );
		};
	}
}
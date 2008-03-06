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
#include <d3d9.h>
#include <d3dx9.h>

#include "Capabilities.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	bool VertexShader20Caps::operator == ( VertexShader20Caps left, VertexShader20Caps right )
	{
		return VertexShader20Caps::Equals( left, right );
	}

	bool VertexShader20Caps::operator != ( VertexShader20Caps left, VertexShader20Caps right )
	{
		return !VertexShader20Caps::Equals( left, right );
	}

	int VertexShader20Caps::GetHashCode()
	{
		return Caps.GetHashCode() + DynamicFlowControlDepth.GetHashCode() + TempCount.GetHashCode()
			 + StaticFlowControlDepth.GetHashCode();
	}

	bool VertexShader20Caps::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<VertexShader20Caps>( value ) );
	}

	bool VertexShader20Caps::Equals( VertexShader20Caps value )
	{
		return ( Caps == value.Caps && DynamicFlowControlDepth == value.DynamicFlowControlDepth && TempCount == value.TempCount
			 && StaticFlowControlDepth == value.StaticFlowControlDepth );
	}

	bool VertexShader20Caps::Equals( VertexShader20Caps% value1, VertexShader20Caps% value2 )
	{
		return ( value1.Caps == value2.Caps && value1.DynamicFlowControlDepth == value2.DynamicFlowControlDepth && value1.TempCount == value2.TempCount
			 && value1.StaticFlowControlDepth == value2.StaticFlowControlDepth );
	}

	bool PixelShader20Caps::operator == ( PixelShader20Caps left, PixelShader20Caps right )
	{
		return PixelShader20Caps::Equals( left, right );
	}

	bool PixelShader20Caps::operator != ( PixelShader20Caps left, PixelShader20Caps right )
	{
		return !PixelShader20Caps::Equals( left, right );
	}

	int PixelShader20Caps::GetHashCode()
	{
		return Caps.GetHashCode() + DynamicFlowControlDepth.GetHashCode() + TempCount.GetHashCode()
			 + StaticFlowControlDepth.GetHashCode();
	}

	bool PixelShader20Caps::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<PixelShader20Caps>( value ) );
	}

	bool PixelShader20Caps::Equals( PixelShader20Caps value )
	{
		return ( Caps == value.Caps && DynamicFlowControlDepth == value.DynamicFlowControlDepth && TempCount == value.TempCount
			 && StaticFlowControlDepth == value.StaticFlowControlDepth );
	}

	bool PixelShader20Caps::Equals( PixelShader20Caps% value1, PixelShader20Caps% value2 )
	{
		return ( value1.Caps == value2.Caps && value1.DynamicFlowControlDepth == value2.DynamicFlowControlDepth && value1.TempCount == value2.TempCount
			 && value1.StaticFlowControlDepth == value2.StaticFlowControlDepth );
	}

	bool Capabilities::operator == ( Capabilities^ left, Capabilities^ right )
	{
		if( ReferenceEquals( left, nullptr ) )
			return ReferenceEquals( right, nullptr );

		return Capabilities::Equals( left, right );
	}

	bool Capabilities::operator != ( Capabilities^ left, Capabilities^ right )
	{
		return !( left == right );
	}

	int Capabilities::GetHashCode()
	{
		return DeviceType.GetHashCode() + AdapterOrdinal.GetHashCode() + Caps.GetHashCode()
			 + Caps2.GetHashCode() + Caps3.GetHashCode() + PresentationIntervals.GetHashCode()
			 + CursorCaps.GetHashCode() + DeviceCaps.GetHashCode() + PrimitiveMiscCaps.GetHashCode()
			 + RasterCaps.GetHashCode() + DepthCompareCaps.GetHashCode() + SourceBlendCaps.GetHashCode()
			 + DestinationBlendCaps.GetHashCode() + AlphaCompareCaps.GetHashCode() + ShadeCaps.GetHashCode()
			 + TextureCaps.GetHashCode() + TextureFilterCaps.GetHashCode() + CubeTextureFilterCaps.GetHashCode()
			 + VolumeTextureFilterCaps.GetHashCode() + TextureAddressCaps.GetHashCode() + VolumeTextureAddressCaps.GetHashCode()
			 + LineCaps.GetHashCode() + MaxTextureWidth.GetHashCode() + MaxTextureHeight.GetHashCode()
			 + MaxVolumeExtent.GetHashCode() + MaxTextureRepeat.GetHashCode() + MaxTextureAspectRatio.GetHashCode()
			 + MaxAnisotropy.GetHashCode() + MaxVertexW.GetHashCode() + GuardBandLeft.GetHashCode()
			 + GuardBandTop.GetHashCode() + GuardBandRight.GetHashCode() + GuardBandBottom.GetHashCode()
			 + ExtentsAdjust.GetHashCode() + StencilCaps.GetHashCode() + FVFCaps.GetHashCode()
			 + TextureOperationCaps.GetHashCode() + MaxTextureBlendStages.GetHashCode() + MaxSimultaneousTextures.GetHashCode()
			 + VertexProcessingCaps.GetHashCode() + MaxActiveLights.GetHashCode() + MaxUserClipPlanes.GetHashCode()
			 + MaxVertexBlendMatrices.GetHashCode() + MaxVertexBlendMatrixIndex.GetHashCode() + MaxPointSize.GetHashCode()
			 + MaxPrimitiveCount.GetHashCode() + MaxVertexIndex.GetHashCode() + MaxStreams.GetHashCode()
			 + MaxStreamStride.GetHashCode() + VertexShaderVersion->GetHashCode() + MaxVertexShaderConstants.GetHashCode()
			 + PixelShaderVersion->GetHashCode() + PixelShader1xMaxValue.GetHashCode() + DeviceCaps2.GetHashCode()
			 + MaxNPatchTessellationLevel.GetHashCode() + MasterAdapterOrdinal.GetHashCode() + AdapterOrdinalInGroup.GetHashCode()
			 + NumberOfAdaptersInGroup.GetHashCode() + DeclarationTypes.GetHashCode() + SimultaneousRTCount.GetHashCode()
			 + StretchRectFilterCaps.GetHashCode() + VS20Caps.GetHashCode() + PS20Caps.GetHashCode()
			 + VertexTextureFilterCaps.GetHashCode() + MaxVShaderInstructionsExecuted.GetHashCode() + MaxPShaderInstructionsExecuted.GetHashCode()
			 + MaxVertexShader30InstructionSlots.GetHashCode() + MaxPixelShader30InstructionSlots.GetHashCode();
	}

	bool Capabilities::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<Capabilities^>( value ) );
	}

	bool Capabilities::Equals( Capabilities^ value )
	{
		if( value == nullptr )
			return false;

		if( ReferenceEquals( this, value ) )
			return true;

		return ( DeviceType == value->DeviceType && AdapterOrdinal == value->AdapterOrdinal && Caps == value->Caps
			 && Caps2 == value->Caps2 && Caps3 == value->Caps3 && PresentationIntervals == value->PresentationIntervals
			 && CursorCaps == value->CursorCaps && DeviceCaps == value->DeviceCaps && PrimitiveMiscCaps == value->PrimitiveMiscCaps
			 && RasterCaps == value->RasterCaps && DepthCompareCaps == value->DepthCompareCaps && SourceBlendCaps == value->SourceBlendCaps
			 && DestinationBlendCaps == value->DestinationBlendCaps && AlphaCompareCaps == value->AlphaCompareCaps && ShadeCaps == value->ShadeCaps
			 && TextureCaps == value->TextureCaps && TextureFilterCaps == value->TextureFilterCaps && CubeTextureFilterCaps == value->CubeTextureFilterCaps
			 && VolumeTextureFilterCaps == value->VolumeTextureFilterCaps && TextureAddressCaps == value->TextureAddressCaps && VolumeTextureAddressCaps == value->VolumeTextureAddressCaps
			 && LineCaps == value->LineCaps && MaxTextureWidth == value->MaxTextureWidth && MaxTextureHeight == value->MaxTextureHeight
			 && MaxVolumeExtent == value->MaxVolumeExtent && MaxTextureRepeat == value->MaxTextureRepeat && MaxTextureAspectRatio == value->MaxTextureAspectRatio
			 && MaxAnisotropy == value->MaxAnisotropy && MaxVertexW == value->MaxVertexW && GuardBandLeft == value->GuardBandLeft
			 && GuardBandTop == value->GuardBandTop && GuardBandRight == value->GuardBandRight && GuardBandBottom == value->GuardBandBottom
			 && ExtentsAdjust == value->ExtentsAdjust && StencilCaps == value->StencilCaps && FVFCaps == value->FVFCaps
			 && TextureOperationCaps == value->TextureOperationCaps && MaxTextureBlendStages == value->MaxTextureBlendStages && MaxSimultaneousTextures == value->MaxSimultaneousTextures
			 && VertexProcessingCaps == value->VertexProcessingCaps && MaxActiveLights == value->MaxActiveLights && MaxUserClipPlanes == value->MaxUserClipPlanes
			 && MaxVertexBlendMatrices == value->MaxVertexBlendMatrices && MaxVertexBlendMatrixIndex == value->MaxVertexBlendMatrixIndex && MaxPointSize == value->MaxPointSize
			 && MaxPrimitiveCount == value->MaxPrimitiveCount && MaxVertexIndex == value->MaxVertexIndex && MaxStreams == value->MaxStreams
			 && MaxStreamStride == value->MaxStreamStride && VertexShaderVersion == value->VertexShaderVersion && MaxVertexShaderConstants == value->MaxVertexShaderConstants
			 && PixelShaderVersion == value->PixelShaderVersion && PixelShader1xMaxValue == value->PixelShader1xMaxValue && DeviceCaps2 == value->DeviceCaps2
			 && MaxNPatchTessellationLevel == value->MaxNPatchTessellationLevel && MasterAdapterOrdinal == value->MasterAdapterOrdinal && AdapterOrdinalInGroup == value->AdapterOrdinalInGroup
			 && NumberOfAdaptersInGroup == value->NumberOfAdaptersInGroup && DeclarationTypes == value->DeclarationTypes && SimultaneousRTCount == value->SimultaneousRTCount
			 && StretchRectFilterCaps == value->StretchRectFilterCaps && VS20Caps == value->VS20Caps && PS20Caps == value->PS20Caps
			 && VertexTextureFilterCaps == value->VertexTextureFilterCaps && MaxVShaderInstructionsExecuted == value->MaxVShaderInstructionsExecuted && MaxPShaderInstructionsExecuted == value->MaxPShaderInstructionsExecuted
			 && MaxVertexShader30InstructionSlots == value->MaxVertexShader30InstructionSlots && MaxPixelShader30InstructionSlots == value->MaxPixelShader30InstructionSlots );
	}

	bool Capabilities::Equals( Capabilities^ value1, Capabilities^ value2 )
	{
		return value1->Equals( value2 );
	}
}
}
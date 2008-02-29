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

		return Equals( static_cast<VertexShader20Caps>( value ) );
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

		return Equals( static_cast<PixelShader20Caps>( value ) );
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

	bool Capabilities::operator == ( Capabilities left, Capabilities right )
	{
		return Capabilities::Equals( left, right );
	}

	bool Capabilities::operator != ( Capabilities left, Capabilities right )
	{
		return !Capabilities::Equals( left, right );
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

		return Equals( static_cast<Capabilities>( value ) );
	}

	bool Capabilities::Equals( Capabilities value )
	{
		return ( DeviceType == value.DeviceType && AdapterOrdinal == value.AdapterOrdinal && Caps == value.Caps
			 && Caps2 == value.Caps2 && Caps3 == value.Caps3 && PresentationIntervals == value.PresentationIntervals
			 && CursorCaps == value.CursorCaps && DeviceCaps == value.DeviceCaps && PrimitiveMiscCaps == value.PrimitiveMiscCaps
			 && RasterCaps == value.RasterCaps && DepthCompareCaps == value.DepthCompareCaps && SourceBlendCaps == value.SourceBlendCaps
			 && DestinationBlendCaps == value.DestinationBlendCaps && AlphaCompareCaps == value.AlphaCompareCaps && ShadeCaps == value.ShadeCaps
			 && TextureCaps == value.TextureCaps && TextureFilterCaps == value.TextureFilterCaps && CubeTextureFilterCaps == value.CubeTextureFilterCaps
			 && VolumeTextureFilterCaps == value.VolumeTextureFilterCaps && TextureAddressCaps == value.TextureAddressCaps && VolumeTextureAddressCaps == value.VolumeTextureAddressCaps
			 && LineCaps == value.LineCaps && MaxTextureWidth == value.MaxTextureWidth && MaxTextureHeight == value.MaxTextureHeight
			 && MaxVolumeExtent == value.MaxVolumeExtent && MaxTextureRepeat == value.MaxTextureRepeat && MaxTextureAspectRatio == value.MaxTextureAspectRatio
			 && MaxAnisotropy == value.MaxAnisotropy && MaxVertexW == value.MaxVertexW && GuardBandLeft == value.GuardBandLeft
			 && GuardBandTop == value.GuardBandTop && GuardBandRight == value.GuardBandRight && GuardBandBottom == value.GuardBandBottom
			 && ExtentsAdjust == value.ExtentsAdjust && StencilCaps == value.StencilCaps && FVFCaps == value.FVFCaps
			 && TextureOperationCaps == value.TextureOperationCaps && MaxTextureBlendStages == value.MaxTextureBlendStages && MaxSimultaneousTextures == value.MaxSimultaneousTextures
			 && VertexProcessingCaps == value.VertexProcessingCaps && MaxActiveLights == value.MaxActiveLights && MaxUserClipPlanes == value.MaxUserClipPlanes
			 && MaxVertexBlendMatrices == value.MaxVertexBlendMatrices && MaxVertexBlendMatrixIndex == value.MaxVertexBlendMatrixIndex && MaxPointSize == value.MaxPointSize
			 && MaxPrimitiveCount == value.MaxPrimitiveCount && MaxVertexIndex == value.MaxVertexIndex && MaxStreams == value.MaxStreams
			 && MaxStreamStride == value.MaxStreamStride && VertexShaderVersion == value.VertexShaderVersion && MaxVertexShaderConstants == value.MaxVertexShaderConstants
			 && PixelShaderVersion == value.PixelShaderVersion && PixelShader1xMaxValue == value.PixelShader1xMaxValue && DeviceCaps2 == value.DeviceCaps2
			 && MaxNPatchTessellationLevel == value.MaxNPatchTessellationLevel && MasterAdapterOrdinal == value.MasterAdapterOrdinal && AdapterOrdinalInGroup == value.AdapterOrdinalInGroup
			 && NumberOfAdaptersInGroup == value.NumberOfAdaptersInGroup && DeclarationTypes == value.DeclarationTypes && SimultaneousRTCount == value.SimultaneousRTCount
			 && StretchRectFilterCaps == value.StretchRectFilterCaps && VS20Caps == value.VS20Caps && PS20Caps == value.PS20Caps
			 && VertexTextureFilterCaps == value.VertexTextureFilterCaps && MaxVShaderInstructionsExecuted == value.MaxVShaderInstructionsExecuted && MaxPShaderInstructionsExecuted == value.MaxPShaderInstructionsExecuted
			 && MaxVertexShader30InstructionSlots == value.MaxVertexShader30InstructionSlots && MaxPixelShader30InstructionSlots == value.MaxPixelShader30InstructionSlots );
	}

	bool Capabilities::Equals( Capabilities% value1, Capabilities% value2 )
	{
		return ( value1.DeviceType == value2.DeviceType && value1.AdapterOrdinal == value2.AdapterOrdinal && value1.Caps == value2.Caps
			 && value1.Caps2 == value2.Caps2 && value1.Caps3 == value2.Caps3 && value1.PresentationIntervals == value2.PresentationIntervals
			 && value1.CursorCaps == value2.CursorCaps && value1.DeviceCaps == value2.DeviceCaps && value1.PrimitiveMiscCaps == value2.PrimitiveMiscCaps
			 && value1.RasterCaps == value2.RasterCaps && value1.DepthCompareCaps == value2.DepthCompareCaps && value1.SourceBlendCaps == value2.SourceBlendCaps
			 && value1.DestinationBlendCaps == value2.DestinationBlendCaps && value1.AlphaCompareCaps == value2.AlphaCompareCaps && value1.ShadeCaps == value2.ShadeCaps
			 && value1.TextureCaps == value2.TextureCaps && value1.TextureFilterCaps == value2.TextureFilterCaps && value1.CubeTextureFilterCaps == value2.CubeTextureFilterCaps
			 && value1.VolumeTextureFilterCaps == value2.VolumeTextureFilterCaps && value1.TextureAddressCaps == value2.TextureAddressCaps && value1.VolumeTextureAddressCaps == value2.VolumeTextureAddressCaps
			 && value1.LineCaps == value2.LineCaps && value1.MaxTextureWidth == value2.MaxTextureWidth && value1.MaxTextureHeight == value2.MaxTextureHeight
			 && value1.MaxVolumeExtent == value2.MaxVolumeExtent && value1.MaxTextureRepeat == value2.MaxTextureRepeat && value1.MaxTextureAspectRatio == value2.MaxTextureAspectRatio
			 && value1.MaxAnisotropy == value2.MaxAnisotropy && value1.MaxVertexW == value2.MaxVertexW && value1.GuardBandLeft == value2.GuardBandLeft
			 && value1.GuardBandTop == value2.GuardBandTop && value1.GuardBandRight == value2.GuardBandRight && value1.GuardBandBottom == value2.GuardBandBottom
			 && value1.ExtentsAdjust == value2.ExtentsAdjust && value1.StencilCaps == value2.StencilCaps && value1.FVFCaps == value2.FVFCaps
			 && value1.TextureOperationCaps == value2.TextureOperationCaps && value1.MaxTextureBlendStages == value2.MaxTextureBlendStages && value1.MaxSimultaneousTextures == value2.MaxSimultaneousTextures
			 && value1.VertexProcessingCaps == value2.VertexProcessingCaps && value1.MaxActiveLights == value2.MaxActiveLights && value1.MaxUserClipPlanes == value2.MaxUserClipPlanes
			 && value1.MaxVertexBlendMatrices == value2.MaxVertexBlendMatrices && value1.MaxVertexBlendMatrixIndex == value2.MaxVertexBlendMatrixIndex && value1.MaxPointSize == value2.MaxPointSize
			 && value1.MaxPrimitiveCount == value2.MaxPrimitiveCount && value1.MaxVertexIndex == value2.MaxVertexIndex && value1.MaxStreams == value2.MaxStreams
			 && value1.MaxStreamStride == value2.MaxStreamStride && value1.VertexShaderVersion == value2.VertexShaderVersion && value1.MaxVertexShaderConstants == value2.MaxVertexShaderConstants
			 && value1.PixelShaderVersion == value2.PixelShaderVersion && value1.PixelShader1xMaxValue == value2.PixelShader1xMaxValue && value1.DeviceCaps2 == value2.DeviceCaps2
			 && value1.MaxNPatchTessellationLevel == value2.MaxNPatchTessellationLevel && value1.MasterAdapterOrdinal == value2.MasterAdapterOrdinal && value1.AdapterOrdinalInGroup == value2.AdapterOrdinalInGroup
			 && value1.NumberOfAdaptersInGroup == value2.NumberOfAdaptersInGroup && value1.DeclarationTypes == value2.DeclarationTypes && value1.SimultaneousRTCount == value2.SimultaneousRTCount
			 && value1.StretchRectFilterCaps == value2.StretchRectFilterCaps && value1.VS20Caps == value2.VS20Caps && value1.PS20Caps == value2.PS20Caps
			 && value1.VertexTextureFilterCaps == value2.VertexTextureFilterCaps && value1.MaxVShaderInstructionsExecuted == value2.MaxVShaderInstructionsExecuted && value1.MaxPShaderInstructionsExecuted == value2.MaxPShaderInstructionsExecuted
			 && value1.MaxVertexShader30InstructionSlots == value2.MaxVertexShader30InstructionSlots && value1.MaxPixelShader30InstructionSlots == value2.MaxPixelShader30InstructionSlots );
	}
}
}
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

#if D3DX_SDK_VERSION != 36
#error You are not compiling against the November 2007 SDK. Change the linker settings to delay load the correct DLLs and update this code.
#endif

#include "../Utilities.h"

#include "Direct3D9Exception.h"
#include "Direct3D9NotFoundException.h"
#include "Direct3DX9NotFoundException.h"

#include "Enums.h"

#include "Direct3D.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	bool DisplayMode::operator == ( DisplayMode left, DisplayMode right )
	{
		return DisplayMode::Equals( left, right );
	}

	bool DisplayMode::operator != ( DisplayMode left, DisplayMode right )
	{
		return !DisplayMode::Equals( left, right );
	}

	int DisplayMode::GetHashCode()
	{
		return Width.GetHashCode() + Height.GetHashCode() + RefreshRate.GetHashCode()
			 + Format.GetHashCode();
	}

	bool DisplayMode::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<DisplayMode>( value ) );
	}

	bool DisplayMode::Equals( DisplayMode value )
	{
		return ( Width == value.Width && Height == value.Height && RefreshRate == value.RefreshRate
			 && Format == value.Format );
	}

	bool DisplayMode::Equals( DisplayMode% value1, DisplayMode% value2 )
	{
		return ( value1.Width == value2.Width && value1.Height == value2.Height && value1.RefreshRate == value2.RefreshRate
			 && value1.Format == value2.Format );
	}

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

	AdapterDetails::AdapterDetails( unsigned int adapter )
	{
		D3DADAPTER_IDENTIFIER9 ident;
		DWORD flags = Direct3D::CheckWhql ? D3DENUM_WHQL_LEVEL : 0;

		HRESULT hr = Direct3D::InternalPointer->GetAdapterIdentifier( adapter, flags, &ident );
		RECORD_D3D9( hr );
		
		Adapter = adapter;
		DriverName = gcnew String( ident.Driver );
		Description = gcnew String( ident.Description );
		DeviceName = gcnew String( ident.DeviceName );
		DriverVersion = gcnew Version( HIWORD( ident.DriverVersion.HighPart ), LOWORD( ident.DriverVersion.HighPart ),
			HIWORD( ident.DriverVersion.LowPart ), LOWORD( ident.DriverVersion.LowPart ) );
		VendorId = ident.VendorId;
		DeviceId = ident.DeviceId;
		SubsystemId = ident.SubSysId;
		Revision = ident.Revision;
		DeviceIdentifier = Utilities::ConvertNativeGuid( ident.DeviceIdentifier );
		WhqlLevel = ident.WHQLLevel;
	}

	DisplayModeCollection::DisplayModeCollection( unsigned int adapter, Format format )
	{
		int count = Direct3D::GetAdapterModeCount( adapter, format );
		m_Modes = gcnew array<DisplayMode>( count );

		for( int i = 0; i < count; ++i )
			m_Modes[i] = Direct3D::EnumerateAdapterModes( adapter, format, i );
	}

	AdapterInformation::AdapterInformation( unsigned int adapter )
	{
		m_Adapter = static_cast<int>( adapter );
		Details = gcnew AdapterDetails( adapter );
	}

	IntPtr AdapterInformation::Monitor::get()
	{
		return Direct3D::GetAdapterMonitor( m_Adapter );
	}

	DisplayMode AdapterInformation::CurrentDisplayMode::get()
	{
        return Direct3D::GetAdapterDisplayMode( m_Adapter );
	}

    Capabilities AdapterInformation::GetCaps( DeviceType type )
    {
        return Direct3D::GetDeviceCaps( m_Adapter, type );
    }

	bool AdapterInformation::SupportsR2VB( DeviceType type )
	{
		return Direct3D::SupportsR2VB( m_Adapter, type );
	}

    DisplayModeCollection^ AdapterInformation::GetDisplayModes( Format format )
    {
        return gcnew DisplayModeCollection( m_Adapter, format );
    }

    AdapterCollection::AdapterCollection( unsigned int adapterCount )
    {
        m_Adapters = gcnew array<AdapterInformation^>( adapterCount );
        for( unsigned int i = 0; i < adapterCount; ++i )
        {
            m_Adapters[i] = gcnew AdapterInformation( i );
        }
    }

	void Direct3D::Initialize()
	{
		if( m_Direct3D != NULL )
			return;

        try
        {
		    m_Direct3D = Direct3DCreate9( D3D_SDK_VERSION );
        }
        catch( System::Runtime::InteropServices::SEHException^ ex )
        {
            throw gcnew Direct3D9NotFoundException( "Direct3D 9 was not found. Reinstalling DirectX may fix the problem.", ex );
        }

		if( m_Direct3D == NULL )
			throw gcnew Direct3D9Exception( "Could not create Direct3D instance." );

		CheckWhql = false;
		Adapters = gcnew AdapterCollection( m_Direct3D->GetAdapterCount() );
		
		System::AppDomain::CurrentDomain->DomainUnload += gcnew System::EventHandler( OnExit );
		System::AppDomain::CurrentDomain->ProcessExit += gcnew System::EventHandler( OnExit );

        //probe for D3DX
        try
        {
            D3DXCheckVersion( D3D_SDK_VERSION, D3DX_SDK_VERSION );
        }
        catch( System::Runtime::InteropServices::SEHException^ ex )
        {
            throw gcnew Direct3DX9NotFoundException( "Direct3DX 9 was not found. Please install "
                "the latest DirectX end-user redistributable package from Microsoft.", ex );
        }
	}

	void Direct3D::Terminate()
	{
		if( m_Direct3D == NULL )
            return;

		m_Direct3D->Release();
		m_Direct3D = NULL;

		System::AppDomain::CurrentDomain->DomainUnload -= gcnew System::EventHandler( OnExit );
		System::AppDomain::CurrentDomain->ProcessExit -= gcnew System::EventHandler( OnExit );
	}

	/// <summary>
	/// Tests the device to see if it supports conversion from one display format to another.
	/// </summary>
	/// <param name="adapter">Index of the adapter to use.</param>
	/// <param name="deviceType">One of the DeviceType members.</param>
	/// <param name="sourceFormat">Format to convert from.</param>
	/// <param name="targetFormat">Format to convert into.</param>
	/// <param name="result">0 if successful.  Otherwise an HRESULT error code for the function.</param>
	/// <returns>TRUE if successful, FALSE if not.</returns>
	bool Direct3D::CheckDeviceFormatConversion(int adapter, DeviceType deviceType, Format sourceFormat, Format targetFormat, [Out] int% result)
	{
		HRESULT hr;		// Error code.

		hr = m_Direct3D->CheckDeviceFormatConversion(adapter, static_cast<D3DDEVTYPE>( deviceType ), 
			static_cast<D3DFORMAT>( sourceFormat ), static_cast<D3DFORMAT>( targetFormat) );

		result = hr;

		return SUCCEEDED(hr);
	}

	/// <summary>
	/// Tests the device to see if it supports conversion from one display format to another.
	/// </summary>
	/// <param name="adapter">Index of the adapter to use.</param>
	/// <param name="deviceType">One of the DeviceType members.</param>
	/// <param name="sourceFormat">Format to convert from.</param>
	/// <param name="targetFormat">Format to convert into.</param>
	/// <returns>TRUE if successful, FALSE if not.</returns>
	bool Direct3D::CheckDeviceFormatConversion(int adapter, DeviceType deviceType, Format sourceFormat, Format targetFormat)
	{
		int result = 0;		// Error result.

		return CheckDeviceFormatConversion(adapter, deviceType, sourceFormat, targetFormat, result);
	}

	bool Direct3D::CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
		Usage usage, ResourceType resourceType, Format checkFormat, [Out] int% result )
	{
		HRESULT hr = m_Direct3D->CheckDeviceFormat( adapter, static_cast<D3DDEVTYPE>( deviceType ), static_cast<D3DFORMAT>( adapterFormat ),
			static_cast<DWORD>( usage ), static_cast<D3DRESOURCETYPE>( resourceType ), static_cast<D3DFORMAT>( checkFormat ) );
		result = hr;
		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
		Usage usage, ResourceType resourceType, Format checkFormat )
	{
		int result;
		return CheckDeviceFormat( adapter, deviceType, adapterFormat, usage, resourceType, checkFormat, result );
	}

	bool Direct3D::CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format backBufferFormat, bool windowed, [Out] int% result )
	{
		HRESULT hr = m_Direct3D->CheckDeviceType( adapter, static_cast<D3DDEVTYPE>( deviceType ), 
			static_cast<D3DFORMAT>( adapterFormat ), static_cast<D3DFORMAT>( backBufferFormat ), windowed );
		result = hr;
		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format backBufferFormat, bool windowed )
	{
		int result;
		return CheckDeviceType( adapter, deviceType, adapterFormat, backBufferFormat, windowed, result );
	}

	bool Direct3D::CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format renderTargetFormat, Format depthStencilFormat, [Out] int% result )
	{
		HRESULT hr = m_Direct3D->CheckDepthStencilMatch( adapter, static_cast<D3DDEVTYPE>( deviceType ),
			static_cast<D3DFORMAT>( adapterFormat ), static_cast<D3DFORMAT>( renderTargetFormat ), static_cast<D3DFORMAT>( depthStencilFormat ) );
		result = hr;
		return hr == S_OK;
	}

	bool Direct3D::CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format renderTargetFormat, Format depthStencilFormat )
	{
		int result;
		return CheckDepthStencilMatch( adapter, deviceType, adapterFormat,
			renderTargetFormat, depthStencilFormat, result );
	}

	bool Direct3D::CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultisampleType multiSampleType, [Out] int% qualityLevels, [Out] int% result )
	{
		DWORD levels;

		HRESULT hr = m_Direct3D->CheckDeviceMultiSampleType( adapter, static_cast<D3DDEVTYPE>( deviceType ), static_cast<D3DFORMAT>( surfaceFormat ),
			windowed, static_cast<D3DMULTISAMPLE_TYPE>( multiSampleType ),  static_cast<DWORD*>( &levels ) );

		qualityLevels = levels;
		result = hr;
		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultisampleType multiSampleType, [Out] int% qualityLevels )
	{
		int result;
		return CheckDeviceMultisampleType( adapter, deviceType, surfaceFormat,
			windowed, multiSampleType, qualityLevels, result );
	}

	bool Direct3D::CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultisampleType multiSampleType )
	{
		int levels, result;
		return CheckDeviceMultisampleType( adapter, deviceType, surfaceFormat, windowed,
			multiSampleType, levels, result );
	}

    DisplayMode Direct3D::GetAdapterDisplayMode( int adapter )
    {
        DisplayMode displayMode;
        m_Direct3D->GetAdapterDisplayMode( adapter, reinterpret_cast<D3DDISPLAYMODE*>( &displayMode ) );
        return displayMode;
    }

    AdapterDetails^ Direct3D::GetAdapterIdentifier( int adapter )
    {
        return gcnew AdapterDetails( adapter );
    }

    int Direct3D::GetAdapterModeCount( int adapter, Format format )
    {
        return m_Direct3D->GetAdapterModeCount( adapter, static_cast<D3DFORMAT>( format ) );
    }

    DisplayMode Direct3D::EnumerateAdapterModes( int adapter, Format format, int modeIndex )
    {
        DisplayMode displayMode;
        HRESULT hr = m_Direct3D->EnumAdapterModes( adapter, static_cast<D3DFORMAT>( format ),
			modeIndex, reinterpret_cast<D3DDISPLAYMODE*>( &displayMode ) );
        RECORD_D3D9( hr );
        return displayMode;
    }

    IntPtr Direct3D::GetAdapterMonitor( int adapter )
    {
        return IntPtr( m_Direct3D->GetAdapterMonitor( adapter ) );
    }

	Capabilities Direct3D::GetDeviceCaps( int adapter, DeviceType deviceType )
	{
		D3DCAPS9 caps;
		HRESULT hr = Direct3D::InternalPointer->GetDeviceCaps( adapter, static_cast<D3DDEVTYPE>( deviceType ), &caps );
		RECORD_D3D9( hr );

		return Capabilities( caps );
	}

	bool Direct3D::SupportsR2VB( int adapter, DeviceType deviceType )
	{
		return CheckDeviceFormat( adapter, deviceType, Format::X8R8G8B8, Usage::None, ResourceType::Surface, Format::ATI_R2VB );
	}

	Capabilities::Capabilities( D3DCAPS9& caps )
	{
		DeviceType = static_cast<SlimDX::Direct3D9::DeviceType>( caps.DeviceType );
		AdapterOrdinal = caps.AdapterOrdinal;

		Caps = static_cast<SlimDX::Direct3D9::Caps>( caps.Caps );
		Caps2 = static_cast<SlimDX::Direct3D9::Caps2>( caps.Caps2 );
		Caps3 = static_cast<SlimDX::Direct3D9::Caps3>( caps.Caps3 );
		PresentationIntervals = static_cast<SlimDX::Direct3D9::PresentInterval>( caps.PresentationIntervals );

		CursorCaps = static_cast<SlimDX::Direct3D9::CursorCaps>( caps.CursorCaps );

		DeviceCaps = static_cast<SlimDX::Direct3D9::DeviceCaps>( caps.DevCaps );

		PrimitiveMiscCaps = static_cast<SlimDX::Direct3D9::PrimitiveMiscCaps>( caps.PrimitiveMiscCaps );
		RasterCaps = static_cast<SlimDX::Direct3D9::RasterCaps>( caps.RasterCaps );
		DepthCompareCaps = static_cast<CompareCaps>( caps.ZCmpCaps );
		SourceBlendCaps = static_cast<BlendCaps>( caps.SrcBlendCaps );
		DestinationBlendCaps = static_cast<BlendCaps>( caps.DestBlendCaps );
		AlphaCompareCaps = static_cast<CompareCaps>( caps.AlphaCmpCaps );
		ShadeCaps = static_cast<SlimDX::Direct3D9::ShadeCaps>( caps.ShadeCaps );
		TextureCaps = static_cast<SlimDX::Direct3D9::TextureCaps>( caps.TextureCaps );
		TextureFilterCaps = static_cast<FilterCaps>( caps.TextureFilterCaps );
		CubeTextureFilterCaps = static_cast<FilterCaps>( caps.CubeTextureFilterCaps );
		VolumeTextureFilterCaps = static_cast<FilterCaps>( caps.VertexTextureFilterCaps );
		TextureAddressCaps = static_cast<SlimDX::Direct3D9::TextureAddressCaps>( caps.TextureAddressCaps );
		VolumeTextureAddressCaps = static_cast<SlimDX::Direct3D9::TextureAddressCaps>( caps.VolumeTextureAddressCaps );

		LineCaps = static_cast<SlimDX::Direct3D9::LineCaps>( caps.LineCaps );

		MaxTextureWidth = caps.MaxTextureWidth;
		MaxTextureHeight = caps.MaxTextureHeight;
		MaxVolumeExtent = caps.MaxVolumeExtent;

		MaxTextureRepeat = caps.MaxTextureRepeat;
		MaxTextureAspectRatio = caps.MaxTextureAspectRatio;
		MaxAnisotropy = caps.MaxAnisotropy;
		MaxVertexW = caps.MaxVertexW;

		GuardBandLeft = caps.GuardBandLeft;
		GuardBandTop = caps.GuardBandTop;
		GuardBandRight = caps.GuardBandRight;
		GuardBandBottom = caps.GuardBandBottom;

		ExtentsAdjust = caps.ExtentsAdjust;
		StencilCaps = static_cast<SlimDX::Direct3D9::StencilCaps>( caps.StencilCaps );

		FVFCaps = static_cast<VertexFormatCaps>( caps.FVFCaps );
		TextureOperationCaps = static_cast<SlimDX::Direct3D9::TextureOperationCaps>( caps.TextureOpCaps );
		MaxTextureBlendStages = caps.MaxTextureBlendStages;
		MaxSimultaneousTextures = caps.MaxSimultaneousTextures;

		VertexProcessingCaps = static_cast<SlimDX::Direct3D9::VertexProcessingCaps>( caps.VertexProcessingCaps );
		MaxActiveLights = caps.MaxActiveLights;
		MaxUserClipPlanes = caps.MaxUserClipPlanes;
		MaxVertexBlendMatrices = caps.MaxVertexBlendMatrices;
		MaxVertexBlendMatrixIndex = caps.MaxVertexBlendMatrixIndex;

		MaxPointSize = caps.MaxPointSize;

		MaxPrimitiveCount = caps.MaxPrimitiveCount;
		MaxVertexIndex = caps.MaxVertexIndex;
		MaxStreams = caps.MaxStreams;
		MaxStreamStride = caps.MaxStreamStride;

		VertexShaderVersion = gcnew Version( D3DSHADER_VERSION_MAJOR( caps.VertexShaderVersion ), 
			D3DSHADER_VERSION_MINOR( caps.VertexShaderVersion ) );
		MaxVertexShaderConstants = caps.MaxVertexShaderConst;

		PixelShaderVersion = gcnew Version( D3DSHADER_VERSION_MAJOR( caps.PixelShaderVersion ), 
			D3DSHADER_VERSION_MINOR( caps.PixelShaderVersion ) );
		PixelShader1xMaxValue = caps.PixelShader1xMaxValue;

		DeviceCaps2 = static_cast<DevCaps2>( caps.DevCaps2 );

		MaxNPatchTessellationLevel = caps.MaxNpatchTessellationLevel;

		MasterAdapterOrdinal = caps.MasterAdapterOrdinal;
		AdapterOrdinalInGroup = caps.AdapterOrdinalInGroup;
		NumberOfAdaptersInGroup = caps.NumberOfAdaptersInGroup;
		DeclarationTypes = static_cast<DeclarationTypeCaps>( caps.DeclTypes );
		SimultaneousRTCount = caps.NumSimultaneousRTs;
		StretchRectFilterCaps = static_cast<FilterCaps>( caps.StretchRectFilterCaps );
		VS20Caps = *reinterpret_cast<VertexShader20Caps*>( &caps.VS20Caps );
		PS20Caps = *reinterpret_cast<PixelShader20Caps*>( &caps.PS20Caps );
		VertexTextureFilterCaps = static_cast<FilterCaps>( caps.VertexTextureFilterCaps );
		MaxVShaderInstructionsExecuted = caps.MaxVShaderInstructionsExecuted;
		MaxPShaderInstructionsExecuted = caps.MaxPShaderInstructionsExecuted;
		MaxVertexShader30InstructionSlots = caps.MaxVertexShader30InstructionSlots;
		MaxPixelShader30InstructionSlots = caps.MaxPixelShader30InstructionSlots;
	}
}
}

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
#include <d3d9.h>
#include <d3dx9.h>

#if D3DX_SDK_VERSION != 34
#error You are not compiling against the June 2007 SDK. Change the linker settings to delay load the correct DLLs and update this code.
#endif

#include "../Direct3D/GraphicsException.h"
#include "Enums.h"

#include "Direct3D.h"

namespace SlimDX
{
namespace Direct3D9
{
	AdapterDetails::AdapterDetails( unsigned int adapter )
	{
		D3DADAPTER_IDENTIFIER9 ident;
		DWORD flags = Direct3D::CheckWhql ? D3DENUM_WHQL_LEVEL : 0;

		HRESULT hr = Direct3D::InternalPointer->GetAdapterIdentifier( adapter, flags, &ident );
		GraphicsException::CheckHResult( hr );
		
		Adapter = adapter;
		DriverName = gcnew String( ident.Driver );
		Description = gcnew String( ident.Description );
		DeviceName = gcnew String( ident.DeviceName );
		DriverVersion = gcnew Version( HIWORD( ident.DriverVersion.HighPart ), LOWORD( ident.DriverVersion.HighPart ),
			HIWORD( ident.DriverVersion.LowPart ), LOWORD( ident.DriverVersion.LowPart ) );
		VendorId = ident.VendorId;
		DeviceId = ident.DeviceId;
		SubSystemId = ident.SubSysId;
		Revision = ident.Revision;
		DeviceIdentifier = Guid( ident.DeviceIdentifier.Data1, ident.DeviceIdentifier.Data2, ident.DeviceIdentifier.Data3,
			ident.DeviceIdentifier.Data4[0], ident.DeviceIdentifier.Data4[1], ident.DeviceIdentifier.Data4[2],
			ident.DeviceIdentifier.Data4[3], ident.DeviceIdentifier.Data4[4], ident.DeviceIdentifier.Data4[5],
			ident.DeviceIdentifier.Data4[6], ident.DeviceIdentifier.Data4[7] );
		WhqlLevel = ident.WHQLLevel;
	}


	AdapterInformation::AdapterInformation( unsigned int adapter )
	{
		m_Adapter = (int) adapter;
		Details = gcnew AdapterDetails( adapter );
	}

	int AdapterInformation::Monitor::get()
	{
		return (int) Direct3D::InternalPointer->GetAdapterMonitor( m_Adapter );
	}

	DisplayMode AdapterInformation::CurrentDisplayMode::get()
	{
		DisplayMode displayMode;
		HRESULT hr = Direct3D::InternalPointer->GetAdapterDisplayMode( m_Adapter, (D3DDISPLAYMODE*) &displayMode );
		return displayMode;
	}


	void Direct3D::Initialize()
	{
		if( m_Direct3D != NULL )
			return;

        try
        {
		    m_Direct3D = Direct3DCreate9( D3D_SDK_VERSION );
        }
        catch( SEHException^ ex )
        {
            throw gcnew Direct3D9NotFoundException( "Direct3D 9 was not found. Reinstalling DirectX may fix the problem.", ex );
        }

		if( m_Direct3D == NULL )
			throw gcnew DirectXException( -1, "Could not create Direct3D instance." );

		CheckWhql = false;
		Adapters = gcnew AdapterList( m_Direct3D->GetAdapterCount() );
		
		System::AppDomain::CurrentDomain->DomainUnload += gcnew System::EventHandler( OnExit );
		System::AppDomain::CurrentDomain->ProcessExit += gcnew System::EventHandler( OnExit );

        //probe for D3DX
        try
        {
            BOOL d3dx = D3DXCheckVersion( D3D_SDK_VERSION, D3DX_SDK_VERSION );
        }
        catch( SEHException^ ex )
        {
            throw gcnew Direct3DX9NotFoundException( "Direct3DX 9 was not found. Please install "
                "the latest DirectX end-user redistributable from Microsoft.", ex );
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

	bool Direct3D::CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
		Usage usage, ResourceType resourceType, Format checkFormat, [Out] int% result )
	{
		HRESULT hr = m_Direct3D->CheckDeviceFormat( adapter, (D3DDEVTYPE) deviceType, (D3DFORMAT) adapterFormat,
			(DWORD) usage, (D3DRESOURCETYPE) resourceType, (D3DFORMAT) checkFormat );
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
		HRESULT hr = m_Direct3D->CheckDeviceType( adapter, (D3DDEVTYPE) deviceType, 
			(D3DFORMAT) adapterFormat, (D3DFORMAT) backBufferFormat, windowed );
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
		HRESULT hr = m_Direct3D->CheckDepthStencilMatch( adapter, (D3DDEVTYPE) deviceType,
			(D3DFORMAT) adapterFormat, (D3DFORMAT) renderTargetFormat, (D3DFORMAT) depthStencilFormat );
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

	bool Direct3D::CheckDeviceMultiSampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultiSampleType multiSampleType, [Out] int% qualityLevels, [Out] int% result )
	{
		DWORD levels;

		HRESULT hr = m_Direct3D->CheckDeviceMultiSampleType( adapter, (D3DDEVTYPE) deviceType, (D3DFORMAT) surfaceFormat,
			windowed, (D3DMULTISAMPLE_TYPE) multiSampleType, (DWORD*) &levels );

		qualityLevels = levels;
		result = hr;
		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceMultiSampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultiSampleType multiSampleType, [Out] int% qualityLevels )
	{
		int result;
		return CheckDeviceMultiSampleType( adapter, deviceType, surfaceFormat,
			windowed, multiSampleType, qualityLevels, result );
	}

	bool Direct3D::CheckDeviceMultiSampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultiSampleType multiSampleType )
	{
		int levels, result;
		return CheckDeviceMultiSampleType( adapter, deviceType, surfaceFormat, windowed,
			multiSampleType, levels, result );
	}

	Capabilities Direct3D::GetDeviceCaps( int adapter, DeviceType deviceType )
	{
		D3DCAPS9 caps;
		Direct3D::InternalPointer->GetDeviceCaps( adapter, (D3DDEVTYPE) deviceType, &caps );
		return Capabilities( caps );
	}


	Capabilities::Capabilities( const D3DCAPS9& caps )
	{
		DeviceType = (SlimDX::Direct3D9::DeviceType) caps.DeviceType;
		AdapterOrdinal = caps.AdapterOrdinal;

		Caps = (SlimDX::Direct3D9::Caps) caps.Caps;
		Caps2 = (SlimDX::Direct3D9::Caps2) caps.Caps2;
		Caps3 = (SlimDX::Direct3D9::Caps3) caps.Caps3;
		PresentInterval = caps.PresentationIntervals;

		CursorCaps = (SlimDX::Direct3D9::CursorCaps) caps.CursorCaps;

		DeviceCaps = (SlimDX::Direct3D9::DeviceCaps) caps.DevCaps;

		PrimitiveMiscCaps = (SlimDX::Direct3D9::PrimitiveMiscCaps) caps.PrimitiveMiscCaps;
		RasterCaps = (SlimDX::Direct3D9::RasterCaps) caps.RasterCaps;
		ZCompareCaps = (CompareCaps) caps.ZCmpCaps;
		SourceBlendCaps = (BlendCaps) caps.SrcBlendCaps;
		DestBlendCaps = (BlendCaps) caps.DestBlendCaps;
		AlphaCompareCaps = (CompareCaps) caps.AlphaCmpCaps;
		ShadeCaps = (SlimDX::Direct3D9::ShadeCaps) caps.ShadeCaps;
		TextureCaps = (SlimDX::Direct3D9::TextureCaps) caps.TextureCaps;
		TextureFilterCaps = (FilterCaps) caps.TextureFilterCaps;
		CubeTextureFilterCaps = (FilterCaps) caps.CubeTextureFilterCaps;
		VolumeTextureFilterCaps = (FilterCaps) caps.VertexTextureFilterCaps;
		TextureAddressCaps = (SlimDX::Direct3D9::TextureAddressCaps) caps.TextureAddressCaps;
		VolumeTextureAddressCaps = (SlimDX::Direct3D9::TextureAddressCaps) caps.VolumeTextureAddressCaps;

		LineCaps = (SlimDX::Direct3D9::LineCaps) caps.LineCaps;

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
		StencilCaps = (SlimDX::Direct3D9::StencilCaps) caps.StencilCaps;

		FVFCaps = (VertexFormatCaps) caps.FVFCaps;
		TextureOpCaps = (SlimDX::Direct3D9::TextureOpCaps) caps.TextureOpCaps;
		MaxTextureBlendStages = caps.MaxTextureBlendStages;
		MaxSimultaneousTextures = caps.MaxSimultaneousTextures;

		VertexProcessingCaps = (SlimDX::Direct3D9::VertexProcessingCaps) caps.VertexProcessingCaps;
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

		DeviceCaps2 = (DevCaps2) caps.DevCaps2;

		MaxNPatchTessellationLevel = caps.MaxNpatchTessellationLevel;

		MasterAdapterOrdinal = caps.MasterAdapterOrdinal;
		AdapterOrdinalInGroup = caps.AdapterOrdinalInGroup;
		NumberOfAdaptersInGroup = caps.NumberOfAdaptersInGroup;
		DeclTypes = (DeclTypeCaps) caps.DeclTypes;
		NumSimultaneousRTs = caps.NumSimultaneousRTs;
		StretchRectFilterCaps = (FilterCaps) caps.StretchRectFilterCaps;
		VS20Caps = *(VertexShader20Caps*) &caps.VS20Caps;
		PS20Caps = *(PixelShader20Caps*) &caps.PS20Caps;
		VertexTextureFilterCaps = (FilterCaps) caps.VertexTextureFilterCaps;
		MaxVShaderInstructionsExecuted = caps.MaxVShaderInstructionsExecuted;
		MaxPShaderInstructionsExecuted = caps.MaxPShaderInstructionsExecuted;
		MaxVertexShader30InstructionSlots = caps.MaxVertexShader30InstructionSlots;
		MaxPixelShader30InstructionSlots = caps.MaxPixelShader30InstructionSlots;
	}
}
}

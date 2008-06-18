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

#if D3DX_SDK_VERSION != 38
#error You are not compiling against the June 2008 SDK. Change the linker settings to delay load the correct DLLs and update this code.
#endif

#include "../Utilities.h"

#include "Direct3D9Exception.h"
#include "Direct3D9NotFoundException.h"
#include "Direct3DX9NotFoundException.h"

#include "Enums.h"

#include "Direct3D.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SlimDX
{
namespace Direct3D9
{
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
		adapters = gcnew AdapterCollection( m_Direct3D->GetAdapterCount() );
		
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

	bool Direct3D::CheckDeviceFormatConversion(int adapter, DeviceType deviceType, Format sourceFormat, Format targetFormat, [Out] Result% result)
	{
		Initialize();

		HRESULT hr;		// Error code.

		hr = m_Direct3D->CheckDeviceFormatConversion(adapter, static_cast<D3DDEVTYPE>( deviceType ), 
			static_cast<D3DFORMAT>( sourceFormat ), static_cast<D3DFORMAT>( targetFormat) );

		result = Result( hr );

		return SUCCEEDED(hr);
	}

	bool Direct3D::CheckDeviceFormatConversion(int adapter, DeviceType deviceType, Format sourceFormat, Format targetFormat)
	{
		Initialize();

		Result result;
		return CheckDeviceFormatConversion(adapter, deviceType, sourceFormat, targetFormat, result);
	}

	bool Direct3D::CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
		Usage usage, ResourceType resourceType, Format checkFormat, [Out] Result% result )
	{
		Initialize();

		HRESULT hr = m_Direct3D->CheckDeviceFormat( adapter, static_cast<D3DDEVTYPE>( deviceType ), static_cast<D3DFORMAT>( adapterFormat ),
			static_cast<DWORD>( usage ), static_cast<D3DRESOURCETYPE>( resourceType ), static_cast<D3DFORMAT>( checkFormat ) );
		
		result = Result( hr );
		
		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceFormat( int adapter, DeviceType deviceType, Format adapterFormat,
		Usage usage, ResourceType resourceType, Format checkFormat )
	{
		Initialize();

		Result result;
		return CheckDeviceFormat( adapter, deviceType, adapterFormat, usage, resourceType, checkFormat, result );
	}

	bool Direct3D::CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format backBufferFormat, bool windowed, [Out] Result% result )
	{
		Initialize();

		HRESULT hr = m_Direct3D->CheckDeviceType( adapter, static_cast<D3DDEVTYPE>( deviceType ), 
			static_cast<D3DFORMAT>( adapterFormat ), static_cast<D3DFORMAT>( backBufferFormat ), windowed );
		
		result = Result( hr );
		
		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format backBufferFormat, bool windowed )
	{
		Initialize();

		Result result;
		return CheckDeviceType( adapter, deviceType, adapterFormat, backBufferFormat, windowed, result );
	}

	bool Direct3D::CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format renderTargetFormat, Format depthStencilFormat, [Out] Result% result )
	{
		Initialize();

		HRESULT hr = m_Direct3D->CheckDepthStencilMatch( adapter, static_cast<D3DDEVTYPE>( deviceType ),
			static_cast<D3DFORMAT>( adapterFormat ), static_cast<D3DFORMAT>( renderTargetFormat ), static_cast<D3DFORMAT>( depthStencilFormat ) );
		
		result = Result( hr );
		
		return hr == S_OK;
	}

	bool Direct3D::CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format renderTargetFormat, Format depthStencilFormat )
	{
		Initialize();

		Result result;
		return CheckDepthStencilMatch( adapter, deviceType, adapterFormat,
			renderTargetFormat, depthStencilFormat, result );
	}

	bool Direct3D::CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultisampleType multiSampleType, [Out] int% qualityLevels, [Out] Result% result )
	{
		Initialize();

		DWORD levels;
		HRESULT hr = m_Direct3D->CheckDeviceMultiSampleType( adapter, static_cast<D3DDEVTYPE>( deviceType ), static_cast<D3DFORMAT>( surfaceFormat ),
			windowed, static_cast<D3DMULTISAMPLE_TYPE>( multiSampleType ),  static_cast<DWORD*>( &levels ) );

		qualityLevels = levels;
		result = Result( hr );

		return hr == S_OK;
	}

	bool Direct3D::CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultisampleType multiSampleType, [Out] int% qualityLevels )
	{
		Initialize();

		Result result;
		return CheckDeviceMultisampleType( adapter, deviceType, surfaceFormat,
			windowed, multiSampleType, qualityLevels, result );
	}

	bool Direct3D::CheckDeviceMultisampleType( int adapter, DeviceType deviceType, Format surfaceFormat,
		bool windowed, MultisampleType multiSampleType )
	{
		Initialize();

		int levels;
		Result result;
		return CheckDeviceMultisampleType( adapter, deviceType, surfaceFormat, windowed,
			multiSampleType, levels, result );
	}

    DisplayMode Direct3D::GetAdapterDisplayMode( int adapter )
    {
		Initialize();

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
		Initialize();

        return m_Direct3D->GetAdapterModeCount( adapter, static_cast<D3DFORMAT>( format ) );
    }

    DisplayMode Direct3D::EnumerateAdapterModes( int adapter, Format format, int modeIndex )
    {
		Initialize();

        DisplayMode displayMode;
        HRESULT hr = m_Direct3D->EnumAdapterModes( adapter, static_cast<D3DFORMAT>( format ),
			modeIndex, reinterpret_cast<D3DDISPLAYMODE*>( &displayMode ) );
        RECORD_D3D9( hr );
        return displayMode;
    }

    IntPtr Direct3D::GetAdapterMonitor( int adapter )
    {
		Initialize();

        return IntPtr( m_Direct3D->GetAdapterMonitor( adapter ) );
    }

	Capabilities^ Direct3D::GetDeviceCaps( int adapter, DeviceType deviceType )
	{
		Initialize();

		D3DCAPS9 caps;
		HRESULT hr = Direct3D::InternalPointer->GetDeviceCaps( adapter, static_cast<D3DDEVTYPE>( deviceType ), &caps );
		RECORD_D3D9( hr );

		return gcnew Capabilities( caps );
	}

	bool Direct3D::SupportsR2VB( int adapter, DeviceType deviceType )
	{
		return CheckDeviceFormat( adapter, deviceType, Format::X8R8G8B8, Usage::None, ResourceType::Surface, Format::ATI_R2VB );
	}
}
}

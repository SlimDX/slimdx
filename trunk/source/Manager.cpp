#include <d3d9.h>
#include <d3dx9.h>
#include "Manager.h"

namespace SlimDX
{
namespace Direct3D
{
	AdapterDetails::AdapterDetails( unsigned int adapter )
	{
		D3DADAPTER_IDENTIFIER9 ident;
		DWORD flags = Manager::CheckWhql ? D3DENUM_WHQL_LEVEL : 0;

		HRESULT hr = Manager::Direct3D->GetAdapterIdentifier( adapter, flags, &ident );
		GraphicsException::CheckHResult( hr );
		
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
		return (int) Manager::Direct3D->GetAdapterMonitor( m_Adapter );
	}

	DisplayMode AdapterInformation::CurrentDisplayMode::get()
	{
		DisplayMode displayMode;
		HRESULT hr = Manager::Direct3D->GetAdapterDisplayMode( m_Adapter, (D3DDISPLAYMODE*) &displayMode );
		return displayMode;
	}


	bool Manager::CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format backBufferFormat, bool windowed, [Out] int% result )
	{
		HRESULT hr = m_Direct3D->CheckDeviceType( adapter, (D3DDEVTYPE) deviceType, 
			(D3DFORMAT) adapterFormat, (D3DFORMAT) backBufferFormat, windowed );
		result = hr;
		return hr == S_OK;
	}

	bool Manager::CheckDeviceType( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format backBufferFormat, bool windowed )
	{
		int result;
		return CheckDeviceType( adapter, deviceType, adapterFormat, backBufferFormat, windowed, result );
	}

	bool Manager::CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format renderTargetFormat, DepthFormat depthStencilFormat, [Out] int% result )
	{
		HRESULT hr = m_Direct3D->CheckDepthStencilMatch( adapter, (D3DDEVTYPE) deviceType,
			(D3DFORMAT) adapterFormat, (D3DFORMAT) renderTargetFormat, (D3DFORMAT) depthStencilFormat );
		result = hr;
		return hr == S_OK;
	}

	bool Manager::CheckDepthStencilMatch( int adapter, DeviceType deviceType, Format adapterFormat, 
		Format renderTargetFormat, DepthFormat depthStencilFormat )
	{
		int result;
		return CheckDepthStencilMatch( adapter, deviceType, adapterFormat,
			renderTargetFormat, depthStencilFormat, result );
	}

	Caps Manager::GetDeviceCaps( int adapter, DeviceType deviceType )
	{
		return Caps( adapter, deviceType );
	}


	Caps::Caps( int adapter, DeviceType deviceType )
	{
		D3DCAPS9 caps;
		Manager::Direct3D->GetDeviceCaps( adapter, (D3DDEVTYPE) deviceType, &caps );

		VertexShaderVersion = gcnew Version( D3DSHADER_VERSION_MAJOR( caps.VertexShaderVersion ), 
			D3DSHADER_VERSION_MINOR( caps.VertexShaderVersion ) );
		PixelShaderVersion = gcnew Version( D3DSHADER_VERSION_MAJOR( caps.PixelShaderVersion ), 
			D3DSHADER_VERSION_MINOR( caps.PixelShaderVersion ) );
	}
}
}

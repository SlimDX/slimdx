#include "stdafx.h"
/*
* Copyright (c) 2007-2010 SlimDX Group
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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../stack_array.h"
#include "../ComObject.h"

#include "Direct3D9Exception.h"

#include "DeviceEx.h"
#include "PresentParameters.h"
#include "Resource.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	void DeviceEx::Internal_Constructor( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
				CreateFlags createFlags, D3DDISPLAYMODEEX* fullscreenDisplayMode, ... array<PresentParameters^>^ presentParameters )
	{
		IDirect3DDevice9Ex* device;
		stack_array<D3DPRESENT_PARAMETERS> d3dpp = stackalloc( D3DPRESENT_PARAMETERS, presentParameters->Length );

		for( int i = 0; i < presentParameters->Length; ++i )
			d3dpp[i] = presentParameters[i]->ToUnmanaged();

		HRESULT hr = direct3D->InternalPointer->CreateDeviceEx( adapter,
			static_cast<D3DDEVTYPE>( deviceType ),
			static_cast<HWND>( controlHandle.ToPointer() ), 
			static_cast<DWORD>( createFlags ),
			&d3dpp[0], fullscreenDisplayMode, &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		for( int i = 0; i < presentParameters->Length; ++i )
		{
			presentParameters[i]->BackBufferCount = d3dpp[i].BackBufferCount;
			presentParameters[i]->BackBufferFormat = static_cast<Format>( d3dpp[i].BackBufferFormat );
			presentParameters[i]->BackBufferWidth = d3dpp[i].BackBufferWidth;
			presentParameters[i]->BackBufferHeight = d3dpp[i].BackBufferHeight;
		}

		Construct(device);
	}

	DeviceEx::DeviceEx( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
		CreateFlags createFlags, PresentParameters^ presentParameters )
	{
		Internal_Constructor( direct3D, adapter, deviceType, controlHandle, createFlags, NULL, presentParameters );
	}

	DeviceEx::DeviceEx( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
		CreateFlags createFlags, PresentParameters^ presentParameters, DisplayModeEx fullscreenDisplayMode )
	{
		D3DDISPLAYMODEEX nativeMode = fullscreenDisplayMode.ToUnmanaged();
		Internal_Constructor( direct3D, adapter, deviceType, controlHandle, createFlags, &nativeMode, presentParameters );
	}

	DeviceEx::DeviceEx( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
		CreateFlags createFlags, array<PresentParameters^>^ presentParameters )
	{
		Internal_Constructor( direct3D, adapter, deviceType, controlHandle, createFlags, NULL, presentParameters );
	}

	DeviceEx::DeviceEx( Direct3DEx^ direct3D, int adapter, DeviceType deviceType, System::IntPtr controlHandle,
		CreateFlags createFlags, array<PresentParameters^>^ presentParameters, array<DisplayModeEx>^ fullscreenDisplayModes )
	{
		stack_array<D3DDISPLAYMODEEX> nativeModes = stackalloc( D3DDISPLAYMODEEX, fullscreenDisplayModes->Length );

		for( int i = 0; i < fullscreenDisplayModes->Length; ++i )
			nativeModes[i] = fullscreenDisplayModes[i].ToUnmanaged();

		Internal_Constructor( direct3D, adapter, deviceType, controlHandle, createFlags, &nativeModes[0], presentParameters );
	}

	int DeviceEx::GpuThreadPriority::get()
	{
		int priority;
		HRESULT hr = InternalPointer->GetGPUThreadPriority( &priority );
		RECORD_D3D9( hr );

		return priority;
	}

	void DeviceEx::GpuThreadPriority::set( int priority )
	{
		HRESULT hr = InternalPointer->SetGPUThreadPriority( priority );
		RECORD_D3D9( hr );
	}

	int DeviceEx::MaximumFrameLatency::get()
	{
		int maxLatency;
		HRESULT hr = InternalPointer->GetMaximumFrameLatency( reinterpret_cast<UINT*>( &maxLatency ) );
		RECORD_D3D9( hr );

		return maxLatency;
	}

	void DeviceEx::MaximumFrameLatency::set( int maxLatency )
	{
		HRESULT hr = InternalPointer->SetMaximumFrameLatency( maxLatency );
		RECORD_D3D9( hr );
	}

	DeviceState DeviceEx::CheckDeviceState( System::IntPtr windowHandle )
	{
		HRESULT hr = InternalPointer->CheckDeviceState( static_cast<HWND>( windowHandle.ToPointer() ) );
		return static_cast<DeviceState>( hr );
	}

	ResourceResidency DeviceEx::CheckResourceResidency( Resource^ resource )
	{
		IDirect3DResource9* resourcePointer = resource->InternalPointer;
		HRESULT hr = InternalPointer->CheckResourceResidency( &resourcePointer, 1 );
		return static_cast<ResourceResidency>( hr );
	}

	ResourceResidency DeviceEx::CheckResourceResidency( array<Resource^>^ resources )
	{
		stack_array<IDirect3DResource9*> resourceArray = stackalloc( IDirect3DResource9*, resources->Length );
		for( int i = 0; i < resources->Length; i++ )
			resourceArray[i] = resources[i]->InternalPointer;

		HRESULT hr = InternalPointer->CheckResourceResidency( &resourceArray[0], resources->Length );
		return static_cast<ResourceResidency>( hr );
	}

	DisplayModeEx DeviceEx::GetDisplayModeEx( int swapChain )
	{
		D3DDISPLAYMODEEX nativeMode = {0};
		nativeMode.Size = sizeof(D3DDISPLAYMODEEX);
		HRESULT hr = InternalPointer->GetDisplayModeEx( swapChain, &nativeMode, NULL );
		RECORD_D3D9( hr );

		DisplayModeEx mode = DisplayModeEx::FromUnmanaged( nativeMode );
		return mode;
	}

	DisplayModeEx DeviceEx::GetDisplayModeEx( int swapChain, [Out] DisplayRotation% rotation )
	{
		D3DDISPLAYMODEEX nativeMode = {0};
		nativeMode.Size = sizeof(D3DDISPLAYMODEEX);
		D3DDISPLAYROTATION nativeRotation = D3DDISPLAYROTATION_IDENTITY;

		HRESULT hr = InternalPointer->GetDisplayModeEx( swapChain, &nativeMode, &nativeRotation );
		RECORD_D3D9( hr );

		rotation = static_cast<DisplayRotation>( nativeRotation );
		DisplayModeEx mode = DisplayModeEx::FromUnmanaged( nativeMode );
		return mode;
	}

	Result DeviceEx::PresentEx( SlimDX::Direct3D9::Present flags )
	{
		HRESULT hr = InternalPointer->PresentEx( 0, 0, 0, 0, static_cast<DWORD>( flags ) );
		RECORD_D3D9( hr );

		return Result::Last;
	}

	Result DeviceEx::PresentEx( System::IntPtr windowOverride, SlimDX::Direct3D9::Present flags )
	{
		HRESULT hr = InternalPointer->PresentEx( 0, 0, static_cast<HWND>( windowOverride.ToPointer() ), 0, static_cast<DWORD>( flags ) );
		RECORD_D3D9( hr );

		return Result::Last;
	}
	
	Result DeviceEx::ResetEx( PresentParameters^ presentParameters )
	{
		D3DPRESENT_PARAMETERS d3dpp;

		d3dpp = presentParameters->ToUnmanaged();
		HRESULT hr = InternalPointer->ResetEx( &d3dpp, NULL );
		RECORD_D3D9( hr );

		presentParameters->BackBufferCount = d3dpp.BackBufferCount;
		presentParameters->BackBufferFormat = static_cast<Format>( d3dpp.BackBufferFormat );
		presentParameters->BackBufferWidth = d3dpp.BackBufferWidth;
		presentParameters->BackBufferHeight = d3dpp.BackBufferHeight;

		return Result::Last;
	}

	Result DeviceEx::ResetEx( PresentParameters^ presentParameters, DisplayModeEx fullscreenDisplayMode )
	{
		D3DPRESENT_PARAMETERS d3dpp = presentParameters->ToUnmanaged();
		D3DDISPLAYMODEEX nativeDisplayMode = fullscreenDisplayMode.ToUnmanaged();
		HRESULT hr = InternalPointer->ResetEx( &d3dpp, &nativeDisplayMode );
		RECORD_D3D9( hr );

		presentParameters->BackBufferCount = d3dpp.BackBufferCount;
		presentParameters->BackBufferFormat = static_cast<Format>( d3dpp.BackBufferFormat );
		presentParameters->BackBufferWidth = d3dpp.BackBufferWidth;
		presentParameters->BackBufferHeight = d3dpp.BackBufferHeight;

		return Result::Last;
	}

	void DeviceEx::WaitForVBlank( int swapChain )
	{
		//This method will always return D3D_OK.
		InternalPointer->WaitForVBlank( swapChain );
	}
}
}
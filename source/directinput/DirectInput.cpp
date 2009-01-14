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
#include <windows.h>
#include <dinput.h>
#include <vcclr.h>

#include "DirectInput.h"
#include "DirectInputException.h"
#include "DirectInputNotFoundException.h"

#include "Callbacks.h"
#include "Device.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace DirectInput
{
    void DirectInput::Initialize()
	{
        if( m_DirectInput != NULL )
            return;

		IDirectInput8W* dinput;
		IntPtr hInstance = Marshal::GetHINSTANCE( DirectInput::typeid->Module );

        try
        {
		    HRESULT hr = DirectInput8Create( static_cast<HINSTANCE>( hInstance.ToPointer() ), DIRECTINPUT_VERSION, 
			    IID_IDirectInput8, reinterpret_cast<void**>( &dinput ), NULL );

			RECORD_DINPUT( hr );
        }
        catch( SEHException^ ex )
        {
            throw gcnew DirectInputNotFoundException( "DirectInput was not found. Reinstalling DirectX may fix the problem.", ex );
        }

		if( dinput == NULL )
			throw gcnew DirectInputException( "Could not create DirectInput instance." );

		m_DirectInput = dinput;
		
		System::AppDomain::CurrentDomain->DomainUnload += gcnew System::EventHandler( OnExit );
		System::AppDomain::CurrentDomain->ProcessExit += gcnew System::EventHandler( OnExit );
	}

	void DirectInput::Terminate()
	{
		if( m_DirectInput == NULL )
            return;

		m_DirectInput->Release();
		m_DirectInput = NULL;

		System::AppDomain::CurrentDomain->DomainUnload -= gcnew System::EventHandler( OnExit );
		System::AppDomain::CurrentDomain->ProcessExit -= gcnew System::EventHandler( OnExit );
	}

	Result DirectInput::RunControlPanel()
	{
		HRESULT hr = m_DirectInput->RunControlPanel( NULL, 0 );
		return RECORD_DINPUT( hr );
	}

	Result DirectInput::RunControlPanel( IntPtr parent )
	{
		HRESULT hr = m_DirectInput->RunControlPanel( static_cast<HWND>( parent.ToPointer() ), 0 );
		return RECORD_DINPUT( hr );
	}

	bool DirectInput::IsDeviceAttached( Guid device )
	{
		HRESULT hr = m_DirectInput->GetDeviceStatus( Utilities::ConvertManagedGuid( device ) );
		RECORD_DINPUT( hr );

		return hr == DI_OK;
	}

	Guid DirectInput::FindDevice( Guid deviceClass, String^ name )
	{
		GUID result;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( name );

		HRESULT hr = m_DirectInput->FindDevice( Utilities::ConvertManagedGuid( deviceClass ),
			reinterpret_cast<LPCTSTR>( pinnedName ), &result );
		RECORD_DINPUT( hr );

		if( FAILED( hr ) )
			return Guid::Empty;

		return Utilities::ConvertNativeGuid( result );
	}

	InputDeviceCollection^ DirectInput::GetDevices()
	{
		return GetDevices( DeviceClass::All, DeviceEnumerationFlags::AllDevices );
	}

	InputDeviceCollection^ DirectInput::GetDevices( DeviceClass deviceClass, DeviceEnumerationFlags enumerationFlags )
	{
		InputDeviceCollection^ results = gcnew InputDeviceCollection();
		InputDeviceCollectionShim shim( results );

		HRESULT hr = m_DirectInput->EnumDevices( static_cast<DWORD>( deviceClass ), static_cast<LPDIENUMDEVICESCALLBACK>( EnumerateDevices ), &shim, static_cast<DWORD>( enumerationFlags ) );
		if( RECORD_DINPUT( hr ).IsFailure )
			return nullptr;

		return results;
	}

	InputDeviceCollection^ DirectInput::GetDevices( DeviceType deviceType, DeviceEnumerationFlags enumerationFlags )
	{
		InputDeviceCollection^ results = gcnew InputDeviceCollection();
		InputDeviceCollectionShim shim( results );

		HRESULT hr = m_DirectInput->EnumDevices( static_cast<DWORD>( deviceType ), static_cast<LPDIENUMDEVICESCALLBACK>( EnumerateDevices ), &shim, static_cast<DWORD>( enumerationFlags ) );
		if( RECORD_DINPUT( hr ).IsFailure )
			return nullptr;

		return results;
	}
}
}
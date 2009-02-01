/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include <dsound.h>
#include <memory>

#include "../ComObject.h"
#include "../multimedia/Enums.h"
#include "../Utilities.h"

#include "DirectSoundException.h"

#include "Guids.h"
#include "Enums.h"
#include "Callbacks.h"
#include "DirectSound.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace DirectSound
{
	DirectSound::DirectSound()
	{
		IDirectSound8* dsound;

		HRESULT hr = DirectSoundCreate8( NULL, &dsound, NULL );
		
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( dsound );
	}

	DirectSound::DirectSound( Guid device )
	{
		IDirectSound8* dsound;

		GUID guid = Utilities::ConvertManagedGuid( device );
		HRESULT hr = DirectSoundCreate8( &guid, &dsound, NULL );

		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException();

		Construct( dsound );
	}

	Capabilities^ DirectSound::Capabilities::get()
	{
		DSCAPS caps;
		caps.dwSize = sizeof( DSCAPS );

		HRESULT hr = InternalPointer->GetCaps( &caps );

		if( RECORD_DSOUND( hr ).IsFailure )
			return nullptr;

		return gcnew SlimDX::DirectSound::Capabilities( caps );
	}

	Result DirectSound::SetCooperativeLevel( IntPtr windowHandle, CooperativeLevel coopLevel )
	{
		HRESULT hr = InternalPointer->SetCooperativeLevel( static_cast<HWND>( windowHandle.ToPointer() ), static_cast<DWORD>( coopLevel ) );
		return RECORD_DSOUND( hr );
	}

	Result DirectSound::SetSpeakerConfiguration( Speakers speakerSet, SpeakerGeometry geometry )
	{
		HRESULT hr = InternalPointer->SetSpeakerConfig( DSSPEAKER_COMBINED( static_cast<DWORD>( speakerSet ), static_cast<DWORD>( geometry ) ) );
		return RECORD_DSOUND( hr );
	}

	Result DirectSound::GetSpeakerConfiguration( [Out] Speakers% speakerSet, [Out] SpeakerGeometry% geometry )
	{
		DWORD config = 0;
		HRESULT hr = InternalPointer->GetSpeakerConfig( &config );
		
		if( RECORD_DSOUND( hr ).IsFailure )
		{
			speakerSet = Speakers::None;
			geometry = SpeakerGeometry::None;
			return Result::Last;
		}

		speakerSet = static_cast<Speakers>( DSSPEAKER_CONFIG( config ) );
		geometry = static_cast<SpeakerGeometry>( DSSPEAKER_GEOMETRY( config ) );

		return Result::Last;
	}

	bool DirectSound::VerifyCertification()
	{
		DWORD certified = DS_UNCERTIFIED;
		HRESULT hr = InternalPointer->VerifyCertification( &certified );
		
		if( RECORD_DSOUND( hr ).IsFailure )
			return false;

		return certified == DS_CERTIFIED;
	}

	DeviceCollection^ DirectSound::GetDevices()
	{
		DeviceCollection^ results = gcnew DeviceCollection();
		std::auto_ptr<DeviceCollectionShim> shim( new DeviceCollectionShim( results ) );

		HRESULT hr = DirectSoundEnumerate( EnumerateDevices, shim.get() );

		if( RECORD_DSOUND( hr ).IsFailure )
			return nullptr;

		return results;
	}
}
}
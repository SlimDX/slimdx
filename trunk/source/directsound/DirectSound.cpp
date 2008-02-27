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

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>

#include "DirectSound.h"
//#include "DirectSoundErrorHandler.h"
#include "DirectSoundException.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	DirectSound::DirectSound( IDirectSound8* dsound )
	{
		Construct( dsound );
	}

	DirectSound::DirectSound( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	DirectSound^ DirectSound::FromPointer( IDirectSound8* pointer )
	{
		DirectSound^ tableEntry = safe_cast<DirectSound^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew DirectSound( pointer );
	}

	DirectSound^ DirectSound::FromPointer( IntPtr pointer )
	{
		DirectSound^ tableEntry = safe_cast<DirectSound^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew DirectSound( pointer );
	}

	DirectSound::DirectSound()
	{
		IDirectSound8* dsound;
		HRESULT hr = DirectSoundCreate8( NULL, &dsound, NULL );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			throw gcnew DirectSoundException();

		Construct(dsound);
	}

	DirectSound::DirectSound( Guid device )
	{
		IDirectSound8* dsound;
		HRESULT hr = DirectSoundCreate8( reinterpret_cast<GUID*>( &device ), &dsound, NULL );
		RECORD_DSOUND( hr );
		if( FAILED( hr ) )
			throw gcnew DirectSoundException();

		Construct(dsound);
	}

	void DirectSound::Initialize()
	{
		HRESULT hr = InternalPointer->Initialize( NULL );
		RECORD_DSOUND( hr );
		caps = GetCapabilities();
	}

	void DirectSound::Initialize( Guid device )
	{
		HRESULT hr = InternalPointer->Initialize( reinterpret_cast<GUID*>( &device ) );
		RECORD_DSOUND( hr );
		caps = GetCapabilities();
	}

	Capabilities DirectSound::GetCapabilities()
	{
		SlimDX::DirectSound::Capabilities caps;
		HRESULT hr = InternalPointer->GetCaps( reinterpret_cast<DSCAPS*>( &caps ) );
		RECORD_DSOUND( hr );
		
		return caps;
	}

	void DirectSound::SetCooperativeLevel( IntPtr windowHandle, CooperativeLevel coopLevel )
	{
		HRESULT hr = InternalPointer->SetCooperativeLevel( static_cast<HWND>( windowHandle.ToPointer() ), static_cast<DWORD>( coopLevel ) );
		RECORD_DSOUND( hr );
	}

	void DirectSound::SetSpeakerConfig( Speaker speakerSet, SpeakerGeometry geometry )
	{
		HRESULT hr = InternalPointer->SetSpeakerConfig( DSSPEAKER_COMBINED( static_cast<DWORD>( speakerSet ), static_cast<DWORD>( geometry ) ) );
		RECORD_DSOUND( hr );
	}

	void DirectSound::GetSpeakerConfig( [Out] Speaker% speakerSet, [Out] SpeakerGeometry% geometry )
	{
		DWORD config = 0;
		HRESULT hr = InternalPointer->GetSpeakerConfig( &config );
		RECORD_DSOUND( hr );

		speakerSet = static_cast<Speaker>( DSSPEAKER_CONFIG( config ) );
		geometry = static_cast<SpeakerGeometry>( DSSPEAKER_GEOMETRY( config ) );
	}

	bool DirectSound::VerifyCertification()
	{
		DWORD certified = DS_UNCERTIFIED;
		HRESULT hr = InternalPointer->VerifyCertification( &certified );
		RECORD_DSOUND( hr );

		return certified == DS_CERTIFIED;
	}
}
}
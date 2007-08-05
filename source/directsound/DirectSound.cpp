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
#pragma once

#include <windows.h>
#include <mmreg.h>
#include <dsound.h>

#include "DirectSound.h"
#include "SoundException.h"

namespace SlimDX
{
namespace DirectSound
{
	DirectSound::DirectSound( IDirectSound8* dsound ) : DirectXObject( dsound )
	{
		if( dsound == NULL )
			throw gcnew ArgumentNullException( "dsound" );
	}

	DirectSound::DirectSound()
	{
		IDirectSound8* dsound;
		HRESULT hr = DirectSoundCreate8( NULL, &dsound, NULL );
		SoundException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew SoundException();

		m_Pointer = dsound;
	}

	DirectSound::DirectSound( Guid device )
	{
		IDirectSound8* dsound;
		HRESULT hr = DirectSoundCreate8( (GUID*) &device, &dsound, NULL );
		SoundException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew SoundException();

		m_Pointer = dsound;
	}

	void DirectSound::Initialize()
	{
		HRESULT hr = m_Pointer->Initialize( NULL );
		SoundException::CheckHResult( hr );
	}

	void DirectSound::Initialize( Guid device )
	{
		HRESULT hr = m_Pointer->Initialize( (GUID*) &device );
		SoundException::CheckHResult( hr );
	}

	Capabilities DirectSound::GetCapabilities()
	{
		Capabilities caps;
		HRESULT hr = m_Pointer->GetCaps( (DSCAPS*) &caps );
		SoundException::CheckHResult( hr );
		
		return caps;
	}

	void DirectSound::SetCooperativeLevel( IntPtr windowHandle, CooperativeLevel coopLevel )
	{
		HRESULT hr = m_Pointer->SetCooperativeLevel( (HWND) windowHandle.ToPointer(), (DWORD) coopLevel );
		SoundException::CheckHResult( hr );
	}

	void DirectSound::SetSpeakerConfig( Speaker speakerSet, SpeakerGeometry geometry )
	{
		HRESULT hr = m_Pointer->SetSpeakerConfig( DSSPEAKER_COMBINED( (DWORD) speakerSet, (DWORD) geometry ) );
		SoundException::CheckHResult( hr );
	}

	void DirectSound::GetSpeakerConfig( [Out] Speaker% speakerSet, [Out] SpeakerGeometry% geometry )
	{
		DWORD config = 0;
		HRESULT hr = m_Pointer->GetSpeakerConfig( &config );
		SoundException::CheckHResult( hr );

		speakerSet = (Speaker) DSSPEAKER_CONFIG( config );
		geometry = (SpeakerGeometry) DSSPEAKER_GEOMETRY( config );
	}

	bool DirectSound::VerifyCertification()
	{
		DWORD certified = DS_UNCERTIFIED;
		HRESULT hr = m_Pointer->VerifyCertification( &certified );
		SoundException::CheckHResult( hr );

		return certified == DS_CERTIFIED;
	}
}
}
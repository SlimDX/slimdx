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
	DirectSound::DirectSound( IDirectSound8* dsound )
	{
		if( dsound == NULL )
			throw gcnew ArgumentNullException( "dsound" );

		m_Pointer = dsound;
	}

	DirectSound::DirectSound( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_IDirectSound8, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<IDirectSound8*>( result );
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
		HRESULT hr = DirectSoundCreate8( reinterpret_cast<GUID*>( &device ), &dsound, NULL );
		SoundException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew SoundException();

		m_Pointer = dsound;
	}

	void DirectSound::Initialize()
	{
		HRESULT hr = m_Pointer->Initialize( NULL );
		SoundException::CheckHResult( hr );
		caps = GetCapabilities();
	}

	void DirectSound::Initialize( Guid device )
	{
		HRESULT hr = m_Pointer->Initialize( reinterpret_cast<GUID*>( &device ) );
		SoundException::CheckHResult( hr );
		caps = GetCapabilities();
	}

	Capabilities DirectSound::GetCapabilities()
	{
		SlimDX::DirectSound::Capabilities caps;
		HRESULT hr = m_Pointer->GetCaps( reinterpret_cast<DSCAPS*>( &caps ) );
		SoundException::CheckHResult( hr );
		
		return caps;
	}

	void DirectSound::SetCooperativeLevel( IntPtr windowHandle, CooperativeLevel coopLevel )
	{
		HRESULT hr = m_Pointer->SetCooperativeLevel( static_cast<HWND>( windowHandle.ToPointer() ), static_cast<DWORD>( coopLevel ) );
		SoundException::CheckHResult( hr );
	}

	void DirectSound::SetSpeakerConfig( Speaker speakerSet, SpeakerGeometry geometry )
	{
		HRESULT hr = m_Pointer->SetSpeakerConfig( DSSPEAKER_COMBINED( static_cast<DWORD>( speakerSet ), static_cast<DWORD>( geometry ) ) );
		SoundException::CheckHResult( hr );
	}

	void DirectSound::GetSpeakerConfig( [Out] Speaker% speakerSet, [Out] SpeakerGeometry% geometry )
	{
		DWORD config = 0;
		HRESULT hr = m_Pointer->GetSpeakerConfig( &config );
		SoundException::CheckHResult( hr );

		speakerSet = static_cast<Speaker>( DSSPEAKER_CONFIG( config ) );
		geometry = static_cast<SpeakerGeometry>( DSSPEAKER_GEOMETRY( config ) );
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
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
#include <d3dx9.h>

#include "../ComObject.h"
#include "../Result.h"
#include "Enums.h"
#include "DirectSoundException.h"
#include "SoundEffectI3DL2Reverb.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace DirectSound
{
	I3DL2ReverbParameters::I3DL2ReverbParameters( const DSFXI3DL2Reverb &value )
	{
		Room = value.lRoom;
		RoomHF = value.lRoomHF;
		RoomolloffFactor = value.flRoomRolloffFactor;
		DecayTime = value.flDecayTime;
		DecayHRRatio = value.flDecayHFRatio;
		Reflections = value.lReflections;
		ReflectionsDelay = value.flReflectionsDelay;
		Reverb = value.lReverb;
		ReverbDelay = value.flReverbDelay;
		Diffusion = value.flDiffusion;
		Density = value.flDensity;
		HFReference = value.flHFReference;
	}

	DSFXI3DL2Reverb I3DL2ReverbParameters::Marshal()
	{	
		DSFXI3DL2Reverb result;
		result.lRoom = Room;
		result.lRoomHF = RoomHF;
		result.flRoomRolloffFactor = RoomolloffFactor;
		result.flDecayTime = DecayTime;
		result.flDecayHFRatio = DecayHRRatio;
		result.lReflections = Reflections;
		result.flReflectionsDelay = ReflectionsDelay;
		result.lReverb = Reverb;
		result.flReverbDelay = ReverbDelay;
		result.flDiffusion = Diffusion;
		result.flDensity = Density;
		result.flHFReference = HFReference;

		return result;
	}

	SoundEffectI3DL2Reverb::SoundEffectI3DL2Reverb( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SoundEffectI3DL2Reverb::SoundEffectI3DL2Reverb( IDirectSoundFXI3DL2Reverb8 *pointer )
	{
		if( pointer == NULL )
			throw gcnew System::ArgumentNullException();

		IDirectSoundFXI3DL2Reverb8* result;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundFXI3DL2Reverb8, reinterpret_cast<void**>( &result ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( result );
	}

	SoundEffectI3DL2Reverb^ SoundEffectI3DL2Reverb::FromPointer( IDirectSoundFXI3DL2Reverb* pointer )
	{
		SoundEffectI3DL2Reverb^ tableEntry = safe_cast<SoundEffectI3DL2Reverb^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SoundEffectI3DL2Reverb( pointer );
	}

	SoundEffectI3DL2Reverb^ SoundEffectI3DL2Reverb::FromPointer( System::IntPtr pointer )
	{
		SoundEffectI3DL2Reverb^ tableEntry = safe_cast<SoundEffectI3DL2Reverb^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SoundEffectI3DL2Reverb( pointer );
	}

	SoundEffectI3DL2Reverb::~SoundEffectI3DL2Reverb()
	{
		Destruct();
	}

	I3DL2ReverbParameters SoundEffectI3DL2Reverb::AllParameters::get()
	{
		DSFXI3DL2Reverb result;
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return I3DL2ReverbParameters( result );
	}

	void SoundEffectI3DL2Reverb::AllParameters::set( I3DL2ReverbParameters value )
	{
		DSFXI3DL2Reverb result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}

	int SoundEffectI3DL2Reverb::Quality::get()
	{
		LONG result;
		HRESULT hr = InternalPointer->GetQuality( &result );
		RECORD_DSOUND( hr );

		return static_cast<int>( result );
	}

	void SoundEffectI3DL2Reverb::Quality::set( int value )
	{
		HRESULT hr = InternalPointer->SetQuality( static_cast<LONG>( value ) );
		RECORD_DSOUND( hr );
	}

	I3DL2ReverbPreset SoundEffectI3DL2Reverb::Preset::get()
	{
		DWORD result;
		HRESULT hr = InternalPointer->GetPreset( &result );
		RECORD_DSOUND( hr );

		return static_cast<I3DL2ReverbPreset>( result );
	}

	void SoundEffectI3DL2Reverb::Preset::set( I3DL2ReverbPreset value )
	{
		HRESULT hr = InternalPointer->SetPreset( static_cast<DWORD>( value ) );
		RECORD_DSOUND( hr );
	}
}
}
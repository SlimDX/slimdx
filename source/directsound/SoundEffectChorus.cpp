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

#include "../Result.h"
#include "../ComObject.h"
#include "Enums.h"
#include "DirectSoundException.h"
#include "SoundEffectChorus.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	ChorusParameters::ChorusParameters( const DSFXChorus &value )
	{
		Delay = value.fDelay;
		Depth = value.fDepth;
		Feedback = value.fFeedback;
		Frequency = value.fFrequency;
		Phase = static_cast<int>( value.lPhase );
		Waveform = static_cast<int>( value.lWaveform );
		WetDryMix = value.fWetDryMix;
	}

	DSFXChorus ChorusParameters::Marshal()
	{
		DSFXChorus result;
		result.fDelay = Delay;
		result.fDepth = Depth;
		result.fFeedback = Feedback;
		result.fFrequency = Frequency;
		result.lPhase = Phase;
		result.lWaveform = Waveform;
		result.fWetDryMix = WetDryMix;

		return result;
	}

	SoundEffectChorus::SoundEffectChorus( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SoundEffectChorus::SoundEffectChorus( IDirectSoundFXChorus *pointer )
	{
		if( pointer == NULL )
			throw gcnew System::ArgumentNullException();

		IDirectSoundFXChorus8* result;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundFXChorus8, reinterpret_cast<void**>( &result ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( result );
	}

	SoundEffectChorus^ SoundEffectChorus::FromPointer( IDirectSoundFXChorus* pointer )
	{
		SoundEffectChorus^ tableEntry = safe_cast<SoundEffectChorus^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SoundEffectChorus( pointer );
	}

	SoundEffectChorus^ SoundEffectChorus::FromPointer( System::IntPtr pointer )
	{
		SoundEffectChorus^ tableEntry = safe_cast<SoundEffectChorus^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SoundEffectChorus( pointer );
	}

	SoundEffectChorus::~SoundEffectChorus()
	{
		Destruct();
	}

	ChorusParameters SoundEffectChorus::AllParameters::get()
	{
		DSFXChorus result;
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return ChorusParameters( result );
	}

	void SoundEffectChorus::AllParameters::set( ChorusParameters value )
	{
		DSFXChorus result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}
}
}
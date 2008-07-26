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
#include "SoundEffectEcho.h"

namespace SlimDX
{
namespace DirectSound
{
	EchoParameters::EchoParameters( const DSFXEcho &value )
	{
		RightDelay = value.fRightDelay;
		LeftDelay = value.fLeftDelay;
		PanDelay = static_cast<int>( value.lPanDelay );
		Feedback = value.fFeedback;
		WetDryMix = value.fWetDryMix;
	}

	DSFXEcho EchoParameters::Marshal()
	{
		DSFXEcho result;
		result.fRightDelay = RightDelay;
		result.fLeftDelay = LeftDelay;
		result.lPanDelay = PanDelay;
		result.fFeedback = Feedback;
		result.fWetDryMix = WetDryMix;

		return result;
	}

	SoundEffectEcho::SoundEffectEcho( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SoundEffectEcho::SoundEffectEcho( IDirectSoundFXEcho *pointer )
	{
		if( pointer == NULL )
			throw gcnew System::ArgumentNullException();

		IDirectSoundFXEcho8* result;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundFXEcho8, reinterpret_cast<void**>( &result ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( result );
	}

	SoundEffectEcho^ SoundEffectEcho::FromPointer( IDirectSoundFXEcho* pointer )
	{
		SoundEffectEcho^ tableEntry = safe_cast<SoundEffectEcho^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SoundEffectEcho( pointer );
	}

	SoundEffectEcho^ SoundEffectEcho::FromPointer( System::IntPtr pointer )
	{
		SoundEffectEcho^ tableEntry = safe_cast<SoundEffectEcho^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SoundEffectEcho( pointer );
	}

	SoundEffectEcho::~SoundEffectEcho()
	{
		Destruct();
	}

	EchoParameters SoundEffectEcho::AllParameters::get()
	{
		DSFXEcho result;
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return EchoParameters( result );
	}

	void SoundEffectEcho::AllParameters::set( EchoParameters value )
	{
		DSFXEcho result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}
}
}
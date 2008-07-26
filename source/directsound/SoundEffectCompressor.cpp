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
#include "SoundEffectCompressor.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace DirectSound
{
	CompressorParameters::CompressorParameters( const DSFXCompressor &value )
	{
		Attack = value.fAttack;
		Gain = value.fGain;
		Release = value.fRelease;
		PreDelay = value.fPredelay;
		Ratio = value.fRatio;
		Threshold = value.fThreshold;
	}

	DSFXCompressor CompressorParameters::Marshal()
	{
		DSFXCompressor result;
		result.fAttack = Attack;
		result.fGain = Gain;
		result.fRelease = Release;
		result.fPredelay = PreDelay;
		result.fRatio = Ratio;
		result.fThreshold = Threshold;

		return result;
	}

	SoundEffectCompressor::SoundEffectCompressor( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SoundEffectCompressor::SoundEffectCompressor( IDirectSoundFXCompressor *pointer )
	{
		if( pointer == NULL )
			throw gcnew System::ArgumentNullException();

		IDirectSoundFXCompressor8* result;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundFXCompressor8, reinterpret_cast<void**>( &result ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( result );
	}

	SoundEffectCompressor^ SoundEffectCompressor::FromPointer( IDirectSoundFXCompressor* pointer )
	{
		SoundEffectCompressor^ tableEntry = safe_cast<SoundEffectCompressor^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew SoundEffectCompressor( pointer );
	}

	SoundEffectCompressor^ SoundEffectCompressor::FromPointer( System::IntPtr pointer )
	{
		SoundEffectCompressor^ tableEntry = safe_cast<SoundEffectCompressor^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew SoundEffectCompressor( pointer );
	}

	SoundEffectCompressor::~SoundEffectCompressor()
	{
		Destruct();
	}

	CompressorParameters SoundEffectCompressor::AllParameters::get()
	{
		DSFXCompressor result;
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return CompressorParameters( result );
	}

	void SoundEffectCompressor::AllParameters::set( CompressorParameters value )
	{
		DSFXCompressor result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}
}
}
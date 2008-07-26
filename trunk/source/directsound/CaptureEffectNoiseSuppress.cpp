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
#include "CaptureEffectNoiseSuppress.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	NoiseSuppressParameters::NoiseSuppressParameters( const DSCFXNoiseSuppress &value )
	{
		Enable = value.fEnable ? true : false;
	}

	DSCFXNoiseSuppress NoiseSuppressParameters::Marshal()
	{
		DSCFXNoiseSuppress value;
		value.fEnable = Enable;

		return value;
	}

	CaptureEffectNoiseSuppress::CaptureEffectNoiseSuppress( IDirectSoundCaptureFXNoiseSuppress *pointer )
	{
		IDirectSoundCaptureFXNoiseSuppress8* suppress;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundCaptureFXNoiseSuppress8, reinterpret_cast<void**>( &suppress ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( suppress );
	}

	CaptureEffectNoiseSuppress::CaptureEffectNoiseSuppress( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	void CaptureEffectNoiseSuppress::Reset()
	{
		HRESULT hr = InternalPointer->Reset();
		RECORD_DSOUND( hr );
	}

	CaptureEffectNoiseSuppress^ CaptureEffectNoiseSuppress::FromPointer( IDirectSoundCaptureFXNoiseSuppress* pointer )
	{
		CaptureEffectNoiseSuppress^ tableEntry = safe_cast<CaptureEffectNoiseSuppress^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew CaptureEffectNoiseSuppress( pointer );
	}

	CaptureEffectNoiseSuppress^ CaptureEffectNoiseSuppress::FromPointer( System::IntPtr pointer )
	{
		CaptureEffectNoiseSuppress^ tableEntry = safe_cast<CaptureEffectNoiseSuppress^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew CaptureEffectNoiseSuppress( pointer );
	}

	CaptureEffectNoiseSuppress::~CaptureEffectNoiseSuppress()
	{
		Destruct();
	}

	NoiseSuppressParameters CaptureEffectNoiseSuppress::AllParameters::get()
	{
		DSCFXNoiseSuppress result;
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return NoiseSuppressParameters( result );
	}

	void CaptureEffectNoiseSuppress::AllParameters::set( NoiseSuppressParameters value )
	{
		DSCFXNoiseSuppress result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}
}
}
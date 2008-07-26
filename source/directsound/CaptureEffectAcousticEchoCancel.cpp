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
#include "ResultCode.h"
#include "Enums.h"
#include "DirectSoundException.h"
#include "CaptureEffectAcousticEchoCancel.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	AcousticEchoCancelParameters::AcousticEchoCancelParameters( const DSCFXAec &value )
	{
		Enable = value.fEnable ? true : false;
		NoiseFill = value.fNoiseFill ? true : false;
		Mode = static_cast<AcousticEchoCancelMode>( value.dwMode );
	}

	DSCFXAec AcousticEchoCancelParameters::Marshal()
	{
		DSCFXAec value;
		value.dwMode = static_cast<DWORD>( Mode );
		value.fEnable = Enable;
		value.fNoiseFill = NoiseFill;

		return value;
	}

	CaptureEffectAcousticEchoCancel::CaptureEffectAcousticEchoCancel( IDirectSoundCaptureFXAec *pointer )
	{
		if( pointer == NULL )
			throw gcnew System::ArgumentNullException();

		IDirectSoundCaptureFXAec8* aec;
		HRESULT hr = pointer->QueryInterface( IID_IDirectSoundCaptureFXAec8, reinterpret_cast<void**>( &aec ) );
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( aec );
	}

	CaptureEffectAcousticEchoCancel::CaptureEffectAcousticEchoCancel( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	CaptureEffectAcousticEchoCancel^ CaptureEffectAcousticEchoCancel::FromPointer( IDirectSoundCaptureFXAec* pointer )
	{
		CaptureEffectAcousticEchoCancel^ tableEntry = safe_cast<CaptureEffectAcousticEchoCancel^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew CaptureEffectAcousticEchoCancel( pointer );
	}

	CaptureEffectAcousticEchoCancel^ CaptureEffectAcousticEchoCancel::FromPointer( IntPtr pointer )
	{
		CaptureEffectAcousticEchoCancel^ tableEntry = safe_cast<CaptureEffectAcousticEchoCancel^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew CaptureEffectAcousticEchoCancel( pointer );
	}

	CaptureEffectAcousticEchoCancel::~CaptureEffectAcousticEchoCancel()
	{
		Destruct();
	}

	void CaptureEffectAcousticEchoCancel::Reset()
	{
		HRESULT hr = InternalPointer->Reset();
		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );
	}

	AcousticEchoCancelParameters CaptureEffectAcousticEchoCancel::AllParameters::get()
	{
		DSCFXAec result = DSCFXAec();
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return AcousticEchoCancelParameters( result );
	}

	void CaptureEffectAcousticEchoCancel::AllParameters::set( AcousticEchoCancelParameters value )
	{
		DSCFXAec result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}

	bool CaptureEffectAcousticEchoCancel::UnInitialized::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		if( ( status & DSCFX_AEC_STATUS_HISTORY_UNINITIALIZED ) != 0 )
			return true;

		return false;
	}

	bool CaptureEffectAcousticEchoCancel::ContinuouslyConverged::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		if( ( status & DSCFX_AEC_STATUS_HISTORY_CONTINUOUSLY_CONVERGED ) != 0 )
			return true;

		return false;
	}

	bool CaptureEffectAcousticEchoCancel::CurrentlyConverged::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		if( ( status & DSCFX_AEC_STATUS_CURRENTLY_CONVERGED ) != 0 )
			return true;

		return false;
	}

	bool CaptureEffectAcousticEchoCancel::PreviouslyDiverged::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		if( ( status & DSCFX_AEC_STATUS_HISTORY_PREVIOUSLY_DIVERGED ) != 0 )
			return true;

		return false;
	}
}
}
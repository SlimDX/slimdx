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
#include <windows.h>
#include <dsound.h>

#include "../ComObject.h"

#include "DirectSoundException.h"

#include "Enums.h"
#include "AcousticEchoCancel.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	AcousticEchoCancel::AcousticEchoCancel( IDirectSoundCaptureFXAec *pointer )
	{
		Construct( pointer );
	}

	AcousticEchoCancel::AcousticEchoCancel( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	AcousticEchoCancel^ AcousticEchoCancel::FromPointer( IDirectSoundCaptureFXAec* pointer )
	{
		if( pointer == NULL )
			return nullptr;

		AcousticEchoCancel^ tableEntry = safe_cast<AcousticEchoCancel^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew AcousticEchoCancel( pointer );
	}

	AcousticEchoCancel^ AcousticEchoCancel::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		AcousticEchoCancel^ tableEntry = safe_cast<AcousticEchoCancel^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew AcousticEchoCancel( pointer );
	}

	Result AcousticEchoCancel::Reset()
	{
		HRESULT hr = InternalPointer->Reset();
		return RECORD_DSOUND( hr );
	}

	AcousticEchoCancelParameters AcousticEchoCancel::AllParameters::get()
	{
		DSCFXAec result = DSCFXAec();
		HRESULT hr = InternalPointer->GetAllParameters( &result );
		RECORD_DSOUND( hr );

		return AcousticEchoCancelParameters( result );
	}

	void AcousticEchoCancel::AllParameters::set( AcousticEchoCancelParameters value )
	{
		DSCFXAec result = value.Marshal();
		HRESULT hr = InternalPointer->SetAllParameters( &result );
		RECORD_DSOUND( hr );
	}

	bool AcousticEchoCancel::UnInitialized::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		return ( status & DSCFX_AEC_STATUS_HISTORY_UNINITIALIZED ) != 0;
	}

	bool AcousticEchoCancel::ContinuouslyConverged::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		return ( status & DSCFX_AEC_STATUS_HISTORY_CONTINUOUSLY_CONVERGED ) != 0;
	}

	bool AcousticEchoCancel::CurrentlyConverged::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		return ( status & DSCFX_AEC_STATUS_CURRENTLY_CONVERGED ) != 0;
	}

	bool AcousticEchoCancel::PreviouslyDiverged::get()
	{
		DWORD status = 0;
		HRESULT hr = InternalPointer->GetStatus( &status );
		RECORD_DSOUND( hr );

		return ( status & DSCFX_AEC_STATUS_HISTORY_PREVIOUSLY_DIVERGED ) != 0;
	}
}
}
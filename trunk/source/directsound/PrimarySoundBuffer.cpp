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

#include "PrimarySoundBuffer.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	PrimarySoundBuffer::PrimarySoundBuffer( IDirectSoundBuffer* buffer )
	{
		Construct( buffer );
	}

	PrimarySoundBuffer::PrimarySoundBuffer( IntPtr buffer )
	{
		Construct( buffer, NativeInterface );
	}

	PrimarySoundBuffer^ PrimarySoundBuffer::FromPointer( IDirectSoundBuffer* pointer )
	{
		if( pointer == NULL )
			return nullptr;

		PrimarySoundBuffer^ tableEntry = safe_cast<PrimarySoundBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew PrimarySoundBuffer( pointer );
	}

	PrimarySoundBuffer^ PrimarySoundBuffer::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		PrimarySoundBuffer^ tableEntry = safe_cast<PrimarySoundBuffer^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew PrimarySoundBuffer( pointer );
	}

	PrimarySoundBuffer::PrimarySoundBuffer( DirectSound^ dsound, SoundBufferDescription description )
	{
		IDirectSoundBuffer* buffer;
		DSBUFFERDESC nativeDesc = description.ToUnmanaged();
		
		HRESULT hr = dsound->InternalPointer->CreateSoundBuffer( &nativeDesc, &buffer, NULL );

		delete[] nativeDesc.lpwfxFormat;

		if( RECORD_DSOUND( hr ).IsFailure )
			throw gcnew DirectSoundException( Result::Last );

		Construct( buffer );
	}
}
}
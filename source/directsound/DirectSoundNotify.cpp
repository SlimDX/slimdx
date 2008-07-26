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
#include <mmreg.h>
#include <dsound.h>
#include <d3dx9.h>

#include "../Result.h"
#include "../ComObject.h"

#include "DirectSound.h"
#include "SoundBufferDescription.h"
#include "SoundBuffer.h"
#include "CaptureBuffer.h"
#include "BufferPositionNotify.h"
#include "DirectSoundNotify.h"
#include "DirectSoundException.h"

namespace SlimDX
{
	namespace DirectSound
	{
		DirectSoundNotify::DirectSoundNotify(System::IntPtr pointer)
		{
			Construct( pointer, NativeInterface );
		}

		DirectSoundNotify::DirectSoundNotify( IDirectSoundNotify *notify )
		{
			if( notify == NULL )
				throw gcnew System::ArgumentNullException( "notify" );

			IDirectSoundNotify8* dsNotify;
			HRESULT hr = notify->QueryInterface( IID_IDirectSoundNotify8, reinterpret_cast<void**>( &dsNotify ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			Construct( dsNotify );
		}

		DirectSoundNotify::DirectSoundNotify( SlimDX::DirectSound::SoundBuffer ^soundBuffer )
		{
			IDirectSoundNotify8* dsNotify;
			HRESULT hr = soundBuffer->InternalPointer->QueryInterface( IID_IDirectSoundNotify8, reinterpret_cast<void**>( &dsNotify ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );
			
			Construct( dsNotify );
		}

		DirectSoundNotify::DirectSoundNotify( SlimDX::DirectSound::SecondarySoundBuffer ^secondaryBuffer )
		{
			IDirectSoundNotify8* dsNotify;
			HRESULT hr = secondaryBuffer->DS8Pointer->QueryInterface( IID_IDirectSoundNotify8, reinterpret_cast<void**>( &dsNotify ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );
			
			Construct( dsNotify );
		}

		DirectSoundNotify::DirectSoundNotify( SlimDX::DirectSound::CaptureBuffer ^captureBuffer )
		{
			IDirectSoundNotify8* dsNotify;
			HRESULT hr = captureBuffer->InternalPointer->QueryInterface( IID_IDirectSoundNotify8, reinterpret_cast<void**>( &dsNotify ) );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );
			
			Construct( dsNotify );
		}

		DirectSoundNotify^ DirectSoundNotify::FromPointer( IDirectSoundNotify* pointer )
		{
			DirectSoundNotify^ tableEntry = safe_cast<DirectSoundNotify^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				pointer->Release();
				return tableEntry;
			}

			return gcnew DirectSoundNotify( pointer );
		}

		DirectSoundNotify^ DirectSoundNotify::FromPointer( System::IntPtr pointer )
		{
			DirectSoundNotify^ tableEntry = safe_cast<DirectSoundNotify^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
			if( tableEntry != nullptr )
			{
				return tableEntry;
			}

			return gcnew DirectSoundNotify( pointer );
		}

		DirectSoundNotify::~DirectSoundNotify()
		{
			Destruct();
		}

		void DirectSoundNotify::SetNotificationPositions( array<SlimDX::DirectSound::BufferPositionNotify> ^notifications, int notifyCount )
		{
			LPDSBPOSITIONNOTIFY dsNotifies = NULL;
			DWORD count = 0;
			
			if( notifications != nullptr )
			{
				dsNotifies = new DSBPOSITIONNOTIFY[ notifyCount ];
				count = static_cast<DWORD>( notifyCount );

				for( int i = 0; i < notifyCount; i++ )
				{
					dsNotifies[i].dwOffset = static_cast<DWORD>( notifications[i].Offset );
					dsNotifies[i].hEventNotify = notifications[i].NotifyEventHandle.ToPointer();
				}
			}

			HRESULT hr = InternalPointer->SetNotificationPositions( count, dsNotifies );
			RECORD_DSOUND( hr );
		}
	}
}
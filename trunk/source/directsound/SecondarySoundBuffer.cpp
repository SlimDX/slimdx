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
#include "../DataStream.h"
#include "../Utilities.h"
#include "../Result.h"
#include "Enums.h"
#include "ResultCode.h"

#include "DirectSound.h"
#include "DirectSoundException.h"

#include "SoundBuffer.h"
#include "SoundBufferDescription.h"
#include "SoundEffectDescription.h"
#include "SecondarySoundBuffer.h"
#include "SoundEffectChorus.h"
#include "SoundEffectCompressor.h"
#include "SoundEffectDistortion.h"
#include "SoundEffectEcho.h"
#include "SoundEffectFlanger.h"
#include "SoundEffectGargle.h"
#include "SoundEffectI3DL2Reverb.h"
#include "SoundEffectParametricEqualizer.h"
#include "SoundEffectWavesReverb.h"

namespace SlimDX
{
	namespace DirectSound
	{
		SecondarySoundBuffer::SecondarySoundBuffer( DirectSound^ dsound, SoundBufferDescription description ) : SoundBuffer( dsound, description )
		{
			SetDS8Pointer();
		}

		SecondarySoundBuffer::SecondarySoundBuffer( System::String^ filename, DirectSound^ dsound ) : SoundBuffer( filename, dsound )
		{
			SetDS8Pointer();
		}

		SecondarySoundBuffer::SecondarySoundBuffer( System::String^ filename, DirectSound^ dsound, SoundBufferDescription description ) : SoundBuffer( filename, dsound, description )
		{
			SetDS8Pointer();
		}

		SecondarySoundBuffer::~SecondarySoundBuffer()
		{
			if( m_DS8Pointer != NULL )
			{
				m_DS8Pointer->Release();
				m_DS8Pointer = NULL;
			}
		}

		void SecondarySoundBuffer::SetDS8Pointer()
		{
			IDirectSoundBuffer8* buffer;
			HRESULT hr = InternalPointer->QueryInterface( IID_IDirectSoundBuffer8, reinterpret_cast<void**>( &buffer ) );
			
			if( SUCCEEDED( hr ) )
			{
				m_DS8Pointer = buffer;
			}
			else
			{
				m_DS8Pointer = NULL;
			}
		}

		array<SoundEffectReturnValue>^ SecondarySoundBuffer::SetEffects( array<SoundEffectDescription> ^effects )
		{
			DWORD count = 0;
			LPDWORD dwResults = NULL;
			LPDSEFFECTDESC dsEffects = NULL;
			array<SoundEffectReturnValue>^ results = nullptr;
			
			if( effects != nullptr )
			{
				count = effects->Length;
				dwResults = new DWORD[count];

				dsEffects = new DSEFFECTDESC[count];
				for( DWORD i = 0; i < count; i++ )
					dsEffects[i] = effects[i].ToUnmanaged();
			}

			HRESULT hr = DS8Pointer->SetFX( count, dsEffects, dwResults );
			if( RECORD_DSOUND( hr ).IsFailure )
				throw gcnew DirectSoundException( Result::Last );

			if( count > 0 )
			{
				results = gcnew array<SoundEffectReturnValue>( count );

				for( DWORD i = 0; i < count; i++ )
					results[i] = static_cast<SoundEffectReturnValue>( dwResults[i] );
			}

			return results;
		}

		System::Object^ SecondarySoundBuffer::GetEffect( int index )
		{
			IUnknown* pointer;

			if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXChorus, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectChorus::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXCompressor, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectCompressor::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXDistortion, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectDistortion::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXEcho, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectEcho::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXFlanger, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectFlanger::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXGargle, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectGargle::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXI3DL2Reverb, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectI3DL2Reverb::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXParamEq, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectParametricEqualizer::FromPointer( System::IntPtr( pointer ) );

			else if( SUCCEEDED( DS8Pointer->GetObjectInPath( GUID_All_Objects, index, IID_IDirectSoundFXWavesReverb, reinterpret_cast<void**>( &pointer ) ) ) )
				return SoundEffectWavesReverb::FromPointer( System::IntPtr( pointer ) );

			throw gcnew DirectSoundException( ResultCode::ObjectNotFound );
		}
	}
}
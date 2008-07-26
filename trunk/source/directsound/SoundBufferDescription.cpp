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

#include <dsound.h>

#include "../Utilities.h"
#include "../WaveFormat.h"
#include "Guids.h"
#include "SoundBufferDescription.h"

namespace SlimDX
{
	namespace DirectSound
	{
		DSBUFFERDESC SoundBufferDescription::ToUnmanaged()
		{
			DSBUFFERDESC result; 
			ZeroMemory( &result, sizeof( DSBUFFERDESC ) );
			result.dwSize = sizeof( DSBUFFERDESC );
			result.dwFlags = static_cast<DWORD>( this->Flags );
			result.dwBufferBytes = static_cast<DWORD>( this->SizeInBytes );
			result.dwReserved = 0;
			result.guid3DAlgorithm = DS3DALG_DEFAULT;
			result.lpwfxFormat = NULL;

			if( ( result.dwFlags & DSBCAPS_CTRL3D ) != 0 )
				result.guid3DAlgorithm = Utilities::ConvertManagedGuid( this->AlgorithmFor3D );

			if( this->Format != nullptr )
				result.lpwfxFormat = new WAVEFORMATEX( *( WaveFormat::ToUnmanaged( this->Format ).get() ) );

			return result;
		}
	}
}
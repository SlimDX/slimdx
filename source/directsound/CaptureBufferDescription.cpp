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

#include "../WaveFormat.h"

#include "CaptureEffectDescription.h"
#include "CaptureBufferDescription.h"

namespace SlimDX
{
	namespace DirectSound
	{
		CaptureBufferDescription::CaptureBufferDescription( const DSCBUFFERDESC &description )
		{
			BufferBytes = description.dwBufferBytes;
			EffectDescriptions = nullptr;

			if( description.dwFXCount > 0 )
			{
				EffectDescriptions = gcnew array<CaptureEffectDescription>( description.dwFXCount );

				for( DWORD i = 0; i < description.dwFXCount; i++ )
					EffectDescriptions[i] = CaptureEffectDescription( description.lpDSCFXDesc[i] );
			}

			if( ( description.dwFlags & DSCBCAPS_CTRLFX ) != 0 )
				ControlEffects = true;

			if( ( description.dwFlags & DSCBCAPS_WAVEMAPPED ) != 0 )
				WaveMapped = true;
		}

		DSCBUFFERDESC CaptureBufferDescription::ToUnmanaged()
		{
			DSCBUFFERDESC description;
			ZeroMemory( &description, sizeof(description) );
			description.dwSize = sizeof( DSCBUFFERDESC );
			description.dwBufferBytes = BufferBytes;
			description.dwFXCount = 0;
			description.dwFlags = 0;
			description.dwReserved = 0;
			description.lpwfxFormat = NULL;
			description.lpDSCFXDesc = NULL;

			if( ControlEffects && ( EffectDescriptions != nullptr ) )
			{
				description.dwFXCount = EffectDescriptions->Length;
				LPDSCEFFECTDESC lpDSCFXDesc = new DSCEFFECTDESC[ description.dwFXCount ];

				for( DWORD i = 0; i < description.dwFXCount; i++ )
					lpDSCFXDesc[i] = EffectDescriptions[i].Marshal();

				description.lpDSCFXDesc = lpDSCFXDesc;
			}

			if( ControlEffects && WaveMapped )
				description.dwFlags = DSCBCAPS_CTRLFX | DSCBCAPS_WAVEMAPPED;
			else if( ControlEffects )
				description.dwFlags = DSCBCAPS_CTRLFX;
			else if( WaveMapped )
				description.dwFlags = DSCBCAPS_WAVEMAPPED;

			if( Format != nullptr )
				description.lpwfxFormat = new WAVEFORMATEX( *( WaveFormat::ToUnmanaged( Format ).get() ) );

			return description;
		}
	}
}
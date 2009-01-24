/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include "ParametricEqualizer.h"

using namespace System;

namespace SlimDX
{
namespace DirectSound
{
	ParametricEqualizer::ParametricEqualizer( IDirectSoundFXParamEq *pointer )
	{
		Construct( pointer );
	}

	ParametricEqualizer::ParametricEqualizer( System::IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	ParametricEqualizer^ ParametricEqualizer::FromPointer( IDirectSoundFXParamEq* pointer )
	{
		if( pointer == NULL )
			return nullptr;

		ParametricEqualizer^ tableEntry = safe_cast<ParametricEqualizer^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew ParametricEqualizer( pointer );
	}

	ParametricEqualizer^ ParametricEqualizer::FromPointer( System::IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		ParametricEqualizer^ tableEntry = safe_cast<ParametricEqualizer^>( ObjectTable::Find( static_cast<System::IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew ParametricEqualizer( pointer );
	}

	float ParametricEqualizer::Center::get()
	{
		DSFXParamEq param;

		HRESULT hr = InternalPointer->GetAllParameters( &param );
		if( RECORD_DSOUND( hr ).IsFailure )
			return 0.0f;

		return param.fCenter;
	}

	void ParametricEqualizer::Center::set( float value )
	{
		DSFXParamEq param;

		HRESULT hr = InternalPointer->GetAllParameters( &param );
		if( RECORD_DSOUND( hr ).IsFailure )
			return;

		param.fCenter = value;
		hr = InternalPointer->SetAllParameters( &param );
		RECORD_DSOUND( hr );
	}

	float ParametricEqualizer::Bandwidth::get()
	{
		DSFXParamEq param;

		HRESULT hr = InternalPointer->GetAllParameters( &param );
		if( RECORD_DSOUND( hr ).IsFailure )
			return 0.0f;

		return param.fBandwidth;
	}

	void ParametricEqualizer::Bandwidth::set( float value )
	{
		DSFXParamEq param;

		HRESULT hr = InternalPointer->GetAllParameters( &param );
		if( RECORD_DSOUND( hr ).IsFailure )
			return;

		param.fBandwidth = value;
		hr = InternalPointer->SetAllParameters( &param );
		RECORD_DSOUND( hr );
	}

	float ParametricEqualizer::Gain::get()
	{
		DSFXParamEq param;

		HRESULT hr = InternalPointer->GetAllParameters( &param );
		if( RECORD_DSOUND( hr ).IsFailure )
			return 0.0f;

		return param.fGain;
	}

	void ParametricEqualizer::Gain::set( float value )
	{
		DSFXParamEq param;

		HRESULT hr = InternalPointer->GetAllParameters( &param );
		if( RECORD_DSOUND( hr ).IsFailure )
			return;

		param.fGain = value;
		hr = InternalPointer->SetAllParameters( &param );
		RECORD_DSOUND( hr );
	}
}
}
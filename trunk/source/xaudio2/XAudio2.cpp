/*
* Copyright (c) 2007 SlimDX Group
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

#ifdef WRAP_XAUDIO2

//XA2 BUG: Idiots missed a closing paren and so nothing compiles with this on.
//#define XAUDIO2_HELPER_FUNCTIONS

#include <windows.h>
#include <mmreg.h>
#include <xaudio2.h>

#include "../ComObject.h"
#include "XAudio2.h"
#include "AudioException.h"
#include "EngineCallback.h"

namespace SlimDX
{
namespace XAudio2
{
	XAudio2::XAudio2( XAudio2Flags flags, EngineCallback^ callback, WindowsProcessorSpecifier processor )
	{
		IXAudio2* xa2;
		IXAudio2EngineCallback* nativeCallback = callback != nullptr ? callback->Shim : NULL;

		HRESULT hr = XAudio2Create( &xa2, static_cast<UINT32>( flags ), nativeCallback, static_cast<XAUDIO2_PROCESSOR>( processor ) );
		AudioException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew AudioException();

		Construct(xa2);
	}

	float XAudio2::AmplitudeRatioToDecibels( float volume )
	{
		//return XAudio2AmplitudeRatioToDecibels( volume );
		throw gcnew NotSupportedException();
	}

	float XAudio2::DecibelsToAmplitudeRatio( float decibels )
	{
		//return XAudio2DecibelsToAmplitudeRatio( decibels );
		throw gcnew NotSupportedException();
	}

	float XAudio2::FrequencyRatioToSemitones( float frequencyRatio )
	{
		//return XAudio2FrequencyRatioToSemitones( frequencyRatio );
		throw gcnew NotSupportedException();
	}

	float XAudio2::SemitonesToFrequencyRatio( float semitones )
	{
		//return XAudio2SemitonesToFrequencyRatio( semitones );
		throw gcnew NotSupportedException();
	}

	void XAudio2::Initialize( EngineCallback^ callback, WindowsProcessorSpecifier processor )
	{
		IXAudio2EngineCallback* nativeCallback = callback != nullptr ? callback->Shim : NULL;

		HRESULT hr = InternalPointer->Initialize( 0, nativeCallback, static_cast<XAUDIO2_PROCESSOR>( processor ) );
		AudioException::CheckHResult( hr );
	}

	void XAudio2::StartEngine()
	{
		HRESULT hr = InternalPointer->StartEngine();
		AudioException::CheckHResult( hr );
	}

	void XAudio2::StopEngine()
	{
		HRESULT hr = InternalPointer->StopEngine();
		AudioException::CheckHResult( hr );
	}

	DeviceDetails XAudio2::GetDeviceDetails( int index )
	{
		DeviceDetails details;
		//HRESULT hr = InternalPointer->GetDeviceDetails( reinterpret_cast<XAUDIO2_DEVICE_DETAILS*>( &details ) );
		//AudioException::CheckHResult( hr );

		return details;
	}

	int XAudio2::DeviceCount::get()
	{
		UINT32 count = 0;
		HRESULT hr = InternalPointer->GetDeviceCount( &count );
		AudioException::CheckHResult( hr );

		return (int) count;
	}

	SlimDX::XAudio2::PerformanceData XAudio2::PerformanceData::get()
	{
		SlimDX::XAudio2::PerformanceData data;
		HRESULT hr = InternalPointer->GetPerformanceData( reinterpret_cast<XAUDIO2_PERFORMANCE_DATA*>( &data ) );
		AudioException::CheckHResult( hr );

		return data;
	}
}
}

#endif //WRAP_XAUDIO2
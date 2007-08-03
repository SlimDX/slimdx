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
* all copies or substantial portions of the Software.`
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

//XA2 BUG: Idiots missed a closing paren and so nothing compiles with this on.
//#define XAUDIO2_HELPER_FUNCTIONS
#include <xaudio2.h>

#include "../DirectXObject.h"
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

		HRESULT hr = XAudio2Create( &xa2, (UINT32) flags, nativeCallback, (XAUDIO2_PROCESSOR) processor );

		m_Pointer = xa2;
	}

	float XAudio2::AmplitudeRatioToDecibels( float volume )
	{
		//return XAudio2AmplitudeRatioToDecibels( volume );
		return 0.0f;
	}

	float XAudio2::DecibelsToAmplitudeRatio( float decibels )
	{
		//return XAudio2DecibelsToAmplitudeRatio( decibels );
		return 0.0f;
	}

	float XAudio2::FrequencyRatioToSemitones( float frequencyRatio )
	{
		//return XAudio2FrequencyRatioToSemitones( frequencyRatio );
		return 0.0f;
	}

	float XAudio2::SemitonesToFrequencyRatio( float semitones )
	{
		//return XAudio2SemitonesToFrequencyRatio( semitones );
		return 0.0f;
	}

	void XAudio2::Initialize( EngineCallback^ callback, WindowsProcessorSpecifier processor )
	{
		IXAudio2EngineCallback* nativeCallback = callback != nullptr ? callback->Shim : NULL;

		HRESULT hr = m_Pointer->Initialize( 0, nativeCallback, (XAUDIO2_PROCESSOR) processor );
	}

	void XAudio2::StartEngine()
	{
		HRESULT hr = m_Pointer->StartEngine();
	}

	void XAudio2::StopEngine()
	{
		HRESULT hr = m_Pointer->StopEngine();
	}

	DeviceDetails XAudio2::GetDeviceDetails( int index )
	{
		DeviceDetails details;
		//HRESULT hr = m_Pointer->GetDeviceDetails( (XAUDIO2_DEVICE_DETAILS*) &details );

		return details;
	}

	int XAudio2::DeviceCount::get()
	{
		UINT32 count;
		HRESULT hr = m_Pointer->GetDeviceCount( &count );

		return (int) count;
	}

	SlimDX::XAudio2::PerformanceData XAudio2::PerformanceData::get()
	{
		SlimDX::XAudio2::PerformanceData data;
		HRESULT hr = m_Pointer->GetPerformanceData( (XAUDIO2_PERFORMANCE_DATA*) &data );

		return data;
	}
}
}
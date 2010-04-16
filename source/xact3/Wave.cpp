#include "stdafx.h"
/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include <xact3.h>

#include "Xact3Exception.h"
#include "Wave.h"

namespace SlimDX
{
namespace XACT3
{
	void Wave::Play()
	{
		HRESULT hr = InternalPointer->Play();
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	void Wave::Stop(StopFlags flags)
	{
		HRESULT hr = InternalPointer->Stop((DWORD)flags);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	void Wave::Pause(bool pause)
	{
		HRESULT hr = InternalPointer->Pause(pause);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	WaveState Wave::State::get()
	{
		DWORD result;

		HRESULT hr = InternalPointer->GetState(&result);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return (WaveState)result;
	}

	void Wave::SetPitch(short pitch)
	{
		HRESULT hr = InternalPointer->SetPitch(pitch);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	void Wave::SetVolume(float volume)
	{
		HRESULT hr = InternalPointer->SetVolume(volume);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	void Wave::SetMatrixCoefficients(int srcChannelCount, int dstChannelCount, array<float>^ matrixCoefficients)
	{
		pin_ptr<float> pinnedMatrix = &matrixCoefficients[0];

		HRESULT hr = InternalPointer->SetMatrixCoefficients(srcChannelCount, dstChannelCount, pinnedMatrix);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	WaveInstanceProperties^ Wave::Properties::get()
	{
		XACT_WAVE_INSTANCE_PROPERTIES result;

		HRESULT hr = InternalPointer->GetProperties(&result);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return gcnew WaveInstanceProperties(result);
	}
}
}

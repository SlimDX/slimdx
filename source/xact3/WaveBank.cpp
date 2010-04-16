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
#include "stdafx.h"

#include "XACT3Exception.h"

#include "WaveBank.h"

namespace SlimDX
{
namespace XACT3
{
	int WaveBank::WaveCount::get()
	{
		XACTINDEX count;

		HRESULT hr = InternalPointer->GetNumWaves(&count);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return count;
	}

	int WaveBank::GetWaveIndex(String^ friendlyName)
	{
		XACTINDEX result;

		array<unsigned char>^ friendlyNameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes(friendlyName);
		pin_ptr<unsigned char> pinnedFriendlyName = &friendlyNameBytes[0];
		result = InternalPointer->GetWaveIndex(reinterpret_cast<PCSTR>(pinnedFriendlyName));

		// Could throw an exception here, I guess.

		return result == XACTINDEX_INVALID ? -1 : result;
	}

	WaveProperties^ WaveBank::GetWaveProperties(int waveIndex)
	{
		XACT_WAVE_PROPERTIES props;

		HRESULT hr = InternalPointer->GetWaveProperties((XACTINDEX)waveIndex, &props);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return gcnew WaveProperties(props);
	}

	Wave^ WaveBank::Prepare(int waveIndex, ContentPreparationFlags flags, int playOffset, int loopCount)
	{
		IXACT3Wave* result;

		HRESULT hr = InternalPointer->Prepare((XACTINDEX)waveIndex, (DWORD)flags, playOffset, (XACTLOOPCOUNT)loopCount, &result);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		//return gcnew Wave(engine, result);
	}

	Wave^ WaveBank::Play(int waveIndex, ContentPreparationFlags flags, int playOffset, int loopCount)
	{
		IXACT3Wave* result;

		HRESULT hr = InternalPointer->Play((XACTINDEX)waveIndex, (DWORD)flags, playOffset, (XACTLOOPCOUNT)loopCount, &result);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		//return gcnew Wave(engine, result);
	}

	Result WaveBank::Stop(int waveIndex, StopFlags flags)
	{
		HRESULT hr = InternalPointer->Stop((XACTINDEX)waveIndex, (DWORD)flags);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	WaveBankState WaveBank::State::get()
	{
		DWORD result;

		HRESULT hr = InternalPointer->GetState(&result);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return (WaveBankState)result;
	}
}
}

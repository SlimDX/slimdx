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

#include "XACT3Exception.h"

#include "SoundBank.h"
#include "Cue.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace XACT3
{
	int SoundBank::GetCueIndex(String^ friendlyName)
	{
		XACTINDEX result;

		array<unsigned char>^ friendlyNameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes(friendlyName);
		pin_ptr<unsigned char> pinnedFriendlyName = &friendlyNameBytes[0];
		result = InternalPointer->GetCueIndex(reinterpret_cast<PCSTR>(pinnedFriendlyName));

		// Could throw an exception here, I guess.

		return result == XACTINDEX_INVALID ? -1 : result;
	}

	int SoundBank::CueCount::get()
	{
		XACTINDEX result;

		HRESULT hr = InternalPointer->GetNumCues(&result);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return result;
	}

	CueProperties^ SoundBank::GetCueProperties(int cueIndex)
	{
		XACT_CUE_PROPERTIES result;

		HRESULT hr = InternalPointer->GetCueProperties((XACTINDEX)cueIndex, &result);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return gcnew CueProperties(result);
	}

	Cue^ SoundBank::Prepare(int cueIndex, int timeOffset)
	{
		IXACT3Cue *cue;

		HRESULT hr = InternalPointer->Prepare((XACTINDEX)cueIndex, 0, timeOffset, &cue);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		//return gcnew Cue(engine, cue);
	}

	Cue^ SoundBank::Play(int cueIndex, int timeOffset)
	{
		IXACT3Cue *cue = 0;

		HRESULT hr = InternalPointer->Play((XACTINDEX)cueIndex, 0, timeOffset, &cue);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		//return gcnew Cue(engine, cue);
	}

	void SoundBank::Stop(int cueIndex, StopFlags flags)
	{
		HRESULT hr = InternalPointer->Stop((XACTINDEX)cueIndex, (DWORD)flags);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);
	}

	SoundBankState SoundBank::State::get()
	{
		DWORD result;
		HRESULT hr = InternalPointer->GetState(&result);
		if(RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		return static_cast<SoundBankState>(result);
	}
}
}

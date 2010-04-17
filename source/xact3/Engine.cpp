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

#include "Engine.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace XACT3
{
	Engine::Engine()
	{
		IXACT3Engine *pointer;

		HRESULT hr = XACT3CreateEngine(0, &pointer);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		Construct(pointer);
	}

	Engine::Engine( CreationFlags flags )
	{
		IXACT3Engine *pointer;

		HRESULT hr = XACT3CreateEngine(static_cast<DWORD>(flags), &pointer);
		if (RECORD_XACT3(hr).IsFailure)
			throw gcnew XACT3Exception(Result::Last);

		Construct(pointer);
	}

	Result Engine::DoWork()
	{
		HRESULT hr = InternalPointer->DoWork();
		return RECORD_XACT3(hr);
	}

	int Engine::GetCategory(String^ friendlyName)
	{
		array<unsigned char>^ friendlyNameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes(friendlyName);
		pin_ptr<unsigned char> pinnedFriendlyName = &friendlyNameBytes[0];

		XACTCATEGORY result = InternalPointer->GetCategory(reinterpret_cast<PCSTR>(pinnedFriendlyName));
		return result == XACTCATEGORY_INVALID ? -1 : result;
	}

	float Engine::GetGlobalVariable(int index)
	{
		XACTVARIABLEVALUE result;

		HRESULT hr = InternalPointer->GetGlobalVariable((XACTVARIABLEINDEX)index, &result);
		RECORD_XACT3(hr);

		return result;
	}

	int Engine::GetGlobalVariableIndex(String^ friendlyName)
	{
		array<unsigned char>^ friendlyNameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes(friendlyName);
		pin_ptr<unsigned char> pinnedFriendlyName = &friendlyNameBytes[0];

		XACTVARIABLEINDEX result = InternalPointer->GetGlobalVariableIndex(reinterpret_cast<PCSTR>(pinnedFriendlyName));
		return result == XACTVARIABLEINDEX_INVALID ? -1 : result;
	}

	RendererDetails Engine::GetRendererDetails(int rendererIndex)
	{
		XACT_RENDERER_DETAILS rendererDetails;

		HRESULT hr = InternalPointer->GetRendererDetails(static_cast<XACTINDEX>(rendererIndex), &rendererDetails);
		RECORD_XACT3(hr);

		return RendererDetails(rendererDetails);
	}

	Result Engine::Initialize( RuntimeParameters parameters )
	{
		XACT_RUNTIME_PARAMETERS rp = parameters.ToUnmanaged();

		HRESULT hr = InternalPointer->Initialize(&rp);
		delete[] rp.pRendererID;

		return RECORD_XACT3(hr);
	}

	Result Engine::Pause(int category, bool pause)
	{
		HRESULT hr = InternalPointer->Pause(static_cast<XACTCATEGORY>(category), pause);
		return RECORD_XACT3(hr);
	}

	Result Engine::SetGlobalVariable(int index, float value)
	{
		HRESULT hr = InternalPointer->SetGlobalVariable(static_cast<XACTVARIABLEINDEX>(index), value);
		return RECORD_XACT3(hr);
	}

	Result Engine::SetVolume(int category, float volume)
	{
		HRESULT hr = InternalPointer->SetVolume(static_cast<XACTCATEGORY>(category), volume);
		return RECORD_XACT3(hr);
	}

	Result Engine::ShutDown()
	{
		HRESULT hr = InternalPointer->ShutDown();
		return RECORD_XACT3(hr);
	}

	Result Engine::Stop(int category, StopFlags flags)
	{
		HRESULT hr = InternalPointer->Stop(static_cast<XACTCATEGORY>(category), static_cast<DWORD>(flags));
		return RECORD_XACT3(hr);
	}

	int Engine::RendererCount::get()
	{
		XACTINDEX result;
		HRESULT hr = InternalPointer->GetRendererCount(&result);
		RECORD_XACT3(hr);

		return static_cast<int>(result);
	}

	WaveFormatExtensible^ Engine::FinalMixFormat::get()
	{
		WAVEFORMATEXTENSIBLE finalMixFormat;

		HRESULT hr = InternalPointer->GetFinalMixFormat(&finalMixFormat);
		RECORD_XACT3(hr);

		return gcnew WaveFormatExtensible(finalMixFormat);
	}
}
}

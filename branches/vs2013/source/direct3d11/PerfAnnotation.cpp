/*
* Copyright (c) 2007-2014 SlimDX Group
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

#include "Direct3D11Exception.h"
#include "DeviceContext11.h"
#include "PerfAnnotation.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	PerfAnnotation::PerfAnnotation(DeviceContext^ context) 
	{
		ID3DUserDefinedAnnotation* result = 0;

		if (RECORD_D3D11(context->InternalPointer->QueryInterface(IID_ID3DUserDefinedAnnotation, reinterpret_cast<void**>(&result))).IsFailure)
			throw gcnew Direct3D11Exception(Result::Last);

		auto other = ObjectTable::Find(IntPtr(result));
		Construct(result, other, other == nullptr);
	}

	int PerfAnnotation::BeginEvent(String^ name)
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(name);
		return InternalPointer->BeginEvent(pinnedName);
	}

	int PerfAnnotation::EndEvent()
	{
		return InternalPointer->EndEvent();
	}

	void PerfAnnotation::SetMarker(String^ name)
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars(name);
		InternalPointer->SetMarker(pinnedName);
	}

	bool PerfAnnotation::IsProfilingToolRunning::get()
	{
		return InternalPointer->GetStatus() != 0;
	}
}
}
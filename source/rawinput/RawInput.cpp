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

#include <windows.h>

#include "RawInput.h"
#include "RawInputDevice.h"
#include "RawInputData.h"
#include "Enums.h"

namespace SlimDX
{
namespace RawInput
{
	void RawInput::RegisterRawInputDevices(array<RawInputDevice^>^ devices)
	{
		RAWINPUTDEVICE* Rid = new RAWINPUTDEVICE[devices->Length];

		for(int i = 0; i < devices->Length; i++)
			Rid[i] = *devices[i]->Internal;

		if(!::RegisterRawInputDevices(Rid, devices->Length, sizeof(Rid[0])))
			throw gcnew System::InvalidOperationException("Unable to register raw input device. Error code " + GetLastError());

		delete[] Rid;
	}

	SlimDX::RawInput::RawInputData^ RawInput::GetRawInputData(System::IntPtr^ lParam, Command command)
	{
		UINT size;
		if(::GetRawInputData((HRAWINPUT)lParam->ToPointer(), RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER)) != 0)
			throw gcnew System::InvalidOperationException("Unable to get size of raw input data. Error code " + GetLastError());

		LPBYTE* lpb = new LPBYTE[size];
		if(::GetRawInputData((HRAWINPUT)lParam->ToPointer(), static_cast<UINT>(command), lpb, &size, sizeof(RAWINPUTHEADER)) != size)
		{
			delete[] lpb;
			throw gcnew System::InvalidOperationException("Raw input data does not make expected size. Error code " + GetLastError());
		}

		RawInputData^ data = gcnew RawInputData((RAWINPUT*)lpb);

		delete[] lpb;
		return data;
	}
}
}
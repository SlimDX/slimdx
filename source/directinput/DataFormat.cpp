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
#include <windows.h>
#include <dinput.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "DirectInput.h"
#include "Device.h"
#include "InputException.h"

namespace SlimDX
{
namespace DirectInput
{
	ObjectDataFormat::ObjectDataFormat()
	{
	}

	ObjectDataFormat::ObjectDataFormat( Guid g, int o, ObjectDeviceType t, int in,
		ObjectDataFormatFlags f ) : guid( g ), offset( o ), type( t ),
		instanceNumber( in ), flags( f )
	{
	}

	DIOBJECTDATAFORMAT ObjectDataFormat::ToUnmanaged()
	{
		DIOBJECTDATAFORMAT format;
		return format;
	}

	DataFormat::DataFormat()
	{
		objectDataFormats = gcnew List<ObjectDataFormat^>();
	}

	DataFormat::DataFormat( DataFormatFlags flags, int dataSize )
	{
		objectDataFormats = gcnew List<ObjectDataFormat^>();
		this->dataSize = dataSize;
		this->flags = flags;
	}

	DIDATAFORMAT DataFormat::ToUnmanaged()
	{
		DIDATAFORMAT format;
		return format;
	}
}
}
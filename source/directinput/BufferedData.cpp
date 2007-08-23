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
	BufferedData::BufferedData( const DIDEVICEOBJECTDATA &objectData )
	{
		offset = objectData.dwOfs;
		data = objectData.dwData;
		timeStamp = objectData.dwTimeStamp;
		sequence = objectData.dwSequence;
		handle = GCHandle::FromIntPtr( ( IntPtr )( ( UIntPtr )objectData.uAppData ).ToPointer() );
		appData = handle.Target;
	}

	BufferedData::BufferedData()
	{
	}

	BufferedData::BufferedData( int offset, int data, int timeStamp, int sequence, Object^ applicationData )
		: offset( offset ), data( data ), timeStamp( timeStamp ), sequence( sequence ), appData( applicationData )
	{
	}

	BufferedData::!BufferedData()
	{
		Destruct();
	}

	BufferedData::~BufferedData()
	{
		Destruct();
	}

	void BufferedData::Destruct()
	{
		if( handle.IsAllocated )
			handle.Free();
	}

	int BufferedData::CompareSequence( int sequence1, int sequence2 )
	{
		if( DISEQUENCE_COMPARE( sequence1, >, sequence2 ) )
			return 1;

		if( DISEQUENCE_COMPARE( sequence1, <, sequence2 ) )
			return -1;

		return 0;
	}
}
}
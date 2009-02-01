/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include <dxgi.h>

#include "DXGIException.h"

#include "Adapter.h"
#include "AdapterDescription.h"
#include "Output.h"

using namespace System;

namespace SlimDX
{
namespace DXGI
{ 	
	AdapterDescription Adapter::Description::get()
	{
		DXGI_ADAPTER_DESC nativeDescription;
		RECORD_DXGI( InternalPointer->GetDesc( &nativeDescription ) );
		if( Result::Last.IsSuccess )
			return AdapterDescription( nativeDescription );
		
		throw gcnew DXGIException( Result::Last );
	}
		
	int Adapter::GetOutputCount()
	{
		int count = 0;
		IDXGIOutput* output = 0;
		while( InternalPointer->EnumOutputs( count, &output) != DXGI_ERROR_NOT_FOUND )
		{
			output->Release();
			++count;
		}

		return count;
	}
	
	Output^ Adapter::GetOutput( int index )
	{
		IDXGIOutput* output = 0;
		RECORD_DXGI( InternalPointer->EnumOutputs( index, &output) );
		if( Result::Last.IsFailure )
			return nullptr;
		return Output::FromPointer( output );
	}

	bool Adapter::IsInterfaceSupported( Type^ type )
	{
		Int64 version = 0;
		return IsInterfaceSupported( type, version );
	}

	bool Adapter::IsInterfaceSupported( Type^ type, [Out] Int64% userModeVersion )
	{
		GUID guid = Utilities::GetNativeGuidForType( type );
		LARGE_INTEGER version;
		RECORD_DXGI( InternalPointer->CheckInterfaceSupport( guid, &version ) );
		if( Result::Last == Result( DXGI_ERROR_UNSUPPORTED ) )
		{
			userModeVersion = 0;
			return false;
		}

		userModeVersion = version.QuadPart;
		return true;
	}
	
	String^ Adapter::ToString() {
		return Description.Description;
	}
}
}

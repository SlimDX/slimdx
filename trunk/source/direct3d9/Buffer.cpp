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
#include <d3d9.h>
#include <d3dx9.h>

#include "../DirectXObject.h"
#include "GraphicsException.h"
#include "Buffer.h"

namespace SlimDX
{
namespace Direct3D9
{
	BufferWrapper::BufferWrapper( ID3DXBuffer* buffer ) : DirectXObject<ID3DXBuffer>( buffer )
	{
		if( buffer == NULL )
			throw gcnew ArgumentNullException( "buffer" );
	}

	BufferWrapper::BufferWrapper( IntPtr buffer )
	{
		if( buffer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "buffer" );

		void* pointer;
		IUnknown* unknown = (IUnknown*) buffer.ToPointer();
		HRESULT hr = unknown->QueryInterface( IID_ID3DXBuffer, &pointer );
		if( FAILED( hr ) )
			throw gcnew GraphicsException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = (ID3DXBuffer*) pointer;
	}

	BufferWrapper::BufferWrapper( int size )
	{
		ID3DXBuffer* buffer;
		HRESULT hr = D3DXCreateBuffer( size, &buffer );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = buffer;
	}

	String^ BufferWrapper::ConvertToString( ID3DXBuffer* buffer )
	{
		if( buffer != NULL )
		{
			String^ string = gcnew String( (const char*) buffer->GetBufferPointer() );
			buffer->Release();
			return string;
		}
		else
		{
			return String::Empty;
		}
	}
}
}
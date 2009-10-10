#include "stdafx.h"
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
#include <d3d10.h>

#include "../Utilities.h"
#include "../DataStream.h"
#include "../SlimDXException.h"

#include "Include10.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D10
{
	IncludeShim::IncludeShim( Include^ wrapped )
	{
		m_Wrapped = wrapped;
		m_Frames = gcnew Stack<IncludeFrame>();
	}

	IncludeShim::~IncludeShim()
	{
		while( m_Frames->Count > 0 )
			m_Frames->Pop().Close();
	}

	HRESULT IncludeShim::Open( D3D10_INCLUDE_TYPE type, LPCSTR fileName, LPCVOID parentData, LPCVOID* data, UINT* bytes )
	{
		SLIMDX_UNREFERENCED_PARAMETER(parentData);
		SLIMDX_UNREFERENCED_PARAMETER(data);

		try
		{
			Stream^ stream;
			m_Wrapped->Open( static_cast<IncludeType>( type ), gcnew String( fileName ), stream );

			if( stream != nullptr )
			{
				if( stream->GetType() == DataStream::typeid )
				{
					DataStream^ localData = safe_cast<DataStream^>( stream );
					*data = localData->PositionPointer;
					*bytes = static_cast<UINT>( localData->Length );

					m_Frames->Push( IncludeFrame( stream, GCHandle() ) );
				}
				else
				{
					array<Byte>^ localData = Utilities::ReadStream( stream, NULL );
					GCHandle handle = GCHandle::Alloc( localData, GCHandleType::Pinned );
					*data = handle.AddrOfPinnedObject().ToPointer();
					*bytes = localData->Length;

					m_Frames->Push( IncludeFrame( stream, handle ) );
				}
			}
			else
			{
				*data = 0;
				*bytes = 0;

				m_Frames->Push( IncludeFrame( nullptr, GCHandle() ) );
			}

			return S_OK;
		}
		catch( SlimDXException^ ex)
		{
			return ex->ResultCode.Code;
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
	}

	HRESULT IncludeShim::Close( LPCVOID data )
	{
		SLIMDX_UNREFERENCED_PARAMETER( data );

		try
		{
			IncludeFrame frame = m_Frames->Pop();

			m_Wrapped->Close( frame.Stream );

			frame.Close();

			return S_OK;
		}
		catch( SlimDXException^ ex)
		{
			return ex->ResultCode.Code;
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
	}

	void IncludeFrame::Close()
	{
		if( m_stream != nullptr )
			delete m_stream;
		if( m_handle.IsAllocated )
			m_handle.Free();
	}
}
}
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
#include <d3d9.h>
#include <d3dx9.h>

#include "../Utilities.h"
#include "../DataStream.h"
#include "../InternalHelpers.h"

#include "Include.h"

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D9
{
	IncludeShim::IncludeShim( Include^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
		m_stream = nullptr;
	}

	HRESULT IncludeShim::Open( D3DXINCLUDE_TYPE includeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes )
	{
		SLIMDX_UNREFERENCED_PARAMETER(pParentData);
		SLIMDX_UNREFERENCED_PARAMETER(ppData);

		try
		{
			Stream^ stream;
			m_WrappedInterface->Open( static_cast<IncludeType>( includeType ), gcnew String(pFileName), stream );
			m_stream = stream;

			if( stream != nullptr )
			{
				if(stream->GetType() == DataStream::typeid)
				{
					//Magic shortcut if we happen to get a DataStream
					DataStream^ data = safe_cast<DataStream^>( stream );
					*ppData = data->RawPointer;
					*pBytes = static_cast<UINT>( data->Length );
				}
				else
				{
					//Read the stream into a byte array and pin it
					array<Byte>^ data = Utilities::ReadStream( stream, 0 );
					m_handle = GCHandle::Alloc( data, GCHandleType::Pinned );
					*ppData = m_handle.AddrOfPinnedObject().ToPointer();
					*pBytes = data->Length;
				}
			}
			else
			{
				*ppData = NULL;
				*pBytes = 0;
			}

			return S_OK;
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
	}

	HRESULT IncludeShim::Close( LPCVOID pData )
	{
		SLIMDX_DEBUG_UNREFERENCED_PARAMETER(pData);

		try
		{
			if( m_handle.IsAllocated )
			{
				m_handle.Free();
			}

			Stream^ stream = m_stream;
			m_WrappedInterface->Close( stream );
			delete stream;
			m_stream = nullptr;

			return S_OK;
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
	}
}
}
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

#include "Device.h"
#include "Query.h"

namespace SlimDX
{
namespace Direct3D9
{
	Query::Query( IDirect3DQuery9* query )
	{
		if( query == NULL )
			throw gcnew ArgumentNullException( "surface" );

		m_Pointer = query;
	}

	Query::Query( IntPtr query )
	{
		if( query == IntPtr::Zero )
			throw gcnew ArgumentNullException( "query" );

		void* pointer;
		IUnknown* unknown = (IUnknown*) query.ToPointer();
		HRESULT hr = unknown->QueryInterface( IID_IDirect3DQuery9, &pointer );
		if( FAILED( hr ) )
			throw gcnew GraphicsException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = (IDirect3DQuery9*) pointer;
	}

	Query::Query( Device^ device, QueryType type )
	{
		IDirect3DQuery9* query;
		HRESULT hr = device->InternalPointer->CreateQuery( (D3DQUERYTYPE) type, &query );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			throw gcnew GraphicsException( "Failed to create Query." );

		m_Pointer = query;
	}

	int Query::DataSize::get()
	{
		return m_Pointer->GetDataSize();
	}

	QueryType Query::Type::get()
	{
		return (QueryType) m_Pointer->GetType();
	}

	Device^ Query::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	void Query::Issue( SlimDX::Direct3D9::Issue flags )
	{
		HRESULT hr = m_Pointer->Issue( (DWORD) flags );
		GraphicsException::CheckHResult( hr );
	}

	bool Query::CheckStatus( bool flush )
	{
		HRESULT hr = m_Pointer->GetData( NULL, 0, flush ? D3DGETDATA_FLUSH : 0 );
		
		switch( hr )
		{
		case S_OK:
			return true;
		case S_FALSE:
			return false;
			
		default:
			GraphicsException::CheckHResult( hr );
			return false;
		}
	}

	generic<typename T>
	T Query::GetData( bool flush )
	{
		HRESULT hr = S_OK;
		QueryType type = Type;

		switch( type )
		{
		case QueryType::BandwidthTimings:
			if( T::typeid != BandwidthTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::CacheUtilization:
			if( T::typeid != CacheUtilization::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::Event:
			if( T::typeid != bool::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::InterfaceTimings:
			if( T::typeid != InterfaceTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::Occlusion:
			if( T::typeid != Int32::typeid && T::typeid != UInt32::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::PipelineTimings:
			if( T::typeid != PipelineTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::ResourceManager:
			if( T::typeid != ResourceManager::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::Timestamp:
			if( T::typeid != Int64::typeid && T::typeid != UInt64::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::TimestampDisjoint:
			if( T::typeid != bool::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::TimestampFreq:
			if( T::typeid != Int64::typeid && T::typeid != UInt64::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::VCache:
			if( T::typeid != VCache::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::VertexStats:
			if( T::typeid != VertexStats::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		case QueryType::VertexTimings:
			if( T::typeid != StageTimings::typeid )
				hr = D3DERR_INVALIDCALL;
			break;

		}

		GraphicsException::CheckHResult( hr );

		DWORD flags = flush ? D3DGETDATA_FLUSH : 0;

		//get the actual data now
		if( type == QueryType::Event || type == QueryType::TimestampDisjoint )
		{
			//need to marshal BOOL (int) to bool
			BOOL value = FALSE;
			hr = m_Pointer->GetData( &value, sizeof(BOOL), flags );
			GraphicsException::CheckHResult( hr );
			//we know that T is a bool, but the runtime does not
			return (T) (value > 0);
		}
		else
		{
			T data;
			hr = m_Pointer->GetData( &data, Marshal::SizeOf( T::typeid ), flags );
			GraphicsException::CheckHResult( hr );
			return data;
		}
	}
}
}

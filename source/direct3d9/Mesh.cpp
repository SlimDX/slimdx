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
#include <vcclr.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "../DataStream.h"

#include "Device.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Buffer.h"
#include "Mesh.h"

namespace SlimDX
{
namespace Direct3D9
{
	//Utility function to convert from D3D color to SlimDX color. Can't put it in ColorValue because
	//that thing is shared between D3D 9 and D3D 10.
	ColorValue ConvertColor( const D3DCOLORVALUE& color )
	{
		ColorValue cv;
		cv.Red = color.r;
		cv.Green = color.g;
		cv.Blue = color.b;
		cv.Alpha = color.a;

		return cv;
	}

	D3DCOLORVALUE ConvertColor( ColorValue color )
	{
		D3DCOLORVALUE cv;
		cv.r = color.Red;
		cv.g = color.Green;
		cv.b = color.Blue;
		cv.a = color.Alpha;

		return cv;
	}

	D3DXMATERIAL ExtendedMaterial::ToUnmanaged( ExtendedMaterial material )
	{
		D3DXMATERIAL result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( material.TextureFilename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		result.pTextureFilename = reinterpret_cast<LPSTR>( pinnedName );
		result.MatD3D.Ambient = ConvertColor( material.MaterialD3D.Ambient );
		result.MatD3D.Diffuse = ConvertColor( material.MaterialD3D.Diffuse );
		result.MatD3D.Specular = ConvertColor( material.MaterialD3D.Specular );
		result.MatD3D.Emissive = ConvertColor( material.MaterialD3D.Emissive );
		result.MatD3D.Power = material.MaterialD3D.Power;

		return result;
	}

	ExtendedMaterial ExtendedMaterial::FromUnmanaged( const D3DXMATERIAL &material )
	{
		ExtendedMaterial result;
		result.MaterialD3D.Diffuse = ConvertColor( material.MatD3D.Diffuse );
		result.MaterialD3D.Ambient = ConvertColor( material.MatD3D.Ambient );
		result.MaterialD3D.Specular = ConvertColor( material.MatD3D.Specular );
		result.MaterialD3D.Emissive = ConvertColor( material.MatD3D.Emissive );
		result.MaterialD3D.Power = material.MatD3D.Power;
		result.TextureFilename = gcnew String( material.pTextureFilename );

		return result;
	}

	array<ExtendedMaterial>^ ExtendedMaterial::FromBuffer( ID3DXBuffer* buffer, unsigned int count )
	{
		const D3DXMATERIAL* source  = reinterpret_cast<const D3DXMATERIAL*>( buffer->GetBufferPointer() );

		array<ExtendedMaterial>^ dest = gcnew array<ExtendedMaterial>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			Material m;
			m.Diffuse = ConvertColor( source[i].MatD3D.Diffuse );
			m.Ambient = ConvertColor( source[i].MatD3D.Ambient );
			m.Specular = ConvertColor( source[i].MatD3D.Specular );
			m.Emissive = ConvertColor( source[i].MatD3D.Emissive );
			m.Power = source[i].MatD3D.Power;
			dest[i].MaterialD3D = m;
			dest[i].TextureFilename = gcnew String( source[i].pTextureFilename );
		}

		return dest;
	}

	EffectInstance EffectInstance::FromUnmanaged( const D3DXEFFECTINSTANCE &effect )
	{
		EffectInstance result;

		result.EffectFilename = gcnew String( effect.pEffectFilename );
		result.Defaults = gcnew array<EffectDefault>( effect.NumDefaults );

		for( unsigned int i = 0; i < effect.NumDefaults; i++ )
		{
			result.Defaults[i].ParameterName = gcnew String( effect.pDefaults[i].pParamName );
			result.Defaults[i].Type = static_cast<EffectDefaultType>( effect.pDefaults[i].Type );
			result.Defaults[i].Value = gcnew DataStream( effect.pDefaults[i].pValue, effect.pDefaults[i].NumBytes, true, false, true );
		}

		return result;
	}

	D3DXEFFECTINSTANCE EffectInstance::ToUnmanaged( EffectInstance effect )
	{
		D3DXEFFECTINSTANCE result;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( effect.EffectFilename );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		int count = effect.Defaults->Length;

		result.pEffectFilename = reinterpret_cast<LPSTR>( pinnedName );
		result.pDefaults = new D3DXEFFECTDEFAULT[count];

		for( int i = 0; i < effect.Defaults->Length; i++ )
		{
			array<unsigned char>^ nameBytes2 = System::Text::ASCIIEncoding::ASCII->GetBytes( effect.Defaults[i].ParameterName );
			pin_ptr<unsigned char> pinnedName2 = &nameBytes2[0];

			result.pDefaults[i].pParamName = reinterpret_cast<LPSTR>( pinnedName2 );
			result.pDefaults[i].Type = static_cast<D3DXEFFECTDEFAULTTYPE>( effect.Defaults[i].Type );
			result.pDefaults[i].NumBytes = static_cast<DWORD>( effect.Defaults[i].Value->Length );
			result.pDefaults[i].pValue = effect.Defaults[i].Value->RawPointer;
		}

		return result;
	}

	array<EffectInstance>^ EffectInstance::FromBuffer( ID3DXBuffer* buffer, unsigned int count )
	{
		const D3DXEFFECTINSTANCE* source  = reinterpret_cast<const D3DXEFFECTINSTANCE*>( buffer->GetBufferPointer() );

		array<EffectInstance>^ dest = gcnew array<EffectInstance>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			dest[i].EffectFilename = gcnew String( source[i].pEffectFilename );
			dest[i].Defaults = gcnew array<EffectDefault>( source[i].NumDefaults );
			for( unsigned int x = 0; x < source[i].NumDefaults; ++x )
			{
				dest[i].Defaults[x].ParameterName = gcnew String( source[i].pDefaults[x].pParamName );
				dest[i].Defaults[x].Type = static_cast<EffectDefaultType>( source[i].pDefaults[x].Type );
				dest[i].Defaults[x].Value = gcnew DataStream( source[i].pDefaults[x].pValue, source[i].pDefaults[x].NumBytes, true, false, true );
			}
		}

		return dest;
	}

	StreamShim::StreamShim( Stream^ stream )
	{
		m_WrappedStream = stream;
		position = -1;
	}

	void StreamShim::SetSizeToPosition()
	{
		if( position != -1 )
		{
			if( position > m_WrappedStream->Length )
				m_WrappedStream->SetLength( position );
			m_WrappedStream->Position = position;
			position = -1;
		}
	}

	void StreamShim::Clone( [Out] System::Runtime::InteropServices::ComTypes::IStream^% ppstm )
	{
		ppstm = nullptr;
		throw gcnew ExternalException( nullptr, STG_E_INVALIDFUNCTION );
	}

	void StreamShim::Commit( int grfCommitFlags )
	{
		m_WrappedStream->Flush();
	}

	void StreamShim::CopyTo( System::Runtime::InteropServices::ComTypes::IStream^ pstm, long long cb, IntPtr pcbRead, IntPtr pcbWritten )
	{
		array<unsigned char>^ buffer = gcnew array<unsigned char>( 4096 );
		long long written = 0;
		int read;

		if( cb != 0 )
		{
			SetSizeToPosition();

			do
			{
				int count = 4096;
				if( written + 4096 > cb )
					count = (int)( cb - written );

				read = m_WrappedStream->Read( buffer, 0, count );
				if( read == 0 )
					break;

				pstm->Write( buffer, read, IntPtr::Zero );
				written += read;

			} while( written < cb );
		}

		if( pcbRead != IntPtr::Zero )
			Marshal::WriteInt64( pcbRead, written );
		if( pcbWritten != IntPtr::Zero )
			Marshal::WriteInt64( pcbWritten, written );
	}

	void StreamShim::LockRegion( long long libOffset, long long cb, int dwLockType )
	{
		throw gcnew ExternalException( nullptr, STG_E_INVALIDFUNCTION );
	}

	void StreamShim::Read( [Out] array<unsigned char>^ pv, int cb, IntPtr pcbRead )
	{
		int read = 0;

		if( cb != 0 )
		{
			SetSizeToPosition();
			read = m_WrappedStream->Read( pv, 0, cb );
		}

		if( pcbRead != IntPtr::Zero )
			Marshal::WriteInt32( pcbRead, read );
	}

	void StreamShim::Revert()
	{
		throw gcnew ExternalException( nullptr, STG_E_INVALIDFUNCTION );
	}

	void StreamShim::Seek( long long dlibMove, int dwOrigin, IntPtr plibNewPosition )
	{
		long long newPosition;

		if( m_WrappedStream->CanWrite )
		{
			SeekOrigin origin = static_cast<SeekOrigin>( dwOrigin );
			if( origin == SeekOrigin::Begin )
				newPosition = dlibMove;
			else if( origin == SeekOrigin::Current )
			{
				newPosition = position;
				if( newPosition == -1 )
					newPosition = m_WrappedStream->Position;
				newPosition += dlibMove;
			}
			else if( origin == SeekOrigin::End )
				newPosition = m_WrappedStream->Length + dlibMove;
			else
				throw gcnew ExternalException( nullptr, STG_E_INVALIDFUNCTION );

			if( newPosition > m_WrappedStream->Length )
				position = newPosition;
			else
			{
				m_WrappedStream->Position = newPosition;
				position = -1;
			}
		}
		else
		{
			try
			{
				newPosition = m_WrappedStream->Seek( dlibMove, static_cast<SeekOrigin>( dwOrigin ) );
			}
			catch( ArgumentException^ )
			{
				throw gcnew ExternalException( nullptr, STG_E_INVALIDFUNCTION );
			}

			position = -1;
		}

		if( plibNewPosition != IntPtr::Zero )
			Marshal::WriteInt64( plibNewPosition, newPosition );
	}

	void StreamShim::SetSize( long long libNewSize )
	{
		m_WrappedStream->SetLength( libNewSize );
	}

	void StreamShim::Stat( [Out] System::Runtime::InteropServices::ComTypes::STATSTG% pstatstg, int grfStatFlag )
	{
		pstatstg = System::Runtime::InteropServices::ComTypes::STATSTG();
		pstatstg.cbSize = m_WrappedStream->Length;
	}

	void StreamShim::UnlockRegion( long long libOffset, long long cb, int dwLockType )
	{
		throw gcnew ExternalException( nullptr, STG_E_INVALIDFUNCTION );
	}

	void StreamShim::Write( array<unsigned char>^ pv, int cb, IntPtr pcbWritten )
	{
		if( cb != 0 )
		{
			SetSizeToPosition();
			m_WrappedStream->Write( pv, 0, cb );
		}

		if( pcbWritten != IntPtr::Zero )
			Marshal::WriteInt32( pcbWritten, cb );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements )
	{
		ID3DXMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &elements[0];

		HRESULT hr = m_Pointer->CloneMesh( static_cast<DWORD>( flags ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinned_elements ),
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = m_Pointer->CloneMeshFVF( static_cast<DWORD>( flags ), static_cast<DWORD>( fvf ), 
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( mesh );
	}

	void BaseMesh::DrawSubset( int subset )
	{
		HRESULT hr = m_Pointer->DrawSubset( subset );
		GraphicsException::CheckHResult( hr );
	}

	Device^ BaseMesh::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	IndexBuffer^ BaseMesh::GetIndexBuffer()
	{
		IDirect3DIndexBuffer9* ib;
		HRESULT hr = m_Pointer->GetIndexBuffer( &ib );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew IndexBuffer( ib );
	}

	VertexBuffer^ BaseMesh::GetVertexBuffer()
	{
		IDirect3DVertexBuffer9* vb;
		HRESULT hr = m_Pointer->GetVertexBuffer( &vb );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew VertexBuffer( vb );
	}

	array<VertexElement>^ BaseMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];
		HRESULT hr = m_Pointer->GetDeclaration( elementBuffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		// Apparently the returned decl does not include an End element. This is bizarre and confusing,
		// not to mention completely unexpected. We patch it up here.
		int count = D3DXGetDeclLength( elementBuffer ) + 1;
		array<VertexElement>^ elements = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedElements = &elements[0];
		memcpy( pinnedElements, elementBuffer, count * sizeof(D3DVERTEXELEMENT9) );
		elements[count - 1] = VertexElement::VertexDeclarationEnd;

		return elements;
	}

	array<AttributeRange>^ BaseMesh::GetAttributeTable()
	{
		DWORD count = 0;
		HRESULT hr = m_Pointer->GetAttributeTable( NULL, &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		array<AttributeRange>^ attribTable = gcnew array<AttributeRange>( count );
		pin_ptr<AttributeRange> pinnedTable = &attribTable[0];
		hr = m_Pointer->GetAttributeTable( reinterpret_cast<D3DXATTRIBUTERANGE*>( pinnedTable ), &count );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return attribTable;
	}

	DataStream^ BaseMesh::LockIndexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = m_Pointer->LockIndexBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		// determine the size of the buffer
		int size = 6 * FaceCount;
		if( (CreationOptions & MeshFlags::Use32Bit) == MeshFlags::Use32Bit )
			size *= 2;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	void BaseMesh::UnlockIndexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockIndexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ BaseMesh::LockVertexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = m_Pointer->LockVertexBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		// determine the size of the buffer
		int size = BytesPerVertex * VertexCount;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly, false );
	}

	void BaseMesh::UnlockVertexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockVertexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	array<int>^ BaseMesh::GenerateAdjacency( float epsilon )
	{
		// allocate the array to write the adjacency into
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = m_Pointer->GenerateAdjacency( epsilon, reinterpret_cast<DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	array<int>^ BaseMesh::ConvertAdjacencyToPointReps( array<int>^ adjacency )
	{
		array<int>^ points = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<int> pinnedPoints = &points[0];

		HRESULT hr = m_Pointer->ConvertAdjacencyToPointReps( reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<DWORD*>( pinnedPoints ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return points;
	}

	array<int>^ BaseMesh::ConvertPointRepsToAdjacency( array<int>^ points )
	{
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<int> pinnedPoints = &points[0];

		HRESULT hr = m_Pointer->ConvertPointRepsToAdjacency( reinterpret_cast<const DWORD*>( pinnedPoints ),
			reinterpret_cast<DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	void BaseMesh::UpdateSemantics( array<VertexElement>^ elements )
	{
		pin_ptr<VertexElement> pinnedElements = &elements[0];

		HRESULT hr = m_Pointer->UpdateSemantics( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ) );
		GraphicsException::CheckHResult( hr );
	}

	int BaseMesh::FaceCount::get()
	{
		return m_Pointer->GetNumFaces();
	}

	int BaseMesh::VertexCount::get()
	{
		return m_Pointer->GetNumVertices();
	}

	SlimDX::Direct3D9::VertexFormat BaseMesh::VertexFormat::get()
	{
		return static_cast<SlimDX::Direct3D9::VertexFormat>( m_Pointer->GetFVF() );
	}

	int BaseMesh::BytesPerVertex::get()
	{
		return m_Pointer->GetNumBytesPerVertex();
	}

	MeshFlags BaseMesh::CreationOptions::get()
	{
		return static_cast<MeshFlags>( m_Pointer->GetOptions() );
	}

	Mesh::Mesh( ID3DXMesh* mesh ) : BaseMesh( mesh )
	{
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, array<VertexElement>^ vertexDecl )
	{
		ID3DXMesh* mesh;
		pin_ptr<VertexElement> pinnedDecl = &vertexDecl[0];

		HRESULT hr = D3DXCreateMesh( numFaces, numVertices, static_cast<DWORD>( options ),
			reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ), device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = mesh;
	}

	Mesh::Mesh( Device^ device, int numFaces, int numVertices, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh* mesh;

		HRESULT hr = D3DXCreateMeshFVF( numFaces, numVertices, static_cast<DWORD>( options ), 
			static_cast<DWORD>( fvf ), device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = mesh;
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] BufferWrapper^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		adjacency = gcnew BufferWrapper( adjacencyBuffer );
		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		// figure out how many effect instances there are, and get them out of the buffer
		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ),
			device->InternalPointer, NULL, &materialBuffer, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, static_cast<DWORD>( flags ),
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] BufferWrapper^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, adjacency, materials, effectInstances );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, materials, effectInstances );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, materials );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] BufferWrapper^% adjacency,
		[Out] array<ExtendedMaterial>^% materials, [Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* adjacencyBuffer;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromX( pinnedFileName, static_cast<DWORD>( flags ), device->InternalPointer,
			&adjacencyBuffer, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			adjacency = nullptr;
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		adjacency = gcnew BufferWrapper( adjacencyBuffer );
		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials,
		[Out] array<EffectInstance>^% effectInstances )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		ID3DXBuffer* instanceBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromX( pinnedFileName, static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, &instanceBuffer, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
		{
			materials = nullptr;
			effectInstances = nullptr;
			return nullptr;
		}

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );

		DWORD instanceCount = 0;
		hr = mesh->GetAttributeTable( NULL, &instanceCount );
		effectInstances = EffectInstance::FromBuffer( instanceBuffer, instanceCount );

		materialBuffer->Release();
		instanceBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<ExtendedMaterial>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuffer;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromXW( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( flags ), device->InternalPointer,
			NULL, &materialBuffer, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );

		materials = ExtendedMaterial::FromBuffer( materialBuffer, materialCount );
		materialBuffer->Release();

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadMeshFromXW( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( flags ), 
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	void Mesh::ComputeTangentFrame( TangentOptions options )
	{
		HRESULT hr = D3DXComputeTangentFrame( MeshPointer, static_cast<DWORD>( options ) );
		GraphicsException::CheckHResult( hr );
	}

	ProgressiveMesh^ ProgressiveMesh::CloneProgressive( Device^ device, MeshFlags flags, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &vertexDeclaration[0];

		HRESULT hr = MeshPointer->ClonePMesh( static_cast<DWORD>( flags ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinned_elements ),
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew ProgressiveMesh( mesh );
	}

	ProgressiveMesh^ ProgressiveMesh::CloneProgressive( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat format )
	{
		ID3DXPMesh* mesh;

		HRESULT hr = MeshPointer->ClonePMeshFVF( static_cast<DWORD>( flags ), static_cast<DWORD>( format ), 
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew ProgressiveMesh( mesh );
	}

	void ProgressiveMesh::GenerateVertexHistory( array<int>^ vertexHistory )
	{
		pin_ptr<int> pinned = &vertexHistory[0];

		HRESULT hr = MeshPointer->GenerateVertexHistory( reinterpret_cast<DWORD*>( pinned ) );
		GraphicsException::CheckHResult( hr );
	}

	array<int>^ ProgressiveMesh::GetAdjacency()
	{
		array<int>^ adjacency = gcnew array<int>( 3 * MaximumFaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = MeshPointer->GetAdjacency( reinterpret_cast<DWORD*>( pinnedAdj ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	Mesh^ ProgressiveMesh::Optimize( MeshOptimizeFlags flags )
	{
		ID3DXMesh *result;

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), NULL, NULL, NULL, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ ProgressiveMesh::Optimize( MeshOptimizeFlags flags, [Out] array<int>^% adjacencyOut )
	{
		ID3DXMesh *result;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedAdj ), NULL, NULL, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Mesh( result );
	}

	Mesh^ ProgressiveMesh::Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] BufferWrapper^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), NULL, reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = gcnew BufferWrapper( buffer );
		return gcnew Mesh( result );
	}

	Mesh^ ProgressiveMesh::Optimize( MeshOptimizeFlags flags, [Out] array<int>^% adjacencyOut, [Out] array<int>^% faceRemap, [Out] BufferWrapper^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedAdj ), \
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = gcnew BufferWrapper( buffer );
		return gcnew Mesh( result );
	}

	void ProgressiveMesh::OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags )
	{
		HRESULT hr = MeshPointer->OptimizeBaseLOD( static_cast<DWORD>( flags ), NULL );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap )
	{
		pin_ptr<int> pinnedFR = &faceRemap[0];
		HRESULT hr = MeshPointer->OptimizeBaseLOD( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedFR ) );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::Save( Stream^ stream, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effects )
	{
		StreamShim^ shim = gcnew StreamShim( stream );
		pin_ptr<StreamShim^> nativeStream = &shim;

		D3DXMATERIAL *nativeMaterials = new D3DXMATERIAL[materials->Length];
		for( int i = 0; i < materials->Length; i++ )
			nativeMaterials[i] = ExtendedMaterial::ToUnmanaged( materials[i] );

		D3DXEFFECTINSTANCE *nativeEffects = new D3DXEFFECTINSTANCE[effects->Length];
		for( int i = 0; i < effects->Length; i++ )
			nativeEffects[i] = EffectInstance::ToUnmanaged( effects[i] );

		HRESULT hr = MeshPointer->Save( reinterpret_cast<IStream*>( nativeStream ), nativeMaterials, nativeEffects, materials->Length );
		GraphicsException::CheckHResult( hr );

		delete[] nativeMaterials;
		delete[] nativeEffects;
	}

	void ProgressiveMesh::SetFaceCount( int faceCount )
	{
		HRESULT hr = MeshPointer->SetNumFaces( faceCount );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::SetVertexCount( int vertexCount )
	{
		HRESULT hr = MeshPointer->SetNumVertices( vertexCount );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::TrimFaces( int newFaceMinimum, int newFaceMaximum )
	{
		HRESULT hr = MeshPointer->TrimByFaces( newFaceMinimum, newFaceMaximum, NULL, NULL );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::TrimFaces( int newFaceMinimum, int newFaceMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = MeshPointer->TrimByFaces( newFaceMinimum, newFaceMaximum, reinterpret_cast<DWORD*>( pinnedFR ), 
			reinterpret_cast<DWORD*>( pinnedVR ) );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::TrimVertices( int newVertexMinimum, int newVertexMaximum )
	{
		HRESULT hr = MeshPointer->TrimByVertices( newVertexMinimum, newVertexMaximum, NULL, NULL );
		GraphicsException::CheckHResult( hr );
	}

	void ProgressiveMesh::TrimVertices( int newVertexMinimum, int newVertexMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = MeshPointer->TrimByVertices( newVertexMinimum, newVertexMaximum, reinterpret_cast<DWORD*>( pinnedFR ), 
			reinterpret_cast<DWORD*>( pinnedVR ) );
		GraphicsException::CheckHResult( hr );
	}

	int ProgressiveMesh::MaximumFaceCount::get()
	{
		return MeshPointer->GetMaxFaces();
	}

	int ProgressiveMesh::MaximumVertexCount::get()
	{
		return MeshPointer->GetMaxVertices();
	}

	int ProgressiveMesh::MinimumFaceCount::get()
	{
		return MeshPointer->GetMinFaces();
	}

	int ProgressiveMesh::MinimumVertexCount::get()
	{
		return MeshPointer->GetMinVertices();
	}

	PatchMesh::PatchMesh( Device^ device, PatchInfo info, int patchCount, int vertexCount, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPatchMesh *result;
		pin_ptr<VertexElement> pinnedElements = &vertexDeclaration[0];

		HRESULT hr = D3DXCreatePatchMesh( reinterpret_cast<D3DXPATCHINFO*>( &info ), patchCount, vertexCount, 0, 
			reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ), device->InternalPointer, &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
	}

	PatchMesh^ PatchMesh::Clone( MeshFlags flags, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPatchMesh *result;
		pin_ptr<VertexElement> pinnedElements = &vertexDeclaration[0];

		HRESULT hr = m_Pointer->CloneMesh( static_cast<DWORD>( flags ), reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedElements ), &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew PatchMesh( result );
	}

	void PatchMesh::GenerateAdjacency( float tolerance )
	{
		HRESULT hr = m_Pointer->GenerateAdjacency( tolerance );
		GraphicsException::CheckHResult( hr );
	}

	array<VertexElement>^ PatchMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];

		HRESULT hr = m_Pointer->GetDeclaration( elementBuffer );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		// Apparently the returned decl does not include an End element. This is bizarre and confusing,
		// not to mention completely unexpected. We patch it up here.
		int count = D3DXGetDeclLength( elementBuffer ) + 1;
		array<VertexElement>^ elements = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedElements = &elements[0];
		memcpy( pinnedElements, elementBuffer, count * sizeof(D3DVERTEXELEMENT9) );
		elements[count - 1] = VertexElement::VertexDeclarationEnd;

		return elements;
	}

	Device^ PatchMesh::GetDevice()
	{
		IDirect3DDevice9* device;

		HRESULT hr = m_Pointer->GetDevice( &device );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	IndexBuffer^ PatchMesh::GetIndexBuffer()
	{
		IDirect3DIndexBuffer9* ib;

		HRESULT hr = m_Pointer->GetIndexBuffer( &ib );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew IndexBuffer( ib );
	}

	VertexBuffer^ PatchMesh::GetVertexBuffer()
	{
		IDirect3DVertexBuffer9* vb;

		HRESULT hr = m_Pointer->GetVertexBuffer( &vb );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew VertexBuffer( vb );
	}

	PatchInfo PatchMesh::GetPatchInfo()
	{
		PatchInfo result;

		HRESULT hr = m_Pointer->GetPatchInfo( reinterpret_cast<D3DXPATCHINFO*>( &result ) );
		GraphicsException::CheckHResult( hr );

		return result;
	}

	void PatchMesh::Optimize()
	{
		HRESULT hr = m_Pointer->Optimize( 0 );
		GraphicsException::CheckHResult( hr );
	}

	DisplacementParameters PatchMesh::GetDisplacementParameters()
	{
		DisplacementParameters result;
		IDirect3DBaseTexture9 *texture;
		D3DTEXTUREFILTERTYPE minFilter;
		D3DTEXTUREFILTERTYPE magFilter;
		D3DTEXTUREFILTERTYPE mipFilter;
		D3DTEXTUREADDRESS wrap;
		DWORD lodBias;

		HRESULT hr = m_Pointer->GetDisplaceParam( &texture, &minFilter, &magFilter, &mipFilter, &wrap, &lodBias );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return result;

		result.Texture = gcnew Texture( reinterpret_cast<IDirect3DTexture9*>( texture ) );
		result.MinFilter = static_cast<TextureFilter>( minFilter );
		result.MagFilter = static_cast<TextureFilter>( magFilter );
		result.MipFilter = static_cast<TextureFilter>( mipFilter );
		result.Wrap = static_cast<TextureAddress>( wrap );
		result.LevelOfDetailBias = lodBias;

		return result;
	}

	void PatchMesh::SetDisplacementParameters( DisplacementParameters parameters )
	{
		HRESULT hr = m_Pointer->SetDisplaceParam( reinterpret_cast<IDirect3DTexture9*>( parameters.Texture->InternalPointer ), 
			static_cast<D3DTEXTUREFILTERTYPE>( parameters.MinFilter ), static_cast<D3DTEXTUREFILTERTYPE>( parameters.MagFilter ),
			static_cast<D3DTEXTUREFILTERTYPE>( parameters.MipFilter ), static_cast<D3DTEXTUREADDRESS>( parameters.Wrap ), parameters.LevelOfDetailBias );
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ PatchMesh::LockAttributeBuffer( LockFlags flags )
	{
		DWORD *data;

		HRESULT hr = m_Pointer->LockAttributeBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, 0, true, !readOnly, false );
	}

	void PatchMesh::UnlockAttributeBuffer()
	{
		HRESULT hr = m_Pointer->UnlockAttributeBuffer();
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ PatchMesh::LockIndexBuffer( LockFlags flags )
	{
		void *data;

		HRESULT hr = m_Pointer->LockIndexBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, 0, true, !readOnly, false );
	}

	void PatchMesh::UnlockIndexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockIndexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ PatchMesh::LockVertexBuffer( LockFlags flags )
	{
		void *data;

		HRESULT hr = m_Pointer->LockVertexBuffer( static_cast<DWORD>( flags ), &data );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, 0, true, !readOnly, false );
	}

	void PatchMesh::UnlockVertexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockVertexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	void PatchMesh::GetTessellationSize( float tessellationLevel, bool adaptive, [Out] int% triangleCount, [Out] int% vertexCount )
	{
		pin_ptr<int> pinnedTriCount = &triangleCount;
		pin_ptr<int> pinnedVertexCount = &vertexCount;

		HRESULT hr = m_Pointer->GetTessSize( tessellationLevel, adaptive, reinterpret_cast<DWORD*>( pinnedTriCount ), 
			reinterpret_cast<DWORD*>( pinnedVertexCount ) );
		GraphicsException::CheckHResult( hr );
	}

	void PatchMesh::Tessellate( float tessellationLevel, Mesh^ mesh )
	{
		HRESULT hr = m_Pointer->Tessellate( tessellationLevel, reinterpret_cast<ID3DXMesh*>( mesh->InternalPointer ) );
		GraphicsException::CheckHResult( hr );
	}

	void PatchMesh::Tessellate( Vector4 translation, int minimumLevel, int maximumLevel, Mesh^ mesh )
	{
		HRESULT hr = m_Pointer->TessellateAdaptive( reinterpret_cast<D3DXVECTOR4*>( &translation ), maximumLevel, minimumLevel, 
			reinterpret_cast<ID3DXMesh*>( mesh->InternalPointer ) );
		GraphicsException::CheckHResult( hr );
	}

	int PatchMesh::ControlVerticesPerPatch::get()
	{
		return m_Pointer->GetControlVerticesPerPatch();
	}

	int PatchMesh::PatchCount::get()
	{
		return m_Pointer->GetNumPatches();
	}

	int PatchMesh::VertexCount::get()
	{
		return m_Pointer->GetNumVertices();
	}

	PatchMeshType PatchMesh::Type::get()
	{
		return static_cast<PatchMeshType>( m_Pointer->GetOptions() );
	}
}
}
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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "../DirectXObject.h"
#include "../Utils.h"
#include "../DataStream.h"

#include "Device.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Mesh.h"

namespace SlimDX
{
namespace Direct3D9
{
	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements )
	{
		ID3DXMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &elements[0];

		HRESULT hr = m_Pointer->CloneMesh( (DWORD) flags, (const D3DVERTEXELEMENT9*) pinned_elements,
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

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

	DataStream^ BaseMesh::LockIndexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = m_Pointer->LockIndexBuffer( (DWORD) flags, &data );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		//determine the size of the buffer
		int size = 6 * FaceCount;
		if( (CreationOptions & MeshFlags::Use32Bit) == MeshFlags::Use32Bit )
			size *= 2;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly );
	}

	void BaseMesh::UnlockIndexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockIndexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	DataStream^ BaseMesh::LockVertexBuffer( LockFlags flags )
	{
		void* data;
		HRESULT hr = m_Pointer->LockVertexBuffer( (DWORD) flags, &data );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		//determine the size of the buffer
		int size = BytesPerVertex * VertexCount;

		bool readOnly = (flags & LockFlags::ReadOnly) == LockFlags::ReadOnly;
		return gcnew DataStream( data, size, true, !readOnly );
	}

	void BaseMesh::UnlockVertexBuffer()
	{
		HRESULT hr = m_Pointer->UnlockVertexBuffer();
		GraphicsException::CheckHResult( hr );
	}

	array<int>^ BaseMesh::GenerateAdjacency( float epsilon )
	{
		//allocate the array to write the adjacency into
		array<int>^ adjacency = gcnew array<int>( 3 * FaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = m_Pointer->GenerateAdjacency( epsilon, (DWORD*) pinnedAdj );
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

		HRESULT hr = m_Pointer->ConvertAdjacencyToPointReps( (const DWORD*) pinnedAdj, (DWORD*) pinnedPoints );
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

		HRESULT hr = m_Pointer->ConvertPointRepsToAdjacency( (const DWORD*) pinnedPoints, (DWORD*) pinnedAdj );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
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
		return (SlimDX::Direct3D9::VertexFormat) m_Pointer->GetFVF();
	}

	int BaseMesh::BytesPerVertex::get()
	{
		return m_Pointer->GetNumBytesPerVertex();
	}

	MeshFlags BaseMesh::CreationOptions::get()
	{
		return (MeshFlags) m_Pointer->GetOptions();
	}

	Mesh::Mesh( ID3DXMesh* mesh ) : BaseMesh( mesh )
	{
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags, [Out] array<Material>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuf;
		DWORD materialCount;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, (DWORD) flags,
			device->InternalPointer, NULL, &materialBuf, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );

		materials = gcnew array<Material>( materialCount );
		pin_ptr<Material> pinnedMaterials = &materials[0];
		memcpy( pinnedMaterials, materialBuf->GetBufferPointer(), materialBuf->GetBufferSize() );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromMemory( Device^ device, array<Byte>^ memory, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<unsigned char> pinnedMemory = &memory[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinnedMemory, memory->Length, (DWORD) flags,
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, [Out] array<Material>^% materials )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags, materials );
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Mesh::FromMemory( device, data, flags );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags, [Out] array<Material>^% materials )
	{
		ID3DXMesh* mesh;
		ID3DXBuffer* materialBuf;
		DWORD materialCount;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		
		HRESULT hr = D3DXLoadMeshFromXW( (LPCWSTR) pinnedName, (DWORD) flags, device->InternalPointer,
			NULL, &materialBuf, NULL, &materialCount, &mesh );
		GraphicsException::CheckHResult( hr );

		materials = gcnew array<Material>( materialCount );
		pin_ptr<Material> pinnedMaterials = &materials[0];
		memcpy( pinnedMaterials, materialBuf->GetBufferPointer(), materialBuf->GetBufferSize() );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadMeshFromXW( (LPCWSTR) pinnedName, (DWORD) flags, 
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	void Mesh::ComputeTangentFrame( TangentOptions options )
	{
		HRESULT hr = D3DXComputeTangentFrame( MeshPointer, (DWORD) options );
		GraphicsException::CheckHResult( hr );
	}
}
}
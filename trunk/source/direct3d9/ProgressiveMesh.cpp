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
#include "ProgressiveMesh.h"

namespace SlimDX
{
namespace Direct3D9
{
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

	ProgressiveMesh::ProgressiveMesh( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights,
		array<float>^ vertexWeights, int minimumValue, MeshSimplification options )
	{
		ID3DXPMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<float> pinnedVW = &vertexWeights[0];
		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXGeneratePMesh( mesh->MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), reinterpret_cast<const FLOAT*>( pinnedVW ),
			minimumValue, static_cast<DWORD>( options ), &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
	}

	ProgressiveMesh::ProgressiveMesh( Mesh^ mesh, array<int>^ adjacency, array<AttributeWeights>^ attributeWeights,
		int minimumValue, MeshSimplification options )
	{
		ID3DXPMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];
		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXGeneratePMesh( mesh->MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ),
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), NULL,
			minimumValue, static_cast<DWORD>( options ), &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
	}

	ProgressiveMesh::ProgressiveMesh( Mesh^ mesh, array<int>^ adjacency, int minimumValue, MeshSimplification options )
	{
		ID3DXPMesh *result;

		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = D3DXGeneratePMesh( mesh->MeshPointer, reinterpret_cast<const DWORD*>( pinnedAdj ),
			NULL, NULL, minimumValue, static_cast<DWORD>( options ), &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
	}

	ProgressiveMesh^ ProgressiveMesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags, 
		[Out] BufferWrapper^% materials, [Out] BufferWrapper^% effects, [Out] int% materialCount )
	{
		ID3DXPMesh *result;
		ID3DXBuffer *om;
		ID3DXBuffer *oe;
		DWORD numMaterials;

		StreamShim^ shim = gcnew StreamShim( stream );
		pin_ptr<StreamShim^> nativeStream = &shim;

		HRESULT hr = D3DXCreatePMeshFromStream( reinterpret_cast<IStream*>( nativeStream ), static_cast<DWORD>( flags ),
			device->InternalPointer, &om, &oe, &numMaterials, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			materials = nullptr;
			effects = nullptr;
			materialCount = 0;
			return nullptr;
		}

		materials = gcnew BufferWrapper( om );
		effects = gcnew BufferWrapper( oe );
		materialCount = numMaterials;
		return gcnew ProgressiveMesh( result );
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

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedAdj ),
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
}
}
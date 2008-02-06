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

#include "../ComObject.h"
#include "../Utilities.h"
#include "../DataStream.h"

#include "Device.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
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

	ProgressiveMesh::ProgressiveMesh( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	ProgressiveMesh::ProgressiveMesh( Mesh^ mesh, array<AttributeWeights>^ attributeWeights,
		array<float>^ vertexWeights, int minimumValue, MeshSimplification options )
	{
		ID3DXPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<float> pinnedVW = &vertexWeights[0];
		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXGeneratePMesh( mesh->MeshPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), reinterpret_cast<const FLOAT*>( pinnedVW ),
			minimumValue, static_cast<DWORD>( options ), &result );
		Result::Record( hr );

		Construct(result);
	}

	ProgressiveMesh::ProgressiveMesh( Mesh^ mesh, array<AttributeWeights>^ attributeWeights,
		int minimumValue, MeshSimplification options )
	{
		ID3DXPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<AttributeWeights> pinnedAW = &attributeWeights[0];

		HRESULT hr = D3DXGeneratePMesh( mesh->MeshPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedAW ), NULL,
			minimumValue, static_cast<DWORD>( options ), &result );
		Result::Record( hr );

		Construct(result);
	}

	ProgressiveMesh::ProgressiveMesh( Mesh^ mesh, int minimumValue, MeshSimplification options )
	{
		ID3DXPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXGeneratePMesh( mesh->MeshPointer, adjacencyIn,
			NULL, NULL, minimumValue, static_cast<DWORD>( options ), &result );
		Result::Record( hr );

		Construct(result);
	}

	ProgressiveMesh^ ProgressiveMesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags )
	{
		ID3DXPMesh *result;
		ID3DXBuffer *om;
		ID3DXBuffer *oe;
		DWORD numMaterials;

		StreamShim^ shim = gcnew StreamShim( stream );
		pin_ptr<StreamShim^> nativeStream = &shim;

		HRESULT hr = D3DXCreatePMeshFromStream( reinterpret_cast<IStream*>( nativeStream ), static_cast<DWORD>( flags ),
			device->InternalPointer, &om, &oe, &numMaterials, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;
		
		ProgressiveMesh^ mesh = gcnew ProgressiveMesh( result );

		mesh->SetMaterials( ExtendedMaterial::FromBuffer( om, numMaterials ) );
		mesh->SetEffects( EffectInstance::FromBuffer( oe, numMaterials ) );

		return mesh;
	}

	ProgressiveMesh^ ProgressiveMesh::CloneProgressive( Device^ device, MeshFlags flags, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &vertexDeclaration[0];

		HRESULT hr = MeshPointer->ClonePMesh( static_cast<DWORD>( flags ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinned_elements ),
			device->InternalPointer, &mesh );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew ProgressiveMesh( mesh );
	}

	ProgressiveMesh^ ProgressiveMesh::CloneProgressive( Device^ device, MeshFlags flags, SlimDX::Direct3D9::VertexFormat format )
	{
		ID3DXPMesh* mesh;

		HRESULT hr = MeshPointer->ClonePMeshFVF( static_cast<DWORD>( flags ), static_cast<DWORD>( format ), 
			device->InternalPointer, &mesh );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew ProgressiveMesh( mesh );
	}

	void ProgressiveMesh::GenerateVertexHistory( array<int>^ vertexHistory )
	{
		pin_ptr<int> pinned = &vertexHistory[0];

		HRESULT hr = MeshPointer->GenerateVertexHistory( reinterpret_cast<DWORD*>( pinned ) );
		Result::Record( hr );
	}

	array<int>^ ProgressiveMesh::GetAdjacency()
	{
		array<int>^ adjacency = gcnew array<int>( 3 * MaximumFaceCount );
		pin_ptr<int> pinnedAdj = &adjacency[0];

		HRESULT hr = MeshPointer->GetAdjacency( reinterpret_cast<DWORD*>( pinnedAdj ) );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return adjacency;
	}

	Mesh^ ProgressiveMesh::Optimize( MeshOptimizeFlags flags )
	{
		ID3DXMesh *result;

		array<int>^ adjacencyOut = gcnew array<int>( FaceCount * 3 );
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedAdj ), NULL, NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );
		mesh->SetAdjacency( adjacencyOut );

		return mesh;
	}

	Mesh^ ProgressiveMesh::Optimize( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;
		ID3DXBuffer *buffer;
		faceRemap = gcnew array<int>( FaceCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];

		array<int>^ adjacencyOut = gcnew array<int>( FaceCount * 3 );
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = MeshPointer->Optimize( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedAdj ), 
			reinterpret_cast<DWORD*>( pinnedFR ), &buffer, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		vertexRemap = ( gcnew DataStream( buffer ) )->ReadRange<int>( result->GetNumVertices() );
		
		Mesh^ mesh = gcnew Mesh( result );
		mesh->SetAdjacency( adjacencyOut );

		return mesh;
	}

	void ProgressiveMesh::OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags )
	{
		HRESULT hr = MeshPointer->OptimizeBaseLOD( static_cast<DWORD>( flags ), NULL );
		Result::Record( hr );
	}

	void ProgressiveMesh::OptimizeBaseLevelOfDetail( MeshOptimizeFlags flags, [Out] array<int>^% faceRemap )
	{
		faceRemap = gcnew array<int>( FaceCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];
		HRESULT hr = MeshPointer->OptimizeBaseLOD( static_cast<DWORD>( flags ), reinterpret_cast<DWORD*>( pinnedFR ) );
		Result::Record( hr );
	}

	void ProgressiveMesh::ToStream( ProgressiveMesh^ mesh, Stream^ stream )
	{
		StreamShim^ shim = gcnew StreamShim( stream );
		pin_ptr<StreamShim^> nativeStream = &shim;

		array<ExtendedMaterial>^ materials = mesh->GetMaterials();
		array<EffectInstance>^ effects = mesh->GetEffects();

		D3DXMATERIAL *nativeMaterials = NULL;
		D3DXEFFECTINSTANCE *nativeEffects = NULL;

		if( materials != nullptr )
		{
			nativeMaterials = new D3DXMATERIAL[materials->Length];
			for( int i = 0; i < materials->Length; i++ )
				nativeMaterials[i] = ExtendedMaterial::ToUnmanaged( materials[i] );
		}

		if( effects != nullptr )
		{
			nativeEffects = new D3DXEFFECTINSTANCE[effects->Length];
			for( int i = 0; i < effects->Length; i++ )
				nativeEffects[i] = EffectInstance::ToUnmanaged( effects[i] );
		}

		HRESULT hr = mesh->MeshPointer->Save( reinterpret_cast<IStream*>( nativeStream ), nativeMaterials, nativeEffects, materials->Length );
		Result::Record( hr );

		delete[] nativeMaterials;
		delete[] nativeEffects;
	}

	void ProgressiveMesh::SetFaceCount( int faceCount )
	{
		HRESULT hr = MeshPointer->SetNumFaces( faceCount );
		Result::Record( hr );
	}

	void ProgressiveMesh::SetVertexCount( int vertexCount )
	{
		HRESULT hr = MeshPointer->SetNumVertices( vertexCount );
		Result::Record( hr );
	}

	void ProgressiveMesh::TrimFaces( int newFaceMinimum, int newFaceMaximum )
	{
		HRESULT hr = MeshPointer->TrimByFaces( newFaceMinimum, newFaceMaximum, NULL, NULL );
		Result::Record( hr );
	}

	void ProgressiveMesh::TrimFaces( int newFaceMinimum, int newFaceMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		faceRemap = gcnew array<int>( FaceCount );
		vertexRemap = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = MeshPointer->TrimByFaces( newFaceMinimum, newFaceMaximum, reinterpret_cast<DWORD*>( pinnedFR ), 
			reinterpret_cast<DWORD*>( pinnedVR ) );
		Result::Record( hr );
	}

	void ProgressiveMesh::TrimVertices( int newVertexMinimum, int newVertexMaximum )
	{
		HRESULT hr = MeshPointer->TrimByVertices( newVertexMinimum, newVertexMaximum, NULL, NULL );
		Result::Record( hr );
	}

	void ProgressiveMesh::TrimVertices( int newVertexMinimum, int newVertexMaximum, [Out] array<int>^% faceRemap, [Out] array<int>^% vertexRemap )
	{
		faceRemap = gcnew array<int>( FaceCount );
		vertexRemap = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedFR = &faceRemap[0];
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = MeshPointer->TrimByVertices( newVertexMinimum, newVertexMaximum, reinterpret_cast<DWORD*>( pinnedFR ), 
			reinterpret_cast<DWORD*>( pinnedVR ) );
		Result::Record( hr );
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

	SimplificationMesh::SimplificationMesh( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	SimplificationMesh::SimplificationMesh( Mesh^ mesh, array<AttributeWeights>^ vertexAttributeWeights, array<float>^ vertexWeights )
	{
		ID3DXSPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<AttributeWeights> pinnedVAW = &vertexAttributeWeights[0];
		pin_ptr<float> pinnedVW = &vertexWeights[0];

		HRESULT hr = D3DXCreateSPMesh( mesh->MeshPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedVAW ), reinterpret_cast<const FLOAT *>( pinnedVW ), &result );
		Result::Record( hr );

		Construct(result);
	}

	SimplificationMesh::SimplificationMesh( Mesh^ mesh, array<AttributeWeights>^ vertexAttributeWeights )
	{
		ID3DXSPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<AttributeWeights> pinnedVAW = &vertexAttributeWeights[0];

		HRESULT hr = D3DXCreateSPMesh( mesh->MeshPointer, adjacencyIn,
			reinterpret_cast<const D3DXATTRIBUTEWEIGHTS*>( pinnedVAW ), NULL, &result );
		Result::Record( hr );

		Construct(result);
	}

	SimplificationMesh::SimplificationMesh( Mesh^ mesh, array<float>^ vertexWeights )
	{
		ID3DXSPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		pin_ptr<float> pinnedVW = &vertexWeights[0];

		HRESULT hr = D3DXCreateSPMesh( mesh->MeshPointer, adjacencyIn,
			NULL, reinterpret_cast<const FLOAT *>( pinnedVW ), &result );
		Result::Record( hr );

		Construct(result);
	}

	SimplificationMesh::SimplificationMesh( Mesh^ mesh )
	{
		ID3DXSPMesh *result;

		DWORD *adjacencyIn = NULL;
		pin_ptr<int> pinnedAdj;
		array<int>^ adjacency = mesh->GetAdjacency();

		if( adjacency != nullptr )
		{
			pinnedAdj = &adjacency[0];
			adjacencyIn = reinterpret_cast<DWORD*>( pinnedAdj );
		}

		HRESULT hr = D3DXCreateSPMesh( mesh->MeshPointer, adjacencyIn, NULL, NULL, &result );
		Result::Record( hr );

		Construct(result);
	}

	Mesh^ SimplificationMesh::Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;

		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];
		array<int>^ adjacencyOut = gcnew array<int>( FaceCount * 3 );
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		vertexRemap = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = InternalPointer->CloneMesh( static_cast<DWORD>( options ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedDecl ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedAdj ), reinterpret_cast<DWORD*>( pinnedVR ), &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		Mesh^ mesh = gcnew Mesh( result );
		mesh->SetAdjacency( adjacencyOut );

		return mesh;
	}

	Mesh^ SimplificationMesh::Clone( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXMesh *result;

		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];
		array<int>^ adjacencyOut = gcnew array<int>( FaceCount * 3 );
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = InternalPointer->CloneMesh( static_cast<DWORD>( options ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedDecl ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedAdj ), NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );
		mesh->SetAdjacency( adjacencyOut );

		return mesh;
	}

	Mesh^ SimplificationMesh::Clone( Device^ device, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf, [Out] array<int>^% vertexRemap )
	{
		ID3DXMesh *result;

		array<int>^ adjacencyOut = gcnew array<int>( FaceCount * 3 );
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];
		vertexRemap = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = InternalPointer->CloneMeshFVF( static_cast<DWORD>( options ), static_cast<DWORD>( fvf ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedAdj ), reinterpret_cast<DWORD*>( pinnedVR ), &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		Mesh^ mesh = gcnew Mesh( result );
		mesh->SetAdjacency( adjacencyOut );

		return mesh;
	}

	Mesh^ SimplificationMesh::Clone( Device^ device, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXMesh *result;

		array<int>^ adjacencyOut = gcnew array<int>( FaceCount * 3 );
		pin_ptr<int> pinnedAdj = &adjacencyOut[0];

		HRESULT hr = InternalPointer->CloneMeshFVF( static_cast<DWORD>( options ), static_cast<DWORD>( fvf ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedAdj ), NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		Mesh^ mesh = gcnew Mesh( result );
		mesh->SetAdjacency( adjacencyOut );

		return mesh;
	}

	ProgressiveMesh^ SimplificationMesh::CloneProgressive( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% vertexRemap, [Out] array<float>^% errorsByFace )
	{
		ID3DXPMesh *result;

		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];
		vertexRemap = gcnew array<int>( VertexCount );
		errorsByFace = gcnew array<float>( FaceCount );
		pin_ptr<float> pinnedEBF = &errorsByFace[0];
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = InternalPointer->ClonePMesh( static_cast<DWORD>( options ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedDecl ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedVR ), reinterpret_cast<FLOAT*>( pinnedEBF ), &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			errorsByFace = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		return gcnew ProgressiveMesh( result );
	}

	ProgressiveMesh^ SimplificationMesh::CloneProgressive( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration, [Out] array<int>^% vertexRemap )
	{
		ID3DXPMesh *result;

		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];
		vertexRemap = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = InternalPointer->ClonePMesh( static_cast<DWORD>( options ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedDecl ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedVR ), NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		return gcnew ProgressiveMesh( result );
	}

	ProgressiveMesh^ SimplificationMesh::CloneProgressive( Device^ device, MeshFlags options, array<VertexElement>^ vertexDeclaration )
	{
		ID3DXPMesh *result;

		pin_ptr<VertexElement> pinnedDecl = &vertexDeclaration[0];

		HRESULT hr = InternalPointer->ClonePMesh( static_cast<DWORD>( options ), reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedDecl ),
			device->InternalPointer, NULL, NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew ProgressiveMesh( result );
	}

	ProgressiveMesh^ SimplificationMesh::CloneProgressive( Device^ device, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf, [Out] array<int>^% vertexRemap, [Out] array<float>^% errorsByFace )
	{
		ID3DXPMesh *result;

		vertexRemap = gcnew array<int>( VertexCount );
		errorsByFace = gcnew array<float>( FaceCount );

		pin_ptr<float> pinnedEBF = &errorsByFace[0];
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = InternalPointer->ClonePMeshFVF( static_cast<DWORD>( options ), static_cast<DWORD>( fvf ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedVR ), reinterpret_cast<FLOAT*>( pinnedEBF ), &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			errorsByFace = nullptr;
			vertexRemap = nullptr;
			return nullptr;
		}

		return gcnew ProgressiveMesh( result );
	}

	ProgressiveMesh^ SimplificationMesh::CloneProgressive( Device^ device, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf, [Out] array<int>^% vertexRemap )
	{
		ID3DXPMesh *result;

		vertexRemap = gcnew array<int>( VertexCount );
		pin_ptr<int> pinnedVR = &vertexRemap[0];

		HRESULT hr = InternalPointer->ClonePMeshFVF( static_cast<DWORD>( options ), static_cast<DWORD>( fvf ),
			device->InternalPointer, reinterpret_cast<DWORD*>( pinnedVR ), NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			vertexRemap = nullptr;
			return nullptr;
		}

		return gcnew ProgressiveMesh( result );
	}

	ProgressiveMesh^ SimplificationMesh::CloneProgressive( Device^ device, MeshFlags options, SlimDX::Direct3D9::VertexFormat fvf )
	{
		ID3DXPMesh *result;

		HRESULT hr = InternalPointer->ClonePMeshFVF( static_cast<DWORD>( options ), static_cast<DWORD>( fvf ),
			device->InternalPointer, NULL, NULL, &result );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew ProgressiveMesh( result );
	}

	array<VertexElement>^ SimplificationMesh::GetDeclaration()
	{
		D3DVERTEXELEMENT9 elementBuffer[MAX_FVF_DECL_SIZE];
		HRESULT hr = InternalPointer->GetDeclaration( elementBuffer );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		int count = D3DXGetDeclLength( elementBuffer ) + 1;
		array<VertexElement>^ elements = gcnew array<VertexElement>( count );
		pin_ptr<VertexElement> pinnedElements = &elements[0];
		memcpy( pinnedElements, elementBuffer, count * sizeof(D3DVERTEXELEMENT9) );
		elements[count - 1] = VertexElement::VertexDeclarationEnd;

		return elements;
	}

	Device^ SimplificationMesh::GetDevice()
	{
		IDirect3DDevice9* device;
		HRESULT hr = InternalPointer->GetDevice( &device );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew Device( device );
	}

	array<AttributeWeights>^ SimplificationMesh::GetVertexAttributeWeights()
	{
		array<AttributeWeights>^ results = gcnew array<AttributeWeights>( MaximumVertexCount );
		pin_ptr<AttributeWeights> pinnedResults = &results[0];

		HRESULT hr = InternalPointer->GetVertexAttributeWeights( reinterpret_cast<D3DXATTRIBUTEWEIGHTS*>( pinnedResults ) );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return results;
	}

	array<float>^ SimplificationMesh::GetVertexWeights()
	{
		array<float>^ results = gcnew array<float>( MaximumVertexCount );
		pin_ptr<float> pinnedResults = &results[0];

		HRESULT hr = InternalPointer->GetVertexWeights( reinterpret_cast<FLOAT*>( pinnedResults ) );
		Result::Record( hr );

		if( FAILED( hr ) )
			return nullptr;

		return results;
	}

	void SimplificationMesh::ReduceFaces( int faces )
	{
		HRESULT hr = InternalPointer->ReduceFaces( faces );
		Result::Record( hr );
	}

	void SimplificationMesh::ReduceVertices( int vertices )
	{
		HRESULT hr = InternalPointer->ReduceVertices( vertices );
		Result::Record( hr );
	}

	int SimplificationMesh::MaximumFaceCount::get()
	{
		return InternalPointer->GetMaxFaces();
	}

	int SimplificationMesh::MaximumVertexCount::get()
	{
		return InternalPointer->GetMaxVertices();
	}

	int SimplificationMesh::FaceCount::get()
	{
		return InternalPointer->GetNumFaces();
	}

	int SimplificationMesh::VertexCount::get()
	{
		return InternalPointer->GetNumVertices();
	}

	SlimDX::Direct3D9::VertexFormat SimplificationMesh::VertexFormat::get()
	{
		return static_cast<SlimDX::Direct3D9::VertexFormat>( InternalPointer->GetFVF() );
	}

	MeshFlags SimplificationMesh::CreationOptions::get()
	{
		return static_cast<MeshFlags>( InternalPointer->GetOptions() );
	}
}
}
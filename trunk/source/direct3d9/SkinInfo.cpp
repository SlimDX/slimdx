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

#include "../DataStream.h"
#include "../DirectXObject.h"

#include "Device.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "SkinInfo.h"

namespace SlimDX
{
namespace Direct3D9
{
	D3DXBONECOMBINATION BoneCombination::ToUnmanaged()
	{
		D3DXBONECOMBINATION result;

		result.AttribId = AttributeId;
		result.FaceCount = FaceCount;
		result.FaceStart = FaceStart;
		result.VertexCount = VertexCount;
		result.VertexStart = VertexStart;

		result.BoneId = new DWORD[BoneIds->Length];
		for( int i = 0; i < BoneIds->Length; i++ )
			result.BoneId[i] = BoneIds[i];

		return result;
	}

	SkinInfo::SkinInfo( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXSkinInfo, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXSkinInfo*>( result );
	}

	SkinInfo::SkinInfo( int vertexCount, array<VertexElement>^ vertexDecl, int boneCount )
	{
		ID3DXSkinInfo *result;

		pin_ptr<VertexElement> pinnedDecl = &vertexDecl[0];

		HRESULT hr = D3DXCreateSkinInfo( vertexCount, reinterpret_cast<const D3DVERTEXELEMENT9*>( pinnedDecl ),
			boneCount, &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
	}

	SkinInfo::SkinInfo( BaseMesh^ mesh, int boneCount, array<BoneCombination^>^ boneCombinationTable )
	{
		ID3DXSkinInfo *result;

		int length = boneCombinationTable->Length;
		D3DXBONECOMBINATION *bones = new D3DXBONECOMBINATION[length];
		for( int i = 0; i < length; i++ )
			bones[i] = boneCombinationTable[i]->ToUnmanaged();

		HRESULT hr = D3DXCreateSkinInfoFromBlendedMesh( mesh->InternalPointer, boneCount, bones, &result );
		GraphicsException::CheckHResult( hr );

		for( int i = 0; i < length; i++ )
			delete[] bones[i].BoneId;
		delete[] bones;

		m_Pointer = result;
	}

	SkinInfo::SkinInfo( int vertexCount, SlimDX::Direct3D9::VertexFormat fvf, int boneCount )
	{
		ID3DXSkinInfo *result;

		HRESULT hr = D3DXCreateSkinInfoFVF( vertexCount, static_cast<DWORD>( fvf ),
			boneCount, &result );
		GraphicsException::CheckHResult( hr );

		m_Pointer = result;
	}

	SkinInfo^ SkinInfo::Clone()
	{
		ID3DXSkinInfo *result;

		HRESULT hr = m_Pointer->Clone( &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		return gcnew SkinInfo( result );
	}

	Mesh^ SkinInfo::ConvertToBlendedMesh( Mesh^ mesh, array<int>^ adjacencyIn, [Out] array<int>^ adjacencyOut,
		[Out] array<int>^ faceRemap, [Out] array<int>^% vertexRemap, [Out] int% maxVertexInfluence,
		[Out] array<BoneCombination^>^% boneCombinationTable )
	{
		ID3DXMesh *result;
		ID3DXBuffer *vr;
		ID3DXBuffer *bct;
		DWORD mvi;
		DWORD bcc;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];
		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = m_Pointer->ConvertToBlendedMesh( mesh->MeshPointer, 0, reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdjOut ), reinterpret_cast<DWORD*>( pinnedFR ), &vr, &mvi, &bcc, &bct, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			boneCombinationTable = nullptr;
			maxVertexInfluence = 0;
			vertexRemap = nullptr;
			faceRemap = nullptr;
			adjacencyOut = nullptr;
			return nullptr;
		}

		boneCombinationTable = gcnew array<BoneCombination^>( bcc );
		char *pointer = static_cast<char*>( bct->GetBufferPointer() );
		int size = ( 5 + mvi ) * 4;

		for( DWORD i = 0; i < bcc; i++ )
		{
			boneCombinationTable[i] = gcnew BoneCombination();
			boneCombinationTable[i]->BoneIds = gcnew array<int>( mvi );

			pin_ptr<BoneCombination^> pinnedBone = &boneCombinationTable[i];
			memcpy( pinnedBone, pointer, size );
			pointer += size;
		}

		maxVertexInfluence = mvi;
		vertexRemap = ( gcnew DataStream( vr ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ SkinInfo::ConvertToBlendedMesh( Mesh^ mesh, array<int>^ adjacencyIn, [Out] array<int>^ adjacencyOut,
		[Out] int% maxVertexInfluence, [Out] array<BoneCombination^>^% boneCombinationTable )
	{
		ID3DXMesh *result;
		ID3DXBuffer *bct;
		DWORD mvi;
		DWORD bcc;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];
		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];

		HRESULT hr = m_Pointer->ConvertToBlendedMesh( mesh->MeshPointer, 0, reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdjOut ), NULL, NULL, &mvi, &bcc, &bct, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			boneCombinationTable = nullptr;
			maxVertexInfluence = 0;
			adjacencyOut = nullptr;
			return nullptr;
		}

		boneCombinationTable = gcnew array<BoneCombination^>( bcc );
		char *pointer = static_cast<char*>( bct->GetBufferPointer() );
		int size = ( 5 + mvi ) * 4;

		for( DWORD i = 0; i < bcc; i++ )
		{
			boneCombinationTable[i] = gcnew BoneCombination();
			boneCombinationTable[i]->BoneIds = gcnew array<int>( mvi );

			pin_ptr<BoneCombination^> pinnedBone = &boneCombinationTable[i];
			memcpy( pinnedBone, pointer, size );
			pointer += size;
		}

		maxVertexInfluence = mvi;
		return gcnew Mesh( result );
	}

	Mesh^ SkinInfo::ConvertToIndexedBlendedMesh( Mesh^ mesh, int paletteSize, array<int>^ adjacencyIn, [Out] array<int>^ adjacencyOut,
		[Out] array<int>^ faceRemap, [Out] array<int>^% vertexRemap, [Out] int% maxVertexInfluence,
		[Out] array<BoneCombination^>^% boneCombinationTable )
	{
		ID3DXMesh *result;
		ID3DXBuffer *vr;
		ID3DXBuffer *bct;
		DWORD mvi;
		DWORD bcc;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];
		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];
		pin_ptr<int> pinnedFR = &faceRemap[0];

		HRESULT hr = m_Pointer->ConvertToIndexedBlendedMesh( mesh->MeshPointer, 0, paletteSize, reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdjOut ), reinterpret_cast<DWORD*>( pinnedFR ), &vr, &mvi, &bcc, &bct, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			boneCombinationTable = nullptr;
			maxVertexInfluence = 0;
			vertexRemap = nullptr;
			faceRemap = nullptr;
			adjacencyOut = nullptr;
			return nullptr;
		}

		boneCombinationTable = gcnew array<BoneCombination^>( bcc );
		char *pointer = static_cast<char*>( bct->GetBufferPointer() );
		int size = ( 5 + paletteSize ) * 4;

		for( DWORD i = 0; i < bcc; i++ )
		{
			boneCombinationTable[i] = gcnew BoneCombination();
			boneCombinationTable[i]->BoneIds = gcnew array<int>( paletteSize );

			pin_ptr<BoneCombination^> pinnedBone = &boneCombinationTable[i];
			memcpy( pinnedBone, pointer, size );
			pointer += size;
		}

		maxVertexInfluence = mvi;
		vertexRemap = ( gcnew DataStream( vr ) )->ReadRange<int>( result->GetNumVertices() );
		return gcnew Mesh( result );
	}

	Mesh^ SkinInfo::ConvertToIndexedBlendedMesh( Mesh^ mesh, int paletteSize, array<int>^ adjacencyIn, [Out] array<int>^ adjacencyOut,
		[Out] int% maxVertexInfluence, [Out] array<BoneCombination^>^% boneCombinationTable )
	{
		ID3DXMesh *result;
		ID3DXBuffer *bct;
		DWORD mvi;
		DWORD bcc;

		pin_ptr<int> pinnedAdjIn = &adjacencyIn[0];
		pin_ptr<int> pinnedAdjOut = &adjacencyOut[0];

		HRESULT hr = m_Pointer->ConvertToIndexedBlendedMesh( mesh->MeshPointer, 0, paletteSize, reinterpret_cast<const DWORD*>( pinnedAdjIn ),
			reinterpret_cast<DWORD*>( pinnedAdjOut ), NULL, NULL, &mvi, &bcc, &bct, &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			boneCombinationTable = nullptr;
			maxVertexInfluence = 0;
			adjacencyOut = nullptr;
			return nullptr;
		}

		boneCombinationTable = gcnew array<BoneCombination^>( bcc );
		char *pointer = static_cast<char*>( bct->GetBufferPointer() );
		int size = ( 5 + paletteSize ) * 4;

		for( DWORD i = 0; i < bcc; i++ )
		{
			boneCombinationTable[i] = gcnew BoneCombination();
			boneCombinationTable[i]->BoneIds = gcnew array<int>( paletteSize );

			pin_ptr<BoneCombination^> pinnedBone = &boneCombinationTable[i];
			memcpy( pinnedBone, pointer, size );
			pointer += size;
		}

		maxVertexInfluence = mvi;
		return gcnew Mesh( result );
	}

	int SkinInfo::FindBoneVertexInfluenceIndex( int bone, int vertex )
	{
		DWORD influence;

		HRESULT hr = m_Pointer->FindBoneVertexInfluenceIndex( bone, vertex, &influence );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return 0;

		return influence;
	}

	void SkinInfo::GetBoneInfluence( int bone, [Out] array<int>^% vertices, [Out] array<float>^% weights )
	{
		pin_ptr<int> pinnedVerts = &vertices[0];
		pin_ptr<float> pinnedWeights = &weights[0];

		HRESULT hr = m_Pointer->GetBoneInfluence( bone, reinterpret_cast<DWORD*>( pinnedVerts ),
			reinterpret_cast<float*>( pinnedWeights ) );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			vertices = nullptr;
			weights = nullptr;
		}
	}

	void SkinInfo::SetBoneInfluence( int bone, array<int>^ vertices, array<float>^ weights )
	{
		pin_ptr<int> pinnedVerts = &vertices[0];
		pin_ptr<float> pinnedWeights = &weights[0];

		HRESULT hr = m_Pointer->SetBoneInfluence( bone, vertices->Length, reinterpret_cast<const DWORD*>( pinnedVerts ),
			reinterpret_cast<const float*>( pinnedWeights ) );
		GraphicsException::CheckHResult( hr );
	}

	String^ SkinInfo::GetBoneName( int bone )
	{
		return gcnew String( m_Pointer->GetBoneName( bone ) );
	}

	void SkinInfo::SetBoneName( int bone, String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		HRESULT hr = m_Pointer->SetBoneName( bone, reinterpret_cast<LPCSTR>( pinnedName ) );
		GraphicsException::CheckHResult( hr );
	}

	void SkinInfo::GetBoneVertexInfluence( int bone, int influence, [Out] float% weight, [Out] int% vertex )
	{
		float w;
		DWORD v;

		HRESULT hr = m_Pointer->GetBoneVertexInfluence( bone, influence, &w, &v );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			weight = 0;
			vertex = 0;
		}
		else
		{
			weight = w;
			vertex = v;
		}
	}

	void SkinInfo::SetBoneVertexInfluence( int bone, int influence, float weight )
	{
		HRESULT hr = m_Pointer->SetBoneVertexInfluence( bone, influence, weight );
		GraphicsException::CheckHResult( hr );
	}

	Matrix SkinInfo::GetBoneOffsetMatrix( int bone )
	{
		return Matrix::FromD3DXMATRIX( *m_Pointer->GetBoneOffsetMatrix( bone ) );
	}

	void SkinInfo::SetBoneOffsetMatrix( int bone, Matrix matrix )
	{
		HRESULT hr = m_Pointer->SetBoneOffsetMatrix( bone, reinterpret_cast<D3DXMATRIX*>( &matrix ) );
		GraphicsException::CheckHResult( hr );
	}

	array<VertexElement>^ SkinInfo::GetDeclaration()
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

	void SkinInfo::SetDeclaration( array<VertexElement>^ declaration )
	{
		pin_ptr<VertexElement> pinnedDecl = &declaration[0];

		HRESULT hr = m_Pointer->SetDeclaration( reinterpret_cast<D3DVERTEXELEMENT9*>( pinnedDecl ) );
		GraphicsException::CheckHResult( hr );
	}

	int SkinInfo::GetMaxFaceInfluences( IndexBuffer^ indexBuffer, int faceCount )
	{
		DWORD ret;

		HRESULT hr = m_Pointer->GetMaxFaceInfluences( indexBuffer->IbPointer, faceCount, &ret );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return 0;

		return ret;
	}

	void SkinInfo::Remap( array<int>^ remapData )
	{
		pin_ptr<int> pinnedData = &remapData[0];

		HRESULT hr = m_Pointer->Remap( remapData->Length, reinterpret_cast<DWORD*>( pinnedData ) );
		GraphicsException::CheckHResult( hr );
	}

	void SkinInfo::UpdateSkinnedMesh( Matrix boneTransform, Matrix boneInvTranspose, DataStream^ source, DataStream^ destination )
	{
		HRESULT hr = m_Pointer->UpdateSkinnedMesh( reinterpret_cast<const D3DXMATRIX*>( &boneTransform ),
			reinterpret_cast<const D3DXMATRIX*>( &boneInvTranspose ), source->RawPointer, destination->RawPointer );
		GraphicsException::CheckHResult( hr );
	}

	int SkinInfo::GetBoneInfluenceCount( int bone )
	{
		return m_Pointer->GetNumBoneInfluences( bone );
	}

	int SkinInfo::MaximumVertexInfluences::get()
	{
		DWORD result;

		HRESULT hr = m_Pointer->GetMaxVertexInfluences( &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return 0;

		return result;
	}

	int SkinInfo::BoneCount::get()
	{
		return m_Pointer->GetNumBones();
	}

	float SkinInfo::MinimumBoneInfluence::get()
	{
		return m_Pointer->GetMinBoneInfluence();
	}

	void SkinInfo::MinimumBoneInfluence::set( float value )
	{
		HRESULT hr = m_Pointer->SetMinBoneInfluence( value );
		GraphicsException::CheckHResult( hr );
	}

	SlimDX::Direct3D9::VertexFormat SkinInfo::VertexFormat::get()
	{
		return static_cast<SlimDX::Direct3D9::VertexFormat>( m_Pointer->GetFVF() );
	}

	void SkinInfo::VertexFormat::set( SlimDX::Direct3D9::VertexFormat value )
	{
		HRESULT hr = m_Pointer->SetFVF( static_cast<DWORD>( value ) );
		GraphicsException::CheckHResult( hr );
	}
}
}

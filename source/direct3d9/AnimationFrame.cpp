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
#include "../Math/Math.h"
#include "../DataStream.h"

#include "GraphicsException.h"
#include "Device.h"
#include "Mesh.h"
#include "SkinInfo.h"
#include "ProgressiveMesh.h"
#include "PatchMesh.h"
#include "AnimationController.h"
#include "AnimationFrame.h"

namespace SlimDX
{
namespace Direct3D9
{
	MeshData::MeshData( SlimDX::Direct3D9::Mesh^ mesh )
	{
		this->mesh = mesh;
		type = MeshDataType::Mesh;
	}

	MeshData::MeshData( SlimDX::Direct3D9::ProgressiveMesh^ mesh )
	{
		this->progressiveMesh = mesh;
		type = MeshDataType::ProgressiveMesh;
	}

	MeshData::MeshData( SlimDX::Direct3D9::PatchMesh^ mesh )
	{
		this->patchMesh = mesh;
		type = MeshDataType::PatchMesh;
	}

	void MeshData::Mesh::set( SlimDX::Direct3D9::Mesh^ value )
	{
		mesh = value;
		type = MeshDataType::Mesh;
	}

	void MeshData::ProgressiveMesh::set( SlimDX::Direct3D9::ProgressiveMesh^ value )
	{
		progressiveMesh = value;
		type = MeshDataType::ProgressiveMesh;
	}

	void MeshData::PatchMesh::set( SlimDX::Direct3D9::PatchMesh^ value )
	{
		patchMesh = value;
		type = MeshDataType::PatchMesh;
	}

	MeshContainer::MeshContainer( const D3DXMESHCONTAINER &container )
	{
		m_Pointer = new D3DXMESHCONTAINER( container );
	}

	MeshContainer::MeshContainer( const D3DXMESHCONTAINER *container )
	{
		m_Pointer = const_cast<D3DXMESHCONTAINER*>( container );
	}

	MeshContainer::MeshContainer()
	{
		m_Pointer = new D3DXMESHCONTAINER();
		Pointer->pMaterials = NULL;
		Pointer->pEffects = NULL;
		Pointer->pAdjacency = NULL;
		Pointer->pSkinInfo = NULL;
		Pointer->pNextMeshContainer = NULL;
	}

	MeshContainer::~MeshContainer()
	{
		Destruct();
	}

	MeshContainer::!MeshContainer()
	{
		Destruct();
	}

	void MeshContainer::Destruct()
	{
		if( m_Pointer != NULL )
		{
			if( Pointer->pMaterials != NULL )
			{
				delete[] Pointer->pMaterials;
				Pointer->pMaterials = NULL;
			}

			if( Pointer->pAdjacency != NULL )
			{
				delete[] Pointer->pAdjacency;
				Pointer->pAdjacency = NULL;
			}

			if( Pointer->pEffects != NULL )
			{
				for( unsigned int i = 0; i < Pointer->NumMaterials; i++ )
				{
					if( Pointer->pEffects[i].pDefaults != NULL )
						delete[] Pointer->pEffects[i].pDefaults;
				}

				delete[] Pointer->pEffects;
				Pointer->pEffects = NULL;
			}

			delete m_Pointer;
			m_Pointer = NULL;
		}
	}

	array<ExtendedMaterial>^ MeshContainer::GetMaterials()
	{
		array<ExtendedMaterial>^ results = gcnew array<ExtendedMaterial>( Pointer->NumMaterials );

		for( unsigned int i = 0; i < Pointer->NumMaterials; i++ )
			results[i] = ExtendedMaterial::FromUnmanaged( Pointer->pMaterials[i] );

		return results;
	}

	void MeshContainer::SetMaterials( array<ExtendedMaterial>^ materials )
	{
		if( Pointer->pMaterials != NULL )
			delete[] Pointer->pMaterials;

		Pointer->NumMaterials = materials->Length;
		Pointer->pMaterials = new D3DXMATERIAL[Pointer->NumMaterials];

		for( int i = 0; i < materials->Length; i++ )
			Pointer->pMaterials[i] = ExtendedMaterial::ToUnmanaged( materials[i] );
	}

	array<EffectInstance>^ MeshContainer::GetEffects()
	{
		array<EffectInstance>^ results = gcnew array<EffectInstance>( Pointer->NumMaterials );

		for( unsigned int i = 0; i < Pointer->NumMaterials; i++ )
			results[i] = EffectInstance::FromUnmanaged( Pointer->pEffects[i] );

		return results;
	}

	void MeshContainer::SetEffects( array<EffectInstance>^ effects )
	{
		if( Pointer->pEffects != NULL )
			delete[] Pointer->pEffects;

		Pointer->NumMaterials = effects->Length;
		Pointer->pEffects = new D3DXEFFECTINSTANCE[effects->Length];

		for( int i = 0; i < effects->Length; i++ )
			Pointer->pEffects[i] = EffectInstance::ToUnmanaged( effects[i] );
	}

	array<int>^ MeshContainer::GetAdjacency()
	{
		int count = 0;

		if( Mesh->Type == MeshDataType::Mesh )
			count = Mesh->Mesh->FaceCount;
		else if( Mesh->Type == MeshDataType::ProgressiveMesh )
			count = Mesh->ProgressiveMesh->FaceCount;
		else if( Mesh->Type == MeshDataType::PatchMesh )
			count = Mesh->PatchMesh->PatchCount;
		count *= 3;

		array<int>^ results = gcnew array<int>( count );

		for( int i = 0; i < count; i++ )
			results[i] = Pointer->pAdjacency[i];

		return results;
	}

	void MeshContainer::SetAdjacency( array<int>^ adjacency )
	{
		if( Pointer->pAdjacency != NULL )
			delete[] Pointer->pAdjacency;

		int count = adjacency->Length;
		Pointer->pAdjacency = new DWORD[count];

		for( int i = 0; i < count; i++ )
			Pointer->pAdjacency[i] = adjacency[i];
	}

	String^ MeshContainer::Name::get()
	{
		if( Pointer->Name == NULL )
			return String::Empty;

		return gcnew String( Pointer->Name );
	}

	void MeshContainer::Name::set( String^ value )
	{
		if( value == nullptr || String::IsNullOrEmpty( value ) )
			Pointer->Name = NULL;
		else
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( value );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			Pointer->Name = reinterpret_cast<LPSTR>( pinnedName );
		}
	}

	MeshData^ MeshContainer::Mesh::get()
	{
		if( Pointer->MeshData.Type == D3DXMESHTYPE_MESH )
			return gcnew MeshData( gcnew SlimDX::Direct3D9::Mesh( Pointer->MeshData.pMesh ) );
		else if( Pointer->MeshData.Type == D3DXMESHTYPE_PMESH )
			return gcnew MeshData( gcnew ProgressiveMesh( Pointer->MeshData.pPMesh ) );
		else if( Pointer->MeshData.Type == D3DXMESHTYPE_PATCHMESH )
			return gcnew MeshData( gcnew PatchMesh( Pointer->MeshData.pPatchMesh ) );

		return nullptr;
	}

	void MeshContainer::Mesh::set( MeshData^ value )
	{
		Pointer->MeshData.Type = static_cast<D3DXMESHDATATYPE>( value->Type );
		
		if( Pointer->MeshData.Type == D3DXMESHTYPE_MESH )
			Pointer->MeshData.pMesh = value->Mesh->MeshPointer;
		else if( Pointer->MeshData.Type == D3DXMESHTYPE_PMESH )
			Pointer->MeshData.pPMesh = value->ProgressiveMesh->MeshPointer;
		else if( Pointer->MeshData.Type == D3DXMESHTYPE_PATCHMESH )
			Pointer->MeshData.pPatchMesh = value->PatchMesh->InternalPointer;
	}

	SlimDX::Direct3D9::SkinInfo^ MeshContainer::SkinInfo::get()
	{
		if( Pointer->pSkinInfo == NULL )
			return nullptr;

		return gcnew SlimDX::Direct3D9::SkinInfo( Pointer->pSkinInfo );
	}

	void MeshContainer::SkinInfo::set( SlimDX::Direct3D9::SkinInfo^ value )
	{
		if( value == nullptr )
			Pointer->pSkinInfo = NULL;
		else
			Pointer->pSkinInfo = value->InternalPointer;
	}

	MeshContainer^ MeshContainer::NextMeshContainer::get()
	{
		if( Pointer->pNextMeshContainer == NULL )
			return nullptr;

		return gcnew MeshContainer( Pointer->pNextMeshContainer );
	}

	void MeshContainer::NextMeshContainer::set( MeshContainer^ value )
	{
		if( value == nullptr )
			Pointer->pNextMeshContainer = NULL;
		else
			Pointer->pNextMeshContainer = value->Pointer;
	}

	IAllocateHierarchyShim::IAllocateHierarchyShim( IAllocateHierarchy^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	HRESULT IAllocateHierarchyShim::CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame )
	{
		Frame^ frame;

		try
		{
			frame = m_WrappedInterface->CreateFrame( gcnew String( Name ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		*ppNewFrame = frame->Pointer;

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData,
		const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials, const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer )
	{
		MeshContainer^ meshContainer;

		MeshData^ meshData;
		int count = 0;

		if( pMeshData->Type == D3DXMESHTYPE_MESH )
		{
			meshData = gcnew MeshData( gcnew Mesh( pMeshData->pMesh ) );
			count = meshData->Mesh->FaceCount;
		}
		else if( pMeshData->Type == D3DXMESHTYPE_PMESH )
		{
			meshData = gcnew MeshData( gcnew ProgressiveMesh( pMeshData->pPMesh ) );
			count = meshData->ProgressiveMesh->FaceCount;
		}
		else if( pMeshData->Type == D3DXMESHTYPE_PATCHMESH )
		{
			meshData = gcnew MeshData( gcnew PatchMesh( pMeshData->pPatchMesh ) );
			count = meshData->PatchMesh->PatchCount;
		}

		count *= 3;

		array<ExtendedMaterial>^ materials = gcnew array<ExtendedMaterial>( NumMaterials );
		array<EffectInstance>^ effects = gcnew array<EffectInstance>( NumMaterials );
		array<int>^ adjacency = gcnew array<int>( count );

		for( unsigned int i = 0; i < NumMaterials; i++ )
		{
			materials[i] = ExtendedMaterial::FromUnmanaged( pMaterials[i] );
			effects[i] = EffectInstance::FromUnmanaged( pEffectInstances[i] );
		}

		for( int i = 0; i < count; i++ )
			adjacency[i] = pAdjacency[i];

		try
		{
			meshContainer = m_WrappedInterface->CreateMeshContainer( gcnew String( Name ), meshData, materials, 
				effects, adjacency, gcnew SkinInfo( pSkinInfo ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::DestroyFrame( LPD3DXFRAME pFrameToFree )
	{
		try
		{
			Frame^ frame = gcnew Frame( pFrameToFree );
			m_WrappedInterface->DestroyFrame( frame );
			frame->~Frame();
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree )
	{
		try
		{
			MeshContainer^ meshContainer = gcnew MeshContainer( pMeshContainerToFree );
			m_WrappedInterface->DestroyMeshContainer( meshContainer );
			meshContainer->~MeshContainer();
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	ILoadUserDataShim::ILoadUserDataShim( ILoadUserData^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	HRESULT ILoadUserDataShim::LoadFrameChildData( LPD3DXFRAME pFrame, LPD3DXFILEDATA pXofChildData )
	{
		try
		{
			m_WrappedInterface->LoadFrameData( gcnew Frame( pFrame ), gcnew XFileData( pXofChildData ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ILoadUserDataShim::LoadMeshChildData( LPD3DXMESHCONTAINER pMeshContainer, LPD3DXFILEDATA pXofChildData )
	{
		try
		{
			m_WrappedInterface->LoadMeshData( gcnew MeshContainer( pMeshContainer ), gcnew XFileData( pXofChildData ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ILoadUserDataShim::LoadTopLevelData( LPD3DXFILEDATA pXofChildData )
	{
		try
		{
			m_WrappedInterface->LoadTopLevelData( gcnew XFileData( pXofChildData ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	ISaveUserDataShim::ISaveUserDataShim( ISaveUserData^ wrappedInterface )
	{
		m_WrappedInterface = wrappedInterface;
	}

	HRESULT ISaveUserDataShim::AddFrameChildData( const D3DXFRAME *pFrame, LPD3DXFILESAVEOBJECT pXofSave, LPD3DXFILESAVEDATA pXofFrameData )
	{
		try
		{
			m_WrappedInterface->AddFrameChildData( gcnew Frame( pFrame ), gcnew XFileSaveObject( pXofSave ), 
				gcnew XFileSaveData( pXofFrameData ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ISaveUserDataShim::AddMeshChildData( const D3DXMESHCONTAINER *pMeshContainer, LPD3DXFILESAVEOBJECT pXofSave, LPD3DXFILESAVEDATA pXofMeshData )
	{
		try
		{
			m_WrappedInterface->AddMeshChildData( gcnew MeshContainer( pMeshContainer ), 
				gcnew XFileSaveObject( pXofSave ), gcnew XFileSaveData( pXofMeshData ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ISaveUserDataShim::AddTopLevelDataObjectsPost( LPD3DXFILESAVEOBJECT pXofSave )
	{
		try
		{
			m_WrappedInterface->AddTopLevelDataPost( gcnew XFileSaveObject( pXofSave ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ISaveUserDataShim::AddTopLevelDataObjectsPre( LPD3DXFILESAVEOBJECT pXofSave )
	{
		try
		{
			m_WrappedInterface->AddTopLevelDataPre( gcnew XFileSaveObject( pXofSave ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ISaveUserDataShim::RegisterTemplates( LPD3DXFILE pXFileApi )
	{
		try
		{
			m_WrappedInterface->RegisterTemplates( gcnew XFile( pXFileApi ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT ISaveUserDataShim::SaveTemplates( LPD3DXFILESAVEOBJECT pXofSave )
	{
		try
		{
			m_WrappedInterface->SaveTemplates( gcnew XFileSaveObject( pXofSave ) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	Frame::Frame( const D3DXFRAME &frame )
	{
		m_Pointer = new D3DXFRAME( frame );
	}

	Frame::Frame( const D3DXFRAME *frame )
	{
		m_Pointer = const_cast<D3DXFRAME*>( frame );
	}

	Frame::Frame()
	{
		m_Pointer = new D3DXFRAME();
	}

	Frame::~Frame()
	{
		Destruct();
	}

	Frame::!Frame()
	{
		Destruct();
	}

	void Frame::Destruct()
	{
		if( m_Pointer != NULL )
		{
			delete m_Pointer;
			m_Pointer = NULL;
		}
	}

	void Frame::AppendChild( Frame^ child )
	{
		HRESULT hr = D3DXFrameAppendChild( Pointer, child->Pointer );
		GraphicsException::CheckHResult( hr );
	}

	Frame^ Frame::FindChild( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		D3DXFRAME* frame = D3DXFrameFind( Pointer, reinterpret_cast<LPCSTR>( pinnedName ) );
		if( frame == NULL )
			return nullptr;

		return gcnew Frame( *frame );
	}

	BoundingSphere Frame::CalculateBoundingSphere( Frame^ root )
	{
		Vector3 objectCenter;
		float radius;

		HRESULT hr = D3DXFrameCalculateBoundingSphere( root->Pointer, reinterpret_cast<D3DXVECTOR3*>( &objectCenter ), &radius );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return BoundingSphere( Vector3( 0, 0, 0 ), 0.0f );

		return BoundingSphere( objectCenter, radius );
	}

	void Frame::DestroyHierarchy( Frame^ root, IAllocateHierarchy^ allocator )
	{
		IAllocateHierarchyShim* shim = new IAllocateHierarchyShim( allocator );

		HRESULT hr = D3DXFrameDestroy( root->Pointer, shim );
		GraphicsException::CheckHResult( hr );

		delete shim;
	}

	int Frame::CountNamedFrames( Frame^ root )
	{
		return D3DXFrameNumNamedMatrices( root->Pointer );
	}

	void Frame::RegisterNamedMatrices( Frame^ root, AnimationController^ controller )
	{
		HRESULT hr = D3DXFrameRegisterNamedMatrices( root->Pointer, controller->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}

	String^ Frame::Name::get()
	{
		if( Pointer->Name == NULL )
			return String::Empty;

		return gcnew String( Pointer->Name );
	}

	void Frame::Name::set( String^ value )
	{
		if( value == nullptr || String::IsNullOrEmpty( value ) )
			Pointer->Name = NULL;
		else
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( value );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			Pointer->Name = reinterpret_cast<LPSTR>( pinnedName );
		}
	}

	Matrix Frame::TransformationMatrix::get()
	{
		return Matrix::FromD3DXMATRIX( Pointer->TransformationMatrix );
	}

	void Frame::TransformationMatrix::set( Matrix value )
	{
		Pointer->TransformationMatrix = Matrix::ToD3DXMATRIX( value );
	}

	SlimDX::Direct3D9::MeshContainer^ Frame::MeshContainer::get()
	{
		if( Pointer->pMeshContainer == NULL )
			return nullptr;

		return gcnew SlimDX::Direct3D9::MeshContainer( *Pointer->pMeshContainer );
	}

	void Frame::MeshContainer::set( SlimDX::Direct3D9::MeshContainer^ value )
	{
		if( value == nullptr )
			Pointer->pMeshContainer = NULL;
		else
			Pointer->pMeshContainer = value->Pointer;
	}

	Frame^ Frame::Sibling::get()
	{
		if( Pointer->pFrameSibling == NULL )
			return nullptr;

		return gcnew Frame( *Pointer->pFrameSibling );
	}

	void Frame::Sibling::set( Frame^ value )
	{
		if( value == nullptr )
			Pointer->pFrameSibling = NULL;
		else
			Pointer->pFrameSibling = value->Pointer;
	}

	Frame^ Frame::FirstChild::get()
	{
		if( Pointer->pFrameFirstChild == NULL )
			return nullptr;

		return gcnew Frame( *Pointer->pFrameFirstChild );
	}

	void Frame::FirstChild::set( Frame^ value )
	{
		if( value == nullptr )
			Pointer->pFrameFirstChild = NULL;
		else
			Pointer->pFrameFirstChild = value->Pointer;
	}

	Frame^ Frame::LoadHierarchyFromX( Device^ device, String^ fileName, MeshFlags options, 
		IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController )
	{
		IAllocateHierarchyShim* allocatorShim = new IAllocateHierarchyShim( allocator );
		ILoadUserDataShim* userDataLoaderShim;
		LPD3DXFRAME result;
		LPD3DXANIMATIONCONTROLLER animationResult;

		if( userDataLoader == nullptr )
			userDataLoaderShim = NULL;
		else
			userDataLoaderShim = new ILoadUserDataShim( userDataLoader );

		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadMeshHierarchyFromX( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( options ), device->InternalPointer,
			allocatorShim, userDataLoaderShim, &result, &animationResult );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		animationController = gcnew AnimationController( animationResult );

		delete allocatorShim;
		delete userDataLoaderShim;

		return gcnew Frame( result );
	}

	Frame^ Frame::LoadHierarchyFromX( Device^ device, array<Byte>^ memory, MeshFlags options, 
		IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController )
	{
		IAllocateHierarchyShim* allocatorShim = new IAllocateHierarchyShim( allocator );
		ILoadUserDataShim* userDataLoaderShim;
		LPD3DXFRAME result;
		LPD3DXANIMATIONCONTROLLER animationResult;

		if( userDataLoader == nullptr )
			userDataLoaderShim = NULL;
		else
			userDataLoaderShim = new ILoadUserDataShim( userDataLoader );

		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadMeshHierarchyFromXInMemory( reinterpret_cast<LPCVOID>( pinnedMemory ), memory->Length, static_cast<DWORD>( options ), 
			device->InternalPointer, allocatorShim, userDataLoaderShim, &result, &animationResult );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			return nullptr;

		animationController = gcnew AnimationController( animationResult );

		delete allocatorShim;
		delete userDataLoaderShim;

		return gcnew Frame( result );
	}

	Frame^ Frame::LoadHierarchyFromX( Device^ device, Stream^ stream, MeshFlags options, 
		IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController )
	{
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		return Frame::LoadHierarchyFromX( device, data, options, allocator, userDataLoader, animationController );
	}

	void Frame::SaveHierarchyToFile( String^ fileName, XFileFormat format, Frame^ root, AnimationController^ animationController, ISaveUserData^ userDataSaver )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		ISaveUserDataShim *shim = new ISaveUserDataShim( userDataSaver );

		HRESULT hr = D3DXSaveMeshHierarchyToFile( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( format ),
			root->Pointer, animationController->InternalPointer, shim );
		GraphicsException::CheckHResult( hr );

		delete shim;
	}

	void Frame::SaveHierarchyToFile( String^ fileName, XFileFormat format, Frame^ root, AnimationController^ animationController )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXSaveMeshHierarchyToFile( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( format ),
			root->Pointer, animationController->InternalPointer, NULL );
		GraphicsException::CheckHResult( hr );
	}
}
}
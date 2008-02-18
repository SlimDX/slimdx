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
#include <vcclr.h>

#include "../ComObject.h"
#include "../Math/Math.h"
#include "../DataStream.h"
#include "../Utilities.h"

#include "Direct3D9Exception.h"
#include "Device.h"
#include "Mesh.h"
#include "SkinInfo.h"
#include "ProgressiveMesh.h"
#include "PatchMesh.h"
#include "AnimationController.h"
#include "AnimationFrame.h"


using namespace System;
using namespace System::IO;
using namespace System::Collections::ObjectModel;

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

	MeshContainerShim::MeshContainerShim( SlimDX::Direct3D9::MeshContainer ^container ) : D3DXMESHCONTAINER( )
	{
		m_Container = container;
	}

	MeshContainer::MeshContainer()
	{
		Pointer = new D3DXMESHCONTAINER();
		Pointer->MeshData = D3DXMESHDATA();
		Pointer->pMaterials = NULL;
		Pointer->pEffects = NULL;
		Pointer->pAdjacency = NULL;
		Pointer->pSkinInfo = NULL;
		Pointer->pNextMeshContainer = NULL;
		m_Name = String::Empty;
		m_NextContainer = nullptr;
		m_SkinInfo = nullptr;
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
		if( Pointer != NULL )
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

			if(m_MeshData != nullptr )
			{
				if(m_MeshData->Mesh != nullptr)
				{
					m_MeshData->Mesh->~Mesh();
				}
				if(m_MeshData->PatchMesh != nullptr)
				{
					m_MeshData->PatchMesh->~PatchMesh();
				}
				if(m_MeshData->ProgressiveMesh != nullptr)
				{
					m_MeshData->ProgressiveMesh->~ProgressiveMesh();
				}
			}

			if(m_SkinInfo != nullptr)
			{
				m_SkinInfo->~SkinInfo();
			}

			delete Pointer;
			Pointer = NULL;
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
		return m_Name;
	}

	void MeshContainer::Name::set( String^ value )
	{
		m_Name = value;

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
		return m_MeshData;
	}

	void MeshContainer::Mesh::set( MeshData^ value )
	{
		m_MeshData = value;

		Pointer->MeshData.Type = static_cast<D3DXMESHDATATYPE>( value->Type );
		
		if( Pointer->MeshData.Type == D3DXMESHTYPE_MESH )
		{
			Pointer->MeshData.pMesh = value->Mesh->MeshPointer;
		}
		else if( Pointer->MeshData.Type == D3DXMESHTYPE_PMESH )
		{
			Pointer->MeshData.pPMesh = value->ProgressiveMesh->MeshPointer;
		}
		else if( Pointer->MeshData.Type == D3DXMESHTYPE_PATCHMESH )
		{
			Pointer->MeshData.pPatchMesh = value->PatchMesh->InternalPointer;
		}
	}

	SlimDX::Direct3D9::SkinInfo^ MeshContainer::SkinInfo::get()
	{
		return m_SkinInfo;
	}

	void MeshContainer::SkinInfo::set( SlimDX::Direct3D9::SkinInfo^ value )
	{
		m_SkinInfo = value;

		if( value == nullptr )
			Pointer->pSkinInfo = NULL;
		else
		{
			Pointer->pSkinInfo = value->InternalPointer;
		}
	}

	MeshContainer^ MeshContainer::NextMeshContainer::get()
	{
		return m_NextContainer;
	}

	void MeshContainer::NextMeshContainer::set( MeshContainer^ value )
	{
		m_NextContainer = value;

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
		*ppNewFrame = NULL;

		try
		{
			frame = m_WrappedInterface->CreateFrame( gcnew String(Name) );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}
		 
		*ppNewFrame = new FrameShim( frame, *(frame->Pointer) );

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData,
		const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials, const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer )
	{
		MeshContainer^ meshContainer;
		*ppNewMeshContainer = NULL;

		MeshData^ meshData;
		int count = 0;

		if( pMeshData->Type == D3DXMESHTYPE_MESH )
		{
			meshData = gcnew MeshData( gcnew Mesh( pMeshData->pMesh ) );
			meshData->Mesh->MeshPointer->AddRef();
			count = meshData->Mesh->FaceCount;
		}
		else if( pMeshData->Type == D3DXMESHTYPE_PMESH )
		{
			meshData = gcnew MeshData( gcnew ProgressiveMesh( pMeshData->pPMesh ) );
			meshData->ProgressiveMesh->MeshPointer->AddRef();
			count = meshData->ProgressiveMesh->FaceCount;
		}
		else if( pMeshData->Type == D3DXMESHTYPE_PATCHMESH )
		{
			meshData = gcnew MeshData( gcnew PatchMesh( pMeshData->pPatchMesh ) );
			meshData->PatchMesh->InternalPointer->AddRef();
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

		SkinInfo^ skinInfo = nullptr;
		if(pSkinInfo != NULL)
		{
			skinInfo = gcnew SkinInfo( pSkinInfo );
			pSkinInfo->AddRef();
		}

		try
		{
			meshContainer = m_WrappedInterface->CreateMeshContainer( gcnew String(Name), meshData, materials, 
				effects, adjacency, skinInfo );
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		*ppNewMeshContainer = new MeshContainerShim( meshContainer );

		return D3D_OK;
	}

	HRESULT IAllocateHierarchyShim::DestroyFrame( LPD3DXFRAME pFrameToFree )
	{
		try
		{
			m_WrappedInterface->DestroyFrame( ((FrameShim*)pFrameToFree)->GetFrame() );
			delete pFrameToFree;
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
			m_WrappedInterface->DestroyMeshContainer( ((MeshContainerShim*)pMeshContainerToFree)->GetMeshContainer() );
			delete pMeshContainerToFree;
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
			XFileData^ data = gcnew XFileData( pXofChildData );
			m_WrappedInterface->LoadFrameData( ((FrameShim*)pFrame)->GetFrame(), data );
			data->~XFileData();
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
			XFileData^ data = gcnew XFileData( pXofChildData );
			m_WrappedInterface->LoadMeshData( ((MeshContainerShim*)pMeshContainer)->GetMeshContainer(), data );
			data->~XFileData();
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
			XFileData^ data = gcnew XFileData( pXofChildData );
			m_WrappedInterface->LoadTopLevelData( data );
			data->~XFileData();
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
			XFileSaveObject^ saveObject = gcnew XFileSaveObject( pXofSave );
			XFileSaveData^ saveData = gcnew XFileSaveData( pXofFrameData );
			m_WrappedInterface->AddFrameChildData( ((FrameShim*)pFrame)->GetFrame(), saveObject, saveData );
			saveObject->~XFileSaveObject();
			saveData->~XFileSaveData();
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
			XFileSaveObject^ saveObject = gcnew XFileSaveObject( pXofSave );
			XFileSaveData^ saveData = gcnew XFileSaveData( pXofMeshData );
			m_WrappedInterface->AddMeshChildData( ((MeshContainerShim*)pMeshContainer)->GetMeshContainer(), saveObject, saveData );
			saveObject->~XFileSaveObject();
			saveData->~XFileSaveData();
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
			XFileSaveObject^ saveObject = gcnew XFileSaveObject( pXofSave );
			m_WrappedInterface->AddTopLevelDataPost( saveObject );
			saveObject->~XFileSaveObject();
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
			XFileSaveObject^ saveObject = gcnew XFileSaveObject( pXofSave );
			m_WrappedInterface->AddTopLevelDataPre( saveObject );
			saveObject->~XFileSaveObject();
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
			XFile^ xFile = gcnew XFile( pXFileApi );
			m_WrappedInterface->RegisterTemplates( xFile );
			xFile->~XFile();
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
			XFileSaveObject^ saveObject = gcnew XFileSaveObject( pXofSave );
			m_WrappedInterface->SaveTemplates( saveObject );
			saveObject->~XFileSaveObject();
		}
		catch( Exception^ )
		{
			return E_FAIL;
		}

		return D3D_OK;
	}

	FrameShim::FrameShim( Frame^ frame, const D3DXFRAME &pFrame ) : D3DXFRAME( pFrame )
	{
		m_Frame = frame;
	}

	FrameShim::FrameShim( Frame^ frame ) : D3DXFRAME( )
	{
		m_Frame = frame;

		// This step is important when saving the frame hierarchy.
		if(frame->Pointer != NULL)
			TransformationMatrix = frame->Pointer->TransformationMatrix;
	}

	Frame::Frame()
	{
		Pointer = new D3DXFRAME();
		m_Name = String::Empty;
		m_FirstChild = nullptr;
		m_Sibling = nullptr;
		m_MeshContainer = nullptr;
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
		if( Pointer != NULL )
		{
			delete Pointer;
			Pointer = NULL;
		}
	}

	void Frame::AppendChild( Frame^ child )
	{
		if( child == this )
			throw gcnew Direct3D9Exception("Child frame can't be the same as the parent." + 
			" This will cause a StackOverflowException.");

		// Append managed child frame to parent.
		if( m_FirstChild != nullptr )
		{
            // Go through all the child frames connected to this frame
			Frame^ frame = FirstChild;
			while( frame != nullptr )
			{
				// Go to the next child
				frame = frame->Sibling;
			}

			// Set child
			frame = child;
		}
		else
		{
			FirstChild = child;
		}
	}

	Frame^ Frame::FindChild( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		FrameShim* shim = Frame::BuildHierarchyFromManaged( this );

		FrameShim* pFrame = (FrameShim*)D3DXFrameFind( shim, reinterpret_cast<LPCSTR>( pinnedName ) );

		if( pFrame == NULL )
		{
			delete shim;
			return nullptr;
		}

		delete shim;
		return pFrame->GetFrame();
	}

	BoundingSphere Frame::CalculateBoundingSphere( Frame^ root )
	{
		Vector3 objectCenter;
		float radius;

		FrameShim* shim = Frame::BuildHierarchyFromManaged( root );

		HRESULT hr = D3DXFrameCalculateBoundingSphere( shim, reinterpret_cast<D3DXVECTOR3*>( &objectCenter ), &radius );
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			delete shim;
			return BoundingSphere( Vector3( 0, 0, 0 ), 0.0f );
		}

		delete shim;
		return BoundingSphere( objectCenter, radius );
	}

	void Frame::DestroyHierarchy( Frame^ root, IAllocateHierarchy^ allocator )
	{
		IAllocateHierarchyShim* shim = new IAllocateHierarchyShim( allocator );
		FrameShim* frameShim = Frame::BuildHierarchyFromManaged( root );

		HRESULT hr = D3DXFrameDestroy( frameShim, shim );
		Result::Record( hr );

		delete shim;
		delete frameShim;
	}

	int Frame::CountNamedFrames( Frame^ root )
	{
		FrameShim* frameShim = Frame::BuildHierarchyFromManaged( root );
		int count = D3DXFrameNumNamedMatrices( frameShim );

		delete frameShim;
		return count;
	}

	void Frame::RegisterNamedMatrices( Frame^ root, AnimationController^ controller )
	{
		if( root == nullptr || controller == nullptr )
			throw gcnew ArgumentNullException();

		Frame::RegisterAnimations( root, controller->InternalPointer );
	}

	String^ Frame::Name::get()
	{
		return m_Name;
	}

	void Frame::Name::set( String^ value )
	{
		m_Name = value;

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
		return m_MeshContainer;
	}

	void Frame::MeshContainer::set( SlimDX::Direct3D9::MeshContainer^ value )
	{
		m_MeshContainer = value;

		/* Update Unmanaged */
		if(value == nullptr)
			Pointer->pMeshContainer = NULL;
		else
			Pointer->pMeshContainer = value->Pointer;
	}

	Frame^ Frame::Sibling::get()
	{
		return m_Sibling;
	}

	void Frame::Sibling::set( Frame^ value )
	{
		m_Sibling = value;

		if(value == nullptr)
			Pointer->pFrameSibling = NULL;
		else
			Pointer->pFrameSibling = value->Pointer;
	}

	Frame^ Frame::FirstChild::get()
	{
		return m_FirstChild;
	}

	void Frame::FirstChild::set( Frame^ value )
	{
		m_FirstChild = value;

		if(value == nullptr)
			Pointer->pFrameFirstChild = NULL;
		else
			Pointer->pFrameFirstChild = value->Pointer;
	}

	Frame^ Frame::LoadHierarchyFromX( Device^ device, String^ fileName, MeshFlags options, 
		IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController )
	{
		IAllocateHierarchyShim* allocatorShim = new IAllocateHierarchyShim( allocator );
		ILoadUserDataShim* userDataLoaderShim = NULL;
		LPD3DXFRAME result = NULL;
		LPD3DXANIMATIONCONTROLLER animationResult;

		if( userDataLoader == nullptr )
			userDataLoaderShim = NULL;
		else
			userDataLoaderShim = new ILoadUserDataShim( userDataLoader );

		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadMeshHierarchyFromX( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( options ), device->InternalPointer,
			allocatorShim, userDataLoaderShim, &result, &animationResult);
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			animationController = nullptr;
			return nullptr;
		}

		// If there is no animation, return a nullptr.
		if( animationResult != NULL )
		{
			animationController = gcnew AnimationController( animationResult );
		}
		else
			animationController = nullptr;

		delete allocatorShim;
		delete userDataLoaderShim;
		
		// Build frame hierarchy.
		Frame^ frame = Frame::BuildHierarchyFromUnmanaged( ((FrameShim*)result) );

		// Register frame animations.
		if( animationResult != NULL )
			Frame::RegisterAnimations( frame, animationResult );

		return frame;
	}

	Frame^ Frame::LoadHierarchyFromX( Device^ device, array<Byte>^ memory, MeshFlags options, 
		IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController )
	{
		IAllocateHierarchyShim* allocatorShim = new IAllocateHierarchyShim( allocator );
		ILoadUserDataShim* userDataLoaderShim = NULL;
		LPD3DXFRAME result = NULL;
		LPD3DXANIMATIONCONTROLLER animationResult = NULL;

		if( userDataLoader == nullptr )
			userDataLoaderShim = NULL;
		else
			userDataLoaderShim = new ILoadUserDataShim( userDataLoader );

		pin_ptr<unsigned char> pinnedMemory = &memory[0];

		HRESULT hr = D3DXLoadMeshHierarchyFromX( reinterpret_cast<LPCWSTR>( pinnedMemory ), static_cast<DWORD>( options ), device->InternalPointer,
			allocatorShim, userDataLoaderShim, &result, &animationResult);
		Result::Record( hr );

		if( FAILED( hr ) )
		{
			animationController = nullptr;
			return nullptr;
		}

		// If there is no animation, return a nullptr.
		if( animationResult != NULL )
		{
			animationController = gcnew AnimationController( animationResult );
		}
		else
			animationController = nullptr;

		delete allocatorShim;
		delete userDataLoaderShim;
		
		// Build frame hierarchy.
		Frame^ frame = Frame::BuildHierarchyFromUnmanaged( (FrameShim*)result );

		// Register frame animations.
		if( animationResult != NULL )
			Frame::RegisterAnimations( frame, animationResult );

		return frame;
	}

	Frame^ Frame::LoadHierarchyFromX( Device^ device, Stream^ stream, MeshFlags options, 
		IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController )
	{
		array<Byte>^ data = Utilities::ReadStream( stream, 0 );
		return Frame::LoadHierarchyFromX( device, data, options, allocator, userDataLoader, animationController );
	}

	void Frame::SaveHierarchyToFile( String^ fileName, XFileFormat format, Frame^ root, AnimationController^ animationController, ISaveUserData^ userDataSaver )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		ISaveUserDataShim *shim = new ISaveUserDataShim( userDataSaver );
		FrameShim *frameShim = Frame::BuildHierarchyFromManaged( root );

		// If animation controller is null, handle it.
		LPD3DXANIMATIONCONTROLLER animation = NULL;
		if(animationController != nullptr)
			animation = animationController->InternalPointer;


		HRESULT hr = D3DXSaveMeshHierarchyToFile( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( format ),
			frameShim, animation, shim );
		Result::Record( hr );

		delete shim;
		delete frameShim;
	}

	void Frame::SaveHierarchyToFile( String^ fileName, XFileFormat format, Frame^ root, AnimationController^ animationController )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );
		FrameShim *frameShim = Frame::BuildHierarchyFromManaged( root );

		// If animation controller is null, handle it.
		LPD3DXANIMATIONCONTROLLER animation = NULL;
		if(animationController != nullptr)
			animation = animationController->InternalPointer;

		HRESULT hr = D3DXSaveMeshHierarchyToFile( reinterpret_cast<LPCWSTR>( pinnedName ), static_cast<DWORD>( format ),
			frameShim, animation, NULL );
		Result::Record( hr );

		delete frameShim;
	}

	void Frame::RegisterAnimations( Frame^ frame, LPD3DXANIMATIONCONTROLLER animation )
	{
		if( frame->Name != nullptr )
		{
			animation->RegisterAnimationOutput( frame->Pointer->Name, &frame->Pointer->TransformationMatrix, NULL, NULL, NULL );
		}

		if( frame->FirstChild != nullptr )
		{
			RegisterAnimations( frame->FirstChild, animation );
		}

		if( frame->Sibling != nullptr )
		{
			RegisterAnimations( frame->Sibling, animation );
		}
	}

	Frame^ Frame::BuildHierarchyFromUnmanaged( FrameShim* pFrame )
	{
		Frame^ hierarchy = nullptr;
		BuildManagedFrames( hierarchy, pFrame );
		return hierarchy;
	}

	void Frame::BuildManagedFrames( Frame^% frame, FrameShim* pFrame )
	{
		frame = pFrame->GetFrame();

		// Since DX adds the frame's transformation matrix after creating the frame,
		// we have to update that here.
		frame->Pointer->TransformationMatrix = pFrame->TransformationMatrix;

		// Get any meshes.
		if( pFrame->pMeshContainer != NULL )
		{
			SlimDX::Direct3D9::MeshContainer^ mc;
			BuildManagedMeshes( mc, (MeshContainerShim*)pFrame->pMeshContainer );
			frame->MeshContainer = mc;
		}

		if( pFrame->pFrameFirstChild != NULL )
		{
			Frame^ fc;
			BuildManagedFrames( fc, (FrameShim*)pFrame->pFrameFirstChild );
			frame->FirstChild = fc;
		}

		if( pFrame->pFrameSibling != NULL )
		{
			Frame^ sb;
			BuildManagedFrames( sb, (FrameShim*)pFrame->pFrameSibling );
			frame->Sibling = sb;
		}
	}

	void Frame::BuildManagedMeshes( SlimDX::Direct3D9::MeshContainer^% mesh, MeshContainerShim* pMesh )
	{
		mesh = pMesh->GetMeshContainer();

		if( pMesh->pNextMeshContainer != NULL )
		{
			SlimDX::Direct3D9::MeshContainer^ nc;
			BuildManagedMeshes( nc, (MeshContainerShim*)pMesh->pNextMeshContainer );
			mesh->NextMeshContainer = nc;
		}
	}

	FrameShim* Frame::BuildHierarchyFromManaged( Frame^ frame )
	{
		FrameShim* hierarchy = nullptr;
		BuildUnmanagedFrames( hierarchy, frame );
		return hierarchy;
	}

	void Frame::BuildUnmanagedFrames( FrameShim*% pFrame, Frame^ frame )
	{
		pFrame = new FrameShim( frame );

		if( frame->Name == nullptr || String::IsNullOrEmpty(frame->Name) )
			pFrame->Name = NULL;
		else
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( frame->Name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			pFrame->Name = reinterpret_cast<LPSTR>( pinnedName );
		}

		// Get any meshes.
		if( frame->MeshContainer != nullptr )
		{
			MeshContainerShim* mc;
			BuildUnmanagedMeshes( mc, frame->MeshContainer );
			pFrame->pMeshContainer = mc;
		}

		if( frame->FirstChild != nullptr )
		{
			FrameShim* fc;
			BuildUnmanagedFrames( fc, frame->FirstChild );
			pFrame->pFrameFirstChild = fc;
		}

		if( frame->Sibling != nullptr )
		{
			FrameShim* sb;
			BuildUnmanagedFrames( sb, frame->Sibling );
			pFrame->pFrameSibling = sb;
		}
	}

	void Frame::BuildUnmanagedMeshes( MeshContainerShim*% pMesh, SlimDX::Direct3D9::MeshContainer^ mesh )
	{
		pMesh = new MeshContainerShim( mesh );

		if( mesh->Name == nullptr || String::IsNullOrEmpty( mesh->Name ) )
			pMesh->Name = NULL;
		else
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( mesh->Name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			pMesh->Name = reinterpret_cast<LPSTR>( pinnedName );
		}

		if( mesh->Pointer != NULL )
		{
			pMesh->NumMaterials = mesh->Pointer->NumMaterials;
			pMesh->pMaterials = mesh->Pointer->pMaterials;
			pMesh->pEffects = mesh->Pointer->pEffects;
			pMesh->pAdjacency = mesh->Pointer->pAdjacency;
			pMesh->pSkinInfo = mesh->Pointer->pSkinInfo;
			pMesh->MeshData.pMesh = mesh->Pointer->MeshData.pMesh;
			pMesh->MeshData.pPatchMesh = mesh->Pointer->MeshData.pPatchMesh;
			pMesh->MeshData.pPMesh = mesh->Pointer->MeshData.pPMesh;
			pMesh->MeshData.Type = mesh->Pointer->MeshData.Type;

			if( mesh->NextMeshContainer != nullptr )
			{
				MeshContainerShim* nc;
				BuildUnmanagedMeshes( nc, mesh->NextMeshContainer );
				pMesh->pNextMeshContainer = nc;
			}
		}
	}
  }
}
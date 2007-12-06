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
#pragma once

using namespace System;
using namespace System::Collections::ObjectModel;

#include "XFile.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class Frame;
		ref class AnimationController;

		public enum class MeshDataType : Int32
		{
			Mesh = D3DXMESHTYPE_MESH,
			ProgressiveMesh = D3DXMESHTYPE_PMESH,
			PatchMesh = D3DXMESHTYPE_PATCHMESH
		};

		public ref class MeshData
		{
		private:
			MeshDataType type;
			Mesh^ mesh;
			ProgressiveMesh^ progressiveMesh;
			PatchMesh^ patchMesh;

		public:
			MeshData( Mesh^ mesh );
			MeshData( ProgressiveMesh^ mesh );
			MeshData( PatchMesh^ mesh );

			property MeshDataType Type
			{
				MeshDataType get() { return type; }
			}

			property Mesh^ Mesh
			{
				SlimDX::Direct3D9::Mesh^ get() { return mesh; }
				void set( SlimDX::Direct3D9::Mesh^ value );
			}

			property ProgressiveMesh^ ProgressiveMesh
			{
				SlimDX::Direct3D9::ProgressiveMesh^ get() { return progressiveMesh; }
				void set( SlimDX::Direct3D9::ProgressiveMesh^ value );
			}

			property PatchMesh^ PatchMesh
			{
				SlimDX::Direct3D9::PatchMesh^ get() { return patchMesh; }
				void set( SlimDX::Direct3D9::PatchMesh^ value );
			}
		};

		public ref class MeshContainer
		{
		private:
			D3DXMESHCONTAINER *m_Pointer;

		internal:
			MeshContainer( const D3DXMESHCONTAINER &container );
			MeshContainer( const D3DXMESHCONTAINER *container );

			property D3DXMESHCONTAINER *Pointer
			{ 
				D3DXMESHCONTAINER* get() { return m_Pointer; }
			}

			void Destruct();

		public:
			MeshContainer();
			virtual ~MeshContainer();
			!MeshContainer();

			array<ExtendedMaterial>^ GetMaterials();
			void SetMaterials( array<ExtendedMaterial>^ materials );

			array<EffectInstance>^ GetEffects();
			void SetEffects( array<EffectInstance>^ effects );

			array<int>^ GetAdjacency();
			void SetAdjacency( array<int>^ adjacency );

			property String^ Name
			{
				String^ get();
				void set( String^ value );
			}

			property MeshData^ Mesh
			{
				MeshData^ get();
				void set( MeshData^ value );
			}

			property SkinInfo^ SkinInfo
			{
				SlimDX::Direct3D9::SkinInfo^ get();
				void set( SlimDX::Direct3D9::SkinInfo^ value );
			}

			property MeshContainer^ NextMeshContainer
			{
				MeshContainer^ get();
				void set( MeshContainer^ value );
			}
		};

		public interface struct IAllocateHierarchy
		{
			virtual MeshContainer^ CreateMeshContainer( String^ name, MeshData^ meshData, array<ExtendedMaterial>^ materials,
				array<EffectInstance>^ effectInstances, array<int>^ adjacency, SkinInfo^ skinInfo ) = 0;

			virtual Frame^ CreateFrame( String^ name ) = 0;
			virtual void DestroyFrame( Frame^ frame ) = 0;
			virtual void DestroyMeshContainer( MeshContainer^ container ) = 0;
		};
		
		public interface struct ILoadUserData
		{
			virtual void LoadFrameData( Frame^ frame, XFileData^ data ) = 0;
			virtual void LoadMeshData( MeshContainer^ meshContainer, XFileData^ data ) = 0;
			virtual void LoadTopLevelData( XFileData^ data ) = 0;
		};

		public interface struct ISaveUserData
		{
			virtual void AddFrameChildData( Frame^ frame, XFileSaveObject^ saveObject, XFileSaveData^ saveData );
			virtual void AddMeshChildData( MeshContainer^ meshContainer, XFileSaveObject^ saveObject, XFileSaveData^ saveData );
			virtual void AddTopLevelDataPost( XFileSaveObject^ saveObject );
			virtual void AddTopLevelDataPre( XFileSaveObject^ saveObject );
			virtual void RegisterTemplates( XFile^ xfile );
			virtual void SaveTemplates( XFileSaveObject^ saveObject );
		};

		class IAllocateHierarchyShim : public ID3DXAllocateHierarchy
		{
		private:
			gcroot<IAllocateHierarchy^> m_WrappedInterface;

		public:
			IAllocateHierarchyShim( IAllocateHierarchy^ wrappedInterface );

			HRESULT WINAPI CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame );
			HRESULT WINAPI CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData,
				const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances,
				DWORD NumMaterials, const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo,
				LPD3DXMESHCONTAINER *ppNewMeshContainer );
			HRESULT WINAPI DestroyFrame( LPD3DXFRAME pFrameToFree );
			HRESULT WINAPI DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree );
		};

		class ILoadUserDataShim : public ID3DXLoadUserData
		{
		private:
			gcroot<ILoadUserData^> m_WrappedInterface;

		public:
			ILoadUserDataShim( ILoadUserData^ wrappedInterface );

			HRESULT WINAPI LoadFrameChildData( LPD3DXFRAME pFrame, LPD3DXFILEDATA pXofChildData );
			HRESULT WINAPI LoadMeshChildData( LPD3DXMESHCONTAINER pMeshContainer, LPD3DXFILEDATA pXofChildData );
			HRESULT WINAPI LoadTopLevelData( LPD3DXFILEDATA pXofChildData );
		};

		class ISaveUserDataShim : public ID3DXSaveUserData
		{
		private:
			gcroot<ISaveUserData^> m_WrappedInterface;

		public:
			ISaveUserDataShim( ISaveUserData^ wrappedInterface );

			HRESULT WINAPI AddFrameChildData( const D3DXFRAME *pFrame, LPD3DXFILESAVEOBJECT pXofSave, LPD3DXFILESAVEDATA pXofFrameData );
			HRESULT WINAPI AddMeshChildData( const D3DXMESHCONTAINER *pMeshContainer, LPD3DXFILESAVEOBJECT pXofSave, LPD3DXFILESAVEDATA pXofMeshData );
			HRESULT WINAPI AddTopLevelDataObjectsPost( LPD3DXFILESAVEOBJECT pXofSave );
			HRESULT WINAPI AddTopLevelDataObjectsPre( LPD3DXFILESAVEOBJECT pXofSave );
			HRESULT WINAPI RegisterTemplates( LPD3DXFILE pXFileApi );
			HRESULT WINAPI SaveTemplates( LPD3DXFILESAVEOBJECT pXofSave );
		};

		public ref class Frame
		{
		private:
			D3DXFRAME *m_Pointer;

		internal:
			Frame( const D3DXFRAME &frame );
			Frame( const D3DXFRAME *frame );

			property D3DXFRAME *Pointer
			{ 
				D3DXFRAME* get() { return m_Pointer; }
			}

			void Destruct();

		public:
			Frame();
			virtual ~Frame();
			!Frame();

			static Frame^ LoadHierarchyFromX( Device^ device, String^ fileName, MeshFlags options, 
				IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController );
			static Frame^ LoadHierarchyFromX( Device^ device, array<Byte>^ memory, MeshFlags options, 
				IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController );
			static Frame^ LoadHierarchyFromX( Device^ device, Stream^ stream, MeshFlags options, 
				IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController );

			static void SaveHierarchyToFile( String^ fileName, XFileFormat format, Frame^ root, 
				AnimationController^ animationController, ISaveUserData^ userDataSaver );
			static void SaveHierarchyToFile( String^ fileName, XFileFormat format, Frame^ root, 
				AnimationController^ animationController );

			void AppendChild( Frame^ child );
			Frame^ FindChild( String^ name );

			static BoundingSphere CalculateBoundingSphere( Frame^ root );
			static void DestroyHierarchy( Frame^ root, IAllocateHierarchy^ allocator );
			static int CountNamedFrames( Frame^ root );
			static void RegisterNamedMatrices( Frame^ root, AnimationController^ controller );

			property String^ Name
			{
				String^ get();
				void set( String^ value );
			}

			property Matrix TransformationMatrix
			{
				Matrix get();
				void set( Matrix value );
			}

			property MeshContainer^ MeshContainer
			{
				SlimDX::Direct3D9::MeshContainer^ get();
				void set( SlimDX::Direct3D9::MeshContainer^ value );
			}

			property Frame^ Sibling
			{
				Frame^ get();
				void set( Frame^ value );
			}

			property Frame^ FirstChild
			{
				Frame^ get();
				void set( Frame^ value );
			}
		};
	}
}
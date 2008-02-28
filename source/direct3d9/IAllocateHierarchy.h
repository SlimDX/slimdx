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
#pragma once

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class MeshContainer;
		ref class Frame;
		ref class MeshData;

		public interface struct IAllocateHierarchy
		{
			virtual MeshContainer^ CreateMeshContainer( System::String^ name, MeshData^ meshData, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effectInstances, array<int>^ adjacency, SkinInfo^ skinInfo ) = 0;
			virtual Frame^ CreateFrame( System::String^ name ) = 0;
			virtual void DestroyFrame( Frame^ frame ) = 0;
			virtual void DestroyMeshContainer( MeshContainer^ container ) = 0;
		};

		class IAllocateHierarchyShim : public ID3DXAllocateHierarchy
		{
		private:
			gcroot<IAllocateHierarchy^> m_WrappedInterface;

		public:
			IAllocateHierarchyShim( IAllocateHierarchy^ wrappedInterface );

			HRESULT WINAPI CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame );
			HRESULT WINAPI CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData, const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppNewMeshContainer );
			HRESULT WINAPI DestroyFrame( LPD3DXFRAME pFrameToFree );
			HRESULT WINAPI DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree );
		};
	}
}
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

#include "Device.h"
#include "Mesh.h"

namespace SlimDX
{
namespace Direct3D
{
	Mesh^ BaseMesh::Clone( Device^ device, MeshFlags flags, array<VertexElement>^ elements )
	{
		ID3DXMesh* mesh;
		pin_ptr<const VertexElement> pinned_elements = &elements[0];

		HRESULT hr = m_BaseMesh->CloneMesh( (DWORD) flags, (const D3DVERTEXELEMENT9*) pinned_elements,
			device->InternalPointer, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	void BaseMesh::DrawSubset( int subset )
	{
		HRESULT hr = m_BaseMesh->DrawSubset( subset );
		GraphicsException::CheckHResult( hr );
	}

	Mesh::Mesh( ID3DXMesh* mesh ) : BaseMesh( mesh ), m_Mesh( mesh )
	{
	}

	Mesh^ Mesh::FromStream( Device^ device, Stream^ stream, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		pin_ptr<unsigned char> pinned_data = &data[0];
		
		HRESULT hr = D3DXLoadMeshFromXInMemory( pinned_data, data->Length, (DWORD) flags,
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	Mesh^ Mesh::FromFile( Device^ device, String^ fileName, MeshFlags flags )
	{
		ID3DXMesh* mesh;
		pin_ptr<const wchar_t> pinned_name = PtrToStringChars( fileName );

		HRESULT hr = D3DXLoadMeshFromX( (LPCWSTR) pinned_name, (DWORD) flags, 
			device->InternalPointer, NULL, NULL, NULL, NULL, &mesh );
		GraphicsException::CheckHResult( hr );

		return gcnew Mesh( mesh );
	}

	void Mesh::ComputeTangentFrame( TangentOptions options )
	{
		HRESULT hr = D3DXComputeTangentFrame( m_Mesh, (DWORD) options );
		GraphicsException::CheckHResult( hr );
	}
}
}
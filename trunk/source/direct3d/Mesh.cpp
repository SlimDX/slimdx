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
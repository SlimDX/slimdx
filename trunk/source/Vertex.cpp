#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>

#include "Device.h"
#include "Vertex.h"

namespace SlimDX
{
namespace Direct3D
{
	VertexDeclaration::VertexDeclaration( Device^ device, array<VertexElement>^ elements )
	{
		pin_ptr<VertexElement> pinnedElements = &elements[0];
		IDirect3DVertexDeclaration9* decl;

		HRESULT hr = device->InternalPointer->CreateVertexDeclaration( (const D3DVERTEXELEMENT9*) pinnedElements, &decl );
		FAILED_THROW( hr );

		m_Decl = decl;
		m_Disposed = false;
	}
}
}

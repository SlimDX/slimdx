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

#include <d3d10.h>
#include <d3dx10.h>

#include "Error.h"

namespace SlimDX
{
namespace Direct3D10
{
	Error::Error()
	{
	}

	Result Error::InvalidCall::get()
	{
		return Result( D3DERR_INVALIDCALL );
	}
	
	Result Error::CannotModifyIndexBuffer::get()
	{
		return Result( D3DX10_ERR_CANNOT_MODIFY_INDEX_BUFFER );
	}
	
	Result Error::InvalidMesh::get()
	{
		return Result( D3DX10_ERR_INVALID_MESH );
	}
	
	Result Error::CannotSortByAttribute::get()
	{
		return Result( D3DX10_ERR_CANNOT_ATTR_SORT );
	}
	
	Result Error::SkinningNotSupported::get()
	{
		return Result( D3DX10_ERR_SKINNING_NOT_SUPPORTED );
	}
	
	Result Error::TooManyInfluences::get()
	{
		return Result( D3DX10_ERR_TOO_MANY_INFLUENCES );
	}
	
	Result Error::InvalidData::get()
	{
		return Result( D3DX10_ERR_INVALID_DATA );
	}
	
	Result Error::LoadedMeshHasNoData::get()
	{
		return Result( D3DX10_ERR_LOADED_MESH_HAS_NO_DATA );
	}
	
	Result Error::DuplicateNamedFragment::get()
	{
		return Result( D3DX10_ERR_DUPLICATE_NAMED_FRAGMENT );
	}
	
	Result Error::CannotRemoveLastItem::get()
	{
		return Result( D3DX10_ERR_CANNOT_REMOVE_LAST_ITEM );
	}
}
}
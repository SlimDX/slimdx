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

#include <d3d10.h>
#include "../ErrorCode.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		public ref class D3D10ErrorCode : ErrorCode
		{
		internal:
			D3D10ErrorCode() { }

		public:
			literal int FileNotFound = D3D10_ERROR_FILE_NOT_FOUND;
			literal int TooManyUniqueStateObjects = D3D10_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS;
			literal int InvalidCall = D3DERR_INVALIDCALL;
			literal int WasStillDrawing = D3DERR_WASSTILLDRAWING;
		};

		public ref class D3DX10ErrorCode : ErrorCode
		{
		internal:
			D3DX10ErrorCode() { }

		public:
			literal int CannotModifyIndexBuffer = D3DX10_ERR_CANNOT_MODIFY_INDEX_BUFFER;
			literal int InvalidMesh = D3DX10_ERR_INVALID_MESH;
			literal int CannotAttributeSort = D3DX10_ERR_CANNOT_ATTR_SORT;
			literal int SkinningNotSupported = D3DX10_ERR_SKINNING_NOT_SUPPORTED;
			literal int TooManyInfluences = D3DX10_ERR_TOO_MANY_INFLUENCES;
			literal int InvalidData = D3DX10_ERR_INVALID_DATA;
			literal int MeshHasNoData = D3DX10_ERR_LOADED_MESH_HAS_NO_DATA;
			literal int DuplicateNamedFragment = D3DX10_ERR_DUPLICATE_NAMED_FRAGMENT;
			literal int CannotRemoveLastItem = D3DX10_ERR_CANNOT_REMOVE_LAST_ITEM;
		};
	}
}
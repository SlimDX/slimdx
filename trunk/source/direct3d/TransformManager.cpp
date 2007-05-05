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

#include "../Exceptions.h"
#include "Device.h"
#include "Math.h"
#include "TransformManager.h"

namespace SlimDX
{
namespace Direct3D
{
	Matrix TransformManager::World::get()
	{
		Matrix matrix;
		m_Device->InternalPointer->GetTransform( D3DTS_WORLD, (D3DMATRIX*) &matrix );
		return matrix;
	}

	void TransformManager::World::set( Matrix value )
	{
		m_Device->InternalPointer->SetTransform( D3DTS_WORLD, (const D3DMATRIX*) &value );
	}

	Matrix TransformManager::View::get()
	{
		Matrix matrix;
		m_Device->InternalPointer->GetTransform( D3DTS_VIEW, (D3DMATRIX*) &matrix );
		return matrix;
	}

	void TransformManager::View::set( Matrix value )
	{
		m_Device->InternalPointer->SetTransform( D3DTS_VIEW, (const D3DMATRIX*) &value );
	}

	Matrix TransformManager::Projection::get()
	{
		Matrix matrix;
		m_Device->InternalPointer->GetTransform( D3DTS_PROJECTION, (D3DMATRIX*) &matrix );
		return matrix;
	}

	void TransformManager::Projection::set( Matrix value )
	{
		m_Device->InternalPointer->SetTransform( D3DTS_PROJECTION, (const D3DMATRIX*) &value );
	}
}
}

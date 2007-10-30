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

#include "../DirectXObject.h"
#include "../math/Math.h"
#include "GraphicsException.h"
#include "MatrixStack.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		MatrixStack::MatrixStack()
		{
			ID3DXMatrixStack* matrixStack;
			HRESULT hr = D3DXCreateMatrixStack( 0, &matrixStack );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				throw gcnew GraphicsException( "Failed to create MatrixStack." );

			m_Pointer = matrixStack;
		}

		void MatrixStack::Push()
		{
		}

		void MatrixStack::Pop()
		{
		}

		void MatrixStack::LoadIdentity()
		{
		}

		void MatrixStack::LoadMatrix( Matrix matrix )
		{
		}

		void MatrixStack::MultiplyMatrix( Matrix matrix )
		{
		}

		void MatrixStack::MultiplyMatrixLocal( Matrix matrix )
		{
		}

		void MatrixStack::RotateAxis( Vector3 axis, float angle )
		{
		}

		void MatrixStack::RotateAxisLocal( Vector3 axis, float angle )
		{
		}

		void MatrixStack::RotateYawPitchRoll( float yaw, float pitch, float roll )
		{
		}

		void MatrixStack::RotateYawPitchRollLocal( float yaw, float pitch, float roll )
		{
		}

		void MatrixStack::Scale( float x, float y, float z )
		{
		}

		void MatrixStack::ScaleLocal( float x, float y, float z )
		{
		}

		void MatrixStack::Translate( float x, float y, float z )
		{
		}

		void MatrixStack::TranslateLocal( float x, float y, float z )
		{
		}

		Matrix MatrixStack::Top::get()
		{
			return Matrix::Identity;
		}
	}
}

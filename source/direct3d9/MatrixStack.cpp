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

#include "../BaseObject.h"
#include "../math/Math.h"

#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

#include "MatrixStack.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		MatrixStack::MatrixStack( IntPtr pointer )
		{
			Construct( pointer, NativeInterface );
		}

		MatrixStack::MatrixStack()
		{
			ID3DXMatrixStack* matrixStack;
			HRESULT hr = D3DXCreateMatrixStack( 0, &matrixStack );
			Direct3D9ErrorHandler::TestForFailure( hr );
			if( FAILED( hr ) )
				throw gcnew Direct3D9Exception( "Failed to create MatrixStack." );

			Construct(matrixStack);
		}

		void MatrixStack::Push()
		{
			HRESULT hr = InternalPointer->Push();
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::Pop()
		{
			HRESULT hr = InternalPointer->Pop();
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::LoadIdentity()
		{
			HRESULT hr = InternalPointer->LoadIdentity();
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::LoadMatrix( Matrix matrix )
		{
			HRESULT hr = InternalPointer->LoadMatrix( reinterpret_cast<D3DXMATRIX*>( &matrix ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::MultiplyMatrix( Matrix matrix )
		{
			HRESULT hr = InternalPointer->MultMatrix( reinterpret_cast<D3DXMATRIX*>( &matrix ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::MultiplyMatrixLocal( Matrix matrix )
		{
			HRESULT hr = InternalPointer->MultMatrixLocal( reinterpret_cast<D3DXMATRIX*>( &matrix ) );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::RotateAxis( Vector3 axis, float angle )
		{
			HRESULT hr = InternalPointer->RotateAxis( reinterpret_cast<D3DXVECTOR3*>( &axis ), angle );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::RotateAxisLocal( Vector3 axis, float angle )
		{
			HRESULT hr = InternalPointer->RotateAxisLocal( reinterpret_cast<D3DXVECTOR3*>( &axis ), angle );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::RotateYawPitchRoll( float yaw, float pitch, float roll )
		{
			HRESULT hr = InternalPointer->RotateYawPitchRoll( yaw, pitch, roll );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::RotateYawPitchRollLocal( float yaw, float pitch, float roll )
		{
			HRESULT hr = InternalPointer->RotateYawPitchRollLocal( yaw, pitch, roll );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::Scale( float x, float y, float z )
		{
			HRESULT hr = InternalPointer->Scale( x, y, z );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::ScaleLocal( float x, float y, float z )
		{
			HRESULT hr = InternalPointer->ScaleLocal( x, y, z );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::Translate( float x, float y, float z )
		{
			HRESULT hr = InternalPointer->Translate( x, y, z );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		void MatrixStack::TranslateLocal( float x, float y, float z )
		{
			HRESULT hr = InternalPointer->TranslateLocal( x, y, z );
			Direct3D9ErrorHandler::TestForFailure( hr );
		}

		Matrix MatrixStack::Top::get()
		{
			D3DXMATRIX* top = InternalPointer->GetTop();
			Matrix result;
			*reinterpret_cast<D3DXMATRIX*>( &result ) = *top;

			return result;
		}
	}
}

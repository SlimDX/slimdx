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

namespace SlimDX
{
	value class Vector3;
	value class Matrix;

	namespace Direct3D9
	{
		public ref class MatrixStack : ComObject
		{
			COMOBJECT(ID3DXMatrixStack);

		public:
			MatrixStack( IntPtr pointer );
			MatrixStack();
			~MatrixStack() { Destruct(); }

			void Push();
			void Pop();

			void LoadIdentity();
			void LoadMatrix( Matrix matrix );
			void MultiplyMatrix( Matrix matrix );
			void MultiplyMatrixLocal( Matrix matrix );

			void RotateAxis( Vector3 axis, float angle );
			void RotateAxisLocal( Vector3 axis, float angle );
			void RotateYawPitchRoll( float yaw, float pitch, float roll );
			void RotateYawPitchRollLocal( float yaw, float pitch, float roll );

			void Scale( float x, float y, float z );
			void ScaleLocal( float x, float y, float z );

			void Translate( float x, float y, float z );
			void TranslateLocal( float x, float y, float z );

			property Matrix Top
			{
				Matrix get();
			}
		};
	}
}

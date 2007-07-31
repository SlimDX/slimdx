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
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
    namespace Direct3D
    {
        value class Viewport;
    }

	[StructLayout( LayoutKind::Sequential )]
	public value class Vector3
	{
	public:
		property float X;
		property float Y;
		property float Z;

		Vector3( float x, float y, float z );

		float Length();
		void Normalize();
		static Vector3 Normalize( Vector3 vec );

		static Vector3 TransformCoordinate( Vector3 coord, Matrix transform );
		static Vector3 TransformNormal( Vector3 normal, Matrix transform );

		static float Dot( Vector3 lhs, Vector3 rhs );
		static Vector3 Cross( Vector3 lhs, Vector3 rhs );
		static Vector3 Lerp( Vector3 start, Vector3 end, float factor );

		Vector3 Project( Direct3D::Viewport viewport, Matrix projection, Matrix view, Matrix world );
		Vector3 Unproject( Direct3D::Viewport viewport, Matrix projection, Matrix view, Matrix world );
		
		static Vector3 Minimize( Vector3 left, Vector3 right );
		static Vector3 Maximize( Vector3 left, Vector3 right );

		static Vector3 operator + ( Vector3 lhs, Vector3 rhs );
		static Vector3 operator - ( Vector3 lhs, Vector3 rhs );
		static Vector3 operator * ( Vector3 vec, float scale );
		static Vector3 operator * ( float scale, Vector3 vec );
	};
}

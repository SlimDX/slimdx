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

#include <d3dx9.h>

namespace SlimDX
{
	[StructLayout( LayoutKind::Sequential )]
	public value class Plane
	{
	public:
		property float A;
		property float B;
		property float C;
		property float D;

		static Plane FromPointNormal( Vector3 point, Vector3 normal );
		static Plane FromPoints( Vector3 p1, Vector3 p2, Vector3 p3 );

		void Normalize();

		static Plane Transform( Plane plane, Matrix transformation );
		static bool IntersectLine( Plane plane, Vector3 start, Vector3 end, [Out] Vector3% intersectPoint );

		float Dot( Vector3 point );
		float Dot( Vector4 point );

		static Plane operator * ( Plane plane, float scale );
	};
}

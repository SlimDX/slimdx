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
#pragma once

#include "Vector3.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	value class BoundingBox;
	value class BoundingSphere;
	value class Plane;

	/// <summary>
	/// Defines a ray in three dimensions, specified by a starting position and a direction.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Ray : System::IEquatable<Ray>
	{
	public:
		Vector3 Position;
		Vector3 Direction;

		Ray( Vector3 position, Vector3 direction );

		static bool Intersects( Ray ray, Plane plane, [Out] float% distance );
		static bool Intersects( Ray ray, Vector3 vertex1, Vector3 vertex2, Vector3 vector3, [Out] float% distance );
		static bool Intersects( Ray ray, BoundingBox box, [Out] float% distance );
		static bool Intersects( Ray ray, BoundingSphere sphere, [Out] float% distance );

		static bool operator == ( Ray left, Ray right );
		static bool operator != ( Ray left, Ray right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Ray other );
		static bool Equals( Ray% value1, Ray% value2 );
	};
}

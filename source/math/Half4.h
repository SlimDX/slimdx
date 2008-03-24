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

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	/// <summary>
	/// Defines a four component vector, using half precision floating point coordinates.
	/// </summary>
	[System::Serializable]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Half4 : System::IEquatable<Half4>
	{
	public:
		/// <summary>
		/// Gets or sets the X component of the vector.
		/// </summary>
		/// <value>The X component of the vector.</value>
		property Half X;

		/// <summary>
		/// Gets or sets the Y component of the vector.
		/// </summary>
		/// <value>The Y component of the vector.</value>
		property Half Y;

		/// <summary>
		/// Gets or sets the Z component of the vector.
		/// </summary>
		/// <value>The Z component of the vector.</value>
		property Half Z;

		/// <summary>
		/// Gets or sets the W component of the vector.
		/// </summary>
		/// <value>The W component of the vector.</value>
		property Half W;

		Half4( Half value );
		Half4( Half x, Half y, Half z, Half w );

		static bool operator == ( Half4 left, Half4 right );
		static bool operator != ( Half4 left, Half4 right );

		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Half4 other );
		static bool Equals( Half4% value1, Half4% value2 );
	};
}

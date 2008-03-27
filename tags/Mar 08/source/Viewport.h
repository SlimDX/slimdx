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

namespace SlimDX
{
	/// <summary>
	/// Defines a rectangular region of a render-target surface onto which 
	/// a 3D rendering is projected.
	/// </summary>
	public value class Viewport : System::IEquatable<Viewport>
	{
		int m_X;
		int m_Y;
		int m_Width;
		int m_Height;
		float m_MinZ;
		float m_MaxZ;

	public:
		/// <summary>
		/// Gets or sets the viewport's X position.
		/// </summary>
		property int X
		{
			int get();
			void set( int value );
		}
		
		/// <summary>
		/// Gets or sets the viewport's Y position.
		/// </summary>
		property int Y
		{
			int get();
			void set( int value );
		}
		
		/// <summary>
		/// Gets or sets the viewport's width.
		/// </summary>
		property int Width
		{
			int get();
			void set( int value );
		}
		
		/// <summary>
		/// Gets or sets the viewport's height.
		/// </summary>
		property int Height
		{
			int get();
			void set( int value );
		}

		/// <summary>
		/// Gets or sets the viewport's minimum Z depth.
		/// </summary>
		property float MinZ
		{
			float get();
			void set( float value );
		}
		
		/// <summary>
		/// Gets or sets the viewport's maximum Z depth.
		/// </summary>
		property float MaxZ
		{
			float get();
			void set( float value );
		}

		static bool operator == ( Viewport left, Viewport right );
		static bool operator != ( Viewport left, Viewport right );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Viewport other );
		static bool Equals( Viewport% value1, Viewport% value2 );
	};
}
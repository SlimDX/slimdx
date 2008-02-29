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
	value class Color3;
	value class Vector3;
	value class Vector4;
		
	[System::Runtime::InteropServices::StructLayout(System::Runtime::InteropServices::LayoutKind::Sequential)]
	public value class Color4
	{
	public:
		property float Red;
		property float Green;
		property float Blue;
		property float Alpha;

		Color4( float alpha, float red, float green, float blue );
		Color4( float red, float green, float blue );
		Color4( System::Drawing::Color color );
		Color4( Color3 color );
		Color4( Vector3 color );
		Color4( Vector4 color );
		Color4( int argb );

		Color3 ToColor3();
		System::Drawing::Color ToColor();
		int ToArgb();
		Vector3 ToVector3();
		Vector4 ToVector4();

		static Color4 Add( Color4 color1, Color4 color2 );
		static void Add( Color4% color1, Color4% color2, [Out] Color4% result );

		static Color4 Subtract( Color4 color1, Color4 color2 );
		static void Subtract( Color4% color1, Color4% color2, [Out] Color4% result );

		static Color4 Modulate( Color4 color1, Color4 color2 );
		static void Modulate( Color4% color1, Color4% color2, [Out] Color4% result );

		static Color4 Lerp( Color4 color1, Color4 color2, float amount );
		static void Lerp( Color4% color1, Color4% color2, float amount, [Out] Color4% result );

		static Color4 Negate( Color4 color );
		static void Negate( Color4% color, [Out] Color4% result );

		static Color4 Scale( Color4 color, float scale );
		static void Scale( Color4% color, float scale, [Out] Color4% result );

		static Color4 AdjustContrast( Color4 color, float contrast );
		static void AdjustContrast( Color4% color, float contrast, [Out] Color4% result );

		static Color4 AdjustSaturation( Color4 color, float saturation );
		static void AdjustSaturation( Color4% color, float saturation, [Out] Color4% result );

		static Color4 operator + ( Color4 left, Color4 right );
		static Color4 operator - ( Color4 left, Color4 right );
		static Color4 operator - ( Color4 value );
		static Color4 operator * ( Color4 value, float scale );
		static Color4 operator * ( float scale, Color4 vector );
		static Color4 operator * ( Color4 color1, Color4 color2 );

		static bool operator == ( Color4 left, Color4 right );
		static bool operator != ( Color4 left, Color4 right );

		static explicit operator int( Color4 value );
		static explicit operator Color3( Color4 value );
		static explicit operator Vector3( Color4 value );
		static explicit operator Vector4( Color4 value );

		static explicit operator Color4( int value );
		static explicit operator Color4( Color3 value );
		static explicit operator Color4( Vector3 value );
		static explicit operator Color4( Vector4 value );

		static operator Color4( System::Drawing::Color value );
		static operator System::Drawing::Color( Color4 value );

		virtual System::String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( System::Object^ obj ) override;
		virtual bool Equals( Color4 other );
		static bool Equals( Color4% value1, Color4% value2 );
	};
}
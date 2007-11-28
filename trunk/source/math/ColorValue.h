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

using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class ColorValue
	{
	internal:
		static ColorValue FromUnmanaged( const D3DXCOLOR &color );

	public:
		property float Red;
		property float Green;
		property float Blue;
		property float Alpha;

		ColorValue( float alpha, float red, float green, float blue );
		ColorValue( float red, float green, float blue );

		static ColorValue FromColor( Color color );
		Color ToColor();
		int ToArgb();

		static ColorValue Add( ColorValue color1, ColorValue color2 );
		static void Add( ColorValue% color1, ColorValue% color2, [Out] ColorValue% result );

		static ColorValue Subtract( ColorValue color1, ColorValue color2 );
		static void Subtract( ColorValue% color1, ColorValue% color2, [Out] ColorValue% result );

		static ColorValue Modulate( ColorValue color1, ColorValue color2 );
		static void Modulate( ColorValue% color1, ColorValue% color2, [Out] ColorValue% result );

		static ColorValue Lerp( ColorValue color1, ColorValue color2, float amount );
		static void Lerp( ColorValue% color1, ColorValue% color2, float amount, [Out] ColorValue% result );

		static ColorValue Negative( ColorValue color );
		static void Negative( ColorValue% color, [Out] ColorValue% result );

		static ColorValue Scale( ColorValue color, float scale );
		static void Scale( ColorValue% color, float scale, [Out] ColorValue% result );

		static ColorValue AdjustContrast( ColorValue color, float contrast );
		static void AdjustContrast( ColorValue% color, float contrast, [Out] ColorValue% result );

		static ColorValue AdjustSaturation( ColorValue color, float saturation );
		static void AdjustSaturation( ColorValue% color, float saturation, [Out] ColorValue% result );

		static ColorValue operator + ( ColorValue left, ColorValue right );
		static ColorValue operator - ( ColorValue left, ColorValue right );
		static ColorValue operator - ( ColorValue value );
		static ColorValue operator * ( ColorValue value, float scale );
		static ColorValue operator * ( float scale, ColorValue vector );
		static ColorValue operator * ( ColorValue color1, ColorValue color2 );

		static bool operator == ( ColorValue left, ColorValue right );
		static bool operator != ( ColorValue left, ColorValue right );

		virtual String^ ToString() override;
		virtual int GetHashCode() override;
		virtual bool Equals( Object^ obj ) override;
		virtual bool Equals( ColorValue other );
		static bool Equals( ColorValue% value1, ColorValue% value2 );
	};
}
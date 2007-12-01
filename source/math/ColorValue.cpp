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
#include <windows.h>
#include <d3dx9.h>

#include "Math.h"

namespace SlimDX
{
	ColorValue ColorValue::FromUnmanaged( const D3DXCOLOR &color )
	{
		return ColorValue( color.a, color.r, color.g, color.b );
	}

	ColorValue::ColorValue( float alpha, float red, float green, float blue )
	{
		Alpha = alpha;
		Red = red;
		Green = green;
		Blue = blue;
	}

	ColorValue::ColorValue( float red, float green, float blue )
	{
		Alpha = 1.0f;
		Red = red;
		Green = green;
		Blue = blue;
	}

	ColorValue::ColorValue( Color color )
	{
		Alpha = color.A / 255.0f;
		Red = color.R / 255.0f;
		Green = color.G / 255.0f;
		Blue = color.B / 255.0f;
	}

	ColorValue::ColorValue( int argb )
	{
		Alpha = ( ( argb >> 24 ) & 255 ) / 255.0f;
		Red = ( ( argb >> 16 ) & 255 ) / 255.0f;
		Green = ( ( argb >> 8 ) & 255 ) / 255.0f;
		Blue = ( argb & 255 ) / 255.0f;
	}

	Color ColorValue::ToColor()
	{
		return Color::FromArgb( (int)Alpha * 255, (int)Red * 255, (int)Green * 255, (int)Blue * 255 );
	}

	int ColorValue::ToArgb()
	{
		unsigned int a, r, g, b;

		a = (unsigned int) (Alpha * 255.0f);
		r = (unsigned int) (Red * 255.0f);
		g = (unsigned int) (Green * 255.0f);
		b = (unsigned int) (Blue * 255.0f);

		unsigned int value = b;
		value += g << 8;
		value += r << 16;
		value += a << 24;

		return (int) value;
	}

	ColorValue ColorValue::Add( ColorValue color1, ColorValue color2 )
	{
		return ColorValue( color1.Alpha + color2.Alpha, color1.Red + color2.Red, color1.Green + color2.Green, color1.Blue + color2.Blue );
	}

	void ColorValue::Add( ColorValue% color1, ColorValue% color2, [Out] ColorValue% result )
	{
		result = ColorValue( color1.Alpha + color2.Alpha, color1.Red + color2.Red, color1.Green + color2.Green, color1.Blue + color2.Blue );
	}

	ColorValue ColorValue::Subtract( ColorValue color1, ColorValue color2 )
	{
		return ColorValue( color1.Alpha - color2.Alpha, color1.Red - color2.Red, color1.Green - color2.Green, color1.Blue - color2.Blue );
	}

	void ColorValue::Subtract( ColorValue% color1, ColorValue% color2, [Out] ColorValue% result )
	{
		result = ColorValue( color1.Alpha - color2.Alpha, color1.Red - color2.Red, color1.Green - color2.Green, color1.Blue - color2.Blue );
	}

	ColorValue ColorValue::Modulate( ColorValue color1, ColorValue color2 )
	{
		return ColorValue( color1.Alpha * color2.Alpha, color1.Red * color2.Red, color1.Green * color2.Green, color1.Blue * color2.Blue );
	}

	void ColorValue::Modulate( ColorValue% color1, ColorValue% color2, [Out] ColorValue% result )
	{
		result = ColorValue( color1.Alpha * color2.Alpha, color1.Red * color2.Red, color1.Green * color2.Green, color1.Blue * color2.Blue );
	}

	ColorValue ColorValue::Lerp( ColorValue color1, ColorValue color2, float amount )
	{
		float a = color1.Alpha + amount * ( color2.Alpha - color1.Alpha );
		float r = color1.Red + amount * ( color2.Red - color1.Red );
		float g = color1.Green + amount * ( color2.Green - color1.Green );
		float b = color1.Blue + amount * ( color2.Blue - color1.Blue );

		return ColorValue( a, r, g, b );
	}

	void ColorValue::Lerp( ColorValue% color1, ColorValue% color2, float amount, [Out] ColorValue% result )
	{
		float a = color1.Alpha + amount * ( color2.Alpha - color1.Alpha );
		float r = color1.Red + amount * ( color2.Red - color1.Red );
		float g = color1.Green + amount * ( color2.Green - color1.Green );
		float b = color1.Blue + amount * ( color2.Blue - color1.Blue );

		result = ColorValue( a, r, g, b );
	}

	ColorValue ColorValue::Negative( ColorValue color )
	{
		return ColorValue( 1.0f - color.Alpha, 1.0f - color.Red, 1.0f - color.Green, 1.0f - color.Blue );
	}

	void ColorValue::Negative( ColorValue% color, [Out] ColorValue% result )
	{
		result = ColorValue( 1.0f - color.Alpha, 1.0f - color.Red, 1.0f - color.Green, 1.0f - color.Blue );
	}

	ColorValue ColorValue::AdjustContrast( ColorValue color, float contrast )
	{
		float r = 0.5f + contrast * ( color.Red - 0.5f );
		float g = 0.5f + contrast * ( color.Green - 0.5f );
		float b = 0.5f + contrast * ( color.Blue - 0.5f );

		return ColorValue( color.Alpha, r, g, b );
	}

	void ColorValue::AdjustContrast( ColorValue% color, float contrast, [Out] ColorValue% result )
	{
		float r = 0.5f + contrast * ( color.Red - 0.5f );
		float g = 0.5f + contrast * ( color.Green - 0.5f );
		float b = 0.5f + contrast * ( color.Blue - 0.5f );

		result = ColorValue( color.Alpha, r, g, b );
	}

	ColorValue ColorValue::AdjustSaturation( ColorValue color, float saturation )
	{
		float grey = color.Red * 0.2125f + color.Green * 0.7154f + color.Blue * 0.0721f;
		float r = grey + saturation * ( color.Red - grey );
		float g = grey + saturation * ( color.Green - grey );
		float b = grey + saturation * ( color.Blue - grey );

		return ColorValue( color.Alpha, r, g, b );
	}

	void ColorValue::AdjustSaturation( ColorValue% color, float saturation, [Out] ColorValue% result )
	{
		float grey = color.Red * 0.2125f + color.Green * 0.7154f + color.Blue * 0.0721f;
		float r = grey + saturation * ( color.Red - grey );
		float g = grey + saturation * ( color.Green - grey );
		float b = grey + saturation * ( color.Blue - grey );

		result = ColorValue( color.Alpha, r, g, b );
	}

	ColorValue ColorValue::Scale( ColorValue color, float scale )
	{
		return ColorValue( color.Alpha, color.Red * scale, color.Green * scale, color.Blue * scale );
	}

	void ColorValue::Scale( ColorValue% color, float scale, [Out] ColorValue% result )
	{
		result = ColorValue( color.Alpha, color.Red * scale, color.Green * scale, color.Blue * scale );
	}

	ColorValue ColorValue::operator + ( ColorValue color1, ColorValue color2 )
	{
		return ColorValue( color1.Alpha + color2.Alpha, color1.Red + color2.Red, color1.Green + color2.Green, color1.Blue + color2.Blue );
	}

	ColorValue ColorValue::operator - ( ColorValue color1, ColorValue color2 )
	{
		return ColorValue( color1.Alpha - color2.Alpha, color1.Red - color2.Red, color1.Green - color2.Green, color1.Blue - color2.Blue );
	}

	ColorValue ColorValue::operator - ( ColorValue color )
	{
		return ColorValue( 1.0f - color.Alpha, 1.0f - color.Red, 1.0f - color.Green, 1.0f - color.Blue );
	}

	ColorValue ColorValue::operator * ( ColorValue color1, ColorValue color2 )
	{
		return ColorValue( color1.Alpha * color2.Alpha, color1.Red * color2.Red, color1.Green * color2.Green, color1.Blue * color2.Blue );
	}

	ColorValue ColorValue::operator * ( ColorValue color, float scale )
	{
		return ColorValue( color.Alpha, color.Red * scale, color.Green * scale, color.Blue * scale );
	}

	ColorValue ColorValue::operator * ( float scale, ColorValue value )
	{
		return value * scale;
	}

	bool ColorValue::operator == ( ColorValue left, ColorValue right )
	{
		return ColorValue::Equals( left, right );
	}

	bool ColorValue::operator != ( ColorValue left, ColorValue right )
	{
		return !ColorValue::Equals( left, right );
	}

	String^ ColorValue::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "A:{0} R:{1} G:{2} B:{3}", 
			Alpha.ToString(CultureInfo::CurrentCulture), Red.ToString(CultureInfo::CurrentCulture), 
			Green.ToString(CultureInfo::CurrentCulture), Blue.ToString(CultureInfo::CurrentCulture) );
	}

	int ColorValue::GetHashCode()
	{
		return Alpha.GetHashCode() + Red.GetHashCode() + Green.GetHashCode() + Blue.GetHashCode();
	}

	bool ColorValue::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ColorValue>( value ) );
	}

	bool ColorValue::Equals( ColorValue value )
	{
		return ( Alpha == value.Alpha && Red == value.Red && Green == value.Green && Blue == value.Blue );
	}

	bool ColorValue::Equals( ColorValue% value1, ColorValue% value2 )
	{
		return ( value1.Alpha == value2.Alpha && value1.Red == value2.Red && value1.Green == value2.Green && value1.Blue == value2.Blue );
	}
}
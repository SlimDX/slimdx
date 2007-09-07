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

/*
This header serves as a storage point for types which are needed in multiple
places but don't really have a proper home. ALL of the contents of this file
should be considered to be misplaced for now.
*/
namespace SlimDX
{
	namespace Direct3D
	{
		public value class ColorValue
		{
		private:
			float alpha, red, green, blue;

		public:
			property float Alpha
            {
                float get() { return alpha; }
                void set( float value ) { alpha = value; }
            }

			property float Red
            {
                float get() { return red; }
                void set( float value ) { red = value; }
            }

			property float Green
            {
                float get() { return green; }
                void set( float value ) { green = value; }
            }

			property float Blue
            {
                float get() { return blue; }
                void set( float value ) { blue = value; }
            }

			ColorValue( float alpha, float red, float green, float blue )
			{
				Alpha = alpha;
				Red = red;
				Green = green;
				Blue = blue;
			}

			ColorValue( float red, float green, float blue )
			{
				Alpha = 1.0f;
				Red = red;
				Green = green;
				Blue = blue;
			}

			static ColorValue FromColor( System::Drawing::Color color )
			{
				ColorValue value;

				value.Alpha = color.A / 255.0f;
				value.Red = color.R / 255.0f;
				value.Green = color.G / 255.0f;
				value.Blue = color.B / 255.0f;

				return value;
			}

			int ToArgb()
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
		};
	}
}
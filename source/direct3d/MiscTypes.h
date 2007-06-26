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
		public:
			float Alpha, Red, Green, Blue;

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
				//TODO: Write this
				return 0;
			}
		};

		public value class Material
		{
		public:
			ColorValue Diffuse;
			ColorValue Ambient;
			ColorValue Specular;
			ColorValue Emissive;
			float Power;
		};

		public value class Viewport
		{
			int X, Y;
			int Width, Height;
			float MinZ, MaxZ;
		};
    }
}
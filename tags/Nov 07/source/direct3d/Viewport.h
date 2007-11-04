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
		public value class Viewport
		{
		private:
			int x;
			int y;
			int width;
			int height;
			float minZ;
			float maxZ;

		public:
			property int X
			{
				int get() { return x; }
				void set( int value ) { x = value; }
			}

			property int Y
			{
				int get() { return y; }
				void set( int value ) { y = value; }
			}

			property int Width
			{
				int get() { return width; }
				void set( int value ) { width = value; }
			}

			property int Height
			{
				int get() { return height; }
				void set( int value ) { height = value; }
			}

			property float MinZ
			{
				float get() { return minZ; }
				void set( float value ) { minZ = value; }
			}

			property float MaxZ
			{
				float get() { return maxZ; }
				void set( float value ) { maxZ = value; }
			}
		};
	}
}
/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "Operation.h"
#include "Primitives.h"

namespace SlimMath
{
	public ref class ColorOps sealed
	{
	private:
		ColorOps() { }

	public:
		static Operation<Handle<Color>^>^ AdjustContrast(Handle<Color>^ color, Handle<float>^ contrast);
		static Operation<Handle<Color>^>^ AdjustSaturation(Handle<Color>^ color, Handle<float>^ saturation);
		static Operation<Handle<bool>^>^ IsEqual(Handle<Color>^ color1, Handle<Color>^ color2);
		static Operation<Handle<bool>^>^ IsGreater(Handle<Color>^ color1, Handle<Color>^ color2);
		static Operation<Handle<bool>^>^ IsGreaterOrEqual(Handle<Color>^ color1, Handle<Color>^ color2);
		static Operation<Handle<bool>^>^ IsInfinite(Handle<Color>^ color);
		static Operation<Handle<bool>^>^ IsNaN(Handle<Color>^ color);
		static Operation<Handle<bool>^>^ IsLess(Handle<Color>^ color1, Handle<Color>^ color2);
		static Operation<Handle<bool>^>^ IsLessOrEqual(Handle<Color>^ color1, Handle<Color>^ color2);
		static Operation<Handle<Color>^>^ Modulate(Handle<Color>^ color1, Handle<Color>^ color2);
		static Operation<Handle<Color>^>^ Negate(Handle<Color>^ color);
		static Operation<Handle<bool>^>^ IsNotEqual(Handle<Color>^ color1, Handle<Color>^ color2);
	};
}

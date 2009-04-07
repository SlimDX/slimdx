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

#include <windows.h>
#include <xnamath.h>

#include "..\native\NativeOperations.h"

#include "Handle.h"
#include "ColorOperations.h"

using namespace System;

namespace SlimMath
{
	Operation<Handle<Color>^>^ ColorOps::AdjustContrast(Handle<Color>^ color, Handle<float>^ contrast)
	{
		return gcnew Operation<Handle<Color>^>(gcnew Handle<Color>(), gcnew array<BaseHandle^>(2) { color, contrast },
			NativeOperation::ColorAdjustContrast);
	}

	Operation<Handle<Color>^>^ ColorOps::AdjustSaturation(Handle<Color>^ color, Handle<float>^ saturation)
	{
		return gcnew Operation<Handle<Color>^>(gcnew Handle<Color>(), gcnew array<BaseHandle^>(2) { color, saturation },
			NativeOperation::ColorAdjustSaturation);
	}

	Operation<Handle<bool>^>^ ColorOps::IsEqual(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorEqual);
	}

	Operation<Handle<bool>^>^ ColorOps::IsGreater(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorGreater);
	}

	Operation<Handle<bool>^>^ ColorOps::IsGreaterOrEqual(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorGreaterOrEqual);
	}

	Operation<Handle<bool>^>^ ColorOps::IsInfinite(Handle<Color>^ color)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(1) { color },
			NativeOperation::ColorIsInfinite);
	}

	Operation<Handle<bool>^>^ ColorOps::IsNaN(Handle<Color>^ color)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(1) { color },
			NativeOperation::ColorIsNaN);
	}

	Operation<Handle<bool>^>^ ColorOps::IsLess(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorLess);
	}

	Operation<Handle<bool>^>^ ColorOps::IsLessOrEqual(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorLessOrEqual);
	}

	Operation<Handle<Color>^>^ ColorOps::Modulate(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<Color>^>(gcnew Handle<Color>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorModulate);
	}

	Operation<Handle<Color>^>^ ColorOps::Negate(Handle<Color>^ color)
	{
		return gcnew Operation<Handle<Color>^>(gcnew Handle<Color>(), gcnew array<BaseHandle^>(1) { color },
			NativeOperation::ColorNegative);
	}

	Operation<Handle<bool>^>^ ColorOps::IsNotEqual(Handle<Color>^ color1, Handle<Color>^ color2)
	{
		return gcnew Operation<Handle<bool>^>(gcnew Handle<bool>(), gcnew array<BaseHandle^>(2) { color1, color2 },
			NativeOperation::ColorNotEqual);
	}
}
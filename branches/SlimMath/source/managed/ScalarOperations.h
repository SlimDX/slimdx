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
#include "SinCosHandle.h"

namespace SlimMath
{
	public ref class ScalarOps sealed
	{
	private:
		ScalarOps() { }

	public:
		static Operation<Handle<float>^>^ Acos(Handle<float>^ angle);
		static Operation<Handle<float>^>^ AcosEstimate(Handle<float>^ angle);
		static Operation<Handle<float>^>^ Asin(Handle<float>^ angle);
		static Operation<Handle<float>^>^ AsinEstimate(Handle<float>^ angle);
		static Operation<Handle<float>^>^ Cos(Handle<float>^ angle);
		static Operation<Handle<float>^>^ CosEstimate(Handle<float>^ angle);
		static Operation<Handle<float>^>^ Sin(Handle<float>^ angle);
		static Operation<Handle<float>^>^ SinEstimate(Handle<float>^ angle);
		static Operation<Handle<float>^>^ ModAngle(Handle<float>^ angle);
		static Operation<Handle<bool>^>^ IsNearlyEqual(Handle<float>^ value1, Handle<float>^ value2, Handle<float>^ epsilon);
		static Operation<SinCosHandle^>^ SinCos(Handle<float>^ angle);
		static Operation<SinCosHandle^>^ SinCosEstimate(Handle<float>^ angle);
	};
}

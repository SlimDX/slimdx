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

#include "Operation.h"

using namespace System;

namespace SlimMath
{
	generic<typename T>
	Operation<T>::Operation(Handle<T>^ result, array<IntPtr>^ parameters, int op)
	{
		this->result = result;
		this->parameters = parameters;
		this->op = op;

		results = gcnew array<IntPtr>(1);
		results[0] = result->RawData;
	}

	generic<typename T, typename U, typename V>
	CompoundOperation<T, U, V>::CompoundOperation(CompoundHandle<T, U, V>^ result, array<IntPtr>^ parameters, int op)
	{
		this->result = result;
		this->parameters = parameters;
		this->op = op;

		int length = 2;
		if(result->ThirdResult != nullptr)
			length = 3;

		results = gcnew array<IntPtr>(length);
		results[0] = result->FirstResult->RawData;
		results[1] = result->SecondResult->RawData;
		
		if(result->ThirdResult != nullptr)
			results[2] = result->ThirdResult->RawData;
	}
}
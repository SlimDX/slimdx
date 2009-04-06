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

#include <memory>

#include "Handle.h"

using namespace System;

namespace SlimMath {
	generic<typename T>
	Handle<T>::Handle() {
		data = new float[sizeof(T)];
	}

	generic<typename T>
	Handle<T>::Handle(T value) {
		data = new float[sizeof(T)];
		memcpy(data, &value, sizeof(T));
	}

	generic<typename T>
	Handle<T>::operator SlimMath::Handle<T>^ (T value) {
		return gcnew Handle<T>(value);
	}

	generic<typename T>
	T Handle<T>::GetData() {
		T t;
		memcpy(&t, data, sizeof(T));
		return t;
	}

	generic<typename T, typename U, typename V>
	CompoundHandle<T, U, V>::CompoundHandle(Handle<T>^ handle1, Handle<U>^ handle2, Handle<V>^ handle3) {
		firstResult = handle1;
		secondResult = handle2;
		thirdResult = handle3;
	}
}
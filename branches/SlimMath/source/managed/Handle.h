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

namespace SlimMath {
	public ref struct IHandle abstract {
		property System::IntPtr RawData {
			System::IntPtr get() { return System::IntPtr(data); };
		}

	internal:
		float* data;
	};

	generic<typename T> where T : value class
	public ref class Handle sealed : IHandle {
	internal:
		Handle();
		Handle(T value);

	public:
		T GetData();

		static operator Handle<T>^ (T value);
	};

	generic<typename T, typename U, typename V> where T : value class where U : value class where V : value class
	public ref class CompoundHandle sealed {
	private:
		Handle<T>^ firstResult;
		Handle<U>^ secondResult;
		Handle<V>^ thirdResult;

	internal:
		CompoundHandle(Handle<T>^ handle1, Handle<U>^ handle2, Handle<V>^ handle3);

	public:
		property Handle<T>^ FirstResult {
			Handle<T>^ get() { return firstResult; }
		}

		property Handle<U>^ SecondResult {
			Handle<U>^ get() { return secondResult; }
		}

		property Handle<V>^ ThirdResult {
			Handle<V>^ get() { return thirdResult; }
		}
	};
}
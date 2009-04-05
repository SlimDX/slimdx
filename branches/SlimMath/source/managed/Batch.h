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
#include "Handle.h"

namespace SlimMath {
	class BatchProcessor;

	public ref class Batch {
	private:
		BatchProcessor* processor;
		System::Collections::Generic::List<IOperation^>^ operations;

		void Destruct();

	public:
		Batch();
		!Batch();
		~Batch();

		generic<typename T> where T : value class
		Handle<T>^ Add(Operation<T>^ operation);

		generic<typename T, typename U, typename V> where T : value class where U : value class where V : value class
		CompoundHandle<T, U, V>^ Add(CompoundOperation<T, U, V>^ operation);

		generic<typename T, typename U> where T : value class where U : value class
		void Batch::Add(TransformVector4ArrayOperation<T, U>^ operation);

		void Process();
	};
}

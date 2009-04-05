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
#include <vector>

#include "..\native\BatchProcessor.h"

#include "Batch.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SlimMath {
	Batch::Batch() {
		operations = gcnew List<IOperation^>();
		processor = new BatchProcessor();
	}

	Batch::~Batch() {
		Destruct();
	}

	Batch::!Batch() {
		Destruct();
	}

	void Batch::Destruct() {
		delete processor;
		processor = 0;
	}

	generic<typename T>
	Handle<T>^ Batch::Add(Operation<T>^ operation) {
		operations->Add(operation);
		return safe_cast<Handle<T>^>(operation->Result);
	}

	generic<typename T, typename U, typename V>
	CompoundHandle<T, U, V>^ Batch::Add(CompoundOperation<T, U, V>^ operation) {
		operations->Add(operation);
		return operation->Result;
	}

	void Batch::Process() {
		std::vector<OpDescriptor> descriptors(operations->Count);

		for(int i = 0; i < operations->Count; ++i) {
			descriptors[i].Op = static_cast<NativeOperation::Ops>(operations[i]->Op);

			for(int j = 0; j < operations[i]->Parameters->Length; ++j)
				descriptors[i].Parameters[j].Data = static_cast<float*>(operations[i]->Parameters[j].ToPointer());

			for(int j = 0; j < operations[i]->Results->Length; ++j)
				descriptors[i].Results[j].Data = static_cast<float*>(operations[i]->Results[j].ToPointer());
		}

		processor->Process(&descriptors[0], operations->Count);
	}
}

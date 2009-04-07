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

#include "..\native\BatchProcessor.h"

#include "Batch.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SlimMath
{
	Batch::Batch()
	{
		operations = gcnew List<BaseOperation^>();
	}

	Batch::Batch(int capacity)
	{
		operations = gcnew List<BaseOperation^>(capacity);
	}

	Batch::Batch(IEnumerable<BaseOperation^>^ collection)
	{
		operations = gcnew List<BaseOperation^>(collection);
	}

	generic<typename T>
	T Batch::Add(Operation<T>^ operation)
	{
		operations->Add(operation);
		return operation->Result;
	}

	void Batch::Process()
	{
		OpDescriptor* descriptors = new OpDescriptor[operations->Count];

		for (int i = 0; i < operations->Count; ++i)
		{
			descriptors[i].Op = operations[i]->Op;

			for (int j = 0; j < operations[i]->Parameters->Length; ++j)
				descriptors[i].Parameters[j].Data = operations[i]->Parameters[j]->Data;

			descriptors[i].Result.Data = operations[i]->InternalResult->Data;
		}
		
		BatchProcessor processor;
		processor.Process(descriptors, operations->Count);

		delete[] descriptors;
	}

	void Batch::Clear()
	{
		for (int i = 0; i < operations->Count; i++)
			delete operations[i];

		operations->Clear();
	}
}

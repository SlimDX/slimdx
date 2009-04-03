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

#include "Batch.h"
#include <windows.h>
#include <xnamath.h>
#include "..\native\BatchProcessor.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SlimMath
{
	Batch::Batch()
	{
		handles = gcnew List<Handle^>();
		processor = new BatchProcessor();
	}

	Batch::~Batch()
	{
		delete processor;
		processor = 0;
	}

	Handle^ Batch::Add(IOperation^ operation)
	{
		Handle^ handle = operation->GetHandle();
		handles->Add(handle);

		return handle;
	}

	void Batch::Process() {
		OpDescriptor* descriptors = new OpDescriptor[handles->Count];

		for(int i = 0; i < handles->Count; ++i)
		{
			descriptors[i].Op = static_cast<Operation::Ops>(handles[i]->Operation);
			descriptors[i].Parameters = handles[i]->Data;
			descriptors[i].Results = handles[i]->Data + handles[i]->ResultOffset;
		}

		processor->Process(descriptors, handles->Count);
		delete descriptors;
	}
}

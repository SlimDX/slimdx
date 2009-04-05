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

#include "Handle.h"

namespace SlimMath
{
	public interface struct IOperation
	{
		property array<System::IntPtr>^ Parameters
		{
			virtual array<System::IntPtr>^ get() = 0;
		}

		property array<System::IntPtr>^ Results
		{
			virtual array<System::IntPtr>^ get() = 0;
		}

		property int Op
		{
			virtual int get() = 0;
		}
	};

	generic<typename T> where T : value class
	public ref class Operation sealed : IOperation
	{
	private:
		array<System::IntPtr>^ parameters;
		array<System::IntPtr>^ results;
		IHandle^ result;
		int op;

	internal:
		Operation(Handle<T>^ result, array<System::IntPtr>^ parameters, int op);

	public:
		property array<System::IntPtr>^ Parameters
		{
			virtual array<System::IntPtr>^ get() { return parameters; }
		}

		property array<System::IntPtr>^ Results
		{
			virtual array<System::IntPtr>^ get() { return results; }
		}

		property int Op
		{
			virtual int get() { return op; }
		}

		property IHandle^ Result
		{
			virtual IHandle^ get() { return result; }
		}
	};

	public ref class CompoundOperation sealed : IOperation
	{
	private:
		array<System::IntPtr>^ parameters;
		array<System::IntPtr>^ results;
		CompoundHandle^ result;
		int op;

	internal:
		CompoundOperation(CompoundHandle^ result, array<System::IntPtr>^ parameters, int op);

	public:
		property array<System::IntPtr>^ Parameters
		{
			virtual array<System::IntPtr>^ get() { return parameters; }
		}

		property array<System::IntPtr>^ Results
		{
			virtual array<System::IntPtr>^ get() { return results; }
		}

		property int Op
		{
			virtual int get() { return op; }
		}

		property CompoundHandle^ Result
		{
			CompoundHandle^ get() { return result; }
		}
	};
}
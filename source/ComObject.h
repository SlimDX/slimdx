/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include <unknwn.h>

#include "Configuration.h"
#include "ObjectTracker.h"
#include "Result.h"
#include "Utilities.h"

#define COMOBJECT(type) \
	internal: \
	static property System::Guid NativeInterface { System::Guid get() { return Utilities::ConvertNativeGuid( IID_ ## type ); } } \
	property type* InternalPointer { type* get() { type* result = 0; UnknownPointer->QueryInterface( IID_ ## type, reinterpret_cast<void**>( &result ) ); return result; } } \
	private:

namespace SlimDX
{
	public ref class ComObject abstract
	{
		IUnknown* m_Unknown;
	
	private:
		
	
	protected:
		ComObject();
		
		void Construct( IUnknown* pointer );
		void Construct( System::IntPtr pointer, System::Guid guid );
		void Destruct();
	
	internal:
		virtual void DisposeHandler( System::Object^ sender, System::EventArgs^ e );

		property IUnknown* UnknownPointer
		{
			IUnknown* get();
		}

	public:
		property bool Disposed
		{
			bool get();
		}

		property System::IntPtr ComPointer
		{
			System::IntPtr get();
		}

		virtual ~ComObject();
	};
}
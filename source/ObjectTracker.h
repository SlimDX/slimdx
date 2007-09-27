/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;
using namespace System::Globalization;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;

namespace SlimDX
{
	ref class ObjectTracker
	{
	private:
		ObjectTracker() { }

		static Dictionary<IDisposable^, StackTrace^>^ m_TrackedObjects;

		static void OnExit( Object^ sender, EventArgs^ e );

	public:
		static ObjectTracker()
		{
			m_TrackedObjects = gcnew Dictionary<IDisposable^, StackTrace^>();

			AppDomain::CurrentDomain->DomainUnload += gcnew EventHandler( OnExit );
			AppDomain::CurrentDomain->ProcessExit += gcnew EventHandler( OnExit );
		}

		static void Add( IDisposable^ obj );
		static void Remove( IDisposable^ obj );
		static void ReportLeaks();
	};
}
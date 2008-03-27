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

namespace SlimDX
{
	ref class ComObject;

#ifdef XMLDOCS
	ref class Configuration;
#endif

	/// <summary>
	/// Maintains a list of all the <see cref="ComObject">COM objects</see> managed by SlimDX.
	/// </summary>
	public ref class ObjectTable sealed
	{
	private:
		static ObjectTable();
		ObjectTable();

		static System::Collections::Generic::Dictionary<System::IntPtr, ComObject^>^ m_Table;

		static void OnExit( System::Object^ sender, System::EventArgs^ e );

	internal:
		static ComObject^ Find( System::IntPtr nativeObject );
		static bool Contains( ComObject^ object );

	public:
		/// <summary>
		/// Gets a list of all the COM objects tracked by SlimDX.
		/// </summary>
		static property System::Collections::Generic::Dictionary<System::IntPtr, ComObject^>::ValueCollection^ Objects
		{
			System::Collections::Generic::Dictionary<System::IntPtr, ComObject^>::ValueCollection^ get();
		}
		
		/// <summary>
		/// Adds a COM object to the table. This will set the object's CreationSource parameter if
		/// <see cref="Configuration">object tracking</see> is on.
		/// </summary>
		/// <param name="object">The object to add.</param>
		static void Add( ComObject^ object );
		
		/// <summary>
		/// Removes a COM object from the table.
		/// </summary>
		/// <param name="object">The object to remove.</param>
		/// <returns><c>true</c> if the object was in the table and was removed; otherwise, <c>false</c>.</returns>
		static bool Remove( ComObject^ object );
		
		/// <summary>
		/// Generates a report of all outstanding COM objects (objects that have not been disposed)
		/// tracked by SlimDX. The report includes the object's type and a stack trace to its creation point.
		/// </summary>
		/// <returns>A string containing the leak report.</returns>
		static System::String^ ReportLeaks();
	};
}
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

namespace SlimDX
{
	namespace DirectInput
	{
		generic<typename DataFormat>
		public ref class BufferedDataCollection : System::Collections::Generic::IEnumerable<BufferedData<DataFormat>^>
		{
		private:
			System::Collections::Generic::List<BufferedData<DataFormat>^>^ list;

		internal:
			BufferedDataCollection( int initialCapacity );

			void Add( BufferedData<DataFormat>^ data );

			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)list)->GetEnumerator();
			}

		public:
			property int Count
			{
				int get() { return list->Count; }
			}

			property BufferedData<DataFormat>^ default[int]
			{
				BufferedData<DataFormat>^ get( int index ) { return list[index]; }
			}

			virtual System::Collections::Generic::IEnumerator<BufferedData<DataFormat>^>^ GetEnumerator() { return list->GetEnumerator(); }
		};
	}
}
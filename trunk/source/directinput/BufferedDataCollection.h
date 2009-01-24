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

namespace SlimDX
{
	namespace DirectInput
	{
		generic<typename DataFormat>
		public ref class BufferedDataCollection : public System::Collections::Generic::ICollection<BufferedData<DataFormat>^>
		{
		private:
			System::Collections::Generic::List<BufferedData<DataFormat>^>^ list;

		internal:
			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)list)->GetEnumerator();
			}

		public:
			BufferedDataCollection() { list = gcnew System::Collections::Generic::List<BufferedData<DataFormat>^>(); }
			BufferedDataCollection( int initialCapacity ) { list = gcnew System::Collections::Generic::List<BufferedData<DataFormat>^>( initialCapacity ); }

			virtual void Add( BufferedData<DataFormat>^ item ) { list->Add( item ); }
			virtual void Clear() { list->Clear(); }
			virtual bool Contains( BufferedData<DataFormat>^ item ) { return list->Contains( item ); }
			virtual void CopyTo( array<BufferedData<DataFormat>^>^ array, int arrayIndex ) { list->CopyTo( array, arrayIndex ); }
			virtual bool Remove( BufferedData<DataFormat>^ item ) { return list->Remove( item ); }

			virtual System::Collections::Generic::IEnumerator<BufferedData<DataFormat>^>^ GetEnumerator() { return list->GetEnumerator(); }

			virtual property int Count
			{
				int get() { return list->Count; }
			}

			virtual property bool IsReadOnly
			{
				bool get() { return false; }
			}

			property BufferedData<DataFormat>^ default[int]
			{
				BufferedData<DataFormat>^ get( int index ) { return list[index]; }
			}
		};
	}
}
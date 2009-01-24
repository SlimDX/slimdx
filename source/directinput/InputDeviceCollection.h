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

#include <gcroot.h>
#include "DeviceInstance.h"

namespace SlimDX
{
	namespace DirectInput
	{
		public ref class InputDeviceCollection : public System::Collections::Generic::ICollection<DeviceInstance^>
		{
		private:
			System::Collections::Generic::List<DeviceInstance^>^ list;

		internal:
			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)list)->GetEnumerator();
			}

		public:
			InputDeviceCollection() { list = gcnew System::Collections::Generic::List<DeviceInstance^>(); }
			InputDeviceCollection( int initialCapacity ) { list = gcnew System::Collections::Generic::List<DeviceInstance^>( initialCapacity ); }

			virtual void Add( DeviceInstance^ item ) { list->Add( item ); }
			virtual void Clear() { list->Clear(); }
			virtual bool Contains( DeviceInstance^ item ) { return list->Contains( item ); }
			virtual void CopyTo( array<DeviceInstance^>^ array, int arrayIndex ) { list->CopyTo( array, arrayIndex ); }
			virtual bool Remove( DeviceInstance^ item ) { return list->Remove( item ); }

			virtual System::Collections::Generic::IEnumerator<DeviceInstance^>^ GetEnumerator() { return list->GetEnumerator(); }

			virtual property int Count
			{
				int get() { return list->Count; }
			}

			property DeviceInstance^ default[int]
			{
				DeviceInstance^ get( int index ) { return list[index]; }
			}

			virtual property bool IsReadOnly
			{
				bool get() { return false; }
			}
		};

		class InputDeviceCollectionShim
		{
		private:
			gcroot<InputDeviceCollection^> devices;

		public:
			InputDeviceCollectionShim( InputDeviceCollection^ collection ) { devices = collection; }

			InputDeviceCollection^ GetDevices() { return devices; }
		};
	}
}
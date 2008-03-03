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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class AdapterDetails;
		value class DisplayMode;
		ref class Capabilities;
		ref class DisplayModeCollection;

		public ref class AdapterInformation
		{
		private:
			AdapterDetails^ details;

		internal:
			initonly int m_Adapter;

			AdapterInformation( unsigned int adapter );

		public:
			property int Adapter
			{
				int get() { return m_Adapter; }
			}

			property System::IntPtr Monitor { System::IntPtr get(); }
			property DisplayMode CurrentDisplayMode { DisplayMode get(); }
            DisplayModeCollection^ GetDisplayModes( Format format );
            Capabilities^ GetCaps( DeviceType type );
			bool SupportsR2VB( DeviceType type );

			property AdapterDetails^ Details
			{
				AdapterDetails^ get() { return details; }
			protected:
				void set( AdapterDetails^ value ) { details = value; }
			}
		};

		public ref class AdapterCollection : public System::Collections::Generic::IEnumerable<AdapterInformation^>
		{
		private:
			System::Collections::Generic::List<AdapterInformation^>^ m_Adapters;

		internal:
			AdapterCollection( unsigned int adapterCount );

			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)m_Adapters)->GetEnumerator();
			}

		public:
            property int Count
            {
                int get() { return m_Adapters->Count; }
            }

            property AdapterInformation^ default[int]
			{
				AdapterInformation^ get( int index )
				{
					return m_Adapters[index];
				}
			}

			virtual System::Collections::Generic::IEnumerator<AdapterInformation^>^ GetEnumerator()
			{
                return m_Adapters->GetEnumerator();
			}
		};
	}
}
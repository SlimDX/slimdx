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
	namespace DXGI
	{
		/// <remarks>
		/// Describes various properties of an Adapter.
		/// </remarks>
		public value class AdapterDescription : System::IEquatable<AdapterDescription>
		{
			System::String^ m_Description;
			int m_VendorId;
			int m_DeviceId;
			int m_SubSysId;
			int m_Revision;
			int m_DedicatedVideoMemory;
			int m_DedicatedSystemMemory;
			int m_SharedSystemMemory;
			System::Int64 m_Luid;

		internal:
			AdapterDescription( const DXGI_ADAPTER_DESC& native );

		public:
			/// <summary>
			/// Gets the adapter's description.
			/// </summary>
			property System::String^ Description
			{
				System::String^ get();
			}
			
			/// <summary>
			/// Gets the adapter's vendor ID.
			/// </summary>
			property int VendorId
			{
				int get();
			}

			/// <summary>
			/// Gets the adapter's device ID.
			/// </summary>
			property int DeviceId
			{
				int get();
			}

			/// <summary>
			/// Gets the adapter's subsystem ID.
			/// </summary>
			property int SubsystemId
			{
				int get();
			}

			/// <summary>
			/// Gets the adapter's revision number.
			/// </summary>
			property int Revision
			{
				int get();
			}

			/// <summary>
			/// Gets the number of bytes of video memory not shared with the CPU.
			/// </summary>
			property int DedicatedVideoMemory
			{
				int get();
			}

			/// <summary>
			/// Gets the number of bytes of system memory not shared with the CPU.
			/// </summary>
			property int DedicatedSystemMemory
			{
				int get();
			}

			/// <summary>
			/// Gets the number of bytes of system memory shared with the CPU.
			/// </summary>
			property int SharedSystemMemory
			{
				int get();
			}

			/// <summary>
			/// Gets the adapter's unique identifier.
			/// </summary>
			property System::Int64 Luid
			{
				System::Int64 get();
			}

			static bool operator == ( AdapterDescription left, AdapterDescription right );
			static bool operator != ( AdapterDescription left, AdapterDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( AdapterDescription other );
			static bool Equals( AdapterDescription% value1, AdapterDescription% value2 );
		};
	}
};
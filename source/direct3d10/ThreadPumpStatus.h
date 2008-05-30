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
	namespace Direct3D10
	{	
		public value class ThreadPumpStatus : System::IEquatable<ThreadPumpStatus>
		{
		private:
			System::UInt32 m_IoQueue;
			System::UInt32 m_ProcessQueue;
			System::UInt32 m_DeviceQueue;
			
		internal:
			ThreadPumpStatus( System::UInt32 ioCount, System::UInt32 processCount, System::UInt32 deviceCount );
			
		public:
			/// <summary>
			/// Gets the number of items in the IO queue.
			/// </summary>
			property System::UInt32 IoQueueCount
			{
				System::UInt32 get();
			}
			
			/// <summary>
			/// Gets the number of items in the process queue.
			/// </summary>
			property System::UInt32 ProcessQueueCount
			{
				System::UInt32 get();
			}
			
			/// <summary>
			/// Gets the number of items in the device queue.
			/// </summary>
			property System::UInt32 DeviceQueueCount
			{
				System::UInt32 get();
			}
			
			/// <summary>
			/// Tests for equality between two ThreadPumpStatuses.
			/// </summary>
			/// <param name="left">The first value to compare.</param>
			/// <param name="right">The second value to compare.</param>
			/// <returns><c>true</c> if <paramref name="left"/> has the same value as <paramref name="right"/>; otherwise, <c>false</c>.</returns>
			static bool operator == ( ThreadPumpStatus left, ThreadPumpStatus right );
			
			/// <summary>
			/// Tests for inequality between two ThreadPumpStatuses.
			/// </summary>
			/// <param name="left">The first value to compare.</param>
			/// <param name="right">The second value to compare.</param>
			/// <returns><c>true</c> if <paramref name="left"/> has a different value than <paramref name="right"/>; otherwise, <c>false</c>.</returns>
			static bool operator != ( ThreadPumpStatus left, ThreadPumpStatus right );

			/// <summary>
			/// Returns the hash code for this instance.
			/// </summary>
			/// <returns>A 32-bit signed integer hash code.</returns>
			virtual int GetHashCode() override;
			
			/// <summary>
			/// Returns a value indicating whether this instance is equal to the specified object.
			/// </summary>
			/// <param name="obj">An object to compare with this instance.</param>
			/// <returns><c>true</c> if <paramref name="obj"/> has the same value as this instance; otherwise, <c>false</c>.</returns>
			virtual bool Equals( System::Object^ obj ) override;
			
			/// <summary>
			/// Returns a value indicating whether this instance is equal to the specified object.
			/// </summary>
			/// <param name="other">A <see cref="SlimDX::Direct3D10::ThreadPumpStatus"/> to compare with this instance.</param>
			/// <returns><c>true</c> if <paramref name="other"/> has the same value as this instance; otherwise, <c>false</c>.</returns>
			virtual bool Equals( ThreadPumpStatus other );
			
			/// <summary>
			/// Returns a value indicating whether the two ThreadPumpStatuses are equivalent.
			/// </summary>
			/// <param name="value1">The first value to compare.</param>
			/// <param name="value2">The second value to compare.</param>
			/// <returns><c>true</c> if <paramref name="value1"/> has the same value as <paramref name="value2"/>; otherwise, <c>false</c>.</returns>
			static bool Equals( ThreadPumpStatus% value1, ThreadPumpStatus% value2 );
		};
	}
};
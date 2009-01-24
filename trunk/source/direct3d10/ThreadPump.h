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

#include "../ComObject.h"

#include "ThreadPumpStatus.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		/// <summary>
		/// Performs asynchronous data loading and processing.
		/// </summary>
		/// <unmanaged>ID3DX10ThreadPump</unmanaged>
		public ref class ThreadPump : public ComObject
		{
			COMOBJECT(ID3DX10ThreadPump, ThreadPump);
		
		public:
			/// <summary>
			/// Gets the number of work items in the pump.
			/// </summary>
			property System::UInt32 WorkItemCount
			{
				System::UInt32 get();
			}
			
			/// <summary>
			/// Gets the status of the thread pump queues.
			/// </summary>
			property ThreadPumpStatus Status
			{
				ThreadPumpStatus get();
			}
			
			/// <summary>
			/// Constructs a new ThreadPump object.
			/// </summary>
			/// <param name="ioThreadCount">The number of IO threads to create. Specify zero to auto-detect.</param>
			/// <param name="processThreadCount">The number of process threads to create. Specify zero to auto-detect.</param>
			ThreadPump::ThreadPump( System::UInt32 ioThreadCount, System::UInt32 processThreadCount );
			
			/// <summary>
			/// Constructs an ThreadPump object from a marshalled native pointer.
			/// </summary>
			/// <param name="pointer">The native object pointer.</param>
			/// <returns>The ThreadPump object for the native object.</returns>
			static ThreadPump^ FromPointer( System::IntPtr pointer );
			
			/// <summary>
			/// Binds items that have completed processing to the device.
			/// </summary>
			/// <param name="amount">The maximum number of items to bind.</param>
			/// <returns>A result code.</returns>
			Result BindProcessedItems( System::UInt32 amount );
			
			/// <summary>
			/// Removes all work items from the pump.
			/// </summary>
			/// <returns>A result code.</returns>
			Result PurgeAllItems();
			
			/// <summary>
			/// Waits for all items in the pump to complete.
			/// </summary>
			/// <returns>A result code.</returns>
			Result WaitForAllItems();
		};
	}
};
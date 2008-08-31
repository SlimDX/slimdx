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

#include <d3dx10.h>
#include <vcclr.h>

#include "Direct3D10Exception.h"

#include "ThreadPump.h"
#include "DataLoader.h"
#include "DataProcessor.h"
#include "DelayedResult.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	ThreadPump::ThreadPump( ID3DX10ThreadPump* pointer )
	{
		Construct( pointer );
		wrappers = gcnew System::Collections::Generic::List<System::IntPtr>();
	}

	ThreadPump::ThreadPump( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	ThreadPump::ThreadPump( System::UInt32 ioThreadCount, System::UInt32 processThreadCount )
	{
		ID3DX10ThreadPump* pump = 0;
		if( RECORD_D3D10( D3DX10CreateThreadPump( ioThreadCount, processThreadCount, &pump ) ).IsFailure ) {
			throw gcnew Direct3D10Exception( Result::Last );
		}
	}	

	ThreadPump^ ThreadPump::FromPointer( ID3DX10ThreadPump* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		ThreadPump^ tableEntry = safe_cast<ThreadPump^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew ThreadPump( pointer );
	}

	ThreadPump^ ThreadPump::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		ThreadPump^ tableEntry = safe_cast<ThreadPump^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew ThreadPump( pointer );
	}

	System::UInt32 ThreadPump::WorkItemCount::get()
	{
		return InternalPointer->GetWorkItemCount();
	}
	
	ThreadPumpStatus ThreadPump::Status::get()
	{
		UINT ioQueueCount = 0;
		UINT processQueueCount = 0;
		UINT deviceQueueCount = 0;
		RECORD_D3D10( InternalPointer->GetQueueStatus( &ioQueueCount, &processQueueCount, &deviceQueueCount ) );
		return ThreadPumpStatus( ioQueueCount, processQueueCount, deviceQueueCount );
	}
	
	Result ThreadPump::AddWorkItem(IDataLoader^ dataLoader, IDataProcessor^ dataProcessor, DelayedResult^ result) {
		DataLoader* loader = new DataLoader(gcroot<ThreadPump^>(this), gcroot<IDataLoader^>(dataLoader));
		DataProcessor* processor = new DataProcessor(gcroot<ThreadPump^>(this), gcroot<IDataProcessor^>(dataProcessor));
		
		Result res;

		try {
			res = RECORD_D3D10( InternalPointer->AddWorkItem(loader, processor, reinterpret_cast<HRESULT*>(result->result), result->deviceObject) );
		} catch(Exception^) {
			delete loader;
			delete processor;
			throw;
		}

		if(res.IsFailure) {
			delete loader;
			delete processor;
		} else {
			wrappers->Add(IntPtr(loader));
			wrappers->Add(IntPtr(processor));
		}

		return res;
	}

	Result ThreadPump::BindProcessedItems( System::UInt32 amount )
	{
		return RECORD_D3D10( InternalPointer->ProcessDeviceWorkItems( amount ) );
	}
	
	Result ThreadPump::PurgeAllItems()
	{
		return RECORD_D3D10( InternalPointer->PurgeAllItems() );
	}
	
	Result ThreadPump::WaitForAllItems()
	{
		return RECORD_D3D10( InternalPointer->WaitForAllItems() );
	}

	void ThreadPump::RemoveWrapper(IntPtr wrapper) {
		wrappers->Remove(wrapper);
	}
}
}

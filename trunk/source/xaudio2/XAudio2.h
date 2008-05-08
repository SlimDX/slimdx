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

#include "WaveFormatExtensible.h"
#include "DeviceDetails.h"
#include "PerformanceData.h"
#include "DebugConfiguration.h"
#include "ErrorEventArgs.h"

namespace SlimDX
{
	namespace XAudio2
	{
		public ref class XAudio2 : public ComObject
		{
			COMOBJECT(IXAudio2, XAudio2);

		internal:
			void InvokeCriticalError( ErrorEventArgs^ e ) { OnCriticalError( e ); }
			void InvokeProcessingPassEnd() { OnProcessingPassEnd( System::EventArgs::Empty ); }
			void InvokeProcessingPassStart() { OnProcessingPassStart( System::EventArgs::Empty); }

		protected:
			void OnCriticalError( ErrorEventArgs^ e );
			void OnProcessingPassEnd( System::EventArgs^ e );
			void OnProcessingPassStart( System::EventArgs^ e );

		public:
			XAudio2();
			XAudio2( XAudio2Flags flags, ProcessorSpecifier processor );

			/// <summary>
			/// Constructs a new instance of the <see cref="XAudio2"/> class using the specified pointer to a
			/// previously constructed unmanaged object.
			/// </summary>
			/// <param name="pointer">The unmanaged IXAudio2 pointer.</param>
			/// <returns>The newly constructed object.</returns>
			static XAudio2^ FromPointer( System::IntPtr pointer );

			Result StartEngine();
			void StopEngine();

			Result CommitChanges();
			Result CommitChanges( int operationSet );

			DeviceDetails^ GetDeviceDetails( int index );

			void SetDebugConfiguration( DebugConfiguration configuration );

			property int DeviceCount
			{
				int get();
			}

			property PerformanceData^ PerformanceData
			{
				SlimDX::XAudio2::PerformanceData^ get();
			}

			event System::EventHandler<ErrorEventArgs^>^ CriticalError;
			event System::EventHandler^ ProcessingPassEnd;
			event System::EventHandler^ ProcessingPassStart;
		};
	}
}
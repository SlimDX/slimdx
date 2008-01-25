/*
* Copyright (c) 2007 SlimDX Group
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

using namespace System;

#include "../ComObject.h"

namespace SlimDX
{
	namespace DXGI
	{
		public value class FrameStatistics
		{
			int m_PresentCount;
			int m_PresentRefreshCount;
			int m_SyncRefreshCount;
			__int64 m_SyncQPCTime;
			__int64 m_SyncGPUTime;
		
		internal:
			FrameStatistics( const DXGI_FRAME_STATISTICS& native );

		public:
			property int PresentCount
			{
				int get();
			}

			property int PresentRefreshCount
			{
				int get();
			}

			property int SyncRefreshCount
			{
				int get();
			}

			property __int64 SyncQPCTime
			{
				__int64 get();
			}

			property __int64 SyncGPUTime
			{
				__int64 get();
			}
		};
	}
};
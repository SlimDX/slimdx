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

#include "Factory.h"
#include "Enums.h"

namespace SlimDX
{
	namespace DXGI
	{
		ref class Factory;
		ref class Device;
		value class FrameStatistics;
		value class ModeDescription;
		value class SwapChainDescription;
		
		/// <remarks>
		/// A swap chain holds one or more surfaces that store rendered data prior to
		/// presenting that data to an output.
		/// </remarks>
		public ref class SwapChain : public ComObject
		{
			COMOBJECT(IDXGISwapChain);
		
		internal:
			SwapChain( IDXGISwapChain* pointer );
			
		public:
			SwapChain( IntPtr pointer );
			SwapChain( Factory^ factory, ComObject^ device, SwapChainDescription description );
			
			generic< typename T > where T : ComObject, ref class
			T GetBuffer( int buffer );

			Result GetFrameStatistics( [Out] FrameStatistics% statistics );

			Result ResizeBuffers( int count, int width, int height, Format format, SwapChainFlags flags );
			Result ResizeTarget( ModeDescription description );

			Result Present( int syncInterval, PresentFlags flags );
		};
	}
};
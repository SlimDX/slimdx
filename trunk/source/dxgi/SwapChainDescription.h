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

//using namespace System;

#include "Enums.h"
#include "ModeDescription.h"
#include "SampleDescription.h"

namespace SlimDX
{
	namespace DXGI
	{		
		public value class SwapChainDescription
		{
		private:
			ModeDescription m_BufferDesc;
			SampleDescription m_SampleDesc;
			Usage m_BufferUsage;
			int m_BufferCount;
			System::IntPtr m_OutputWindow;
			bool m_Windowed;
			SwapEffect m_SwapEffect;
			SwapChainFlags m_Flags;
		
		internal:
			DXGI_SWAP_CHAIN_DESC CreateNativeVersion();

		public:
			property ModeDescription ModeDescription
            {
                DXGI::ModeDescription get();
                void set( DXGI::ModeDescription value );
            }

            property SampleDescription SampleDescription
            {
                DXGI::SampleDescription get();
                void set( DXGI::SampleDescription value );
            }

            property Usage Usage
            {
                DXGI::Usage get();
                void set( DXGI::Usage value );
            }

            property int BufferCount
            {
                int get();
                void set( int value );
            }

            property System::IntPtr OutputHandle
            {
                System::IntPtr get();
                void set( System::IntPtr value );
            }

            property bool IsWindowed
            {
                bool get();
                void set( bool value );
            }

            property DXGI::SwapEffect SwapEffect
            {
                DXGI::SwapEffect get();
                void set( DXGI::SwapEffect value );
            }

            property SwapChainFlags Flags
            {
                SwapChainFlags get();
                void set( SwapChainFlags value );
            }
		};
	}
};
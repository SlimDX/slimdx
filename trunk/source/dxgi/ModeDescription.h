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

#include "Enums.h"
#include "../math/Rational.h"

namespace SlimDX
{
	namespace DXGI
	{	
		public value class ModeDescription
		{
			int m_Width;
			int m_Height;
			Rational m_RefreshRate;
			Format m_Format;
			DisplayModeScanlineOrdering m_ScanlineOrdering;
			DisplayModeScaling m_Scaling;
			
		internal:
			ModeDescription( const DXGI_MODE_DESC& native );
			
			DXGI_MODE_DESC CreateNativeVersion();
			
		public:
			property int Width
			{
				int get();
				void set( int value );
			}

			property int Height
			{
				int get();
				void set( int value );
			}

			property Rational RefreshRate
			{
				Rational get();
				void set( Rational value );
			}

			property Format Format
			{
				DXGI::Format get();
				void set( DXGI::Format value );
			}

			property DisplayModeScanlineOrdering ScanlineOrdering
			{
				DisplayModeScanlineOrdering get();
				void set( DisplayModeScanlineOrdering value );
			}

			property DisplayModeScaling Scaling
			{
				DisplayModeScaling get();
				void set( DisplayModeScaling value );
			}
			
			ModeDescription( int width, int height, Rational refreshRate, DXGI::Format format );
		};
	}
};
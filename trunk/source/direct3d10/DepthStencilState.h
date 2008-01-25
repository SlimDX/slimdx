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

#include "Enums.h"
#include "DepthStencilStateDescription.h"

namespace SlimDX
{
	namespace Direct3D10
	{	
		ref class Device;
		
		public ref class DepthStencilState : ComObject
		{
			COMOBJECT(ID3D10DepthStencilState);

		private:
			DepthStencilStateDescription^ m_Description;
		
		internal:
			DepthStencilState( ID3D10DepthStencilState* state );
		
		public:
			DepthStencilState( IntPtr state );
			~DepthStencilState() { Destruct(); }

			property bool DepthEnabled
			{
				bool get() { return m_Description->DepthEnabled; }
			}
			
			property SlimDX::Direct3D10::DepthWriteMask DepthWriteMask
			{
				SlimDX::Direct3D10::DepthWriteMask get() { return m_Description->DepthWriteMask; }
			}
			
			property Comparison DepthComparison
			{
				Comparison get() { return m_Description->DepthComparison; }
			}
			
			property bool StencilEnabled
			{
				bool get() { return m_Description->StencilEnabled; }
			}
			
			property Byte StencilReadMask
			{
				Byte get() { return m_Description->StencilReadMask; }
			}
			
			property Byte StencilWriteMask
			{
				Byte get() { return m_Description->StencilWriteMask; }
			}
			
			property Comparison FrontStencilComparison
			{
				Comparison get() { return m_Description->FrontStencilComparison; }
			}
			
			property StencilOperation FrontStencilFailureOperation
			{
				StencilOperation get() { return m_Description->FrontStencilFailureOperation; }
			}
			
			property StencilOperation FrontStencilDepthFailureOperation
			{
				StencilOperation get() { return m_Description->FrontStencilDepthFailureOperation; }
			}
			
			property StencilOperation FrontStencilPassOperation
			{
				StencilOperation get() { return m_Description->FrontStencilPassOperation; }
			}
			
			property Comparison BackStencilComparison
			{
				Comparison get() { return m_Description->BackStencilComparison; }
			}
			
			property StencilOperation BackStencilFailureOperation
			{
				StencilOperation get() { return m_Description->BackStencilFailureOperation; }
			}
			
			property StencilOperation BackStencilDepthFailureOperation
			{
				StencilOperation get() { return m_Description->BackStencilDepthFailureOperation; }
			}
			
			property StencilOperation BackStencilPassOperation
			{
				StencilOperation get() { return m_Description->BackStencilPassOperation; }
			}
			
			
			DepthStencilState( Device^ device, DepthStencilStateDescription^ description );
			
			DepthStencilStateDescription^ CloneDescription();
		};
	}
};
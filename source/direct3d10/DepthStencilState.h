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

#include "../DirectXObject.h"

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{	
		ref class Device;
		
		public ref class DepthStencilState : DirectXObject<ID3D10DepthStencilState>
		{
			bool m_EnableDepth;
			DepthWriteMask m_DepthWriteMask;
			Comparison m_DepthComparison;
			bool m_EnableStencil;
			Byte m_StencilReadMask;
			Byte m_StencilWriteMask;
			Comparison m_FrontStencilComparison;
			StencilOperation m_FrontStencilFailureOp;
			StencilOperation m_FrontStencilDepthFailureOp;
			StencilOperation m_FrontStencilPassOp;
			Comparison m_BackStencilComparison;
			StencilOperation m_BackStencilFailureOp;
			StencilOperation m_BackStencilDepthFailureOp;
			StencilOperation m_BackStencilPassOp;
		
		internal:
			DepthStencilState( ID3D10DepthStencilState* state );
		
		public:
			property bool EnableDepth
			{
				bool get() { return m_EnableDepth; }
			}
			
			property SlimDX::Direct3D10::DepthWriteMask DepthWriteMask
			{
				SlimDX::Direct3D10::DepthWriteMask get() { return m_DepthWriteMask; }
			}
			
			property Comparison DepthComparison
			{
				Comparison get() { return m_DepthComparison; }
			}
			
			property bool EnableStencil
			{
				bool get() { return m_EnableStencil; }
			}
			
			property Byte StencilReadMask
			{
				Byte get() { return m_StencilReadMask; }
			}
			
			property Byte StencilWriteMask
			{
				Byte get() { return m_StencilWriteMask; }
			}
			
			property Comparison FrontStencilComparison
			{
				Comparison get() { return m_FrontStencilComparison; }
			}
			
			property StencilOperation FrontStencilFailureOperation
			{
				StencilOperation get() { return m_FrontStencilFailureOp; }
			}
			
			property StencilOperation FrontStencilDepthFailureOperation
			{
				StencilOperation get() { return m_FrontStencilDepthFailureOp; }
			}
			
			property StencilOperation FrontStencilPassOperation
			{
				StencilOperation get() { return m_FrontStencilPassOp; }
			}
			
			property Comparison BackStencilComparison
			{
				Comparison get() { return m_BackStencilComparison; }
			}
			
			property StencilOperation BackStencilFailureOperation
			{
				StencilOperation get() { return m_BackStencilFailureOp; }
			}
			
			property StencilOperation BackStencilDepthFailureOperation
			{
				StencilOperation get() { return m_BackStencilDepthFailureOp; }
			}
			
			property StencilOperation BackStencilPassOperation
			{
				StencilOperation get() { return m_BackStencilPassOp; }
			}
			
			DepthStencilState( Device^ device, bool enableDepth, SlimDX::Direct3D10::DepthWriteMask depthWriteMask, Comparison depthComparison,
				bool enableStencil, Byte stencilReadMask, Byte stencilWriteMask,
				Comparison frontComparison, StencilOperation frontFailOp, StencilOperation frontDepthFailOp, StencilOperation frontPassOp,
				Comparison backComparison, StencilOperation backFailOp, StencilOperation backDepthFailOp, StencilOperation backPassOp );
		};
	}
};
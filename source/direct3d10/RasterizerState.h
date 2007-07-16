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
		
		public ref class RasterizerState : DirectXObject<ID3D10RasterizerState>
		{
			FillMode m_FillMode;
			CullMode m_CullMode;
			bool m_FrontCounterClockwise;
			int m_DepthBias;
			float m_DepthBiasClamp;
			float m_SlopeScaledDepthBias;
			bool m_EnableDepthClip;
			bool m_EnableScissor;
			bool m_EnableMultisample;
			bool m_EnableAntialiasedLine;
			
		public:
			property SlimDX::Direct3D10::FillMode FillMode
			{
				SlimDX::Direct3D10::FillMode get() { return m_FillMode; }
			}
			
			property SlimDX::Direct3D10::CullMode CullMode
			{
				SlimDX::Direct3D10::CullMode get() { return m_CullMode; }
			}
			
			property bool FrontIsCounterClockwise
			{
				bool get() { return m_FrontCounterClockwise; }
			}
			
			property int DepthBias
			{
				int get() { return m_DepthBias; }
			}
			
			property float DepthBiasClamp
			{
				float get() { return m_DepthBiasClamp; }
			}
			
			property float SlopeScaledDepthBias
			{
				float get() { return m_SlopeScaledDepthBias; }
			}
			
			property bool IsDepthClipEnabled
			{
				bool get() { return m_EnableDepthClip; }
			}
			
			property bool IsScissorEnabled
			{
				bool get() { return m_EnableScissor; }
			}
			
			property bool IsMultisampleEnabled
			{
				bool get() { return m_EnableMultisample; }
			}
			
			property bool IsAntialiasedLineEnabled
			{
				bool get() { return m_EnableAntialiasedLine; }
			}
			
			RasterizerState( Device^ device,SlimDX::Direct3D10::FillMode fillMode, SlimDX::Direct3D10::CullMode cullMode,
			  bool frontIsCounterClockwise, int depthBias, float depthBiasClamp, float slopeScaledDepthBias,
			  bool enableDepthClip, bool enableScissor, bool enableMultisample, bool enableAntialiasedLine );
		};
	}
};
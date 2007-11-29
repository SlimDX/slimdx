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
using namespace System::Globalization;

#include "../math/Math.h"
#include "EffectPassShaderMapping.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class EffectVariable;
		ref class ShaderSignature;
		
		public ref class EffectPass
		{
			ID3D10EffectPass *m_Pointer;
			String^ m_Name;
			int m_AnnotationCount;
			ShaderSignature^ m_Signature;
			int m_StencilReference;
			int m_SampleMask;
			ColorValue m_BlendFactor;
			
			
		internal:
			EffectPass( ID3D10EffectPass* pass );
			
		public:
			property String^ Name
			{
				String^ get() { return m_Name; }
			}
			
			property int AnnotationCount
			{
				int get() { return m_AnnotationCount; }
			}
			
			property ShaderSignature^ Signature
			{
				ShaderSignature^ get() { return m_Signature; }
			}
			
			property int StencilReference
			{
				int get() { return m_StencilReference; }
			}
			
			property int SampleMask
			{
				int get() { return m_SampleMask; }
			}
			
			property ColorValue BlendFactor
			{
				ColorValue get() { return m_BlendFactor; }
			}
			
			property bool IsValid
			{
				bool get() { return m_Pointer->IsValid() ? true : false; }
			}
			
			property EffectPassShaderMapping PixelShaderDescription
			{
				EffectPassShaderMapping get();
			}
			
			property EffectPassShaderMapping VertexShaderDescription
			{
				EffectPassShaderMapping get();
			}
			
			property EffectPassShaderMapping GeometryShaderDescription
			{
				EffectPassShaderMapping get();
			}
			
			EffectVariable^ GetAnnotationByIndex( int index );
			EffectVariable^ GetAnnotationByName( String^ name );
			
			void Apply();
		
			
		};
	}
};

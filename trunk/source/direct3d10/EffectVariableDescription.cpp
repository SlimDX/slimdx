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

#include <d3d10.h>

#include "EffectVariableDescription.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 	
	EffectVariableDescription::EffectVariableDescription( const D3D10_EFFECT_VARIABLE_DESC& native )
	{
		m_Name = gcnew String( native.Name );
		m_Semantic = gcnew String( native.Semantic );
		m_Flags = static_cast<EffectVariableFlags>( native.Flags );
		m_Annotations = native.Annotations;
		m_BufferOffset = native.BufferOffset;
		m_ExplicitBindPoint = native.ExplicitBindPoint;
	}

	String^ EffectVariableDescription::Name::get()
	{
		return m_Name;
	}
	
	String^ EffectVariableDescription::Semantic::get()
	{
		return m_Semantic;
	}

	EffectVariableFlags EffectVariableDescription::Flags::get()
	{
		return m_Flags;
	}
	
	int EffectVariableDescription::AnnotationCount::get()
	{
		return m_Annotations;
	}
	
	int EffectVariableDescription::ConstantBufferOffset::get()
	{
		return m_BufferOffset;
	}
	
	int EffectVariableDescription::ExplicitBindPoint::get()
	{
		return m_ExplicitBindPoint;
	}
}
}

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

#include "EffectDescription.h"

namespace SlimDX
{
namespace Direct3D10
{ 	
	EffectDescription::EffectDescription( const D3D10_EFFECT_DESC& native )
	{
		m_IsChildEffect = native.IsChildEffect ? true : false;
		m_ConstantBuffers = native.ConstantBuffers;
		m_SharedConstantBuffers = native.SharedConstantBuffers;
		m_GlobalVariables = native.GlobalVariables;
		m_SharedGlobalVariables = native.SharedGlobalVariables;
		m_Techniques = native.Techniques;
	}

	bool EffectDescription::IsChildEffect::get()
	{
		return m_IsChildEffect;
	}

	int EffectDescription::ConstantBufferCount::get()
	{
		return m_ConstantBuffers;
	}
	
	int EffectDescription::SharedConstantBufferCount::get()
	{
		return m_SharedConstantBuffers;
	}
	
	int EffectDescription::GlobalVariableCount::get()
	{
		return m_GlobalVariables;
	}
	
	int EffectDescription::SharedGlobalVariableCount::get()
	{
		return m_SharedGlobalVariables;
	}
	
	int EffectDescription::TechniqueCount::get()
	{
		return m_Techniques;
	}
}
}

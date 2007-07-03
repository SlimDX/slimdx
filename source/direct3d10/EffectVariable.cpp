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

#include <d3d10.h>
#include <d3dx10.h>

#include "GraphicsException.h"

#include "EffectResourceVariable.h"
#include "EffectVariable.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectVariable::EffectVariable( ID3D10EffectVariable* variable )
	{
		if( variable == NULL )
			throw gcnew ArgumentNullException( "variable" );
		m_Pointer = variable;
		
		D3D10_EFFECT_VARIABLE_DESC desc;
		HRESULT hr = m_Pointer->GetDesc( &desc );
		
		Name = gcnew String( desc.Name );
		Semantic = gcnew String( desc.Semantic );
		Flags = ( EffectVariableFlags ) desc.Flags;
		AnnotationCount = desc.Annotations;
		BufferOffset = desc.BufferOffset;
		ExplicitBindPoint = desc.ExplicitBindPoint;
	}
	
	EffectResourceVariable^ EffectVariable::AsResource()
	{
		//@TODO D3D10: Test variable->IsValid() to ensure cast was safe, and throw if it fails.
		ID3D10EffectShaderResourceVariable* variable = m_Pointer->AsShaderResource();
		return gcnew EffectResourceVariable( variable );
	}
}
}

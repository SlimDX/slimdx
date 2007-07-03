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
#include "ShaderResourceView.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectResourceVariable::EffectResourceVariable( ID3D10EffectShaderResourceVariable* variable ) : EffectVariable( variable )
	{
	}
	
	void EffectResourceVariable::SetResource( ShaderResourceView^ view )
	{
		HRESULT hr = ( ( ID3D10EffectShaderResourceVariable* ) m_Pointer )->SetResource( (ID3D10ShaderResourceView*) view->InternalPointer );
		GraphicsException::CheckHResult( hr );
	}
	
	ShaderResourceView^ EffectResourceVariable::GetResource()
	{
		ID3D10ShaderResourceView* view = 0;
		HRESULT hr = ( ( ID3D10EffectShaderResourceVariable* ) m_Pointer )->GetResource( &view );
		GraphicsException::CheckHResult( hr );
		
		return gcnew ShaderResourceView( view );
	}
}
}

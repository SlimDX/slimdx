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
#include <vcclr.h>

#include "GraphicsException.h"

#include "EffectPass.h"
#include "EffectVariable.h"
#include "ShaderBytecode.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectPass::EffectPass( ID3D10EffectPass* pass )
	{
		if( pass == NULL )
			throw gcnew ArgumentNullException( "pass" );
		m_Pointer = pass;
		
		D3D10_PASS_DESC desc;
		HRESULT hr = m_Pointer->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );
		
		m_Name = gcnew String( desc.Name );
		m_AnnotationCount = desc.Annotations;
		m_Signature = gcnew ShaderBytecode( desc.pIAInputSignature, desc.IAInputSignatureSize );
		m_StencilReference = desc.StencilRef;
		m_SampleMask = desc.SampleMask;
		m_BlendFactor = SlimDX::Direct3D::ColorValue( desc.BlendFactor[3], desc.BlendFactor[0], desc.BlendFactor[1], desc.BlendFactor[2] );
	}
	
	EffectVariable^ EffectPass::GetAnnotationByIndex( int index )
	{
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByIndex( index );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectPass::GetAnnotationByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByName( (LPCSTR) pinnedName );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	void EffectPass::Apply()
	{
		HRESULT hr = m_Pointer->Apply(0);
		GraphicsException::CheckHResult( hr );
	}
}
}

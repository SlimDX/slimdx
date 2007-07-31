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

#include "EffectMatrixVariable.h"
#include "EffectResourceVariable.h"
#include "EffectScalarVariable.h"
#include "EffectVariable.h"
#include "EffectVectorVariable.h"

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
		GraphicsException::CheckHResult( hr );
		
		m_Name = gcnew String( desc.Name );
		m_Semantic = gcnew String( desc.Semantic );
		m_Flags = ( EffectVariableFlags ) desc.Flags;
		m_AnnotationCount = desc.Annotations;
		m_BufferOffset = desc.BufferOffset;
		m_ExplicitBindPoint = desc.ExplicitBindPoint;
	}
	
	EffectVariable^ EffectVariable::GetAnnotationByIndex( int index )
	{
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByIndex( index );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetAnnotationByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByName( (LPCSTR) pinnedName );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetElement( int index )
	{
		//@TODO D3D10: Throw if improper type (not array).
		ID3D10EffectVariable* variable = m_Pointer->GetElement( index );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetMemberByIndex( int index )
	{
		//@TODO D3D10: Throw if improper type (not structure).
		ID3D10EffectVariable* variable = m_Pointer->GetMemberByIndex( index );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetMemberByName( String^ name )
	{
		//@TODO D3D10: Throw if improper type (not structure).
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetMemberByName( (LPCSTR) pinnedName );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetMemberBySemantic( String^ name )
	{
		//@TODO D3D10: Throw if improper type (not structure).
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetMemberBySemantic( (LPCSTR) pinnedName );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectMatrixVariable^ EffectVariable::AsMatrix()
	{
		//@TODO D3D10: Test variable->IsValid() to ensure cast was safe, and throw if it fails.
		ID3D10EffectMatrixVariable* variable = m_Pointer->AsMatrix();
		return gcnew EffectMatrixVariable( variable );
	}
	
	EffectResourceVariable^ EffectVariable::AsResource()
	{
		//@TODO D3D10: Test variable->IsValid() to ensure cast was safe, and throw if it fails.
		ID3D10EffectShaderResourceVariable* variable = m_Pointer->AsShaderResource();
		return gcnew EffectResourceVariable( variable );
	}
	
	EffectScalarVariable^ EffectVariable::AsScalar()
	{
		//@TODO D3D10: Test variable->IsValid() to ensure cast was safe, and throw if it fails.
		ID3D10EffectScalarVariable* variable = m_Pointer->AsScalar();
		return gcnew EffectScalarVariable( variable );
	}
	
	EffectVectorVariable^ EffectVariable::AsVector()
	{
		//@TODO D3D10: Test variable->IsValid() to ensure cast was safe, and throw if it fails.
		ID3D10EffectVectorVariable* variable = m_Pointer->AsVector();
		return gcnew EffectVectorVariable( variable );
	}
}
}

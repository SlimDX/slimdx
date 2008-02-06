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

#include "EffectVariable.h"
//#include "Direct3D10ErrorHandler.h"

#include "EffectConstantBuffer.h"
#include "EffectMatrixVariable.h"
#include "EffectResourceVariable.h"
#include "EffectShaderVariable.h"
#include "EffectScalarVariable.h"
#include "EffectVectorVariable.h"
#include "EffectStringVariable.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectVariable::EffectVariable( ID3D10EffectVariable* variable )
	{
		if( variable == NULL )
			throw gcnew ArgumentNullException( "variable" );
		m_Pointer = variable;
		
		D3D10_EFFECT_VARIABLE_DESC description;
		HRESULT hr = m_Pointer->GetDesc( &description );
		Result::Record( hr );
		
		m_Name = gcnew String( description.Name );
		m_Semantic = gcnew String( description.Semantic );
		m_Flags = static_cast<EffectVariableFlags>( description.Flags );
		m_AnnotationCount = description.Annotations;
		m_BufferOffset = description.BufferOffset;
		m_ExplicitBindPoint = description.ExplicitBindPoint;
	}
	
	EffectVariable^ EffectVariable::GetAnnotationByIndex( int index )
	{
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByIndex( index );
		if( variable == NULL || !variable->IsValid() )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any annotation on the variable.", index ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetAnnotationByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == NULL || !variable->IsValid() )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any annotation on the variable.", name ) );
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
		ID3D10EffectVariable* variable = m_Pointer->GetMemberByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectVariable::GetMemberBySemantic( String^ name )
	{
		//@TODO D3D10: Throw if improper type (not structure).
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetMemberBySemantic( reinterpret_cast<LPCSTR>( pinnedName ) );
		//@TODO D3D10: Check for null and throw "not found"
		return gcnew EffectVariable( variable );
	}
	
	EffectConstantBuffer^ EffectVariable::AsConstantBuffer()
	{
		ID3D10EffectConstantBuffer* variable = m_Pointer->AsConstantBuffer();
		if( variable == 0 || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a constant buffer." );
		return gcnew EffectConstantBuffer( variable );
	}
	
	EffectMatrixVariable^ EffectVariable::AsMatrix()
	{
		ID3D10EffectMatrixVariable* variable = m_Pointer->AsMatrix();
		if( variable == NULL || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a matrix." );
		return gcnew EffectMatrixVariable( variable );
	}
	
	EffectResourceVariable^ EffectVariable::AsResource()
	{
		ID3D10EffectShaderResourceVariable* variable = m_Pointer->AsShaderResource();
		if( variable == NULL || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a resource." );
		return gcnew EffectResourceVariable( variable );
	}
	
	EffectShaderVariable^ EffectVariable::AsShader()
	{
		ID3D10EffectShaderVariable* variable = m_Pointer->AsShader();
		if( variable == NULL || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a shader." );
		return gcnew EffectShaderVariable( variable );
	}
	
	EffectScalarVariable^ EffectVariable::AsScalar()
	{
		ID3D10EffectScalarVariable* variable = m_Pointer->AsScalar();
		if( variable == NULL || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a scalar." );
		return gcnew EffectScalarVariable( variable );
	}
	
	EffectVectorVariable^ EffectVariable::AsVector()
	{
		ID3D10EffectVectorVariable* variable = m_Pointer->AsVector();
		if( variable == NULL || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a resource." );
		return gcnew EffectVectorVariable( variable );
	}

	EffectStringVariable^ EffectVariable::AsString()
	{
		ID3D10EffectStringVariable* variable = m_Pointer->AsString();
		if( variable == NULL || !variable->IsValid() )
			throw gcnew InvalidOperationException( "The variable is not convertable to a string." );
		return gcnew EffectStringVariable( variable );
	}
}
}

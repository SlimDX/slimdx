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

#include "EffectTechnique.h"
#include "EffectPass.h"
#include "EffectVariable.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectTechnique::EffectTechnique( ID3D10EffectTechnique* technique )
	{
		if( technique == NULL )
			throw gcnew ArgumentNullException( "technique" );
		m_Pointer = technique;
	
		D3D10_TECHNIQUE_DESC desc;
		HRESULT hr = m_Pointer->GetDesc( &desc );
		GraphicsException::CheckHResult( hr );
		
		m_Name = gcnew String( desc.Name );
		m_PassCount = desc.Passes;
		m_AnnotationCount = desc.Annotations;
	}
	
	EffectVariable^ EffectTechnique::GetAnnotationByIndex( int index )
	{
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByIndex( index );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any annotation on the technique.", index ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ EffectTechnique::GetAnnotationByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectVariable* variable = m_Pointer->GetAnnotationByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any annotation on the techinque.", name ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectPass^ EffectTechnique::GetPassByIndex( int index )
	{
		ID3D10EffectPass* pass = m_Pointer->GetPassByIndex( index );
		if( pass == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any pass in the technique.", index ) );
		return gcnew EffectPass( pass );
	}
	
	EffectPass^ EffectTechnique::GetPassByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		ID3D10EffectPass* pass = m_Pointer->GetPassByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( pass == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any pass in the technique.", name ) );
		return gcnew EffectPass( pass );
	}
}
}

#include "stdafx.h"
/*
* Copyright (c) 2007-2010 SlimDX Group
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

#include <d3d11.h>
#include <vcclr.h>

#include "Direct3D11Exception.h"

#include "ShaderReflectionType11.h"
#include "ShaderTypeDescription11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	ShaderReflectionType::ShaderReflectionType( ID3D11ShaderReflectionType* pointer )
	{
		if( pointer == 0 )
			throw gcnew ArgumentNullException( "pointer" );
		m_Pointer = pointer;
	}
	
	ShaderReflectionType::ShaderReflectionType( System::IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );
		m_Pointer = reinterpret_cast<ID3D11ShaderReflectionType*>( pointer.ToPointer() );
	}

	ShaderTypeDescription ShaderReflectionType::Description::get()
	{
		D3D11_SHADER_TYPE_DESC nativeDescription;
		RECORD_D3D11( m_Pointer->GetDesc( &nativeDescription ) );
		if( Result::Last.IsSuccess )
			return ShaderTypeDescription( nativeDescription );
		
		throw gcnew Direct3D11Exception( Result::Last );
	}

	ShaderReflectionType^ ShaderReflectionType::BaseClass::get()
	{
		ID3D11ShaderReflectionType* type = m_Pointer->GetBaseClass();
		if( type == 0 )
			return nullptr;
		return gcnew ShaderReflectionType( type );
	}

	ShaderReflectionType^ ShaderReflectionType::SubType::get()
	{
		ID3D11ShaderReflectionType* type = m_Pointer->GetSubType();
		if( type == 0 )
			return nullptr;
		return gcnew ShaderReflectionType( type );
	}

	ShaderReflectionType^ ShaderReflectionType::GetInterfaceByIndex( int index )
	{
		ID3D11ShaderReflectionType* type = m_Pointer->GetInterfaceByIndex( index );
		if( type == 0 )
			return nullptr;
		return gcnew ShaderReflectionType( type );
	}

	ShaderReflectionType^ ShaderReflectionType::GetMemberTypeByIndex( int index )
	{
		ID3D11ShaderReflectionType* type = m_Pointer->GetMemberTypeByIndex( index );
		if( type == 0 )
			return nullptr;
		return gcnew ShaderReflectionType( type );
	}

	ShaderReflectionType^ ShaderReflectionType::GetMemberTypeByName( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3D11ShaderReflectionType* type = m_Pointer->GetMemberTypeByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( type == 0 )
			return nullptr;
		return gcnew ShaderReflectionType( type );
	}

	System::String^ ShaderReflectionType::GetMemberTypeName( int index )
	{
		LPCSTR result = m_Pointer->GetMemberTypeName( index );
		if ( result == 0 )
			return nullptr;
		return gcnew String(result);
	}

	bool ShaderReflectionType::ImpelmentsInterface( ShaderReflectionType^ base )
	{
		return m_Pointer->ImplementsInterface( base->m_Pointer ) != S_FALSE;
	}

	bool ShaderReflectionType::IsOfType( ShaderReflectionType^ type )
	{
		return m_Pointer->IsOfType( type->m_Pointer ) != S_FALSE;
	}
}
}
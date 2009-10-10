#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include <d3dx11effect.h>

#include "ShaderDescription11.h"

namespace SlimDX
{
namespace Direct3D11
{ 
	ShaderDescription::ShaderDescription( const D3DX11_EFFECT_SHADER_DESC& native )
	{
		m_InputSignature = gcnew SlimDX::Direct3D10::ShaderSignature( static_cast<const void*>( native.pInputSignature ), static_cast<long>( native.BytecodeLength - (native.pInputSignature - native.pBytecode) ) );
		m_IsInline = native.IsInline ? true : false;
		m_Bytecode = gcnew SlimDX::Direct3D10::ShaderBytecode( static_cast<const void*>( native.pBytecode ), native.BytecodeLength );
		m_SODecl = gcnew array<System::String^>( D3D11_SO_STREAM_COUNT );
		for( int i = 0; i < D3D11_SO_STREAM_COUNT; ++i )
		{
			m_SODecl[i] = gcnew System::String( native.SODecls[i] );
		}
		m_NumInputSignatureEntries = native.NumInputSignatureEntries;
		m_NumOutputSignatureEntries = native.NumOutputSignatureEntries;
	}
	
	SlimDX::Direct3D10::ShaderSignature^ ShaderDescription::Signature::get()
	{
		return m_InputSignature;
	}
	
	bool ShaderDescription::IsInline::get()
	{
		return m_IsInline;
	}
	
	SlimDX::Direct3D10::ShaderBytecode^ ShaderDescription::Bytecode::get()
	{
		return m_Bytecode;
	}
	
	System::String^ ShaderDescription::StreamOutputDeclaration::get(int index)
	{
		return m_SODecl[index];
	}

	int ShaderDescription::RasterizedStream::get()
	{
		return m_RasterizedStream;
	}

	int ShaderDescription::InputParameterCount::get()
	{
		return m_NumInputSignatureEntries;
	}
	
	int ShaderDescription::OutputParameterCount::get()
	{
	  return m_NumOutputSignatureEntries;
	}

	int ShaderDescription::PatchConstantCount::get()
	{
		return m_NumPatchConstantSignatureEntries;
	}

	bool ShaderDescription::operator == ( ShaderDescription left, ShaderDescription right )
	{
		return ShaderDescription::Equals( left, right );
	}

	bool ShaderDescription::operator != ( ShaderDescription left, ShaderDescription right )
	{
		return !ShaderDescription::Equals( left, right );
	}

	int ShaderDescription::GetHashCode()
	{
		return m_InputSignature->GetHashCode() + m_IsInline.GetHashCode() + m_Bytecode->GetHashCode() + m_SODecl->GetHashCode() + m_NumInputSignatureEntries.GetHashCode() + m_NumOutputSignatureEntries.GetHashCode();
	}

	bool ShaderDescription::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( safe_cast<ShaderDescription>( value ) );
	}

	bool ShaderDescription::Equals( ShaderDescription value )
	{
		return ( m_InputSignature == value.m_InputSignature && m_IsInline == value.m_IsInline && m_Bytecode == value.m_Bytecode && m_SODecl == value.m_SODecl && m_NumInputSignatureEntries == value.m_NumInputSignatureEntries && m_NumOutputSignatureEntries == value.m_NumOutputSignatureEntries );
	}

	bool ShaderDescription::Equals( ShaderDescription% value1, ShaderDescription% value2 )
	{
		return ( value1.m_InputSignature == value2.m_InputSignature && value1.m_IsInline == value2.m_IsInline && value1.m_Bytecode == value2.m_Bytecode && value1.m_SODecl == value2.m_SODecl && value1.m_NumInputSignatureEntries == value2.m_NumInputSignatureEntries && value1.m_NumOutputSignatureEntries == value2.m_NumOutputSignatureEntries );
	}
}
}

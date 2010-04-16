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
#include <d3dx11effect.h>

#include "Direct3D11Exception.h"

#include "EffectShaderVariable11.h"
#include "GeometryShader11.h"
#include "PixelShader11.h"
#include "EffectShaderDescription11.h"
#include "ShaderParameterDescription11.h"
#include "VertexShader11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{ 
	EffectShaderVariable::EffectShaderVariable( ID3DX11EffectShaderVariable* pointer )
	: EffectVariable( pointer )
	{
		m_Pointer = pointer;
	}
	
	EffectShaderVariable::EffectShaderVariable( IntPtr pointer )
	: EffectVariable( pointer )
	{
		m_Pointer = reinterpret_cast<ID3DX11EffectShaderVariable*>( pointer.ToPointer() );
	}
	
	PixelShader^ EffectShaderVariable::GetPixelShader( int index )
	{
		ID3D11PixelShader* shader = 0;
		if( RECORD_D3D11( m_Pointer->GetPixelShader( index, &shader ) ).IsFailure )
			return nullptr;
			
		return PixelShader::FromPointer( shader );
	}
	
	VertexShader^ EffectShaderVariable::GetVertexShader( int index )
	{
		ID3D11VertexShader* shader = 0;
		if( RECORD_D3D11( m_Pointer->GetVertexShader( index, &shader ) ).IsFailure )
			return nullptr;
		
		return VertexShader::FromPointer( shader );
	}
	
	GeometryShader^ EffectShaderVariable::GetGeometryShader( int index )
	{
		ID3D11GeometryShader* shader = 0;
		if( RECORD_D3D11( m_Pointer->GetGeometryShader( index, &shader ) ).IsFailure )
			return nullptr;
			
		return GeometryShader::FromPointer( shader );
	}
	
	Result EffectShaderVariable::GetInputParameterDescription( int shaderIndex, int parameterIndex, ShaderParameterDescription% result )
	{
		D3D11_SIGNATURE_PARAMETER_DESC description;
		if( RECORD_D3D11( m_Pointer->GetInputSignatureElementDesc( shaderIndex, parameterIndex, &description ) ).IsSuccess )
			result = ShaderParameterDescription( description );
			
		return Result::Last;
	}
	
	Result EffectShaderVariable::GetOutputParameterDescription( int shaderIndex, int parameterIndex, ShaderParameterDescription% result )
	{
		D3D11_SIGNATURE_PARAMETER_DESC description;
		if( RECORD_D3D11( m_Pointer->GetOutputSignatureElementDesc( shaderIndex, parameterIndex, &description ) ).IsSuccess )
			result = ShaderParameterDescription( description );
		
		return Result::Last;
	}
	
	Result EffectShaderVariable::GetShaderDescription( int shaderIndex, EffectShaderDescription% result )
	{
		D3DX11_EFFECT_SHADER_DESC description;
		if( RECORD_D3D11( m_Pointer->GetShaderDesc( shaderIndex, &description ) ).IsSuccess )
			result = EffectShaderDescription( description );
	
		return Result::Last;
	}
}
}

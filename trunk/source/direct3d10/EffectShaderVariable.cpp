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

//#include "Direct3D10ErrorHandler.h"

#include "EffectShaderVariable.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "GeometryShader.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectShaderVariable::EffectShaderVariable( ID3D10EffectShaderVariable* variable ) : EffectVariable( variable )
	{
	}
	
	PixelShader^ EffectShaderVariable::GetPixelShader( int index )
	{
		ID3D10PixelShader* shader;
		HRESULT hr = static_cast<ID3D10EffectShaderVariable*>( Pointer )->GetPixelShader( index, &shader );
		Result::Record( hr );
		
		return gcnew PixelShader( shader );
	}
	
	VertexShader^ EffectShaderVariable::GetVertexShader( int index )
	{
		ID3D10VertexShader* shader;
		HRESULT hr = static_cast<ID3D10EffectShaderVariable*>( Pointer )->GetVertexShader( index, &shader );
		Result::Record( hr );
		
		return gcnew VertexShader( shader );
	}
	
	GeometryShader^ EffectShaderVariable::GetGeometryShader( int index )
	{
		ID3D10GeometryShader* shader;
		HRESULT hr = static_cast<ID3D10EffectShaderVariable*>( Pointer )->GetGeometryShader( index, &shader );
		Result::Record( hr );
		
		return gcnew GeometryShader( shader );
	}
	
	ShaderParameterDescription EffectShaderVariable::GetInputParameterDescription( int shaderIndex, int parameterIndex )
	{
		D3D10_SIGNATURE_PARAMETER_DESC description;
		HRESULT hr = static_cast<ID3D10EffectShaderVariable*>( Pointer )->GetInputSignatureElementDesc( shaderIndex, parameterIndex, &description );
		Result::Record( hr );
		
		return ShaderParameterDescription( description );
	}
	
	ShaderParameterDescription EffectShaderVariable::GetOutputParameterDescription( int shaderIndex, int parameterIndex )
	{
		D3D10_SIGNATURE_PARAMETER_DESC description;
		HRESULT hr = static_cast<ID3D10EffectShaderVariable*>( Pointer )->GetOutputSignatureElementDesc( shaderIndex, parameterIndex, &description );
		Result::Record( hr );
		
		return ShaderParameterDescription( description );
	}
	
	ShaderDescription EffectShaderVariable::GetShaderDescription( int shaderIndex )
	{
		D3D10_EFFECT_SHADER_DESC description;
		HRESULT hr = static_cast<ID3D10EffectShaderVariable*>( Pointer )->GetShaderDesc( shaderIndex, &description );
		Result::Record( hr );
		
		return ShaderDescription( description );
	}
}
}

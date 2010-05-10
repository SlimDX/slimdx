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
#pragma once

#include "EffectVariable11.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace D3DCompiler
	{
		value class ShaderParameterDescription;
	}

	namespace Direct3D11
	{
		ref class PixelShader;
		ref class VertexShader;
		ref class GeometryShader;
		value class EffectShaderDescription;
		
		public ref class EffectShaderVariable : public EffectVariable
		{	
		private:
			ID3DX11EffectShaderVariable* m_Pointer;
			
		internal:
			EffectShaderVariable( ID3DX11EffectShaderVariable* pointer );

		public:
			EffectShaderVariable( System::IntPtr pointer );
			
			PixelShader^ GetPixelShader( int index );
			VertexShader^ GetVertexShader( int index );
			GeometryShader^ GetGeometryShader( int index );
			
			Result GetInputParameterDescription( int shaderIndex, int parameterIndex, [Out] D3DCompiler::ShaderParameterDescription% result );
			Result GetOutputParameterDescription( int shaderIndex, int parameterIndex, [Out] D3DCompiler::ShaderParameterDescription% result );
			
			Result GetShaderDescription( int shaderIndex, [Out] EffectShaderDescription% result );
		};
	}
};
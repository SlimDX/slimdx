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
#pragma once

#include "Effect.h"
#include "Buffer.h"
#include "ConstantTable.h"
#include "Shader.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class EffectBytecode sealed : public BufferWrapper
		{
		public:
			EffectBytecode( ID3DXBuffer* buffer ) : BufferWrapper( buffer )
			{ }

			EffectBytecode( int size ) : BufferWrapper( size )
			{ }
		};

		public ref class EffectCompiler sealed : public BaseEffect
		{
		private:
			void InitThis( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors );

		internal:
			property ID3DXEffectCompiler* CompilerPointer
			{
				ID3DXEffectCompiler* get() { return (ID3DXEffectCompiler*) m_Pointer; }
			}

		public:
			EffectCompiler( ID3DXEffectCompiler* compiler );
			EffectCompiler( String^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors );
			EffectCompiler( array<Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] String^% errors );
			~EffectCompiler() { Destruct(); }

			static EffectCompiler^ FromFile( String^ fileName, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );

			ShaderBytecode^ CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
				[Out] String^% compilationErrors, [Out] ConstantTable^% constantTable );
			ShaderBytecode^ CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags,
				[Out] String^% compilationErrors );
			ShaderBytecode^ CompileShader( EffectHandle^ functionHandle, String^ target, ShaderFlags flags );

			EffectBytecode^ CompileEffect( ShaderFlags flags, [Out] String^% compilationErrors );
			EffectBytecode^ CompileEffect( ShaderFlags flags );

			void SetLiteral( EffectHandle^ handle, bool literal );
			bool GetLiteral( EffectHandle^ handle );
		};
	}
}
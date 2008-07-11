/*
* Copyright (c) 2007-2008 SlimDX Group
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
#include "ConstantTable.h"
#include "ShaderBytecode.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		public ref class EffectCompiler : public BaseEffect
		{
		private:
			void InitThis( array<System::Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% compilationErrors );

		internal:
			property ID3DXEffectCompiler* CompilerPointer
			{
				ID3DXEffectCompiler* get() { return static_cast<ID3DXEffectCompiler*>( InternalPointer ); }
			}

			EffectCompiler( ID3DXEffectCompiler* compiler );

		public:
			EffectCompiler( System::IntPtr compiler );
			EffectCompiler( System::String^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% compilationErrors );
			EffectCompiler( array<System::Byte>^ data, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% compilationErrors );
			virtual ~EffectCompiler() { }

			static EffectCompiler^ FromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );

			ShaderBytecode^ CompileShader( EffectHandle^ functionHandle, System::String^ target, ShaderFlags flags, [Out] System::String^% compilationErrors, [Out] ConstantTable^% constantTable );
			ShaderBytecode^ CompileShader( EffectHandle^ functionHandle, System::String^ target, ShaderFlags flags, [Out] System::String^% compilationErrors );
			ShaderBytecode^ CompileShader( EffectHandle^ functionHandle, System::String^ target, ShaderFlags flags );

			DataStream^ CompileEffect( ShaderFlags flags, [Out] System::String^% compilationErrors );
			DataStream^ CompileEffect( ShaderFlags flags );

			Result SetLiteral( EffectHandle^ handle, bool literal );
			bool GetLiteral( EffectHandle^ handle );
		};
	}
}
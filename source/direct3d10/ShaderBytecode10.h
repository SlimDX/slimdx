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

#include "Include10.h"
#include "ShaderMacro10.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		public ref class ShaderBytecode : ComObject
		{
			COMOBJECT(ID3D10Blob, ShaderBytecode);
		
		internal:
			static System::String^ ExceptionDataKey = "CompilationErrors";

			ShaderBytecode( const BYTE* data, UINT length );

		public:
			ShaderBytecode( array<System::Byte>^ data );

			static ShaderBytecode^ Compile( System::String^ shaderSource, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags );
			static ShaderBytecode^ Compile( System::String^ shaderSource, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include );
			static ShaderBytecode^ Compile( System::String^ shaderSource, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include, [Out] System::String^ %compilationErrors );

			static ShaderBytecode^ Compile( array<System::Byte>^ shaderSource, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags );
			static ShaderBytecode^ Compile( array<System::Byte>^ shaderSource, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include );
			static ShaderBytecode^ Compile( array<System::Byte>^ shaderSource, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include, [Out] System::String^ %compilationErrors );

			static ShaderBytecode^ CompileFromFile( System::String^ fileName, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags );
			static ShaderBytecode^ CompileFromFile( System::String^ fileName, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include );
			static ShaderBytecode^ CompileFromFile( System::String^ fileName, System::String^ entryPoint, System::String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, array<ShaderMacro>^ defines, Include^ include, [Out] System::String^ %compilationErrors );

			property DataStream^ Data
			{
				DataStream^ get();
			}

			/// <summary>
			/// Returns the hash code for this instance.
			/// </summary>
			/// <returns>A 32-bit signed integer hash code.</returns>
			virtual int GetHashCode() override;
		};
	}
};
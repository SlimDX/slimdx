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

using namespace System::IO;
using namespace System::Runtime::InteropServices;

#include "Device.h"
#include "ConstantTable.h"
#include "Buffer.h"
#include <vcclr.h>

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		class IncludeShim;

		public ref class Include abstract
		{
		internal:
			IncludeShim* Shim;

		protected:
			Include();

		public:
			~Include();
			!Include();

			virtual void Open() = 0;
			virtual void Close() = 0;
		};

		class IncludeShim : public ID3DXInclude
		{
		private:
			gcroot<Include^> m_WrappedInterface;

		public:
			IncludeShim( Include^ wrappedInterface );

			HRESULT WINAPI Open( D3DXINCLUDE_TYPE includeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes );
			HRESULT WINAPI Close( LPCVOID pData );
		};

		public value class Macro
		{
		internal:
			//helper function to resolve array<Macro>^ to D3DXMACRO*
			static D3DXMACRO* Marshal( array<Macro>^ macros, [Out] array<GCHandle>^% handles );
			static void Unmarshal( D3DXMACRO* macros, array<GCHandle>^ handles );

		public:
			String^ Name;
			String^ Definition;
		};

		public ref class ShaderBytecode sealed : public BufferWrapper
		{
		public:
			ShaderBytecode( ID3DXBuffer* buffer ) : BufferWrapper( buffer )
			{ }
		};

		public ref class Shader sealed
		{
		public:
			//D3DXAssembleShader
			static ShaderBytecode^ Assemble( array<Byte>^ sourceData, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );
			static ShaderBytecode^ Assemble( String^ sourceData, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );

			//D3DXAssembleShaderFromFile
			static ShaderBytecode^ AssembleFromFile( String^ fileName, array<Macro>^ defines,
				Include^ includeFile, ShaderFlags flags, [Out] String^% errors );

			//D3DXCompileShader
			static ShaderBytecode^ Compile( array<Byte>^ sourceData, array<Macro>^ defines,
				Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
				[Out] String^% errors, [Out] ConstantTable^% constantTable );
			static ShaderBytecode^ Compile( String^ sourceData, array<Macro>^ defines,
				Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
				[Out] String^% errors, [Out] ConstantTable^% constantTable );
			static ShaderBytecode^ Compile( array<Byte>^ sourceData, array<Macro>^ defines,
				Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
				[Out] String^% errors );
			static ShaderBytecode^ Compile( String^ sourceData, array<Macro>^ defines,
				Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
				[Out] String^% errors );

			//D3DXCompileShaderFromFile
			static ShaderBytecode^ CompileFromFile( String^ fileName, array<Macro>^ defines,
				Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
				[Out] String^% errors, [Out] ConstantTable^% constantTable );
			static ShaderBytecode^ CompileFromFile( String^ fileName, array<Macro>^ defines,
				Include^ includeFile, String^ functionName, String^ profile, ShaderFlags flags,
				[Out] String^% errors );
		};
	}
}
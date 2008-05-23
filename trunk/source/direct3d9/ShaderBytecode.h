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

#include "ShaderSemantic.h"
#include "ConstantTable.h"
#include "Include.h"
#include "Macro.h"

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		ref class ConstantTable;

		public ref class ShaderBytecode : ComObject
		{
			COMOBJECT(ID3DXBuffer, ShaderBytecode);

			ConstantTable^ m_constantTable;

		public:
			virtual ~ShaderBytecode() { delete m_constantTable; }

			static ShaderBytecode^ FromPointer( System::IntPtr pointer );

			static ShaderBytecode^ Assemble( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ Assemble( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags );
			static ShaderBytecode^ Assemble( array<System::Byte>^ sourceData, ShaderFlags flags );

			static ShaderBytecode^ Assemble( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ Assemble( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags );
			static ShaderBytecode^ Assemble( System::String^ sourceData, ShaderFlags flags );

			static ShaderBytecode^ AssembleFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ AssembleFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags );
			static ShaderBytecode^ AssembleFromFile( System::String^ fileName, ShaderFlags flags );

			static ShaderBytecode^ Compile( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ Compile( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags );
			static ShaderBytecode^ Compile( array<System::Byte>^ sourceData, System::String^ functionName, System::String^ profile, ShaderFlags flags );

			static ShaderBytecode^ Compile( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ Compile( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags );
			static ShaderBytecode^ Compile( System::String^ sourceData, System::String^ functionName, System::String^ profile, ShaderFlags flags );

			static ShaderBytecode^ CompileFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ CompileFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags );
			static ShaderBytecode^ CompileFromFile( System::String^ fileName, System::String^ functionName, System::String^ profile, ShaderFlags flags );

			static System::String^ Preprocess( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, [Out] System::String^% errors );
			static System::String^ Preprocess( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile );
			static System::String^ Preprocess( array<System::Byte>^ sourceData );

			static System::String^ Preprocess( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, [Out] System::String^% errors );
			static System::String^ Preprocess( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile );
			static System::String^ Preprocess( System::String^ sourceData );

			static System::String^ PreprocessFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, [Out] System::String^% errors );
			static System::String^ PreprocessFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile );
			static System::String^ PreprocessFromFile( System::String^ fileName );

			static int MajorVersion( int version );
			static int MinorVersion( int version );
			static System::Version^ ParseVersion( int version );

			DataStream^ Disassemble( bool enableColorCode, System::String^ comments );
			DataStream^ Disassemble( bool enableColorCode );
			DataStream^ Disassemble();

			DataStream^ FindComment( Format fourCC );

			array<ShaderSemantic>^ GetInputSemantics();
			array<ShaderSemantic>^ GetOutputSemantics();
			array<System::String^>^ GetSamplers();

			property DataStream^ Data
			{
				DataStream^ get();
			}

			property ConstantTable^ ConstantTable
			{
				SlimDX::Direct3D9::ConstantTable^ get();
			}

			property int Version
			{
				int get();
			}
		};
	}
}
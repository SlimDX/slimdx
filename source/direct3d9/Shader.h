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

#include "Device.h"
#include "ConstantTable.h"
#include <vcclr.h>

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	ref class DataStream;

	namespace Direct3D9
	{
		class IncludeShim;

		

		public interface struct Include
		{
			virtual void Open( IncludeType includeType, System::String^ fileName, [Out] System::IO::Stream^ stream ) = 0;
			virtual void Close( System::IO::Stream^stream ) = 0;
		};

		class IncludeShim : public ID3DXInclude
		{
		private:
			gcroot<Include^> m_WrappedInterface;
			gcroot<System::IO::Stream^> m_stream;
			System::Runtime::InteropServices::GCHandle m_handle;

		public:
			IncludeShim( Include^ wrappedInterface );

			HRESULT WINAPI Open( D3DXINCLUDE_TYPE includeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes );
			HRESULT WINAPI Close( LPCVOID pData );
		};

		public value class Macro : System::IEquatable<Macro>
		{
		internal:
			static D3DXMACRO* Marshal( array<Macro>^ macros, [Out] array<System::Runtime::InteropServices::GCHandle>^% handles );
			static void Unmarshal( D3DXMACRO* macros, array<System::Runtime::InteropServices::GCHandle>^ handles );

		public:
			property System::String^ Name;
			property System::String^ Definition;

			static bool operator == ( Macro left, Macro right );
			static bool operator != ( Macro left, Macro right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( Macro other );
			static bool Equals( Macro% value1, Macro% value2 );
		};

		public value class ShaderSemantic : System::IEquatable<ShaderSemantic>
		{
		public:
			property DeclarationUsage Usage;
			property int UsageIndex;

			static bool operator == ( ShaderSemantic left, ShaderSemantic right );
			static bool operator != ( ShaderSemantic left, ShaderSemantic right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ShaderSemantic other );
			static bool Equals( ShaderSemantic% value1, ShaderSemantic% value2 );
		};

		public ref class ShaderBytecode : ComObject
		{
			COMOBJECT(ID3DXBuffer, ShaderBytecode);

		public:
			static ShaderBytecode^ FromPointer( System::IntPtr pointer );

			DataStream^ GetData();

			ConstantTable^ GetConstantTable();
			array<ShaderSemantic>^ GetInputSemantics();
			array<ShaderSemantic>^ GetOutputSemantics();
			array<System::String^>^ GetSamplers();

			property int Version
			{
				int get();
			}
		};

		public ref class Shader sealed
		{
		private:
			Shader() { }

		public:
			static ShaderBytecode^ Assemble( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ Assemble( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );

			static ShaderBytecode^ AssembleFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, ShaderFlags flags, [Out] System::String^% errors );

			static ShaderBytecode^ Compile( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors, [Out] ConstantTable^% constantTable );
			static ShaderBytecode^ Compile( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors, [Out] ConstantTable^% constantTable );
			static ShaderBytecode^ Compile( array<System::Byte>^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors );
			static ShaderBytecode^ Compile( System::String^ sourceData, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors );

			static ShaderBytecode^ CompileFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors, [Out] ConstantTable^% constantTable );
			static ShaderBytecode^ CompileFromFile( System::String^ fileName, array<Macro>^ defines, Include^ includeFile, System::String^ functionName, System::String^ profile, ShaderFlags flags, [Out] System::String^% errors );

			static int MajorVersion( int version );
			static int MinorVersion( int version );
			static System::Version^ ParseVersion( int version );
		};
	}
}
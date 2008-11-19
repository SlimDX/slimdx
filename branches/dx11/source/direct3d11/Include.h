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

#include <vcclr.h>

#include "../ComObject.h"

#include "Enums.h"

using System::Runtime::InteropServices::OutAttribute;

namespace SlimDX
{
	namespace Direct3D11
	{
		/// <summary>
		/// Specifies an interface for handling #include directives in shader or effect files.
		/// </summary>
		public interface struct Include
		{
			/// <summary>
			/// Opens and reads the contents of an included file.
			/// </summary>
			/// <param name="type">Flags specifying the type of the include file.</param>
			/// <param name="fileName">Name of the include file to open.</param>
			/// <param name="stream">When the method completes, contains a stream pointing to the include file.</param>
			virtual void Open( IncludeType type, System::String^ fileName, [Out] System::IO::Stream^ %stream ) = 0;

			/// <summary>
			/// Closes an included file.
			/// </summary>
			/// <param name="stream">The previously opened include stream.</param>
			virtual void Close( System::IO::Stream^ stream ) = 0;
		};

		value class IncludeFrame
		{
		private:
			System::IO::Stream^ m_stream;
			System::Runtime::InteropServices::GCHandle m_handle;

		public:
			IncludeFrame(System::IO::Stream^ stream, System::Runtime::InteropServices::GCHandle handle)
				: m_stream(stream), m_handle(handle) { }

			property System::IO::Stream^ Stream
			{
				System::IO::Stream^ get() { return m_stream; }
			}

			void Close();
		};
		
		class IncludeShim : public ID3D11Include
		{
		private:
			gcroot<Include^> m_Wrapped;
			gcroot<System::Collections::Generic::Stack<IncludeFrame>^> m_Frames;

		public:
			IncludeShim( Include^ wrapped );
			~IncludeShim();

			HRESULT WINAPI Open( D3D11_INCLUDE_TYPE type, LPCSTR fileName, LPCVOID parentData, LPCVOID* data, UINT* bytes );
			HRESULT WINAPI Close( LPCVOID data );
		};
	}
};
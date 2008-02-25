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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <memory>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../StackAlloc.h"

//#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

#include "Device.h"
#include "PixelShader.h"
#include "ConstantTable.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D9
	{
		PixelShader::PixelShader( IDirect3DPixelShader9* pixelShader )
		{
			if( pixelShader == NULL )
				throw gcnew ArgumentNullException( "pixelShader" );

			Construct(pixelShader);

			m_ConstantTable = nullptr;
		}

		PixelShader::PixelShader( IntPtr pixelShader )
		{
			Construct( pixelShader, NativeInterface );
		}

		PixelShader::PixelShader( IDirect3DPixelShader9* pixelShader, ID3DXConstantTable* constantTable )
		{
			if( pixelShader == NULL )
				throw gcnew ArgumentNullException( "pixelShader" );
			if( constantTable == NULL )
				throw gcnew ArgumentNullException( "constantTable" );

			Construct(pixelShader);

			IDirect3DDevice9* device;
			HRESULT hr = pixelShader->GetDevice(&device);
			
			if( RECORD_D3D9( hr ).IsFailure )
				throw gcnew Direct3D9Exception( Result::Last );
			
			m_ConstantTable = gcnew ConstantTable( device, constantTable );
			device->Release();
		}

		PixelShader^ PixelShader::FromString( Device^ device, String^ sourceCode, String^ entryPoint, String^ profile, ShaderFlags flags, [Out] String^ %compilationErrors )
		{
			array<unsigned char>^ rawCode = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceCode );
			pin_ptr<unsigned char> pinnedCode = &rawCode[0];
			array<Byte>^ rawFunction = System::Text::ASCIIEncoding::ASCII->GetBytes( entryPoint );
			pin_ptr<unsigned char> pinnedFunction = &rawFunction[0];
			array<Byte>^ rawProfile = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
			pin_ptr<unsigned char> pinnedProfile = &rawProfile[0];
			
			ID3DXBuffer *shaderBuffer;
			ID3DXBuffer *errorBuffer;
			ID3DXConstantTable* constantTable;
			
			HRESULT hr = D3DXCompileShader( reinterpret_cast<const char*>( pinnedCode ), rawCode->Length, NULL, NULL,
				reinterpret_cast<const char*>( pinnedFunction ), reinterpret_cast<const char*>( pinnedProfile ),
				static_cast<DWORD>( flags ), &shaderBuffer, &errorBuffer, &constantTable );
			
			if( errorBuffer != NULL )
			{
				compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBuffer->GetBufferPointer() ) );
			}
			else
			{
				compilationErrors = String::Empty;
			}
			
			// CheckHResult() is not used because we need to include the compiler errors.
			if( FAILED(hr) )
			{
				Direct3D9Exception^ ex = gcnew Direct3D9Exception( Result::Last );
				ex->Data->Add( "CompilationErrors", compilationErrors );
				throw ex;
			}

			SetLastError( hr );
			
			IDirect3DPixelShader9 *pixelShader;
			device->InternalPointer->CreatePixelShader( reinterpret_cast<const DWORD*>( shaderBuffer->GetBufferPointer() ), &pixelShader );
			if( pixelShader == NULL)
				return nullptr;
			return gcnew PixelShader( pixelShader, constantTable );
		}

		Result PixelShader::RetrieveConstantTable()
		{
			if( m_ConstantTable != nullptr )
				return RECORD_D3D9( E_FAIL );

			//Retrieve the binary data
			UINT size = 0;
			HRESULT hr = InternalPointer->GetFunction( NULL, &size );
			if( RECORD_D3D9( hr ).IsFailure )
				return Result::Last;

			stack_ptr<char> data( new (stackalloc) char[size] );
			hr = InternalPointer->GetFunction( data.get(), &size );
			if( RECORD_D3D9( hr ).IsFailure )
				return Result::Last;

			//Ask D3DX to give us the actual table
			ID3DXConstantTable* constantTable = NULL;
			hr = D3DXGetShaderConstantTable( reinterpret_cast<const DWORD*>( data.get() ), &constantTable );
			
			if( RECORD_D3D9( hr ).IsFailure )
				return Result::Last;

			m_ConstantTable = gcnew ConstantTable( constantTable );

			return Result::Last;
		}
	}
}
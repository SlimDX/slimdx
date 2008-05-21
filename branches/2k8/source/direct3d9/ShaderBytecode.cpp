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
#include <d3d9.h>
#include <d3dx9.h>

#include "../ComObject.h"
#include "../DataStream.h"
#include "../StackAlloc.h"

#include "Direct3D9Exception.h"
#include "ConstantTable.h"
#include "ShaderBytecode.h"

#include "Device.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	ShaderBytecode::ShaderBytecode( ID3DXBuffer* pointer )
	{
		Construct( pointer );
	}

	ShaderBytecode::ShaderBytecode( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	ShaderBytecode^ ShaderBytecode::FromPointer( ID3DXBuffer* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		ShaderBytecode^ tableEntry = safe_cast<ShaderBytecode^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew ShaderBytecode( pointer );
	}

	ShaderBytecode^ ShaderBytecode::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		ShaderBytecode^ tableEntry = safe_cast<ShaderBytecode^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew ShaderBytecode( pointer );
	}

	DataStream^ ShaderBytecode::Data::get()
	{
		return gcnew DataStream( InternalPointer->GetBufferPointer(), InternalPointer->GetBufferSize(), true, true, false );
	}

	ConstantTable^ ShaderBytecode::ConstantTable::get()
	{
		ID3DXConstantTable* constantTable;
		HRESULT hr = D3DXGetShaderConstantTable( reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() ), &constantTable );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return SlimDX::Direct3D9::ConstantTable::FromPointer( constantTable );
	}

	array<ShaderSemantic>^ ShaderBytecode::GetInputSemantics()
	{
		UINT count = 0;
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );

		HRESULT hr = D3DXGetShaderInputSemantics( function, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		array<ShaderSemantic>^ inputs = gcnew array<ShaderSemantic>( count );
		pin_ptr<ShaderSemantic> pinnedInputs = &inputs[0];

		hr = D3DXGetShaderInputSemantics( function, reinterpret_cast<D3DXSEMANTIC*>( pinnedInputs ), &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		return inputs;
	}

	array<ShaderSemantic>^ ShaderBytecode::GetOutputSemantics()
	{
		UINT count = 0;
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );

		HRESULT hr = D3DXGetShaderOutputSemantics( function, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		array<ShaderSemantic>^ outputs = gcnew array<ShaderSemantic>( count );
		pin_ptr<ShaderSemantic> pinnedOutputs = &outputs[0];

		hr = D3DXGetShaderOutputSemantics( function, reinterpret_cast<D3DXSEMANTIC*>( pinnedOutputs ), &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		return outputs;
	}

	array<String^>^ ShaderBytecode::GetSamplers()
	{
		UINT count = 0;
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );

		HRESULT hr = D3DXGetShaderSamplers( function, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		stack_vector<LPCSTR> samplers( count );

		hr = D3DXGetShaderSamplers( function, &samplers[0], &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;
		
		array<String^>^ outputSamplers = gcnew array<String^>( count );
		for( UINT i = 0; i < count; ++i )
		{
			outputSamplers[i] = gcnew String( samplers[i] );
		}

		return outputSamplers;
	}

	int ShaderBytecode::Version::get()
	{
		const DWORD* function = reinterpret_cast<const DWORD*>( InternalPointer->GetBufferPointer() );
		return static_cast<int>( D3DXGetShaderVersion( function ) );
	}
}
}
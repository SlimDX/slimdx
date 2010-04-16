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
#include "stdafx.h"

#include "Direct3D11Exception.h"

#include "ShaderReflection11.h"
#include "ShaderBytecode11.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D11
{
	ShaderReflection::ShaderReflection( ShaderBytecode^ byteCode )
	{
		ID3D11ShaderReflection* result = 0;
		HRESULT hr = D3DReflect( byteCode->InternalPointer->GetBufferPointer(), byteCode->InternalPointer->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>( &result ) );
		if( RECORD_D3D11( hr ).IsFailure )
			throw gcnew Direct3D11Exception( Result::Last );

		Construct( result );

		D3D11_SHADER_DESC desc;
		InternalPointer->GetDesc( &desc );
		description = gcnew ShaderDescription( desc );
	}

	ConstantBuffer^ ShaderReflection::GetConstantBuffer( int index )
	{
		return gcnew ConstantBuffer( InternalPointer->GetConstantBufferByIndex( index ) );
	}

	ConstantBuffer^ ShaderReflection::GetConstantBuffer( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		return gcnew ConstantBuffer( InternalPointer->GetConstantBufferByName( reinterpret_cast<LPCSTR>(pinnedName) ) );
	}
	
	int ShaderReflection::BitwiseInstructionCount::get()
	{
		return InternalPointer->GetBitwiseInstructionCount();
	}
	
	int ShaderReflection::ConversionInstructionCount::get()
	{
		return InternalPointer->GetConversionInstructionCount();
	}
	
	int ShaderReflection::MoveInstructionCount::get()
	{
		return InternalPointer->GetMovInstructionCount();
	}
	
	int ShaderReflection::ConditionalMoveInstructionCount::get()
	{
		return InternalPointer->GetMovcInstructionCount() ;
	}
	
	int ShaderReflection::InterfaceSlotCount::get()
	{
		return InternalPointer->GetNumInterfaceSlots();
	}
	
	bool ShaderReflection::IsSampleFrequencyShader::get()
	{
		return InternalPointer->IsSampleFrequencyShader() > 0;
	}
}
}
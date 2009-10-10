#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx11effect.h>
#include <vcclr.h>

#include "../DataStream.h"
#include "Effect11.h"

#include "Direct3D11Exception.h"

#include "Device11.h"
#include "ClassLinkage11.h"
#include "EffectConstantBuffer11.h"
#include "EffectDescription11.h"
#include "EffectTechnique11.h"
#include "EffectVariable11.h"

using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D11
{ 
	EffectDescription Effect::Description::get()
	{
		D3DX11_EFFECT_DESC nativeDescription;
		RECORD_D3D11( InternalPointer->GetDesc( &nativeDescription ) );
		if( Result::Last.IsSuccess )
			return EffectDescription( nativeDescription );
		
		throw gcnew Direct3D11Exception( Result::Last );
	}
	
	bool Effect::IsOptimized::get()
	{
		return InternalPointer->IsOptimized() ? true : false;
	}
	
	bool Effect::IsValid::get()
	{
		return InternalPointer->IsValid() ? true : false;
	}
	
	SlimDX::Direct3D11::Device^ Effect::Device::get()
	{
		ID3D11Device* device = 0;
		if( RECORD_D3D11( InternalPointer->GetDevice( &device ) ).IsFailure )
			return nullptr;
		
		return SlimDX::Direct3D11::Device::FromPointer( device );
	}
	
	SlimDX::Direct3D11::ClassLinkage^ Effect::ClassLinkage::get()
	{
		ID3D11ClassLinkage* linkage = InternalPointer->GetClassLinkage();
		if( linkage == NULL )
			return nullptr;

		return SlimDX::Direct3D11::ClassLinkage::FromPointer( linkage );
	}

	EffectConstantBuffer^ Effect::GetConstantBufferByIndex( int index )
	{
		ID3DX11EffectConstantBuffer* buffer = InternalPointer->GetConstantBufferByIndex( index );
		if( buffer == 0 )
			return nullptr;
			
		return gcnew EffectConstantBuffer( buffer );
	}
	
	EffectConstantBuffer^ Effect::GetConstantBufferByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3DX11EffectConstantBuffer* buffer = InternalPointer->GetConstantBufferByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( buffer == 0 )
			return nullptr;
			
		return gcnew EffectConstantBuffer( buffer );
	}
	
	EffectTechnique^ Effect::GetTechniqueByIndex( int index )
	{
		ID3DX11EffectTechnique* technique = InternalPointer->GetTechniqueByIndex( index );
		if( technique == 0 )
			return nullptr;
			
		return gcnew EffectTechnique( technique );
	}

	EffectTechnique^ Effect::GetTechniqueByName( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3DX11EffectTechnique* technique = InternalPointer->GetTechniqueByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( technique == 0 )
			return nullptr;
			
		return gcnew EffectTechnique( technique );
	}
	
	EffectVariable^ Effect::GetVariableByIndex( int index )
	{
		ID3DX11EffectVariable* variable = InternalPointer->GetVariableByIndex( index );
		if( variable == 0 )
			return nullptr;
			
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableByName( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3DX11EffectVariable* variable = InternalPointer->GetVariableByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == 0 )
			return nullptr;
		
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableBySemantic( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3DX11EffectVariable* variable = InternalPointer->GetVariableBySemantic( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == 0 )
			return nullptr;
		
		return gcnew EffectVariable( variable );
	}
	
	Result Effect::Optimize()
	{
		return RECORD_D3D11( InternalPointer->Optimize() );
	}

	Effect^ Effect::FromMemory_Internal( SlimDX::Direct3D11::Device^ device, void* memory, SIZE_T size, UINT effectFlags )
	{
		ID3DX11Effect* effect = 0;

		HRESULT hr = D3DX11CreateEffectFromMemory(
			memory,
			size,
			static_cast<UINT>( effectFlags ),
			device->InternalPointer,
			&effect
		);
		
		RECORD_D3D11( hr );
		if( effect == NULL )
			return nullptr;
		return gcnew Effect( effect, nullptr );
	}

	Effect^ Effect::FromMemory( SlimDX::Direct3D11::Device^ device, array<Byte>^ memory, int effectFlags )
	{
		pin_ptr<unsigned char> pinnedMemory = &memory[ 0 ];

		Effect^ effect = FromMemory_Internal( device, pinnedMemory, static_cast<SIZE_T>( memory->Length ), effectFlags );
		return effect;
	}	
	
	Effect^ Effect::FromStream( SlimDX::Direct3D11::Device^ device, Stream^ stream, int effectFlags )
	{
		DataStream^ ds = nullptr;
		array<Byte>^ memory = Utilities::ReadStream( stream, &ds );

		if( memory == nullptr )
		{
			SIZE_T size = static_cast<SIZE_T>( ds->RemainingLength );
			Effect^ effect = FromMemory_Internal( device, ds->SeekToEnd(), size, effectFlags );
			return effect;
		}

		return FromMemory( device, memory, effectFlags );
	}
}
}

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

#include <d3d10.h>
#include <d3dx10.h>
#include <vcclr.h>

#include "../DataStream.h"
#include "Effect.h"

#include "Direct3D10Exception.h"

#include "Device.h"
#include "EffectConstantBuffer.h"
#include "EffectDescription.h"
#include "EffectTechnique.h"
#include "EffectVariable.h"
#include "EffectPool.h"
#include "Include.h"

using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D10
{ 
	Effect::Effect( ID3D10Effect* pointer )
	{
		Construct( pointer );
	}

	Effect::Effect( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Effect^ Effect::FromPointer( ID3D10Effect* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Effect^ tableEntry = safe_cast<Effect^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Effect( pointer );
	}

	Effect^ Effect::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Effect^ tableEntry = safe_cast<Effect^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Effect( pointer );
	}

	EffectDescription Effect::Description::get()
	{
		D3D10_EFFECT_DESC nativeDescription;
		RECORD_D3D10( InternalPointer->GetDesc( &nativeDescription ) );
		if( Result::Last.IsSuccess )
			return EffectDescription( nativeDescription );
		
		throw gcnew Direct3D10Exception( Result::Last );
	}
	
	bool Effect::IsOptimized::get()
	{
		return InternalPointer->IsOptimized() ? true : false;
	}
	
	bool Effect::IsPooled::get()
	{
		return InternalPointer->IsPool() ? true : false;
	}
	
	bool Effect::IsValid::get()
	{
		return InternalPointer->IsValid() ? true : false;
	}
	
	SlimDX::Direct3D10::Device^ Effect::Device::get()
	{
		ID3D10Device* device = 0;
		if( RECORD_D3D10( InternalPointer->GetDevice( &device ) ).IsFailure )
			return nullptr;
		
		return SlimDX::Direct3D10::Device::FromPointer( device );
	}
	
	EffectConstantBuffer^ Effect::GetConstantBufferByIndex( int index )
	{
		ID3D10EffectConstantBuffer* buffer = InternalPointer->GetConstantBufferByIndex( index );
		if( buffer == 0 )
			return nullptr;
			
		return gcnew EffectConstantBuffer( buffer );
	}
	
	EffectConstantBuffer^ Effect::GetConstantBufferByName( String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3D10EffectConstantBuffer* buffer = InternalPointer->GetConstantBufferByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( buffer == 0 )
			return nullptr;
			
		return gcnew EffectConstantBuffer( buffer );
	}
	
	EffectTechnique^ Effect::GetTechniqueByIndex( int index )
	{
		ID3D10EffectTechnique* technique = InternalPointer->GetTechniqueByIndex( index );
		if( technique == 0 )
			return nullptr;
			
		return gcnew EffectTechnique( technique );
	}

	EffectTechnique^ Effect::GetTechniqueByName( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3D10EffectTechnique* technique = InternalPointer->GetTechniqueByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( technique == 0 )
			return nullptr;
			
		return gcnew EffectTechnique( technique );
	}
	
	EffectVariable^ Effect::GetVariableByIndex( int index )
	{
		ID3D10EffectVariable* variable = InternalPointer->GetVariableByIndex( index );
		if( variable == 0 )
			return nullptr;
			
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableByName( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3D10EffectVariable* variable = InternalPointer->GetVariableByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == 0 )
			return nullptr;
		
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableBySemantic( System::String^ name )
	{
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[ 0 ];
		ID3D10EffectVariable* variable = InternalPointer->GetVariableBySemantic( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == 0 )
			return nullptr;
		
		return gcnew EffectVariable( variable );
	}
	
	Result Effect::Optimize()
	{
		return RECORD_D3D10( InternalPointer->Optimize() );
	}

	Effect^ Effect::FromFile( SlimDX::Direct3D10::Device^ device, String ^fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include )
	{
		String^ compilationErrors;
		return (FromFile( device, fileName, profile, shaderFlags, effectFlags, pool, include, compilationErrors ));
	}
	
	Effect^ Effect::FromFile( SlimDX::Direct3D10::Device^ device, String ^fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include, [Out] String^ %compilationErrors  )
	{
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[ 0 ];
		ID3D10Effect* effect = 0;
		ID3D10EffectPool* effectPool = pool == nullptr ? NULL : static_cast<ID3D10EffectPool*>( pool->InternalPointer );
		ID3D10Blob* errorBlob = 0;
		ID3D10Include* nativeInclude = 0;
		IncludeShim shim = IncludeShim( include );

		if( include != nullptr ) {
			nativeInclude = &shim;
		}
		
		HRESULT hr = D3DX10CreateEffectFromFile(
			pinnedFileName,
			0,
			nativeInclude,
			reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ),
			static_cast<UINT>( effectFlags ),
			device->InternalPointer,
			effectPool,
			0,
			&effect,
			&errorBlob,
			0
		);

		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		RECORD_D3D10( hr );
		if( effect == NULL)
			return nullptr;
		return gcnew Effect( effect );
	}
	
	Effect^ Effect::FromMemory_Internal( SlimDX::Direct3D10::Device^ device, const void* memory, SIZE_T size, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include, String^* compilationErrors )
	{
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[ 0 ];
		ID3D10Effect* effect = 0;
		ID3D10EffectPool* effectPool = pool == nullptr ? NULL : static_cast<ID3D10EffectPool*>( pool->InternalPointer );
		ID3D10Blob* errorBlob = 0;
		ID3D10Include* nativeInclude = 0;
		IncludeShim shim = IncludeShim( include );

		if( include != nullptr ) {
			nativeInclude = &shim;
		}
		
		HRESULT hr = D3DX10CreateEffectFromMemory(
			memory,
			size,
			"n/a",
			0,
			nativeInclude,
			reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ),
			static_cast<UINT>( effectFlags ),
			device->InternalPointer,
			effectPool,
			0,
			&effect,
			&errorBlob,
			0
		);

		if( compilationErrors != 0 )
		{
			if( errorBlob != 0 )
				*compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
			else
				*compilationErrors = nullptr;
		}		
		
		if( errorBlob != 0 )
			errorBlob->Release();

		RECORD_D3D10( hr );
		if( effect == NULL )
			return nullptr;
		return gcnew Effect( effect );
	}

	Effect^ Effect::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include, [Out] String^ %compilationErrors  )
	{
		String^ compilationErrorsLocal;
		pin_ptr<unsigned char> pinnedMemory = &memory[ 0 ];

		Effect^ effect = FromMemory_Internal( device, pinnedMemory, static_cast<SIZE_T>( memory->Length ), profile, shaderFlags, effectFlags, pool, include, &compilationErrorsLocal );
		compilationErrors = compilationErrorsLocal;
		return effect;
	}	
	
	Effect^ Effect::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include )
	{
		String^ compilationErrors;
		return (FromMemory( device, memory, profile, shaderFlags, effectFlags, pool, include, compilationErrors ) );
	}

	Effect^ Effect::FromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include )
	{
		String^ compilationErrors;
		return (FromStream( device, stream, profile, shaderFlags, effectFlags, pool, include, compilationErrors ) );
	}
	
	Effect^ Effect::FromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include, [Out] String^ %compilationErrors )
	{
		DataStream^ ds = nullptr;
		array<Byte>^ memory = Utilities::ReadStream( stream, 0, &ds );

		if( memory == nullptr )
		{
			String^ compilationErrorsLocal;
			SIZE_T size = static_cast<SIZE_T>( ds->RemainingLength );
			Effect^ effect = FromMemory_Internal( device, ds->SeekToEnd(), size, profile, shaderFlags, effectFlags, pool, include, &compilationErrorsLocal );
			compilationErrors = compilationErrorsLocal;
			return effect;
		}

		return (FromMemory( device, memory, profile, shaderFlags, effectFlags, pool, include, compilationErrors ) );
	}
	
	Effect^ Effect::FromString( SlimDX::Direct3D10::Device^ device, String^ code, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include )
	{
		String^ compilationErrors;
		return (FromString( device, code, profile, shaderFlags, effectFlags, pool, include, compilationErrors ));
	}
	
	Effect^ Effect::FromString( SlimDX::Direct3D10::Device^ device, String^ code, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, Include^ include, [Out] String^ %compilationErrors  )
	{
		array<unsigned char>^ codeBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( code );
		pin_ptr<unsigned char> pinnedCode = &codeBytes[ 0 ];
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[ 0 ];
		ID3D10Effect* effect = 0;
		ID3D10EffectPool* effectPool = pool == nullptr ? NULL : static_cast<ID3D10EffectPool*>( pool->InternalPointer );
		ID3D10Blob* errorBlob = 0;
		ID3D10Include* nativeInclude = 0;
		IncludeShim shim = IncludeShim( include );
		
		if( include != nullptr ) {
			nativeInclude = &shim;
		}
		
		HRESULT hr = D3DX10CreateEffectFromMemory(
			pinnedCode,
			code->Length,
			"n/a",
			0,
			nativeInclude,
			reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ),
			static_cast<UINT>( effectFlags ),
			device->InternalPointer,
			effectPool,
			0,
			&effect,
			&errorBlob,
			0
		);
		
		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		RECORD_D3D10( hr );
		if( effect == NULL )
			return nullptr;
		return gcnew Effect( effect );
	}
}
}

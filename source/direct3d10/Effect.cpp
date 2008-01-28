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

#include <d3d10.h>
#include <d3dx10.h>
#include <vcclr.h>

#include "Effect.h"
#include "Direct3D10ErrorHandler.h"
#include "Direct3D10Exception.h"

#include "Device.h"
#include "EffectConstantBuffer.h"
#include "EffectTechnique.h"
#include "EffectVariable.h"
#include "EffectPool.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Effect::Effect( ID3D10Effect* effect )
	{
		Construct(effect);

		D3D10_EFFECT_DESC description;
		HRESULT hr = effect->GetDesc( &description );
		Direct3D10ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			throw gcnew Direct3D10Exception( "Failed to get description for effect." );
		
		m_IsChildEffect = description.IsChildEffect ? true : false;
		m_ConstantBufferCount = description.ConstantBuffers;
		m_SharedConstantBufferCount = description.SharedConstantBuffers;
		m_GlobalVariableCount = description.GlobalVariables;
		m_TechniqueCount = description.Techniques;
	}

	Effect::Effect( IntPtr effect )
	{
		Construct( effect, NativeInterface );

		D3D10_EFFECT_DESC description;
		HRESULT hr = InternalPointer->GetDesc( &description );
		Direct3D10ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			throw gcnew Direct3D10Exception( "Failed to get description for effect." );

		m_IsChildEffect = description.IsChildEffect ? true : false;
		m_ConstantBufferCount = description.ConstantBuffers;
		m_SharedConstantBufferCount = description.SharedConstantBuffers;
		m_GlobalVariableCount = description.GlobalVariables;
		m_TechniqueCount = description.Techniques;
	}
	
	EffectConstantBuffer^ Effect::GetConstantBufferByIndex( int index )
	{
		ID3D10EffectConstantBuffer* buffer = 0;

		buffer = InternalPointer->GetConstantBufferByIndex( index );
		if( buffer == 0 )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any constant buffer in the effect.", index ) );
		return gcnew EffectConstantBuffer( buffer );
	}
	
	EffectConstantBuffer^ Effect::GetConstantBufferByName( String^ name )
	{
		ID3D10EffectConstantBuffer* buffer = 0;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		buffer = InternalPointer->GetConstantBufferByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( buffer == 0 )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any constant buffer in the effect.", name ) );
		return gcnew EffectConstantBuffer( buffer );
	}
	
	EffectTechnique^ Effect::GetTechniqueByIndex( int index )
	{
		ID3D10EffectTechnique* technique;

		technique = InternalPointer->GetTechniqueByIndex( index );
		if( technique == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any technique in the effect.", index ) );
		return gcnew EffectTechnique( technique );
	}

	EffectTechnique^ Effect::GetTechniqueByName( System::String^ name )
	{
		ID3D10EffectTechnique* technique;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		technique = InternalPointer->GetTechniqueByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( technique == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any technique in the effect.", name ) );
		return gcnew EffectTechnique( technique );
	}
	
	EffectVariable^ Effect::GetVariableByIndex( int index )
	{
		ID3D10EffectVariable* variable;
		
		variable = InternalPointer->GetVariableByIndex( index );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Index '{0}' does not identify any variable in the effect.", index ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableByName( System::String^ name )
	{
		ID3D10EffectVariable* variable;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		variable = InternalPointer->GetVariableByName( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Name '{0}' does not identify any variable in the effect.", name ) );
		return gcnew EffectVariable( variable );
	}
	
	EffectVariable^ Effect::GetVariableBySemantic( System::String^ name )
	{
		ID3D10EffectVariable* variable;
		array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		variable = InternalPointer->GetVariableBySemantic( reinterpret_cast<LPCSTR>( pinnedName ) );
		if( variable == NULL )
			throw gcnew ArgumentException( String::Format( CultureInfo::InvariantCulture, "Semantic '{0}' does not identify any variable in the effect.", name ) );
		return gcnew EffectVariable( variable );
	}
	
	void Effect::Optimize()
	{
		HRESULT hr = InternalPointer->Optimize();
		Direct3D10ErrorHandler::TestForFailure( hr );
	}

	Effect^ Effect::FromFile( Device^ device, String ^fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool )
	{
		String^ compilationErrors;
		return (FromFile( device, fileName, profile, shaderFlags, effectFlags, pool, compilationErrors ));
	}
	
	Effect^ Effect::FromFile( Device^ device, String ^fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, [Out] String^ %compilationErrors  )
	{
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;
		ID3D10Blob* errorBlob;
		
		ID3D10EffectPool* effectPool = pool == nullptr ? NULL : static_cast<ID3D10EffectPool*>( pool->InternalPointer );
		HRESULT hr = D3DX10CreateEffectFromFile( pinnedFileName, NULL, NULL, reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ), static_cast<UINT>( effectFlags ), device->InternalPointer,
			effectPool, NULL, &effect, &errorBlob, NULL );

		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		Direct3D10ErrorHandler::TestForFailure( hr );
		if( effect == NULL)
			return nullptr;
		return gcnew Effect( effect );
	}
	
	Effect^ Effect::FromMemory( Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool )
	{
		String^ compilationErrors;
		return (FromMemory( device, memory, profile, shaderFlags, effectFlags, pool, compilationErrors ) );
	}
	
	Effect^ Effect::FromMemory( Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, [Out] String^ %compilationErrors  )
	{
		pin_ptr<unsigned char> pinnedData = &memory[0];
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;
		ID3D10Blob* errorBlob;
		
		ID3D10EffectPool* effectPool = pool == nullptr ? NULL : static_cast<ID3D10EffectPool*>( pool->InternalPointer );
		HRESULT hr = D3DX10CreateEffectFromMemory( pinnedData, memory->Length, "n/a", NULL, NULL, reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ), static_cast<UINT>( effectFlags ), device->InternalPointer,
			effectPool, NULL, &effect, &errorBlob, NULL );
			
		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		Direct3D10ErrorHandler::TestForFailure( hr );
		if( effect == NULL )
			return nullptr;
		return gcnew Effect( effect );
	}
	
	Effect^ Effect::FromStream( Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool )
	{
		String^ compilationErrors;
		return (FromStream( device, stream, profile, shaderFlags, effectFlags, pool, compilationErrors ) );
	}
	
	Effect^ Effect::FromStream( Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, [Out] String^ %compilationErrors )
	{
		array<Byte>^ memory = Utilities::ReadStream( stream, 0 );
		return (FromMemory( device, memory, profile, shaderFlags, effectFlags, pool, compilationErrors ) );
	}
	
	Effect^ Effect::FromString( Device^ device, String^ code, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool )
	{
		String^ compilationErrors;
		return (FromString( device, code, profile, shaderFlags, effectFlags, pool, compilationErrors ));
	}
	
	Effect^ Effect::FromString( Device^ device, String^ code, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, EffectPool^ pool, [Out] String^ %compilationErrors  )
	{
		array<unsigned char>^ codeBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( code );
		pin_ptr<unsigned char> pinnedCode = &codeBytes[0];
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10Effect* effect;
		ID3D10Blob* errorBlob;
		
		ID3D10EffectPool* effectPool = pool == nullptr ? NULL : static_cast<ID3D10EffectPool*>( pool->InternalPointer );
		HRESULT hr = D3DX10CreateEffectFromMemory( pinnedCode, code->Length, "n/a", NULL, NULL, reinterpret_cast<LPCSTR>( pinnedProfile ),
			static_cast<UINT>( shaderFlags ), static_cast<UINT>( effectFlags ), device->InternalPointer,
			effectPool, NULL, &effect, &errorBlob, NULL );
		
		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		Direct3D10ErrorHandler::TestForFailure( hr );
		if( effect == NULL )
			return nullptr;
		return gcnew Effect( effect );
	}
}
}

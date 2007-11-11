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

#include "GraphicsException.h"

#include "EffectPool.h"
#include "Device.h"
#include "Effect.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectPool::EffectPool( ID3D10EffectPool* effectPool ) : DirectXObject( effectPool )
	{
	}

	EffectPool::EffectPool( IntPtr effectPool )
	{
		if( effectPool == IntPtr::Zero )
			throw gcnew ArgumentNullException( "effectPool" );

		void* pointer;
		IUnknown* unknown = static_cast<IUnknown*>( effectPool.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3D10EffectPool, &pointer );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3D10EffectPool*>( pointer );
	}

	Effect^ EffectPool::AsEffect()
	{
		ID3D10Effect* effect = m_Pointer->AsEffect();
		if( effect == 0 )
			return nullptr;
	  return gcnew Effect( effect );
	}

	EffectPool^ EffectPool::FromFile( Device^ device, String^ fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags )
	{
		String^ compilationErrors;
		return (FromFile( device, fileName, profile, shaderFlags, effectFlags, compilationErrors ));
	}
	
	EffectPool^ EffectPool::FromFile( Device^ device, String^ fileName, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, [Out] String^ %compilationErrors  )
	{
		pin_ptr<const wchar_t> pinnedFileName = PtrToStringChars( fileName );
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		ID3D10EffectPool* effectPool;
		ID3D10Blob* errorBlob;

		HRESULT hr = D3DX10CreateEffectPoolFromFile( pinnedFileName, NULL, NULL, (LPCSTR) pinnedProfile,
			static_cast<UINT>(shaderFlags), static_cast< UINT>(effectFlags ), device->DevicePointer,
			NULL, &effectPool, &errorBlob, NULL );

		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( (const char*) errorBlob->GetBufferPointer() );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", compilationErrors );
		if( effectPool == NULL)
			return nullptr;
		return gcnew EffectPool( effectPool );
	}
	
	EffectPool^ EffectPool::FromStream( Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags )
	{
		String^ compilationErrors;
		return (FromStream( device, stream, profile, shaderFlags, effectFlags, compilationErrors ));
	}
	
	EffectPool^ EffectPool::FromStream( Device^ device, Stream^ stream, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, [Out] String^ %compilationErrors  )
	{
		array<Byte>^ memory = Utils::ReadStream( stream, 0 );
		return (FromMemory( device, memory, profile, shaderFlags, effectFlags, compilationErrors ));
	}
	
	EffectPool^ EffectPool::FromMemory( Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags )
	{
		String^ compilationErrors;
		return (FromMemory( device, memory, profile, shaderFlags, effectFlags, compilationErrors ));
	}
	
	EffectPool^ EffectPool::FromMemory( Device^ device, array<Byte>^ memory, String^ profile, ShaderFlags shaderFlags, EffectFlags effectFlags, [Out] String^ %compilationErrors )
	{
		ID3D10EffectPool* effectPool;
		ID3D10Blob* errorBlob;
	
		array<unsigned char>^ profileBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( profile );
		pin_ptr<unsigned char> pinnedProfile = &profileBytes[0];
		pin_ptr<unsigned char> pinnedData = &memory[0];

		HRESULT hr = D3DX10CreateEffectPoolFromMemory( pinnedData, memory->Length, "<no file name>", NULL, NULL,
			(LPCSTR) pinnedProfile, static_cast<UINT>(shaderFlags), static_cast< UINT>(effectFlags ), device->DevicePointer,
			NULL, &effectPool, &errorBlob, NULL );

		if( errorBlob != 0 )
		{
		  compilationErrors = gcnew String( (const char*) errorBlob->GetBufferPointer() );
		  errorBlob->Release();
		}
		else
		{
			compilationErrors = String::Empty;
		}
		
		GraphicsException::CheckHResult( hr, "Compilation Errors", compilationErrors );
		if( effectPool == NULL)
			return nullptr;
		return gcnew EffectPool( effectPool );
		}
}
}

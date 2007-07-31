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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "Device.h"
#include "Effect.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		Effect::Effect( ID3DXEffect* effect ) : BaseEffect( effect )
		{
			if( effect == NULL )
				throw gcnew ArgumentNullException( "effect" );
		}

		Effect^ Effect::FromMemory( Device ^device, array<Byte>^ memory, array<Macro>^ preprocessorDefines,
			Include ^includeFile, String^ skipConstants, ShaderFlags flags, EffectPool^ pool,
			[Out] String^ %compilationErrors )
		{
			ID3DXEffect* effect;
			ID3DXBuffer* errorBuffer;
			pin_ptr<unsigned char> pinned_data = &memory[0];

			//TODO: Fix some of these params
			HRESULT hr = D3DXCreateEffectEx( device->InternalPointer, pinned_data, memory->Length, NULL, NULL, NULL,
				(DWORD) flags, NULL, &effect, &errorBuffer );
			
			if( errorBuffer != NULL )
			{
				compilationErrors = gcnew String( (const char*) errorBuffer->GetBufferPointer() );
			}
			else
			{
				compilationErrors = String::Empty;
			}
			
			// CheckHResult() is not used because we need to include the compiler errors.
			if( DirectXException::EnableExceptions && FAILED(hr) )
			{
				GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( hr );
				ex->Data->Add( "CompilationErrors", compilationErrors );
				throw ex;
			}

			SetLastError( hr );
			
			if( effect == NULL)
				return nullptr;
			return gcnew Effect( effect );
		}

		Effect^ Effect::FromStream( Device^ device, Stream^ stream, array<Macro>^ preprocessorDefines, Include^ includeFile,
			String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
		{
			array<Byte>^ data = Utils::ReadStream( stream, 0 );

			return Effect::FromMemory( device, data, preprocessorDefines, includeFile,
				skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromStream( Device^ device, Stream^ stream, Include^ includeFile, String^ skipConstants,
			ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
		{
			return FromStream( device, stream, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromStream( Device^ device, Stream^ stream, Include^ includeFile, 
			String^ skipConstants, ShaderFlags flags, EffectPool^ pool )
		{
			String^ compilationErrors;
			return FromStream( device, stream, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromString( Device^ device, String^ sourceData, array<Macro>^ preprocessorDefines, Include^ includeFile,
			String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
		{
			array<Byte>^ data = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceData );

			return Effect::FromMemory( device, data, preprocessorDefines, includeFile,
				skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromString( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
			ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors)
		{
			return FromString(device, sourceData, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromString( Device^ device, String^ sourceData, Include^ includeFile, String^ skipConstants,
			ShaderFlags flags, EffectPool^ pool)
		{
			String^ compilationErrors;
			return FromString(device, sourceData, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromFile( Device^ device, String^ fileName, array<Macro>^ preprocessorDefines, Include^ includeFile,
			String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
		{
			ID3DXEffect* effect;
			ID3DXBuffer* errorBuffer;
			pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

			//TODO: Fix some of these parameters
			HRESULT hr = D3DXCreateEffectFromFile( device->InternalPointer, pinnedName, NULL, NULL,
				(DWORD) flags, NULL, &effect, &errorBuffer );
			
			if( errorBuffer != NULL )
			{
				compilationErrors = gcnew String( (const char*) errorBuffer->GetBufferPointer() );
			}
			else
			{
				compilationErrors = String::Empty;
			}
			
			// CheckHResult() is not used because we need to include the compiler errors.
			if( DirectXException::EnableExceptions && FAILED(hr) )
			{
				GraphicsException^ ex = GraphicsException::GetExceptionFromHResult( hr );
				ex->Data->Add( "CompilationErrors", compilationErrors );
				throw ex;
			}

			SetLastError( hr );
			
			if( effect == NULL)
				return nullptr;
			return gcnew Effect( effect );
		}

		Effect^ Effect::FromFile( Device^ device, String^ fileName, Include^ includeFile, String^ skipConstants,
			ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors)
		{
			return Effect::FromFile( device, fileName, nullptr, includeFile, skipConstants, flags, pool, compilationErrors );
		}

		Effect^ Effect::FromFile( Device^ device, String^ fileName, Include^ includeFile, String^ skipConstants,
			ShaderFlags flags, EffectPool^ pool)
		{
			String^ compilationErrors;
			return Effect::FromFile( device, fileName, includeFile, skipConstants, flags, pool, compilationErrors );
		}

		int Effect::Begin( FX flags )
		{
			unsigned int passCount;

			HRESULT hr = EffectPointer->Begin( &passCount, (DWORD) flags );
			GraphicsException::CheckHResult( hr );

			return passCount;
		}

		void Effect::End()
		{
			HRESULT hr = EffectPointer->End();
			GraphicsException::CheckHResult( hr );
		}

		void Effect::BeginPass( int pass )
		{
			HRESULT hr = EffectPointer->BeginPass( pass );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::EndPass()
		{
			HRESULT hr = EffectPointer->EndPass();
			GraphicsException::CheckHResult( hr );
		}

		void Effect::BeginParameterBlock()
		{
			HRESULT hr = EffectPointer->BeginParameterBlock();
			GraphicsException::CheckHResult( hr );
		}

		EffectHandle^ Effect::EndParameterBlock()
		{
			D3DXHANDLE handle = EffectPointer->EndParameterBlock();
			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		void Effect::ApplyParameterBlock( EffectHandle^ parameterBlock )
		{
			D3DXHANDLE handle = parameterBlock != nullptr ? parameterBlock->InternalHandle : NULL;
			HRESULT hr = EffectPointer->ApplyParameterBlock( handle );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::DeleteParameterBlock( EffectHandle^ parameterBlock )
		{
			D3DXHANDLE handle = parameterBlock != nullptr ? parameterBlock->InternalHandle : NULL;
			HRESULT hr = EffectPointer->DeleteParameterBlock( handle );
			GraphicsException::CheckHResult( hr );
		}

		bool Effect::IsParameterUsed( EffectHandle^ parameter, EffectHandle^ technique )
		{
			D3DXHANDLE paramHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE techHandle = technique != nullptr ? technique->InternalHandle : NULL;
			BOOL used = EffectPointer->IsParameterUsed( paramHandle, techHandle );
			return used > 0;
		}

		void Effect::CommitChanges()
		{
			HRESULT hr = EffectPointer->CommitChanges();
			GraphicsException::CheckHResult( hr );
		}

		EffectHandle^ Effect::FindNextValidTechnique( EffectHandle^ technique )
		{
			D3DXHANDLE handle;
			D3DXHANDLE parentHandle = technique != nullptr ? technique->InternalHandle : NULL;

			HRESULT hr = EffectPointer->FindNextValidTechnique( parentHandle, &handle );
			GraphicsException::CheckHResult( hr );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		bool Effect::ValidateTechnique( EffectHandle^ technique )
		{
			D3DXHANDLE handle = technique != nullptr ? technique->InternalHandle : NULL;
			return FAILED( EffectPointer->ValidateTechnique( handle ) );
		}

		EffectHandle^ Effect::Technique::get()
		{
			D3DXHANDLE handle = EffectPointer->GetCurrentTechnique();
			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		void Effect::Technique::set( EffectHandle^ value )
		{
			D3DXHANDLE handle = value != nullptr ? value->InternalHandle : NULL;
			HRESULT hr = EffectPointer->SetTechnique( handle );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::OnLostDevice()
		{
			HRESULT hr = EffectPointer->OnLostDevice();
			GraphicsException::CheckHResult( hr );
		}

		void Effect::OnResetDevice()
		{
			HRESULT hr = EffectPointer->OnResetDevice();
			GraphicsException::CheckHResult( hr );
		}
	}
}

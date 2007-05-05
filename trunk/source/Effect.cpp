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

#include "Device.h"
#include "Texture.h"
#include "Effect.h"

namespace SlimDX
{
	namespace Direct3D
	{
		EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, int index )
		{
			D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE annotation = m_BaseEffect->GetAnnotation( parentHandle, index );

			if( annotation == NULL )
				return nullptr;
			return gcnew EffectHandle( annotation );
		}

		EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinned_name = &nameBytes[0];

			D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE annotation = m_BaseEffect->GetAnnotationByName( parentHandle, (LPCSTR) pinned_name );

			if( annotation == NULL )
				return nullptr;
			return gcnew EffectHandle( annotation );
		}

		EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, int index )
		{
			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_BaseEffect->GetParameter( parentHandle, index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinned_name = &nameBytes[0];

			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_BaseEffect->GetParameterByName( parentHandle, (const char*) pinned_name );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameterBySemantic( EffectHandle^ parameter, String^ semantic )
		{
			array<Byte>^ semanticBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( semantic );
			pin_ptr<unsigned char> pinned_semantic = &semanticBytes[0];

			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_BaseEffect->GetParameterBySemantic( parentHandle, (const char*) pinned_semantic );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameterElement( EffectHandle^ parameter, int index )
		{
			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_BaseEffect->GetParameterElement( parentHandle, index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		ParameterDescription BaseEffect::GetParameterDescription( EffectHandle^ parameter )
		{
			D3DXPARAMETER_DESC desc;

			HRESULT hr = m_BaseEffect->GetParameterDesc( parameter->InternalHandle, &desc );
			GraphicsException::CheckHResult( hr );

			ParameterDescription outDesc;
			outDesc.Name = gcnew String( desc.Name );
			outDesc.Semantic = gcnew String( desc.Semantic );
			outDesc.Class = (ParameterClass) desc.Class;
			outDesc.Type = (ParameterType) desc.Type;
			outDesc.Rows = desc.Rows;
			outDesc.Columns = desc.Columns;
			outDesc.Elements = desc.Elements;
			outDesc.Annotations = desc.Annotations;
			outDesc.StructMembers = desc.StructMembers;
			outDesc.Flags = (ParameterFlags) desc.Flags;
			outDesc.Bytes = desc.Bytes;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetFunction( int index )
		{
			D3DXHANDLE handle = m_BaseEffect->GetFunction( index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetFunction( String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinned_name = &nameBytes[0];

			D3DXHANDLE handle = m_BaseEffect->GetFunctionByName( (const char*) pinned_name );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		FunctionDescription BaseEffect::GetFunctionDescription( EffectHandle^ handle )
		{
			D3DXFUNCTION_DESC desc;

			HRESULT hr = m_BaseEffect->GetFunctionDesc( handle->InternalHandle, &desc );
			GraphicsException::CheckHResult( hr );

			FunctionDescription outDesc;
			outDesc.Name = gcnew String( desc.Name );
			outDesc.Annotations = desc.Annotations;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetTechnique( int index )
		{
			D3DXHANDLE handle = m_BaseEffect->GetTechnique( index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetTechnique( String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinned_name = &nameBytes[0];

			D3DXHANDLE handle = m_BaseEffect->GetTechniqueByName( (const char*) pinned_name );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		TechniqueDescription BaseEffect::GetTechniqueDescription( EffectHandle^ handle )
		{
			D3DXTECHNIQUE_DESC desc;

			HRESULT hr = m_BaseEffect->GetTechniqueDesc( handle->InternalHandle, &desc );
			GraphicsException::CheckHResult( hr );

			TechniqueDescription outDesc;
			outDesc.Name = gcnew String( desc.Name );
			outDesc.Annotations = desc.Annotations;
			outDesc.Passes = desc.Passes;

			return outDesc;
		}

		EffectDescription BaseEffect::Description::get()
		{
			D3DXEFFECT_DESC desc;

			HRESULT hr = m_BaseEffect->GetDesc( &desc );
			GraphicsException::CheckHResult( hr );

			EffectDescription outDesc;
			outDesc.Creator = gcnew String( desc.Creator );
			outDesc.Parameters = desc.Parameters;
			outDesc.Techniques = desc.Techniques;
			outDesc.Functions = desc.Functions;

			return outDesc;
		}

		void BaseEffect::SetValue( EffectHandle^ param, bool value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_BaseEffect->SetBool( param->InternalHandle, value );
			GraphicsException::CheckHResult( hr );
		}

		//implementing set for bool array is REALLY ANNOYING.

		void BaseEffect::SetValue( EffectHandle^ param, int value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_BaseEffect->SetInt( handle, value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<int>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<int> pinned_value = &values[0];
			HRESULT hr = m_BaseEffect->SetIntArray( handle, pinned_value, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, float value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_BaseEffect->SetFloat( handle, value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<float>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<float> pinned_value = &values[0];
			HRESULT hr = m_BaseEffect->SetFloatArray( handle, pinned_value, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, Vector4 value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Vector4> pinned_value = &value;
			HRESULT hr = m_BaseEffect->SetVector( handle, (const D3DXVECTOR4*) pinned_value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<Vector4>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Vector4> pinned_value = &values[0];
			HRESULT hr = m_BaseEffect->SetVectorArray( handle, (const D3DXVECTOR4*) pinned_value, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, ColorValue value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<ColorValue> pinned_value = &value;
			HRESULT hr = m_BaseEffect->SetVector( handle, (const D3DXVECTOR4*) pinned_value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<ColorValue>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<ColorValue> pinned_value = &values[0];
			HRESULT hr = m_BaseEffect->SetVectorArray( handle, (const D3DXVECTOR4*) pinned_value, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, Matrix value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_BaseEffect->SetMatrix( handle, (const D3DXMATRIX*) &value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<Matrix>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Matrix> pinned_value = &values[0];
			HRESULT hr = m_BaseEffect->SetMatrixArray( handle, (const D3DXMATRIX*) pinned_value, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, BaseTexture^ value )
		{
			IDirect3DBaseTexture9* texture = NULL;
			if( value != nullptr )
				texture = static_cast<IDirect3DBaseTexture9*>( value->ResourcePointer );

			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_BaseEffect->SetTexture( handle, texture );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValueTranspose( EffectHandle^ param, Matrix value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_BaseEffect->SetMatrixTranspose( handle, (const D3DXMATRIX*) &value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValueTranspose( EffectHandle^ param, array<Matrix>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Matrix> pinned_value = &values[0];
			HRESULT hr = m_BaseEffect->SetMatrixTransposeArray( handle, (const D3DXMATRIX*) pinned_value, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		String^ BaseEffect::GetValueString( EffectHandle^ param )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			LPCSTR data = 0;

			HRESULT hr = m_BaseEffect->GetString(handle,&data);
			GraphicsException::CheckHResult( hr );

			return (gcnew String(data));
		}

		Effect::Effect( ID3DXEffect* effect ) : BaseEffect( effect )
		{
			if( effect == NULL )
				throw gcnew ArgumentNullException( "effect" );

			m_Effect = effect;
		}

		Effect^ Effect::FromStream( Device^ device, Stream^ stream, array<Macro^>^ preprocessorDefines, Include^ includeFile,
			String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
		{
			//TODO: This is nearly identical to FromString. Could we factor this out?
			ID3DXEffect* effect;
			ID3DXBuffer* errorBuffer;

			array<Byte>^ data = Utils::ReadStream( stream, 0 );
			pin_ptr<unsigned char> pinned_data = &data[0];

			//TODO: Fix some of these params
			HRESULT hr = D3DXCreateEffectEx( device->InternalPointer, pinned_data, data->Length, NULL, NULL, NULL,
				(DWORD) flags, NULL, &effect, &errorBuffer );
			GraphicsException::CheckHResult( hr );

			if( errorBuffer != NULL )
			{
				compilationErrors = gcnew String( (const char*) errorBuffer->GetBufferPointer() );
			}
			else
			{
				compilationErrors = String::Empty;
			}

			return gcnew Effect( effect );
		}

		Effect^ Effect::FromString( Device^ device, String^ sourceData, array<Macro^>^ preprocessorDefines, Include^ includeFile,
			String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
		{
			//TODO: This is nearly identical to FromStream. Could we factor this out?
			ID3DXEffect* effect;
			ID3DXBuffer* errorBuffer;

			array<Byte>^ data = System::Text::ASCIIEncoding::ASCII->GetBytes( sourceData );
			pin_ptr<unsigned char> pinned_data = &data[0];

			//TODO: Fix some of these params
			HRESULT hr = D3DXCreateEffectEx( device->InternalPointer, pinned_data, data->Length, NULL, NULL, NULL,
				(DWORD) flags, NULL, &effect, &errorBuffer );
			GraphicsException::CheckHResult( hr );

			if( errorBuffer != NULL )
			{
				compilationErrors = gcnew String( (const char*) errorBuffer->GetBufferPointer() );
			}
			else
			{
				compilationErrors = String::Empty;
			}

			return gcnew Effect( effect );
		}

		int Effect::Begin( FX flags )
		{
			unsigned int passCount;

			HRESULT hr = m_Effect->Begin( &passCount, (DWORD) flags );
			GraphicsException::CheckHResult( hr );

			return passCount;
		}

		void Effect::End()
		{
			HRESULT hr = m_Effect->End();
			GraphicsException::CheckHResult( hr );
		}

		void Effect::BeginPass( int pass )
		{
			HRESULT hr = m_Effect->BeginPass( pass );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::EndPass()
		{
			HRESULT hr = m_Effect->EndPass();
			GraphicsException::CheckHResult( hr );
		}

		void Effect::BeginParameterBlock()
		{
			HRESULT hr = m_Effect->BeginParameterBlock();
			GraphicsException::CheckHResult( hr );
		}

		EffectHandle^ Effect::EndParameterBlock()
		{
			D3DXHANDLE handle = m_Effect->EndParameterBlock();
			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		void Effect::ApplyParameterBlock( EffectHandle^ parameterBlock )
		{
			D3DXHANDLE handle = parameterBlock != nullptr ? parameterBlock->InternalHandle : nullptr;
			HRESULT hr = m_Effect->ApplyParameterBlock( handle );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::DeleteParameterBlock( EffectHandle^ parameterBlock )
		{
			D3DXHANDLE handle = parameterBlock != nullptr ? parameterBlock->InternalHandle : nullptr;
			HRESULT hr = m_Effect->DeleteParameterBlock( handle );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::CommitChanges()
		{
			HRESULT hr = m_Effect->CommitChanges();
			GraphicsException::CheckHResult( hr );
		}

		EffectHandle^ Effect::FindNextValidTechnique( EffectHandle^ technique )
		{
			D3DXHANDLE handle;
			D3DXHANDLE parentHandle = technique != nullptr ? technique->InternalHandle : nullptr;

			HRESULT hr = m_Effect->FindNextValidTechnique( parentHandle, &handle );
			GraphicsException::CheckHResult( hr );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		bool Effect::ValidateTechnique( EffectHandle^ technique )
		{
			D3DXHANDLE handle = technique != nullptr ? technique->InternalHandle : nullptr;
			return FAILED( m_Effect->ValidateTechnique( handle ) );
		}

		EffectHandle^ Effect::Technique::get()
		{
			D3DXHANDLE handle = m_Effect->GetCurrentTechnique();
			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		void Effect::Technique::set( EffectHandle^ value )
		{
			D3DXHANDLE handle = value != nullptr ? value->InternalHandle : nullptr;
			HRESULT hr = m_Effect->SetTechnique( handle );
			GraphicsException::CheckHResult( hr );
		}

		void Effect::OnLostDevice()
		{
			HRESULT hr = m_Effect->OnLostDevice();
			GraphicsException::CheckHResult( hr );
		}

		void Effect::OnResetDevice()
		{
			HRESULT hr = m_Effect->OnResetDevice();
			GraphicsException::CheckHResult( hr );
		}
	}
}

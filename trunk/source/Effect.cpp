#include <d3d9.h>
#include <d3dx9.h>

#include "Device.h"
#include "Texture.h"
#include "Effect.h"

namespace SlimDX
{
namespace Direct3D
{
	void BaseEffect::SetValue( EffectHandle^ param, bool value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		HRESULT hr = m_BaseEffect->SetBool( param->InternalHandle, value );
		FAILED_THROW( hr );
	}

	//implementing set for bool array is REALLY ANNOYING.

	void BaseEffect::SetValue( EffectHandle^ param, int value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		HRESULT hr = m_BaseEffect->SetInt( handle, value );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, array<int>^ values )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<int> pinned_value = &values[0];
		HRESULT hr = m_BaseEffect->SetIntArray( handle, pinned_value, values->Length );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, float value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		HRESULT hr = m_BaseEffect->SetFloat( handle, value );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, array<float>^ values )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<float> pinned_value = &values[0];
		HRESULT hr = m_BaseEffect->SetFloatArray( handle, pinned_value, values->Length );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, Vector4 value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<Vector4> pinned_value = &value;
		HRESULT hr = m_BaseEffect->SetVector( handle, (const D3DXVECTOR4*) pinned_value );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, array<Vector4>^ values )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<Vector4> pinned_value = &values[0];
		HRESULT hr = m_BaseEffect->SetVectorArray( handle, (const D3DXVECTOR4*) pinned_value, values->Length );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, ColorValue value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<ColorValue> pinned_value = &value;
		HRESULT hr = m_BaseEffect->SetVector( handle, (const D3DXVECTOR4*) pinned_value );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, array<ColorValue>^ values )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<ColorValue> pinned_value = &values[0];
		HRESULT hr = m_BaseEffect->SetVectorArray( handle, (const D3DXVECTOR4*) pinned_value, values->Length );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, Matrix value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		HRESULT hr = m_BaseEffect->SetMatrix( handle, (const D3DXMATRIX*) &value );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, array<Matrix>^ values )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = m_BaseEffect->SetMatrixArray( handle, (const D3DXMATRIX*) pinned_value, values->Length );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValue( EffectHandle^ param, BaseTexture^ value )
	{
		IDirect3DBaseTexture9* texture = NULL;
		if( value != nullptr )
			texture = static_cast<IDirect3DBaseTexture9*>( value->ResourcePointer );

		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		HRESULT hr = m_BaseEffect->SetTexture( handle, texture );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValueTranspose( EffectHandle^ param, Matrix value )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		HRESULT hr = m_BaseEffect->SetMatrixTranspose( handle, (const D3DXMATRIX*) &value );
		FAILED_THROW( hr );
	}

	void BaseEffect::SetValueTranspose( EffectHandle^ param, array<Matrix>^ values )
	{
		D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = m_BaseEffect->SetMatrixTransposeArray( handle, (const D3DXMATRIX*) pinned_value, values->Length );
		FAILED_THROW( hr );
	}


	Effect::Effect( ID3DXEffect* effect ) : BaseEffect( effect )
	{
		if( effect == NULL )
			throw gcnew ArgumentNullException( "effect" );

		m_Effect = effect;
		m_Disposed = false;
	}

	Effect^ Effect::FromStream( Device^ device, Stream^ stream, array<Macro^>^ preprocessorDefines, Include^ includeFile,
		String^ skipConstants, ShaderFlags flags, EffectPool^ pool, [Out] String^ %compilationErrors )
	{
		ID3DXEffect* effect;
		ID3DXBuffer* errorBuffer;

		array<Byte>^ data = Utils::ReadStream( stream, 0 );
		pin_ptr<unsigned char> pinned_data = &data[0];

		//TODO: Fix some of these params
		D3DXCreateEffectEx( device->InternalPointer, pinned_data, data->Length, NULL, NULL, NULL,
			(DWORD) flags, NULL, &effect, &errorBuffer );

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
		m_Effect->Begin( &passCount, (DWORD) flags );
		return passCount;
	}

	void Effect::End()
	{
		m_Effect->End();
	}

	void Effect::BeginPass( int pass )
	{
		m_Effect->BeginPass( pass );
	}

	void Effect::EndPass()
	{
		m_Effect->EndPass();
	}

	EffectHandle^ Effect::FindNextValidTechnique( EffectHandle^ technique )
	{
		D3DXHANDLE handle;
		D3DXHANDLE parentHandle = technique != nullptr ? technique->InternalHandle : nullptr;
		m_Effect->FindNextValidTechnique( parentHandle, &handle );
		return gcnew EffectHandle( handle );
	}
}
}

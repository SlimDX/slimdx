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

#include "../math/Math.h"
#include "Device.h"
#include "Texture.h"
#include "BaseEffect.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, int index )
		{
			D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE annotation = m_Pointer->GetAnnotation( parentHandle, index );

			if( annotation == NULL )
				return nullptr;
			return gcnew EffectHandle( annotation );
		}

		EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE annotation = m_Pointer->GetAnnotationByName( parentHandle, reinterpret_cast<LPCSTR>( pinnedName ) );

			if( annotation == NULL )
				return nullptr;
			return gcnew EffectHandle( annotation );
		}

		EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, int index )
		{
			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_Pointer->GetParameter( parentHandle, index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_Pointer->GetParameterByName( parentHandle, reinterpret_cast<const char*>( pinnedName ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameterBySemantic( EffectHandle^ parameter, String^ semantic )
		{
			array<Byte>^ semanticBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( semantic );
			pin_ptr<unsigned char> pinnedSemantic = &semanticBytes[0];

			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_Pointer->GetParameterBySemantic( parentHandle, reinterpret_cast<const char*>( pinnedSemantic ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetParameterElement( EffectHandle^ parameter, int index )
		{
			D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
			D3DXHANDLE handle = m_Pointer->GetParameterElement( parentHandle, index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		ParameterDescription BaseEffect::GetParameterDescription( EffectHandle^ parameter )
		{
			D3DXPARAMETER_DESC desc;

			HRESULT hr = m_Pointer->GetParameterDesc( parameter->InternalHandle, &desc );
			GraphicsException::CheckHResult( hr );

			ParameterDescription outDesc;
			outDesc.Name = gcnew String( desc.Name );
			outDesc.Semantic = gcnew String( desc.Semantic );
			outDesc.Class = static_cast<ParameterClass>( desc.Class );
			outDesc.Type = static_cast<ParameterType>( desc.Type );
			outDesc.Rows = desc.Rows;
			outDesc.Columns = desc.Columns;
			outDesc.Elements = desc.Elements;
			outDesc.Annotations = desc.Annotations;
			outDesc.StructMembers = desc.StructMembers;
			outDesc.Flags = static_cast<ParameterFlags>( desc.Flags );
			outDesc.Bytes = desc.Bytes;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetFunction( int index )
		{
			D3DXHANDLE handle = m_Pointer->GetFunction( index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetFunction( String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE handle = m_Pointer->GetFunctionByName( reinterpret_cast<const char*>( pinnedName ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		FunctionDescription BaseEffect::GetFunctionDescription( EffectHandle^ handle )
		{
			D3DXFUNCTION_DESC desc;

			HRESULT hr = m_Pointer->GetFunctionDesc( handle->InternalHandle, &desc );
			GraphicsException::CheckHResult( hr );

			FunctionDescription outDesc;
			outDesc.Name = gcnew String( desc.Name );
			outDesc.Annotations = desc.Annotations;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetTechnique( int index )
		{
			D3DXHANDLE handle = m_Pointer->GetTechnique( index );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		EffectHandle^ BaseEffect::GetTechnique( String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE handle = m_Pointer->GetTechniqueByName( reinterpret_cast<const char*>( pinnedName ) );

			if( handle == NULL )
				return nullptr;
			return gcnew EffectHandle( handle );
		}

		TechniqueDescription BaseEffect::GetTechniqueDescription( EffectHandle^ handle )
		{
			D3DXTECHNIQUE_DESC desc;

			HRESULT hr = m_Pointer->GetTechniqueDesc( handle->InternalHandle, &desc );
			GraphicsException::CheckHResult( hr );

			TechniqueDescription outDesc;
			outDesc.Name = gcnew String( desc.Name );
			outDesc.Annotations = desc.Annotations;
			outDesc.Passes = desc.Passes;

			return outDesc;
		}

		EffectHandle^ BaseEffect::GetPass( EffectHandle^ handle, int index )
		{
			D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE pass = m_Pointer->GetPass( nativeHandle, index );

			if( pass == NULL )
				return nullptr;
			return gcnew EffectHandle( pass );
		}

		EffectHandle^ BaseEffect::GetPass( EffectHandle^ handle, String^ name )
		{
			array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];

			D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
			D3DXHANDLE pass = m_Pointer->GetPassByName( nativeHandle, reinterpret_cast<const char*>( pinnedName ) );

			if( pass == NULL )
				return nullptr;
			return gcnew EffectHandle( pass );
		}

		PassDescription BaseEffect::GetPassDescription( EffectHandle^ handle )
		{
			D3DXPASS_DESC desc;
			D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;

			HRESULT hr = m_Pointer->GetPassDesc( nativeHandle, &desc );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return PassDescription();

			PassDescription passDesc;
			passDesc.Name = gcnew String( desc.Name );
			passDesc.Annotations = desc.Annotations;
			passDesc.VertexShaderFunction = IntPtr( const_cast<void*>( static_cast<const void*>( desc.pVertexShaderFunction ) ) );
			passDesc.PixelShaderFunction = IntPtr( const_cast<void*>( static_cast<const void*>( desc.pPixelShaderFunction ) ) );

			return passDesc;
		}

		EffectDescription BaseEffect::Description::get()
		{
			D3DXEFFECT_DESC desc;

			HRESULT hr = m_Pointer->GetDesc( &desc );
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
			HRESULT hr = m_Pointer->SetBool( handle, value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<bool>^ values )
		{
			//implementing set for bool array is REALLY ANNOYING.
			//Win32 uses BOOL, which is an int
			array<BOOL>^ expandedArray = gcnew array<BOOL>( values->Length );
			Array::Copy( values, expandedArray, values->Length );

			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<BOOL> pinnedValue = &expandedArray[0];
			HRESULT hr = m_Pointer->SetBoolArray( handle, pinnedValue, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, int value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetInt( handle, value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<int>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<int> pinnedValue = &values[0];
			HRESULT hr = m_Pointer->SetIntArray( handle, pinnedValue, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, float value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetFloat( handle, value );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<float>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<float> pinnedValues = &values[0];
			HRESULT hr = m_Pointer->SetFloatArray( handle, pinnedValues, values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, Vector4 value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<Vector4>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Vector4> pinnedValue = &values[0];
			HRESULT hr = m_Pointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinnedValue ), values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, ColorValue value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<ColorValue>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<ColorValue> pinnedValue = &values[0];
			HRESULT hr = m_Pointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinnedValue ), values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, Matrix value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetMatrix( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, array<Matrix>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Matrix> pinnedValue = &values[0];
			HRESULT hr = m_Pointer->SetMatrixArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinnedValue ), values->Length );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, BaseTexture^ value )
		{
			IDirect3DBaseTexture9* texture = NULL;
			if( value != nullptr )
				texture = value->BaseTexturePointer;

			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetTexture( handle, texture );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValue( EffectHandle^ param, String^ value )
		{
			array<unsigned char>^ valueBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( value );
			pin_ptr<unsigned char> pinnedValue = &valueBytes[0];

			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetString( handle, reinterpret_cast<LPCSTR>( pinnedValue ) );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValueTranspose( EffectHandle^ param, Matrix value )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->SetMatrixTranspose( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
			GraphicsException::CheckHResult( hr );
		}

		void BaseEffect::SetValueTranspose( EffectHandle^ param, array<Matrix>^ values )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			pin_ptr<Matrix> pinnedValue = &values[0];
			HRESULT hr = m_Pointer->SetMatrixTransposeArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinnedValue ), values->Length );
			GraphicsException::CheckHResult( hr );
		}

		bool BaseEffect::GetBool( EffectHandle^ param )
		{
			BOOL value = FALSE;
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetBool( handle, &value );
			GraphicsException::CheckHResult( hr );

			return value < 0;
		}

		array<bool>^ BaseEffect::GetBoolArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<BOOL>^ data = gcnew array<BOOL>( count );
			pin_ptr<BOOL> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetBoolArray( handle, pinnedData, count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

            //now we go from BOOL to bool
            array<bool>^ boolData = gcnew array<bool>( count );
            Array::Copy( data, boolData, count );
            return boolData;
		}

		int BaseEffect::GetInt( EffectHandle^ param )
		{
			int value = 0;
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetInt( handle, &value );
			GraphicsException::CheckHResult( hr );

			return value;
		}

		array<int>^ BaseEffect::GetIntArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<int>^ data = gcnew array<int>( count );
			pin_ptr<int> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetIntArray( handle, pinnedData, count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		float BaseEffect::GetFloat( EffectHandle^ param )
		{
			float value = 0.0f;
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetFloat( handle, &value );
			GraphicsException::CheckHResult( hr );

			return value;
		}

		array<float>^ BaseEffect::GetFloatArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<float>^ data = gcnew array<float>( count );
			pin_ptr<float> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetFloatArray( handle, pinnedData, count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		Vector4 BaseEffect::GetVector( EffectHandle^ param )
		{
			Vector4 value = Vector4();
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetVector( handle, reinterpret_cast<D3DXVECTOR4*>( &value ) );
			GraphicsException::CheckHResult( hr );

			return value;
		}

		array<Vector4>^ BaseEffect::GetVectorArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<Vector4>^ data = gcnew array<Vector4>( count );
			pin_ptr<Vector4> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetVectorArray( handle, reinterpret_cast<D3DXVECTOR4*>( pinnedData ), count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		ColorValue BaseEffect::GetColor( EffectHandle^ param )
		{
			ColorValue value = ColorValue();
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetVector( handle, reinterpret_cast<D3DXVECTOR4*>( &value ) );
			GraphicsException::CheckHResult( hr );

			return value;
		}

		array<ColorValue>^ BaseEffect::GetColorArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<ColorValue>^ data = gcnew array<ColorValue>( count );
			pin_ptr<ColorValue> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetVectorArray( handle, reinterpret_cast<D3DXVECTOR4*>( pinnedData ), count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		Matrix BaseEffect::GetMatrix( EffectHandle^ param )
		{
			Matrix value = Matrix();
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetMatrix( handle, reinterpret_cast<D3DXMATRIX*>( &value ) );
			GraphicsException::CheckHResult( hr );

			return value;
		}

		array<Matrix>^ BaseEffect::GetMatrixArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<Matrix>^ data = gcnew array<Matrix>( count );
			pin_ptr<Matrix> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetMatrixArray( handle, reinterpret_cast<D3DXMATRIX*>( pinnedData ), count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		BaseTexture^ BaseEffect::GetTexture( EffectHandle^ param )
		{
			IDirect3DBaseTexture9* texture = NULL;
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetTexture( handle, &texture );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			switch( texture->GetType() )
			{
			case D3DRTYPE_TEXTURE:
				return gcnew Texture( static_cast<IDirect3DTexture9*>( texture ) );
			case D3DRTYPE_VOLUMETEXTURE:
				return gcnew VolumeTexture( static_cast<IDirect3DVolumeTexture9*>( texture ) );
			case D3DRTYPE_CUBETEXTURE:
				return gcnew CubeTexture( static_cast<IDirect3DCubeTexture9*>( texture ) );

			default:
				return nullptr;
			}
		}

		Matrix BaseEffect::GetMatrixTranspose( EffectHandle^ param )
		{
			Matrix value = Matrix();
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			HRESULT hr = m_Pointer->GetMatrixTranspose( handle, reinterpret_cast<D3DXMATRIX*>( &value ) );
			GraphicsException::CheckHResult( hr );

			return value;
		}

		array<Matrix>^ BaseEffect::GetMatrixTransposeArray( EffectHandle^ param, int count )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			array<Matrix>^ data = gcnew array<Matrix>( count );
			pin_ptr<Matrix> pinnedData = &data[0];

			HRESULT hr = m_Pointer->GetMatrixTransposeArray( handle, reinterpret_cast<D3DXMATRIX*>( pinnedData ), count );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			return data;
		}

		String^ BaseEffect::GetString( EffectHandle^ param )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			LPCSTR data = 0;

			HRESULT hr = m_Pointer->GetString(handle,&data);
			GraphicsException::CheckHResult( hr );

			return gcnew String(data);
		}

		DataStream^ BaseEffect::GetValue( EffectHandle^ param, int bytes )
		{
			D3DXHANDLE handle = param != nullptr ? param->InternalHandle : NULL;
			void* data = new char[bytes];

			HRESULT hr = m_Pointer->GetValue( handle, data, bytes );
			GraphicsException::CheckHResult( hr );
			if( FAILED( hr ) )
				return nullptr;

			DataStream^ ds = gcnew DataStream( data, bytes, true, true, false );
			ds->TakeOwnership();
			return ds;
		}
	}
}
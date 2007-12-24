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
#include <memory>

#include "../DataStream.h"
#include "../DirectXObject.h"
#include "../Utils.h"

#include "Device.h"
#include "D3DX.h"
#include "Effect.h"
#include "ConstantTable.h"
#include "TextureShader.h"

namespace SlimDX
{
namespace Direct3D9
{
	TextureShader::TextureShader( ID3DXTextureShader *pointer )
	{
		m_Pointer = pointer;
	}

	TextureShader::TextureShader( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		void* result;
		IUnknown* unknown = static_cast<IUnknown*>( pointer.ToPointer() );
		HRESULT hr = unknown->QueryInterface( IID_ID3DXTextureShader, &result );
		if( FAILED( hr ) )
			throw gcnew InvalidCastException( "Failed to QueryInterface on user-supplied pointer." );

		m_Pointer = static_cast<ID3DXTextureShader*>( result );
	}

	TextureShader::TextureShader( DataStream^ stream )
	{
		ID3DXTextureShader *result;

		HRESULT hr = D3DXCreateTextureShader( reinterpret_cast<const DWORD*>( stream->RawPointer ), &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
			throw gcnew GraphicsException();

		m_Pointer = result;
	}

	EffectHandle^ TextureShader::GetConstant(SlimDX::Direct3D9::EffectHandle ^handle, int index)
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = m_Pointer->GetConstant( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ TextureShader::GetConstant(SlimDX::Direct3D9::EffectHandle ^handle, String^ name )
	{
		array<unsigned char>^ rawName = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &rawName[0];
		
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = m_Pointer->GetConstantByName( parentHandle, reinterpret_cast<const char*>( pinnedName ) );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ TextureShader::GetConstantElement( EffectHandle^ handle, int index )
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = m_Pointer->GetConstantElement( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}

	ConstantDescription TextureShader::GetConstantDescription( EffectHandle^ handle )
	{
		D3DXCONSTANT_DESC nativeDesc;
		ConstantDescription desc;

		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		unsigned int count = 1;

		HRESULT hr = m_Pointer->GetConstantDesc( nativeHandle, &nativeDesc, &count );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return desc;

		desc.Initialize( nativeDesc );
		return desc;
	}

	array<ConstantDescription>^ TextureShader::GetConstantDescriptionArray( EffectHandle^ handle )
	{
		//TODO: Check that the logic here is actually correct. The SDK doesn't bother to explain.
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		unsigned int count = 0;

		//Determine the count
		HRESULT hr = m_Pointer->GetConstantDesc( nativeHandle, NULL, &count );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		//Get the actual data
		std::auto_ptr<D3DXCONSTANT_DESC> nativeDescArray(new D3DXCONSTANT_DESC[count]);
		hr = m_Pointer->GetConstantDesc( nativeHandle, nativeDescArray.get(), &count );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return nullptr;

		//Marshal the data
		array<ConstantDescription>^ descArray = gcnew array<ConstantDescription>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			const D3DXCONSTANT_DESC* nativeDesc = nativeDescArray.get() + i;
			descArray[i].Initialize( *nativeDesc );
		}

		return descArray;
	}

	DataStream^ TextureShader::GetConstantBuffer()
	{
		ID3DXBuffer *result = NULL;

		HRESULT hr = m_Pointer->GetConstantBuffer( &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			if( result != NULL )
				result->Release();
			return nullptr;
		}

		return gcnew DataStream( result );
	}

	DataStream^ TextureShader::GetFunctionStream()
	{
		ID3DXBuffer *result = NULL;

		HRESULT hr = m_Pointer->GetFunction( &result );
		GraphicsException::CheckHResult( hr );

		if( FAILED( hr ) )
		{
			if( result != NULL )
				result->Release();
			return nullptr;
		}

		return gcnew DataStream( result );
	}

	void TextureShader::SetDefaults()
	{
		HRESULT hr = m_Pointer->SetDefaults();
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, bool value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetBool( handle, value );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ param, array<bool>^ values )
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

	void TextureShader::SetValue( EffectHandle^ constant, int value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetInt( handle, value );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<int>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<int> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetIntArray( handle, pinned_value, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, float value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetFloat( handle, value );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<float>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<float> pinned_values = &values[0];
		HRESULT hr = m_Pointer->SetFloatArray( handle, pinned_values, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, Vector4 value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<Vector4>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Vector4> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinned_value ), values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, ColorValue value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<ColorValue>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<ColorValue> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinned_value ), values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetMatrix( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetMatrixArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinned_value ), values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValueTranspose( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetMatrixTranspose( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
		GraphicsException::CheckHResult( hr );
	}

	void TextureShader::SetValueTranspose( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetMatrixTransposeArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinned_value ), values->Length );
		GraphicsException::CheckHResult( hr );
	}

	ConstantTableDescription TextureShader::Description::get()
	{
		D3DXCONSTANTTABLE_DESC nativeDesc;
		ConstantTableDescription desc;

		HRESULT hr = m_Pointer->GetDesc( &nativeDesc );
		GraphicsException::CheckHResult( hr );
		if( FAILED( hr ) )
			return desc;

		desc.Creator = gcnew String( nativeDesc.Creator );
		desc.Version = gcnew Version( D3DSHADER_VERSION_MAJOR( nativeDesc.Version ), D3DSHADER_VERSION_MINOR( nativeDesc.Version ) );
		desc.Constants = nativeDesc.Constants;
		return desc;
	}
}
}
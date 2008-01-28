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
#include "../ComObject.h"
#include "../Utilities.h"

#include "Direct3D9ErrorHandler.h"
#include "Direct3D9Exception.h"

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
		Construct(pointer);
	}

	TextureShader::TextureShader( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	TextureShader::TextureShader( DataStream^ stream )
	{
		ID3DXTextureShader *result;

		HRESULT hr = D3DXCreateTextureShader( reinterpret_cast<const DWORD*>( stream->RawPointer ), &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

		if( FAILED( hr ) )
			throw gcnew Direct3D9Exception( hr );

		Construct(result);
	}

	EffectHandle^ TextureShader::GetConstant(SlimDX::Direct3D9::EffectHandle ^handle, int index)
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = InternalPointer->GetConstant( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ TextureShader::GetConstant(SlimDX::Direct3D9::EffectHandle ^handle, String^ name )
	{
		array<unsigned char>^ rawName = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &rawName[0];
		
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = InternalPointer->GetConstantByName( parentHandle, reinterpret_cast<const char*>( pinnedName ) );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ TextureShader::GetConstantElement( EffectHandle^ handle, int index )
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = InternalPointer->GetConstantElement( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}

	ConstantDescription TextureShader::GetConstantDescription( EffectHandle^ handle )
	{
		D3DXCONSTANT_DESC nativeDesc;
		ConstantDescription description;

		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		unsigned int count = 1;

		HRESULT hr = InternalPointer->GetConstantDesc( nativeHandle, &nativeDesc, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return description;

		description.Initialize( nativeDesc );
		return description;
	}

	array<ConstantDescription>^ TextureShader::GetConstantDescriptionArray( EffectHandle^ handle )
	{
		//TODO: Check that the logic here is actually correct. The SDK doesn't bother to explain.
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		unsigned int count = 0;

		//Determine the count
		HRESULT hr = InternalPointer->GetConstantDesc( nativeHandle, NULL, &count );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return nullptr;

		//Get the actual data
		std::auto_ptr<D3DXCONSTANT_DESC> nativeDescArray(new D3DXCONSTANT_DESC[count]);
		hr = InternalPointer->GetConstantDesc( nativeHandle, nativeDescArray.get(), &count );
		Direct3D9ErrorHandler::TestForFailure( hr );
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

		HRESULT hr = InternalPointer->GetConstantBuffer( &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

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

		HRESULT hr = InternalPointer->GetFunction( &result );
		Direct3D9ErrorHandler::TestForFailure( hr );

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
		HRESULT hr = InternalPointer->SetDefaults();
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, bool value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetBool( handle, value );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ parameter, array<bool>^ values )
	{
		//implementing set for bool array is REALLY ANNOYING.
		//Win32 uses BOOL, which is an int
		array<BOOL>^ expandedArray = gcnew array<BOOL>( values->Length );
		Array::Copy( values, expandedArray, values->Length );

		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		pin_ptr<BOOL> pinnedValue = &expandedArray[0];
		HRESULT hr = InternalPointer->SetBoolArray( handle, pinnedValue, values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, int value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetInt( handle, value );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<int>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<int> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetIntArray( handle, pinned_value, values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, float value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetFloat( handle, value );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<float>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<float> pinned_values = &values[0];
		HRESULT hr = InternalPointer->SetFloatArray( handle, pinned_values, values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, Vector4 value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<Vector4>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Vector4> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinned_value ), values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, ColorValue value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetVector( handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<ColorValue>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<ColorValue> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetVectorArray( handle, reinterpret_cast<const D3DXVECTOR4*>( pinned_value ), values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetMatrix( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValue( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetMatrixArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinned_value ), values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValueTranspose( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetMatrixTranspose( handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	void TextureShader::SetValueTranspose( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetMatrixTransposeArray( handle, reinterpret_cast<const D3DXMATRIX*>( pinned_value ), values->Length );
		Direct3D9ErrorHandler::TestForFailure( hr );
	}

	ConstantTableDescription TextureShader::Description::get()
	{
		D3DXCONSTANTTABLE_DESC nativeDesc;
		ConstantTableDescription description;

		HRESULT hr = InternalPointer->GetDesc( &nativeDesc );
		Direct3D9ErrorHandler::TestForFailure( hr );
		if( FAILED( hr ) )
			return description;

		description.Creator = gcnew String( nativeDesc.Creator );
		description.Version = gcnew Version( D3DSHADER_VERSION_MAJOR( nativeDesc.Version ), D3DSHADER_VERSION_MINOR( nativeDesc.Version ) );
		description.Constants = nativeDesc.Constants;
		return description;
	}
}
}
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
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <memory>

#include "../DataStream.h"

#include "../math/Color4.h"
#include "../math/Matrix.h"
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "Texture.h"
#include "BaseEffect.h"
#include "PixelShader.h"
#include "VertexShader.h"

using namespace System;
using namespace System::Reflection;

namespace SlimDX
{
namespace Direct3D9
{
	EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, int index )
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE annotation = InternalPointer->GetAnnotation( parentHandle, index );

		if( annotation == NULL )
			return nullptr;
		return gcnew EffectHandle( annotation );
	}

	EffectHandle^ BaseEffect::GetAnnotation( EffectHandle^ handle, String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE annotation = InternalPointer->GetAnnotationByName( parentHandle, reinterpret_cast<LPCSTR>( pinnedName ) );

		if( annotation == NULL )
			return nullptr;
		return gcnew EffectHandle( annotation );
	}

	EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, int index )
	{
		D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
		D3DXHANDLE handle = InternalPointer->GetParameter( parentHandle, index );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	EffectHandle^ BaseEffect::GetParameter( EffectHandle^ parameter, String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
		D3DXHANDLE handle = InternalPointer->GetParameterByName( parentHandle, reinterpret_cast<const char*>( pinnedName ) );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	EffectHandle^ BaseEffect::GetParameterBySemantic( EffectHandle^ parameter, String^ semantic )
	{
		array<Byte>^ semanticBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( semantic );
		pin_ptr<unsigned char> pinnedSemantic = &semanticBytes[0];

		D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
		D3DXHANDLE handle = InternalPointer->GetParameterBySemantic( parentHandle, reinterpret_cast<const char*>( pinnedSemantic ) );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	EffectHandle^ BaseEffect::GetParameterElement( EffectHandle^ parameter, int index )
	{
		D3DXHANDLE parentHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
		D3DXHANDLE handle = InternalPointer->GetParameterElement( parentHandle, index );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	ParameterDescription BaseEffect::GetParameterDescription( EffectHandle^ parameter )
	{
		D3DXPARAMETER_DESC description;

		HRESULT hr = InternalPointer->GetParameterDesc( parameter->InternalHandle, &description );
		if( RECORD_D3D9( hr ).IsFailure )
			return ParameterDescription();

		ParameterDescription outDesc;
		outDesc.Name = gcnew String( description.Name );
		outDesc.Semantic = gcnew String( description.Semantic );
		outDesc.Class = static_cast<ParameterClass>( description.Class );
		outDesc.Type = static_cast<ParameterType>( description.Type );
		outDesc.Rows = description.Rows;
		outDesc.Columns = description.Columns;
		outDesc.Elements = description.Elements;
		outDesc.Annotations = description.Annotations;
		outDesc.StructMembers = description.StructMembers;
		outDesc.Flags = static_cast<ParameterFlags>( description.Flags );
		outDesc.Bytes = description.Bytes;

		return outDesc;
	}

	EffectHandle^ BaseEffect::GetFunction( int index )
	{
		D3DXHANDLE handle = InternalPointer->GetFunction( index );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	EffectHandle^ BaseEffect::GetFunction( String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		D3DXHANDLE handle = InternalPointer->GetFunctionByName( reinterpret_cast<const char*>( pinnedName ) );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	FunctionDescription BaseEffect::GetFunctionDescription( EffectHandle^ handle )
	{
		D3DXFUNCTION_DESC description;

		HRESULT hr = InternalPointer->GetFunctionDesc( handle->InternalHandle, &description );
		if( RECORD_D3D9( hr ).IsFailure )
			return FunctionDescription();

		FunctionDescription outDesc;
		outDesc.Name = gcnew String( description.Name );
		outDesc.Annotations = description.Annotations;

		return outDesc;
	}

	EffectHandle^ BaseEffect::GetTechnique( int index )
	{
		D3DXHANDLE handle = InternalPointer->GetTechnique( index );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	EffectHandle^ BaseEffect::GetTechnique( String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		D3DXHANDLE handle = InternalPointer->GetTechniqueByName( reinterpret_cast<const char*>( pinnedName ) );

		if( handle == NULL )
			return nullptr;
		return gcnew EffectHandle( handle );
	}

	TechniqueDescription BaseEffect::GetTechniqueDescription( EffectHandle^ handle )
	{
		D3DXTECHNIQUE_DESC description;

		HRESULT hr = InternalPointer->GetTechniqueDesc( handle->InternalHandle, &description );
		if( RECORD_D3D9( hr ).IsFailure )
			return TechniqueDescription();

		TechniqueDescription outDesc;
		outDesc.Name = gcnew String( description.Name );
		outDesc.Annotations = description.Annotations;
		outDesc.Passes = description.Passes;

		return outDesc;
	}

	EffectHandle^ BaseEffect::GetPass( EffectHandle^ handle, int index )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE pass = InternalPointer->GetPass( nativeHandle, index );

		if( pass == NULL )
			return nullptr;
		return gcnew EffectHandle( pass );
	}

	EffectHandle^ BaseEffect::GetPass( EffectHandle^ handle, String^ name )
	{
		array<Byte>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &nameBytes[0];

		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE pass = InternalPointer->GetPassByName( nativeHandle, reinterpret_cast<const char*>( pinnedName ) );

		if( pass == NULL )
			return nullptr;
		return gcnew EffectHandle( pass );
	}

	PassDescription BaseEffect::GetPassDescription( EffectHandle^ handle )
	{
		D3DXPASS_DESC description;
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;

		HRESULT hr = InternalPointer->GetPassDesc( nativeHandle, &description );
		if( RECORD_D3D9( hr ).IsFailure )
			return PassDescription();

		PassDescription passDesc;
		passDesc.Name = gcnew String( description.Name );
		passDesc.Annotations = description.Annotations;
		passDesc.VertexShaderFunction = IntPtr( const_cast<void*>( static_cast<const void*>( description.pVertexShaderFunction ) ) );
		passDesc.PixelShaderFunction = IntPtr( const_cast<void*>( static_cast<const void*>( description.pPixelShaderFunction ) ) );

		return passDesc;
	}

	PixelShader^ BaseEffect::GetPixelShader( EffectHandle^ parameter )
	{
		IDirect3DPixelShader9 *pixelShader;

		D3DXHANDLE nativeHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
		HRESULT hr = InternalPointer->GetPixelShader( nativeHandle, &pixelShader );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return PixelShader::FromPointer( pixelShader );
	}

	VertexShader^ BaseEffect::GetVertexShader( EffectHandle^ parameter )
	{
		IDirect3DVertexShader9 *vertexShader;

		D3DXHANDLE nativeHandle = parameter != nullptr ? parameter->InternalHandle : NULL;
		HRESULT hr = InternalPointer->GetVertexShader( nativeHandle, &vertexShader );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return VertexShader::FromPointer( vertexShader );
	}

	EffectDescription BaseEffect::Description::get()
	{
		D3DXEFFECT_DESC description;

		HRESULT hr = InternalPointer->GetDesc( &description );
		if( RECORD_D3D9( hr ).IsFailure )
			return EffectDescription();

		EffectDescription outDesc;
		outDesc.Creator = gcnew String( description.Creator );
		outDesc.Parameters = description.Parameters;
		outDesc.Techniques = description.Techniques;
		outDesc.Functions = description.Functions;

		return outDesc;
	}

	Result BaseEffect::SetTexture( EffectHandle^ parameter, BaseTexture^ value )
	{
		IDirect3DBaseTexture9* texture = NULL;
		if( value != nullptr )
			texture = value->InternalPointer;

		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetTexture( handle, texture );
		return RECORD_D3D9( hr );
	}

	Result BaseEffect::SetString( EffectHandle^ parameter, String^ value )
	{
		array<unsigned char>^ valueBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( value );
		pin_ptr<unsigned char> pinnedValue = &valueBytes[0];

		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetString( handle, reinterpret_cast<LPCSTR>( pinnedValue ) );
		return RECORD_D3D9( hr );
	}

	BaseTexture^ BaseEffect::GetTexture( EffectHandle^ parameter )
	{
		IDirect3DBaseTexture9* texture = NULL;
		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		HRESULT hr = InternalPointer->GetTexture( handle, &texture );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return BaseTexture::FromUnmanaged( texture );
	}

	String^ BaseEffect::GetString( EffectHandle^ parameter )
	{
		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		LPCSTR data = 0;

		HRESULT hr = InternalPointer->GetString( handle, &data );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return gcnew String(data);
	}

	generic<typename T> where T : value class
	Result BaseEffect::SetValue( EffectHandle^ parameter, T value )
	{
		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;

		HRESULT	hr = InternalPointer->SetValue( handle, &value, sizeof(T) );
		return RECORD_D3D9( hr );
	}

	generic<typename T> where T : value class
	T BaseEffect::GetValue( EffectHandle^ parameter )
	{
		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		T result;

		HRESULT hr = InternalPointer->GetValue( handle, &result, sizeof(T) );

		if( RECORD_D3D9( hr ).IsFailure )
			return T();

		return result;
	}

	generic<typename T> where T : value class
	Result BaseEffect::SetValue( EffectHandle^ parameter, array<T>^ values )
	{
		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		pin_ptr<T> pinnedData = &values[0];

		HRESULT	hr = InternalPointer->SetValue( handle, pinnedData, sizeof(T) * values->Length );
		return RECORD_D3D9( hr );
	}

	generic<typename T> where T : value class
	array<T>^ BaseEffect::GetValue( EffectHandle^ parameter, int count )
	{
		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		array<T>^ results = gcnew array<T>( count );
		pin_ptr<T> pinnedData = &results[0];

		HRESULT hr = InternalPointer->GetValue( handle, pinnedData, sizeof(T) * count );

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return results;
	}
}
}

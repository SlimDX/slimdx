
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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <memory>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../StackAlloc.h"
#include "../DataStream.h"

#include "Direct3D9Exception.h"

#include "Effect.h"
#include "ConstantTable.h"
#include "Device.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	bool ConstantTableDescription::operator == ( ConstantTableDescription left, ConstantTableDescription right )
	{
		return ConstantTableDescription::Equals( left, right );
	}

	bool ConstantTableDescription::operator != ( ConstantTableDescription left, ConstantTableDescription right )
	{
		return !ConstantTableDescription::Equals( left, right );
	}

	int ConstantTableDescription::GetHashCode()
	{
		return Creator->GetHashCode() + Version->GetHashCode() + Constants.GetHashCode();
	}

	bool ConstantTableDescription::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ConstantTableDescription>( value ) );
	}

	bool ConstantTableDescription::Equals( ConstantTableDescription value )
	{
		return ( Creator == value.Creator && Version == value.Version && Constants == value.Constants );
	}

	bool ConstantTableDescription::Equals( ConstantTableDescription% value1, ConstantTableDescription% value2 )
	{
		return ( value1.Creator == value2.Creator && value1.Version == value2.Version && value1.Constants == value2.Constants );
	}

	bool ConstantDescription::operator == ( ConstantDescription left, ConstantDescription right )
	{
		return ConstantDescription::Equals( left, right );
	}

	bool ConstantDescription::operator != ( ConstantDescription left, ConstantDescription right )
	{
		return !ConstantDescription::Equals( left, right );
	}

	int ConstantDescription::GetHashCode()
	{
		return Name->GetHashCode() + RegisterSet.GetHashCode() + RegisterIndex.GetHashCode()
			 + RegisterCount.GetHashCode() + Class.GetHashCode() + Type.GetHashCode()
			 + Rows.GetHashCode() + Columns.GetHashCode() + Elements.GetHashCode()
			 + StructMembers.GetHashCode() + Bytes.GetHashCode();
	}

	bool ConstantDescription::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<ConstantDescription>( value ) );
	}

	bool ConstantDescription::Equals( ConstantDescription value )
	{
		return ( Name == value.Name && RegisterSet == value.RegisterSet && RegisterIndex == value.RegisterIndex
			 && RegisterCount == value.RegisterCount && Class == value.Class && Type == value.Type
			 && Rows == value.Rows && Columns == value.Columns && Elements == value.Elements
			 && StructMembers == value.StructMembers && Bytes == value.Bytes );
	}

	bool ConstantDescription::Equals( ConstantDescription% value1, ConstantDescription% value2 )
	{
		return ( value1.Name == value2.Name && value1.RegisterSet == value2.RegisterSet && value1.RegisterIndex == value2.RegisterIndex
			 && value1.RegisterCount == value2.RegisterCount && value1.Class == value2.Class && value1.Type == value2.Type
			 && value1.Rows == value2.Rows && value1.Columns == value2.Columns && value1.Elements == value2.Elements
			 && value1.StructMembers == value2.StructMembers && value1.Bytes == value2.Bytes );
	}

	void ConstantDescription::Initialize( const D3DXCONSTANT_DESC& description )
	{
		Name = gcnew String( description.Name );
		RegisterSet = static_cast<SlimDX::Direct3D9::RegisterSet>( description.RegisterSet );
		RegisterIndex = description.RegisterIndex;
		RegisterCount = description.RegisterCount;
		Class = static_cast<ParameterClass>( description.Class );
		Type = static_cast<ParameterType>( description.Type );
		Rows = description.Rows;
		Columns = description.Columns;
		Elements = description.Elements;
		StructMembers = description.StructMembers;
		Bytes = description.Bytes;
	}

	ConstantTable::ConstantTable( ID3DXConstantTable* pointer )
	{
		Construct( pointer );
	}

	ConstantTable::ConstantTable( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	ConstantTable::ConstantTable( IDirect3DDevice9* device, ID3DXConstantTable* constantTable )
	{
		Construct(constantTable);
		m_Device = Device::FromPointer( device );
	}

	ConstantTable^ ConstantTable::FromPointer( ID3DXConstantTable* pointer )
	{
		ConstantTable^ tableEntry = safe_cast<ConstantTable^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew ConstantTable( pointer );
	}

	ConstantTable^ ConstantTable::FromPointer( IntPtr pointer )
	{
		ConstantTable^ tableEntry = safe_cast<ConstantTable^>( ObjectTable::Construct( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew ConstantTable( pointer );
	}

	ConstantTable^ ConstantTable::FromPointer( IDirect3DDevice9* device, ID3DXConstantTable* constantTable )
	{
		ConstantTable^ tableEntry = safe_cast<ConstantTable^>( ObjectTable::Construct( static_cast<IntPtr>( constantTable ) ) );
		if( tableEntry != nullptr )
		{
			constantTable->Release();
			return tableEntry;
		}

		return gcnew ConstantTable( device, constantTable );
	}

	ConstantTable::~ConstantTable()
	{
		delete m_Device;
		m_Device = nullptr;
	}
	
	EffectHandle^ ConstantTable::GetConstant(SlimDX::Direct3D9::EffectHandle ^handle, int index)
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = InternalPointer->GetConstant( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ ConstantTable::GetConstant(SlimDX::Direct3D9::EffectHandle ^handle, String^ name )
	{
		array<unsigned char>^ rawName = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &rawName[0];
		
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = InternalPointer->GetConstantByName( parentHandle, reinterpret_cast<const char*>( pinnedName ) );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ ConstantTable::GetConstantElement( EffectHandle^ handle, int index )
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = InternalPointer->GetConstantElement( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}

	ConstantDescription ConstantTable::GetConstantDescription( EffectHandle^ handle )
	{
		D3DXCONSTANT_DESC nativeDesc;
		ConstantDescription description;

		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		unsigned int count = 1;

		HRESULT hr = InternalPointer->GetConstantDesc( nativeHandle, &nativeDesc, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return ConstantDescription();

		description.Initialize( nativeDesc );
		return description;
	}

	array<ConstantDescription>^ ConstantTable::GetConstantDescriptionArray( EffectHandle^ handle )
	{
		D3DXHANDLE nativeHandle = handle != nullptr ? handle->InternalHandle : NULL;
		unsigned int count = 0;

		HRESULT hr = InternalPointer->GetConstantDesc( nativeHandle, NULL, &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		stack_vector<D3DXCONSTANT_DESC> nativeDescArray( count );
		hr = InternalPointer->GetConstantDesc( nativeHandle, &nativeDescArray[0], &count );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		array<ConstantDescription>^ descArray = gcnew array<ConstantDescription>( count );
		for( unsigned int i = 0; i < count; ++i )
		{
			descArray[i].Initialize( nativeDescArray[i] );
		}

		return descArray;
	}

	int ConstantTable::GetSamplerIndex( EffectHandle^ sampler )
	{
		D3DXHANDLE handle = sampler != nullptr ? sampler->InternalHandle : NULL;
		int result = InternalPointer->GetSamplerIndex( handle );
		return result;
	}

	DataStream^ ConstantTable::GetBuffer()
	{
		DWORD size = InternalPointer->GetBufferSize();
		void* pointer = InternalPointer->GetBufferPointer();
		if( pointer == NULL )
			return nullptr;

		return gcnew DataStream( pointer, size, true, true, false );
	}

	Result ConstantTable::SetDefaults()
	{
		HRESULT hr = InternalPointer->SetDefaults( m_Device->InternalPointer );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, bool value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetBool( m_Device->InternalPointer, handle, value );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ parameter, array<bool>^ values )
	{
		//implementing set for bool array is REALLY ANNOYING.
		//Win32 uses BOOL, which is an int
		array<BOOL>^ expandedArray = gcnew array<BOOL>( values->Length );
		Array::Copy( values, expandedArray, values->Length );

		D3DXHANDLE handle = parameter != nullptr ? parameter->InternalHandle : NULL;
		pin_ptr<BOOL> pinnedValue = &expandedArray[0];
		HRESULT hr = InternalPointer->SetBoolArray( m_Device->InternalPointer, handle, pinnedValue, values->Length );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, int value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetInt( m_Device->InternalPointer, handle, value );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, array<int>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<int> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetIntArray( m_Device->InternalPointer, handle, pinned_value, values->Length );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, float value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetFloat( m_Device->InternalPointer, handle, value );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, array<float>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<float> pinned_values = &values[0];
		HRESULT hr = InternalPointer->SetFloatArray( m_Device->InternalPointer, handle, pinned_values, values->Length );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, Vector4 value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetVector( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, array<Vector4>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Vector4> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetVectorArray( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXVECTOR4*>( pinned_value ), values->Length );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, Color4 value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetVector( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXVECTOR4*>( &value ) );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, array<Color4>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Color4> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetVectorArray( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXVECTOR4*>( pinned_value ), values->Length );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetMatrix( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValue( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetMatrixArray( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXMATRIX*>( pinned_value ), values->Length );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValueTranspose( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = InternalPointer->SetMatrixTranspose( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXMATRIX*>( &value ) );
		return RECORD_D3D9( hr );
	}

	Result ConstantTable::SetValueTranspose( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = InternalPointer->SetMatrixTransposeArray( m_Device->InternalPointer, handle, reinterpret_cast<const D3DXMATRIX*>( pinned_value ), values->Length );
		return RECORD_D3D9( hr );
	}

	ConstantTableDescription ConstantTable::Description::get()
	{
		D3DXCONSTANTTABLE_DESC nativeDesc;
		ConstantTableDescription description;

		HRESULT hr = InternalPointer->GetDesc( &nativeDesc );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return ConstantTableDescription();

		description.Creator = gcnew String( nativeDesc.Creator );
		description.Version = gcnew Version( D3DSHADER_VERSION_MAJOR( nativeDesc.Version ), D3DSHADER_VERSION_MINOR( nativeDesc.Version ) );
		description.Constants = nativeDesc.Constants;
		return description;
	}
}
}

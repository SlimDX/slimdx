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
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>

#include "../DirectXObject.h"
#include "../Utils.h"

#include "ConstantTable.h"
#include "Effect.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D
{
	ConstantTable::ConstantTable( IDirect3DDevice9* device,ID3DXConstantTable* constantTable )
		: DirectXObject(constantTable), m_Device(device)
	{
		m_Device->AddRef();
	}

	ConstantTable::~ConstantTable()
	{
		m_Device->Release();
	}
	
	EffectHandle^ ConstantTable::GetConstant(SlimDX::Direct3D::EffectHandle ^handle, int index)
	{
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = m_Pointer->GetConstant( parentHandle, index );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	EffectHandle^ ConstantTable::GetConstant(SlimDX::Direct3D::EffectHandle ^handle, String^ name )
	{
		array<unsigned char>^ rawName = System::Text::ASCIIEncoding::ASCII->GetBytes( name );
		pin_ptr<unsigned char> pinnedName = &rawName[0];
		
		D3DXHANDLE parentHandle = handle != nullptr ? handle->InternalHandle : NULL;
		D3DXHANDLE result = m_Pointer->GetConstantByName( parentHandle, (const char*) pinnedName );
		
		if( result == NULL )
			return nullptr;
		return gcnew EffectHandle( result );
	}
	
	int ConstantTable::GetSamplerIndex( EffectHandle^ sampler )
	{
		D3DXHANDLE handle = sampler != nullptr ? sampler->InternalHandle : NULL;
		int result = m_Pointer->GetSamplerIndex( handle );
		return result;
	}
	
	void ConstantTable::SetValue( EffectHandle^ constant, bool value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetBool( m_Device, constant->InternalHandle, value );
		GraphicsException::CheckHResult( hr );
	}

	//implementing set for bool array is REALLY ANNOYING.

	void ConstantTable::SetValue( EffectHandle^ constant, int value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetInt( m_Device, handle, value );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, array<int>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<int> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetIntArray( m_Device, handle, pinned_value, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, float value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetFloat( m_Device, handle, value );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, array<float>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<float> pinned_values = &values[0];
		HRESULT hr = m_Pointer->SetFloatArray( m_Device, handle, pinned_values, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, Vector4 value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetVector( m_Device, handle, (const D3DXVECTOR4*) &value );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, array<Vector4>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Vector4> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetVectorArray( m_Device, handle, (const D3DXVECTOR4*) pinned_value, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, ColorValue value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetVector( m_Device, handle, (const D3DXVECTOR4*) &value );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, array<ColorValue>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<ColorValue> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetVectorArray( m_Device, handle, (const D3DXVECTOR4*) pinned_value, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetMatrix( m_Device, handle, (const D3DXMATRIX*) &value );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValue( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetMatrixArray( m_Device, handle, (const D3DXMATRIX*) pinned_value, values->Length );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValueTranspose( EffectHandle^ constant, Matrix value )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		HRESULT hr = m_Pointer->SetMatrixTranspose( m_Device, handle, (const D3DXMATRIX*) &value );
		GraphicsException::CheckHResult( hr );
	}

	void ConstantTable::SetValueTranspose( EffectHandle^ constant, array<Matrix>^ values )
	{
		D3DXHANDLE handle = constant != nullptr ? constant->InternalHandle : NULL;
		pin_ptr<Matrix> pinned_value = &values[0];
		HRESULT hr = m_Pointer->SetMatrixTransposeArray( m_Device, handle, (const D3DXMATRIX*) pinned_value, values->Length );
		GraphicsException::CheckHResult( hr );
	}
}
}
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

#include <d3d10.h>

#include "Direct3D10Exception.h"

#include "Device.h"
#include "InputLayout.h"
#include "ShaderBytecode.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace SlimDX
{
namespace Direct3D10
{ 
	InputElement::InputElement( System::String^ name, int index, DXGI::Format format, int offset, int slot )
	{
		m_SemanticName = name;
		m_SemanticIndex = index;
		m_Format = format;
		m_InputSlot = slot;
		m_AlignedByteOffset = offset;
		m_InputSlotClass = InputClassification::PerVertexData;
		m_InstanceDataStepRate = 0;
	}

	InputElement::InputElement( System::String^ name, int index, DXGI::Format format, int offset, int slot, InputClassification slotClass, int stepRate )
	{
		m_SemanticName = name;
		m_SemanticIndex = index;
		m_Format = format;
		m_InputSlot = slot;
		m_AlignedByteOffset = offset;
		m_InputSlotClass = slotClass;
		m_InstanceDataStepRate = stepRate;
	}
	
	D3D10_INPUT_ELEMENT_DESC InputElement::CreateNativeVersion()
	{
		D3D10_INPUT_ELEMENT_DESC native;
	
		native.SemanticName = Utilities::AllocateNativeString( m_SemanticName );
		native.SemanticIndex = m_SemanticIndex;
		native.Format = static_cast<DXGI_FORMAT>( m_Format );
		native.InputSlot = m_InputSlot;
		native.AlignedByteOffset = m_AlignedByteOffset;
		native.InputSlotClass = static_cast<D3D10_INPUT_CLASSIFICATION>( m_InputSlotClass );
		native.InstanceDataStepRate = m_InstanceDataStepRate;
		
		return native;
	}
	
	String^ InputElement::SemanticName::get()
	{
		return m_SemanticName;
	}
	
	void InputElement::SemanticName::set( String^ value )
	{
		m_SemanticName = value;
	}
	
	int InputElement::SemanticIndex::get()
	{
		return m_SemanticIndex;
	}
	
	void InputElement::SemanticIndex::set( int value )
	{
		m_SemanticIndex = value;
	}
	
	DXGI::Format InputElement::Format::get()
	{
		return m_Format;
	}
	
	void InputElement::Format::set( DXGI::Format value )
	{
		m_Format = value;
	}
	
	int InputElement::Slot::get()
	{
		return m_InputSlot;
	}
	
	void InputElement::Slot::set( int value )
	{
		m_InputSlot = value;
	}
	
	int InputElement::AlignedByteOffset::get()
	{
		return m_AlignedByteOffset;
	}
	
	void InputElement::AlignedByteOffset::set( int value )
	{
		m_AlignedByteOffset = value;
	}
	
	InputClassification InputElement::Classification::get()
	{
		return m_InputSlotClass;
	}
	
	void InputElement::Classification::set( InputClassification value )
	{
		m_InputSlotClass = value;	
	}
	
	int InputElement::InstanceDataStepRate::get()
	{
		return m_InstanceDataStepRate;
	}
	
	void InputElement::InstanceDataStepRate::set( int value )
	{
		m_InstanceDataStepRate = value;
	}
}
}

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

#include "ShaderParameterDescription.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	ShaderParameterDescription::ShaderParameterDescription( const D3D10_SIGNATURE_PARAMETER_DESC& description )
	{
		m_SemanticName = gcnew System::String( description.SemanticName );
		m_SemanticIndex = description.SemanticIndex;
		m_Register = description.Register;
		m_SystemValueType = static_cast<SystemValueType>( description.SystemValueType );
		m_ComponentType = static_cast<RegisterComponentType>( description.ComponentType );
		m_Mask = description.Mask;
		m_ReadWriteMask = description.ReadWriteMask;
	}
	
	System::String^ ShaderParameterDescription::SemanticName::get()
	{
		return m_SemanticName;
	}

	System::UInt32 ShaderParameterDescription::SemanticIndex::get()
	{
		return m_SemanticIndex;
	}

	System::UInt32 ShaderParameterDescription::Register::get()
	{
		return m_Register;
	}

	SystemValueType ShaderParameterDescription::SystemType::get()
	{
		return m_SystemValueType;
	}

	RegisterComponentType ShaderParameterDescription::ComponentType::get()
	{
		return m_ComponentType;
	}

	System::Byte ShaderParameterDescription::UsageMask::get()
	{
		return m_Mask;
	}

	System::Byte ShaderParameterDescription::ReadWriteMask::get()
	{
		return m_ReadWriteMask;
	}
}
}

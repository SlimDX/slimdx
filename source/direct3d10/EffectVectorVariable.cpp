#include "stdafx.h"
/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "EffectVectorVariable.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D10
{ 
	EffectVectorVariable::EffectVectorVariable( ID3D10EffectVectorVariable* pointer )
	: EffectVariable( pointer )
	{
		m_Pointer = pointer;
	}
	
	EffectVectorVariable::EffectVectorVariable( IntPtr pointer )
	: EffectVariable( pointer )
	{
		m_Pointer = reinterpret_cast<ID3D10EffectVectorVariable*>( pointer.ToPointer() );
	}
	
	Result EffectVectorVariable::Set( Vector4 value )
	{
		return RECORD_D3D10( m_Pointer->SetFloatVector( reinterpret_cast<float*>( &value ) ) );
	}
	
	Result EffectVectorVariable::Set( array<Vector4>^ values )
	{
		pin_ptr<Vector4> pinnedValues = &values[ 0 ];
		return RECORD_D3D10( m_Pointer->SetFloatVectorArray( reinterpret_cast<float*>( pinnedValues ), 0, values->Length ) );
	}
}
}

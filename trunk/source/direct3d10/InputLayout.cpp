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

#include <d3d10.h>
#include <d3dx10.h>

#include "GraphicsException.h"

#include "InputLayout.h"
#include "Device.h"
#include "ShaderBytecode.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	InputLayout::InputLayout( Device^ device, array<InputElement>^ elements, ShaderSignature^ shaderSignature )
	{
		if( device == nullptr )
			throw gcnew ArgumentNullException( "device" );
			
		D3D10_INPUT_ELEMENT_DESC nativeElements[D3D10_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT];
		
		for( int i = 0; i < elements->Length; ++i )
		{
			array<unsigned char>^ nameBytes = System::Text::ASCIIEncoding::ASCII->GetBytes( elements[i].SemanticName );
			pin_ptr<unsigned char> pinnedName = &nameBytes[0];
		
			nativeElements[i].SemanticName = (LPCSTR) pinnedName;
			nativeElements[i].SemanticIndex = elements[i].SemanticIndex;
			nativeElements[i].Format = (DXGI_FORMAT) elements[i].AFormat;
			nativeElements[i].InputSlot = elements[i].InputSlot;
			nativeElements[i].AlignedByteOffset = elements[i].AlignedByteOffset;
			nativeElements[i].InputSlotClass = (D3D10_INPUT_CLASSIFICATION) elements[i].InputSlotClass;
			nativeElements[i].InstanceDataStepRate = elements[i].InstanceDataStepRate;
		}

		ID3D10InputLayout* layout;
		HRESULT hr = device->DevicePointer->CreateInputLayout( nativeElements, elements->Length, shaderSignature->Buffer, shaderSignature->Length, &layout );
		GraphicsException::CheckHResult( hr );

		m_Pointer = layout;
	}
}
}

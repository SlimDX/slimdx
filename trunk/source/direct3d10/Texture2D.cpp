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
#include <vcclr.h>

#include "GraphicsException.h"

#include "Texture2D.h"
#include "Device.h"

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture2D::Texture2D( ID3D10Texture2D* texture ) : Resource( texture )
	{
		D3D10_TEXTURE2D_DESC desc;
		texture->GetDesc( &desc );
		MipLevels = desc.MipLevels;
		Format = (SlimDX::Direct3D10::Format) desc.Format;
	}
	
	Texture2D^ Texture2D::FromFile( Device^ device, String^ fileName )
	{
		pin_ptr<const wchar_t> pinnedName = PtrToStringChars( fileName );

		ID3D10Resource* texture = 0;
		HRESULT hr = D3DX10CreateTextureFromFile( device->DevicePointer, pinnedName, NULL, NULL, &texture, NULL ); 
		GraphicsException::CheckHResult( hr );
		
		if( texture == NULL )
			return nullptr;
		return gcnew Texture2D( (ID3D10Texture2D*) texture );
	}
}
}

/*
* Copyright (c) 2007-2010 SlimDX Group
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
#pragma once

#include "../dxgi/Enums.h"

#include "Enums11.h"

namespace SlimDX
{
	namespace Direct3D11
	{	
		public value class ShaderResourceViewDescription : System::IEquatable<ShaderResourceViewDescription>
		{
		private:
			DXGI::Format m_Format;
			ShaderResourceViewDimension m_ViewDimension;
			int m_ElementOffset;
			int m_ElementWidth;
			int m_MostDetailedMip;
			int m_MipLevels;
			int m_FirstArraySlice;
			int m_ArraySize;
				
		internal:
			ShaderResourceViewDescription( const D3D11_SHADER_RESOURCE_VIEW_DESC& native );
			
			D3D11_SHADER_RESOURCE_VIEW_DESC CreateNativeVersion();
		
		public:
			property DXGI::Format Format;
			property ShaderResourceViewDimension Dimension;
			property int ElementOffset;
			property int ElementWidth;
			property int MostDetailedMip;
			property int MipLevels;
			property int FirstArraySlice;
			property int ArraySize;
			property int FirstElement;
			property int ElementCount;
			property ShaderResourceViewExtendedBufferFlags Flags;

			static bool operator == ( ShaderResourceViewDescription left, ShaderResourceViewDescription right );
			static bool operator != ( ShaderResourceViewDescription left, ShaderResourceViewDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( ShaderResourceViewDescription other );
			static bool Equals( ShaderResourceViewDescription% value1, ShaderResourceViewDescription% value2 );
		};
	}
};
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
#pragma once

using namespace System;

#include "../DirectXObject.h"
#include "../direct3d/GraphicsStream.h"

#include "Enums.h"
#include "Resource.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		
		public ref class Buffer : public Resource
		{
			int m_SizeInBytes;
			ResourceUsage m_Usage;
			BindFlags m_BindFlags;
			CpuAccessFlags m_AccessFlags;
			ResourceOptionFlags m_OptionFlags;
			
			void Construct( Device^ device, int sizeInBytes, GraphicsStream^ data, ResourceUsage usage, BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags );
		
		internal:
			Buffer( ID3D10Buffer* buffer );
			
		public:
			property int SizeInBytes
			{
				int get() { return m_SizeInBytes; }
			}
			
			property ResourceUsage Usage
			{
				ResourceUsage get() { return m_Usage; }
			}
			
			property SlimDX::Direct3D10::BindFlags BindFlags
			{
				SlimDX::Direct3D10::BindFlags get() { return m_BindFlags; }
			}
			
			property CpuAccessFlags AccessFlags
			{
				CpuAccessFlags get() { return m_AccessFlags; }
			}
			
			property ResourceOptionFlags OptionFlags
			{
				ResourceOptionFlags get() { return m_OptionFlags; }
			}
		
			Buffer( Device^ device, int sizeInBytes, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags );
			Buffer( Device^ device, int sizeInBytes, GraphicsStream^ data, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags );
			
			GraphicsStream^ Map( MapMode mode, MapFlags flags );
			void Unmap();
		};
	}
};
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
#pragma once

#include "../ComObject.h"
#include "../DataStream.h"

#include "Enums.h"
#include "Resource.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		value class BufferDescription;
		
		public ref class Buffer : public Resource
		{
			COMOBJECT(ID3D10Buffer);
			
		private:
			ID3D10Buffer* Build( Device^ device, DataStream^ data, int sizeInBytes, ResourceUsage usage, BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags );
		
		internal:
			Buffer( ID3D10Buffer* buffer );
		
		public:
			property BufferDescription Description
			{
				BufferDescription get();
			}
			
			Buffer( System::IntPtr pointer );
			Buffer( Device^ device, BufferDescription description );
			Buffer( Device^ device, DataStream^ data, BufferDescription description );
			Buffer( Device^ device, int sizeInBytes, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags );
			Buffer( Device^ device, DataStream^ data, int sizeInBytes, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags, ResourceOptionFlags optionFlags );
			
			DataStream^ Map( MapMode mode, MapFlags flags );
			void Unmap();
		};
	}
};
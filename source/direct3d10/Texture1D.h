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
#include "../DataStream.h"

#include "Enums.h"
#include "Resource.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		
		public ref class Texture1D : public Resource
		{
			int m_Width;
			int m_MipLevels;
			int m_ArraySize;
			SlimDX::Direct3D10::Format m_Format;
			ResourceUsage m_Usage;
			SlimDX::Direct3D10::BindFlags m_BindFlags;
			CpuAccessFlags m_AccessFlags;
			ResourceOptionFlags m_OptionFlags;
			
		internal:
			Texture1D( ID3D10Texture1D* pointer );
			void Construct( ID3D10Texture1D* pointer );
			
		public:
			/// <summary>
			/// Gets the width of the texture in texels.
			/// </summary>
			property int Width
			{
				int get() { return m_Width; }
			}
			
			/// <summary>
			/// Gets the number of subtextures (mipmap levels).
			/// </summary>
			property int MipLevels
			{
				int get() { return m_MipLevels; }
			}
			
			property int ArraySize
			{
				int get() { return m_ArraySize; }
			}
			
			property SlimDX::Direct3D10::Format Format
			{
				SlimDX::Direct3D10::Format get() { return m_Format; }
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
			
			DataStream^ Map( int subResource, MapMode mode, MapFlags flags );
			void Unmap( int subResource );
			
			/// <summary>
			/// Constructs a <see cref="Texture1D"/> from a native pointer.
			/// </summary>
			/// <param name="nativeObject">A native ID3D10Texture1D pointer, as an IntPtr.</param>
			Texture1D( IntPtr nativeObject );
			Texture1D( Device^ device, int width, int mipLevels, int arraySize, SlimDX::Direct3D10::Format format,
				ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags,ResourceOptionFlags optionFlags );
			
			static Texture1D^ FromFile( Device^ device, String^ fileName );
			static Texture1D^ FromStream( Device^ device, Stream^ stream, int sizeInBytes );
		};
	}
};
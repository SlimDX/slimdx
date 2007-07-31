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
#include "../direct3d/..\DataStream.h"
#include "../direct3d/LockedRect.h"

#include "Enums.h"
#include "SampleDescription.h"
#include "Resource.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device;
		
		public ref class Texture2D : public Resource
		{
			int m_Width;
			int m_Height;
			int m_MipLevels;
			int m_ArraySize;
			SlimDX::Direct3D10::Format m_Format;
			SlimDX::Direct3D10::SampleDescription m_SampleDesc;
			ResourceUsage m_Usage;
			SlimDX::Direct3D10::BindFlags m_BindFlags;
			CpuAccessFlags m_AccessFlags;
			ResourceOptionFlags m_OptionFlags;
			
			void Construct( Device^ device, int width, int height, int mipLevels, int arraySize, SlimDX::Direct3D10::Format format,
				int sampleCount, int sampleQuality, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags,
				ResourceOptionFlags optionFlags );
			
		internal:
			Texture2D( ID3D10Texture2D* texture );
			
		public:
			Texture2D( Device^ device, int width, int height, int mipLevels, int arraySize, SlimDX::Direct3D10::Format format,
				int sampleCount, int sampleQuality, ResourceUsage usage, SlimDX::Direct3D10::BindFlags bindFlags, CpuAccessFlags accessFlags,
				ResourceOptionFlags optionFlags );
			
			/// <summary>
			/// Gets the width of the texture in texels.
			/// </summary>
			property int Width
			{
				int get() { return m_Width; }
			}
			
			/// <summary>
			/// Gets the height of the texture in texels.
			/// </summary>
			property int Height
			{
				int get() { return m_Height; }
			}
		
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
			
			property SlimDX::Direct3D10::SampleDescription SampleDescription
			{
				SlimDX::Direct3D10::SampleDescription get() { return m_SampleDesc; }
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
			
			SlimDX::Direct3D::LockedRect Map( int subResource, MapMode mode, MapFlags flags );
			void Unmap( int subResource );
			
			
			static Texture2D^ FromFile( Device^ device, String^ fileName );
		};
	}
};
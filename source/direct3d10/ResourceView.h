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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		public ref class ResourceView : public DirectXBase
		{
			DXOBJECT(ID3D10View);

		private:
			Format format;
            ResourceViewDimension dimension;
            int elementOffset;
            int elementWidth;
            int mipSlice;
            int firstArraySlice;
            int arraySize;
            int firstDepthSlice;
            int depthSize;

		protected:
			ResourceView();
			ResourceView( ID3D10ShaderResourceView* view );
			
		public:
			virtual ~ResourceView() { Destruct(); }

			property SlimDX::Direct3D10::Format Format
            {
				SlimDX::Direct3D10::Format get() { return format; }
			protected:
                void set( SlimDX::Direct3D10::Format value ) { format = value; }
            }

            property ResourceViewDimension Dimension
            {
                ResourceViewDimension get() { return dimension; }
			protected:
                void set( ResourceViewDimension value ) { dimension = value; }
            }

            property int ElementOffset
            {
                int get() { return elementOffset; }
			protected:
                void set( int value ) { elementOffset = value; }
            }

            property int ElementWidth
            {
                int get() { return elementWidth; }
			protected:
                void set( int value ) { elementWidth = value; }
            }

            property int MipSlice
            {
                int get() { return mipSlice; }
			protected:
                void set( int value ) { mipSlice = value; }
            }

            property int FirstArraySlice
            {
                int get() { return firstArraySlice; }
			protected:
                void set( int value ) { firstArraySlice = value; }
            }

            property int ArraySize
            {
                int get() { return arraySize; }
			protected:
                void set( int value ) { arraySize = value; }
            }

            property int FirstDepthSlice
            {
                int get() { return firstDepthSlice; }
			protected:
                void set( int value ) { firstDepthSlice = value; }
            }

            property int DepthSize
            {
                int get() { return depthSize; }
			protected:
                void set( int value ) { depthSize = value; }
            }
		};
	}
};
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
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{	
		public ref class BlendStateDescription
		{
		private:
			bool alphaToCoverageEnabled;
            List<bool>^ renderTargetBlendEnabled;
            BlendOption sourceBlend;
            BlendOption destinationBlend;
            SlimDX::Direct3D10::BlendOperation blendOperation;
            BlendOption sourceAlphaBlend;
            BlendOption destinationAlphaBlend;
            SlimDX::Direct3D10::BlendOperation alphaBlendOperation;
            List<ColorWriteMaskFlags>^ renderTargetWriteMask;

		internal:
			BlendStateDescription( const D3D10_BLEND_DESC& description );
			
			void FillNativeObject( D3D10_BLEND_DESC& description);
			
		public:
			property bool AlphaToCoverageEnabled
            {
                bool get() { return alphaToCoverageEnabled; }
                void set( bool value ) { alphaToCoverageEnabled = value; }
            }

            property ReadOnlyCollection<bool>^ RenderTargetBlendEnabled
            {
                ReadOnlyCollection<bool>^ get() { return gcnew ReadOnlyCollection<bool>( renderTargetBlendEnabled ); }
            }

            property BlendOption SourceBlend
            {
                BlendOption get() { return sourceBlend; }
                void set( BlendOption value ) { sourceBlend = value; }
            }

            property BlendOption DestinationBlend
            {
                BlendOption get() { return destinationBlend; }
                void set( BlendOption value ) { destinationBlend = value; }
            }

            property SlimDX::Direct3D10::BlendOperation BlendOperation
            {
                SlimDX::Direct3D10::BlendOperation get() { return blendOperation; }
                void set( SlimDX::Direct3D10::BlendOperation value ) { blendOperation = value; }
            }

            property BlendOption SourceAlphaBlend
            {
                BlendOption get() { return sourceAlphaBlend; }
                void set( BlendOption value ) { sourceAlphaBlend = value; }
            }

            property BlendOption DestinationAlphaBlend
            {
                BlendOption get() { return destinationAlphaBlend; }
                void set( BlendOption value ) { destinationAlphaBlend = value; }
            }

            property SlimDX::Direct3D10::BlendOperation AlphaBlendOperation
            {
                SlimDX::Direct3D10::BlendOperation get() { return alphaBlendOperation; }
                void set( SlimDX::Direct3D10::BlendOperation value ) { alphaBlendOperation = value; }
            }

            property ReadOnlyCollection<ColorWriteMaskFlags>^ RenderTargetWriteMask
            {
                ReadOnlyCollection<ColorWriteMaskFlags>^ get() { return gcnew ReadOnlyCollection<ColorWriteMaskFlags>( renderTargetWriteMask ); }
            }
			
			BlendStateDescription();
		};
	}
};
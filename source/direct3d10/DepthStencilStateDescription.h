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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{	
		public ref class DepthStencilStateDescription
		{
		private:
			bool depthEnabled;
            DepthWriteMask depthWriteMask;
            Comparison depthComparison;
            bool stencilEnabled;
            Byte stencilReadMask;
            Byte stencilWriteMask;
            Comparison frontStencilComparison;
            StencilOperation frontStencilFailureOperation;
            StencilOperation frontStencilDepthFailureOperation;
            StencilOperation frontStencilPassOperation;
            Comparison backStencilComparison;
            StencilOperation backStencilFailureOperation;
            StencilOperation backStencilDepthFailureOperation;
            StencilOperation backStencilPassOperation;

		internal:
			DepthStencilStateDescription( const D3D10_DEPTH_STENCIL_DESC& description );
			
			void FillNativeObject( D3D10_DEPTH_STENCIL_DESC& description);
			
		public:
			property bool DepthEnabled
            {
                bool get() { return depthEnabled; }
                void set( bool value ) { depthEnabled = value; }
            }

            property DepthWriteMask DepthWriteMask
            {
				SlimDX::Direct3D10::DepthWriteMask get() { return depthWriteMask; }
				void set( SlimDX::Direct3D10::DepthWriteMask value ) { depthWriteMask = value; }
            }

            property Comparison DepthComparison
            {
                Comparison get() { return depthComparison; }
                void set( Comparison value ) { depthComparison = value; }
            }

            property bool StencilEnabled
            {
                bool get() { return stencilEnabled; }
                void set( bool value ) { stencilEnabled = value; }
            }

            property Byte StencilReadMask
            {
                Byte get() { return stencilReadMask; }
                void set( Byte value ) { stencilReadMask = value; }
            }

            property Byte StencilWriteMask
            {
                Byte get() { return stencilWriteMask; }
                void set( Byte value ) { stencilWriteMask = value; }
            }

            property Comparison FrontStencilComparison
            {
                Comparison get() { return frontStencilComparison; }
                void set( Comparison value ) { frontStencilComparison = value; }
            }

            property StencilOperation FrontStencilFailureOperation
            {
                StencilOperation get() { return frontStencilFailureOperation; }
                void set( StencilOperation value ) { frontStencilFailureOperation = value; }
            }

            property StencilOperation FrontStencilDepthFailureOperation
            {
                StencilOperation get() { return frontStencilDepthFailureOperation; }
                void set( StencilOperation value ) { frontStencilDepthFailureOperation = value; }
            }

            property StencilOperation FrontStencilPassOperation
            {
                StencilOperation get() { return frontStencilPassOperation; }
                void set( StencilOperation value ) { frontStencilPassOperation = value; }
            }

            property Comparison BackStencilComparison
            {
                Comparison get() { return backStencilComparison; }
                void set( Comparison value ) { backStencilComparison = value; }
            }

            property StencilOperation BackStencilFailureOperation
            {
                StencilOperation get() { return backStencilFailureOperation; }
                void set( StencilOperation value ) { backStencilFailureOperation = value; }
            }

            property StencilOperation BackStencilDepthFailureOperation
            {
                StencilOperation get() { return backStencilDepthFailureOperation; }
                void set( StencilOperation value ) { backStencilDepthFailureOperation = value; }
            }

            property StencilOperation BackStencilPassOperation
            {
                StencilOperation get() { return backStencilPassOperation; }
                void set( StencilOperation value ) { backStencilPassOperation = value; }
            }
			
			DepthStencilStateDescription();
		};
	}
};
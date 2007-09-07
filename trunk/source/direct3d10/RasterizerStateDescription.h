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
		public ref class RasterizerStateDescription
		{
		private:
			FillMode fillMode;
            CullMode cullMode;
            bool frontIsCounterClockwise;
            int depthBias;
            float depthBiasClamp;
            float slopeScaledDepthBias;
            bool depthClipEnabled;
            bool scissorEnabled;
            bool multisampleEnabled;
            bool antialiasedLineEnabled;

		internal:
			RasterizerStateDescription( const D3D10_RASTERIZER_DESC& desc );
			
			void FillNativeObject( D3D10_RASTERIZER_DESC& desc);
			
		public:
			property SlimDX::Direct3D10::FillMode FillMode
            {
                SlimDX::Direct3D10::FillMode get() { return fillMode; }
                void set( SlimDX::Direct3D10::FillMode value ) { fillMode = value; }
            }

            property SlimDX::Direct3D10::CullMode CullMode
            {
                SlimDX::Direct3D10::CullMode get() { return cullMode; }
                void set( SlimDX::Direct3D10::CullMode value ) { cullMode = value; }
            }

            property bool FrontIsCounterClockwise
            {
                bool get() { return frontIsCounterClockwise; }
                void set( bool value ) { frontIsCounterClockwise = value; }
            }

            property int DepthBias
            {
                int get() { return depthBias; }
                void set( int value ) { depthBias = value; }
            }

            property float DepthBiasClamp
            {
                float get() { return depthBiasClamp; }
                void set( float value ) { depthBiasClamp = value; }
            }

            property float SlopeScaledDepthBias
            {
                float get() { return slopeScaledDepthBias; }
                void set( float value ) { slopeScaledDepthBias = value; }
            }

            property bool DepthClipEnabled
            {
                bool get() { return depthClipEnabled; }
                void set( bool value ) { depthClipEnabled = value; }
            }

            property bool ScissorEnabled
            {
                bool get() { return scissorEnabled; }
                void set( bool value ) { scissorEnabled = value; }
            }

            property bool MultisampleEnabled
            {
                bool get() { return multisampleEnabled; }
                void set( bool value ) { multisampleEnabled = value; }
            }

            property bool AntialiasedLineEnabled
            {
                bool get() { return antialiasedLineEnabled; }
                void set( bool value ) { antialiasedLineEnabled = value; }
            }
			
			RasterizerStateDescription();
		};
	}
};
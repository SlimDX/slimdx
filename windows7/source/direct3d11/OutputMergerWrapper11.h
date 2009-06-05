/*
* Copyright (c) 2007-2009 SlimDX Group
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

namespace SlimDX
{
	namespace Direct3D11
	{
		ref class BlendState;
		ref class DepthStencilState;
		ref class DepthStencilView;
		ref class RenderTargetView;
		
		public ref class OutputMergerWrapper
		{
		private:
			ID3D11DeviceContext* deviceContext;
			
		internal:
			OutputMergerWrapper( ID3D11DeviceContext* device );
			
		public:
			property SlimDX::Direct3D11::DepthStencilState^ DepthStencilState
			{
				void set( SlimDX::Direct3D11::DepthStencilState^ value );
				SlimDX::Direct3D11::DepthStencilState^ get();
			}
			
			property int DepthStencilReference
			{
				void set( int value );
				int get();
			}
			
			property SlimDX::Direct3D11::BlendState^ BlendState
			{
				void set( SlimDX::Direct3D11::BlendState^ value );
				SlimDX::Direct3D11::BlendState^ get();
			}
			
			property Color4 BlendFactor
			{
				void set( Color4 value );
				Color4 get();
			}
			
			property int BlendSampleMask
			{
				void set( int value );
				int get();
			}
			
			void SetTargets( RenderTargetView^ renderTargetView );
			void SetTargets( DepthStencilView^ depthStencilView, RenderTargetView^ renderTargetView );
			void SetTargets( ... array<RenderTargetView^>^ renderTargetViews );
			void SetTargets( DepthStencilView^ depthStencilView, ... array<RenderTargetView^>^ renderTargetViews );
		};
	}
};

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

#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D11
	{	
		public value class BlendStateRendertargetDescription
		{
		private:
			bool m_BlendEnable;
			BlendOption m_SrcBlend;
			BlendOption m_DestBlend;
			Direct3D11::BlendOperation m_BlendOp;
			BlendOption m_SrcBlendAlpha;
			BlendOption m_DestBlendAlpha;
			Direct3D11::BlendOperation m_BlendOpAlpha;
			ColorWriteMaskFlags m_RenderTargetWriteMask;
		internal:
			BlendStateRendertargetDescription( const D3D11_RENDER_TARGET_BLEND_DESC& native );
			
			D3D11_RENDER_TARGET_BLEND_DESC CreateNativeVersion();

		public:
			property bool BlendEnable
			{
				bool get();
				void set( bool value );
			}

			property BlendOption SourceBlend
			{
				BlendOption get();
				void set( BlendOption value );
			}

			property BlendOption DestinationBlend
			{
				BlendOption get();
				void set( BlendOption value );
			}

			property Direct3D11::BlendOperation BlendOperation
			{
				Direct3D11::BlendOperation get();
				void set( Direct3D11::BlendOperation value );
			}

			property BlendOption SourceAlphaBlend
			{
				BlendOption get();
				void set( BlendOption value );
			}

			property BlendOption DestinationAlphaBlend
			{
				BlendOption get();
				void set( BlendOption value );
			}

			property Direct3D11::BlendOperation AlphaBlendOperation
			{
				Direct3D11::BlendOperation get();
				void set( Direct3D11::BlendOperation value );
			}

			property ColorWriteMaskFlags RenderTargetWriteMask
			{
				ColorWriteMaskFlags get();
				void set( ColorWriteMaskFlags value );
			}

			// TODO: Fix
			/*
			static bool operator == ( BlendStateRendertargetDescription left, BlendStateRendertargetDescription right );
			static bool operator != ( BlendStateRendertargetDescription left, BlendStateRendertargetDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( BlendStateRendertargetDescription other );
			static bool Equals( BlendStateRendertargetDescription% value1, BlendStateRendertargetDescription% value2 );
			*/
		};
	
		public value class BlendStateDescription : System::IEquatable<BlendStateDescription>
		{
		private:		
			bool m_AlphaToCoverageEnable;
			bool m_IndependentBlendEnable;
			array<BlendStateRendertargetDescription>^ m_Rendertargets;
		
			// TODO: Remove
			void ConstructLazyProperties();
			
		internal:
			BlendStateDescription( const D3D11_BLEND_DESC& native );
			
			D3D11_BLEND_DESC CreateNativeVersion();
			
		public:
			property bool IsAlphaToCoverageEnabled
			{
				bool get();
				void set( bool value );
			}

			property bool IsIndependentBlendEnabled
			{
				bool get();
				void set( bool value );
			}
			
			static bool operator == ( BlendStateDescription left, BlendStateDescription right );
			static bool operator != ( BlendStateDescription left, BlendStateDescription right );

			virtual int GetHashCode() override;
			virtual bool Equals( System::Object^ obj ) override;
			virtual bool Equals( BlendStateDescription other );
			static bool Equals( BlendStateDescription% value1, BlendStateDescription% value2 );
		};
	}
};

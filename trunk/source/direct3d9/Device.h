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
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

#include "Enums.h"
#include "Direct3D.h"
#include "Vertex.h"
#include "../Direct3D/MiscTypes.h"

using namespace SlimDX::Direct3D;

namespace SlimDX
{
	value class Matrix;

	namespace Direct3D9
	{
		public value class Material
		{
		public:
			ColorValue Diffuse;
			ColorValue Ambient;
			ColorValue Specular;
			ColorValue Emissive;
			float Power;
		};

		[StructLayout( LayoutKind::Sequential )]
		public ref class PresentParameters
		{
		public:
			int BackBufferWidth;
			int BackBufferHeight;
			Format BackBufferFormat;
			int BackBufferCount;

			MultiSampleType MultiSample;
			int MultiSampleQuality;

			SwapEffect SwapEffect;
			IntPtr DeviceWindowHandle;
			bool Windowed;
			bool EnableAutoDepthStencil;
			Format AutoDepthStencilFormat;
			PresentFlag PresentFlag;

			int FullScreenRefreshRateInHz;
			PresentInterval PresentationInterval;
		};

		ref class IndexBuffer;
		ref class VertexBuffer;
		ref class BaseTexture;
		ref class Surface;
		ref class PixelShader;
		ref class VertexShader;

		public ref class Device : public DirectXObject<IDirect3DDevice9>
		{
		private:
			IndexBuffer^ m_Indices;
			VertexFormat m_VertexFormat;
			VertexDeclaration^ m_VertexDecl;

		public:
			Device( IDirect3DDevice9* device );
			Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams );

			// --- Properties ---

			property IndexBuffer^ Indices
			{
				IndexBuffer^ get() { return m_Indices; }
				void set( IndexBuffer^ value );
			}

			property VertexFormat VertexFormat
			{
				SlimDX::Direct3D9::VertexFormat get() { return m_VertexFormat; }
				void set( SlimDX::Direct3D9::VertexFormat value );
			}

			property SlimDX::Direct3D9::VertexDeclaration^ VertexDeclaration
			{
				SlimDX::Direct3D9::VertexDeclaration^ get() { return m_VertexDecl; }
				void set( SlimDX::Direct3D9::VertexDeclaration^ value );
			}

			property bool SoftwareVertexProcessing
			{
				bool get();
				void set( bool value );
			}

			property Material Material
			{
				SlimDX::Direct3D9::Material get();
				void set( SlimDX::Direct3D9::Material value );
			}

			property Viewport Viewport
			{
				SlimDX::Direct3D::Viewport get();
				void set( SlimDX::Direct3D::Viewport value );
			}

			property Drawing::Rectangle ScissorRect
			{
				Drawing::Rectangle get();
				void set( Drawing::Rectangle value );
			}

			property int AvailableTextureMem
			{
				int get();
			}

			property bool ShowCursor
			{
				bool get();
				void set( bool show );
			}

			// --- Methods ---

			bool IsQuerySupported( QueryType type );
			Capabilities GetDeviceCaps();
			int ValidateDevice();

			void TestCooperativeLevel();
			CooperativeLevel CheckCooperativeLevel();
			void Reset( PresentParameters^ presentParams );

			void Clear( ClearFlags clearFlags, int color, float zdepth, int stencil );
			void Clear( ClearFlags clearFlags, Color color, float zdepth, int stencil );
			void BeginScene();
			void EndScene();
			void Present();
			void Present( SlimDX::Direct3D9::Present flags );

			Surface^ GetBackBuffer( int swapChain, int backBuffer );
			Surface^ GetDepthStencilSurface();

			void SetRenderState( RenderState state, int value );
			void SetRenderState( RenderState state, bool value );
			void SetRenderState( RenderState state, float value );
			//TODO: Make this accept only the enums that are legal, rather than everything in the world
			generic<typename T> where T : Enum
			void SetRenderState( RenderState state, T value );

			void SetTextureStageState( int stage, TextureStage type, int value );
			void SetTextureStageState( int stage, TextureStage type, TextureOperation texOp );
			void SetTextureStageState( int stage, TextureStage type, TextureArgument texArg );
			void SetTextureStageState( int stage, TextureStage type, TextureTransform texTransform );
			void SetTextureStageState( int stage, TextureStage type, float value );

			void SetSamplerState( int sampler, SamplerState type, int value );
			void SetSamplerState( int sampler, SamplerState type, TextureAddress texAddr );
			void SetSamplerState( int sampler, SamplerState type, TextureFilter texFilter );

			void SetTransform( TransformState state, Matrix value );
			void SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride );
			void SetStreamSourceFreq( int stream, int frequency );
			void SetTexture( int sampler, BaseTexture^ texture );
			void SetRenderTarget( int rtIndex, Surface^ target );
			void SetPixelShader( PixelShader^ pixelShader );
			void SetVertexShader( VertexShader^ vertexShader );
			
			void SetDepthStencilSurface( Surface^ target );
			
			void DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			void DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
				int numVertices, int startIndex, int primCount );

			generic<typename T> where T : value class
			void DrawUserPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount, array<T>^ data );
		};
	}
}

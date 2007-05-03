#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;

#include "Enums.h"
#include "Vertex.h"
#include "Math.h"

namespace SlimDX
{
	namespace Direct3D
	{
		public value class ColorValue
		{
		public:
			float Alpha, Red, Green, Blue;
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
			DepthFormat AutoDepthStencilFormat;
			PresentFlag PresentFlag;

			int FullScreenRefreshRateInHz;
			PresentInterval PresentationInterval;
		};

		ref class IndexBuffer;
		ref class VertexBuffer;
		ref class RenderStateManager;

		public ref class Device
		{
		private:
			IDirect3DDevice9* m_Device;
			bool m_Disposed;

			RenderStateManager^ m_RenderState;
			IndexBuffer^ m_Indices;
			VertexFormats m_VertexFormat;
			VertexDeclaration^ m_VertexDecl;

		internal:
			property IDirect3DDevice9* InternalPointer
			{
				IDirect3DDevice9* get() { return m_Device; }
			}

		public:
			Device( int adapter, DeviceType deviceType, IntPtr controlHandle, CreateFlags createFlags, PresentParameters^ presentParams );
			~Device();
			!Device();

			property RenderStateManager^ RenderState
			{
				RenderStateManager^ get() { return m_RenderState; }
			}

			property IndexBuffer^ Indices
			{
				IndexBuffer^ get() { return m_Indices; }
				void set( IndexBuffer^ value );
			}

			property VertexFormats VertexFormat
			{
				VertexFormats get() { return m_VertexFormat; }
				void set( VertexFormats value );
			}

			property SlimDX::Direct3D::VertexDeclaration^ VertexDeclaration
			{
				SlimDX::Direct3D::VertexDeclaration^ get() { return m_VertexDecl; }
				void set( SlimDX::Direct3D::VertexDeclaration^ value );
			}

			void Clear( ClearFlags clearFlags, int color, float zdepth, int stencil );
			void Clear( ClearFlags clearFlags, Color color, float zdepth, int stencil );
			void BeginScene();
			void EndScene();
			void Present();

			void SetStreamSource( int stream, VertexBuffer^ streamData, int offsetInBytes, int stride );
			
			void DrawPrimitives( PrimitiveType primitiveType, int startIndex, int primitiveCount );
			void DrawIndexedPrimitives( PrimitiveType primitiveType, int baseVertexIndex, int minVertexIndex, 
				int numVertices, int startIndex, int primCount );
		};
	}
}

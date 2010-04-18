#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device : IDevice, ComObject<ID3D10Device>
		{
			public:
				Device( ID3D10Device* native );
				Device( System::IntPtr native );
				
				virtual IRenderTargetView^ CreateRenderTargetView( IResource^ resource );
				generic<typename T> where T : value class
				virtual IBuffer^ CreateBuffer(BufferDescription bufferDescription, array<T>^ bufferData);
				virtual IBuffer^ CreateEmptyBuffer(BufferDescription bufferDescription);
				virtual IInputLayout^ CreateInputLayout(array<InputElement>^ elements, ShaderSignature signature);//TODO fix this

				virtual void ClearRenderTargetView(IRenderTargetView^ renderTargetView, System::Drawing::Color clearColor);

				virtual void IASetPrimitiveTopology(PrimitiveTopology primitiveTopology);
				virtual void IASetVertexBuffer(int startSlot, VertexBufferBinding vertexBufferBinding);
				virtual void IASetVertexBuffers(int startSlot, array<VertexBufferBinding>^ vertexBufferBindings);
				virtual void IASetInputLayout(IInputLayout^ inputLayout);

				virtual void RSSetViewport(Viewport viewport);
				virtual void RSSetViewports(array<Viewport>^ viewports);

				virtual void OMSetRenderTargets(array<IRenderTargetView^>^ renderTargetViews, IDepthStencilView^ depthStencilView);
				virtual void OMSetRenderTarget(IRenderTargetView^ renderTargetView, IDepthStencilView^ depthStencilView);

				virtual void Draw(int vertexCount, int startLocation);
				
			private:
				ID3D10Device* m_Native;
		};
	}
}
#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class Device10 : IDevice10, ComObject<ID3D10Device>
		{
			public:
				Device10( ID3D10Device* native );
				Device10( System::IntPtr native );
				
				virtual IRenderTargetView10^ CreateRenderTargetView( IResource10^ resource );
				generic<typename T> where T : value class
				virtual IBuffer10^ Device10::CreateBuffer(BufferDescription10 bufferDescription, array<T>^ bufferData);

				virtual void ClearRenderTargetView(IRenderTargetView10^ renderTargetView, System::Drawing::Color clearColor);

				virtual void IASetPrimitiveTopology(PrimitiveTopology10 primitiveTopology);

				virtual void RSSetViewport(Viewport10 viewport);
				virtual void RSSetViewports(array<Viewport10>^ viewports);

				virtual void OMSetRenderTargets(array<IRenderTargetView10^>^ renderTargetViews, IDepthStencilView10^ depthStencilView);
				virtual void OMSetRenderTarget(IRenderTargetView10^ renderTargetView, IDepthStencilView10^ depthStencilView);
			private:
				ID3D10Device* m_Native;
		};
	}
}
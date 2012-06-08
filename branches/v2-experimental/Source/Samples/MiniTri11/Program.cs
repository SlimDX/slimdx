// Copyright (c) 2007-2011 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

using System;
using System.IO;
using System.Windows.Forms;
using SlimBuffer;
using SlimDX;
using SlimDX.Direct3D11;
using SlimDX.DXGI;
using SlimDX.ShaderCompiler;
using SlimMath;

namespace MiniTri11
{
	static class Program
	{
		static void Main()
		{
			ReferenceTracker.TrackReferences = true;
			Form form = new Form();

			IDXGIFactory factory = DXGI.CreateFactory();
			IDXGIAdapter adapter = null;
			factory.EnumAdapters(0, out adapter);

			DXGI_SWAP_CHAIN_DESC swapChainDescription = new DXGI_SWAP_CHAIN_DESC
			{
				BufferCount = 1,
				BufferDesc = new DXGI_MODE_DESC
				{
					Format = DXGI_FORMAT.DXGI_FORMAT_R8G8B8A8_UNORM,
					Height = form.ClientSize.Height,
					RefreshRate = new DXGI_RATIONAL
					{
						Denominator = 1,
						Numerator = 60
					},

					Scaling = DXGI_MODE_SCALING.DXGI_MODE_SCALING_UNSPECIFIED,
					ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER.DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
					Width = form.ClientSize.Width
				},
				BufferUsage = (int)DXGI_USAGE.DXGI_USAGE_RENDER_TARGET_OUTPUT,
				Flags = 0,
				OutputWindow = form.Handle,
				SampleDesc = new DXGI_SAMPLE_DESC
				{
					Count = 1,
					Quality = 0
				},
				SwapEffect = DXGI_SWAP_EFFECT.DXGI_SWAP_EFFECT_DISCARD,
				Windowed = true
			};

			ID3D11Device device = SlimDX.Direct3D11.Direct3D11.CreateDevice(adapter);
			IDXGISwapChain swapChain = null;
			factory.CreateSwapChain(device, swapChainDescription, out swapChain);

			ID3D11Texture2D backbuffer = swapChain.GetBuffer<ID3D11Texture2D>(0);
			ID3D11RenderTargetView view = null;
			device.CreateRenderTargetView(backbuffer, null, out view);

			ID3DBlob vertexShaderBytecode = ShaderCompiler.CompileFromString(File.ReadAllText("MiniTri11.fx"), "MiniTri11.fx", "VS", "vs_4_0");
			ID3DBlob pixelShaderBytecode = ShaderCompiler.CompileFromString(File.ReadAllText("MiniTri11.fx"), "MiniTri11.fx", "PS", "ps_4_0");
			D3D11_INPUT_ELEMENT_DESC[] inputElements = new[] {
				new D3D11_INPUT_ELEMENT_DESC { SemanticName = "POSITION", AlignedByteOffset = 0, SemanticIndex = 0, Format = DXGI_FORMAT.DXGI_FORMAT_R32G32B32A32_FLOAT, InstanceDataStepRate = 0, InputSlot = 0, InputSlotClass = D3D11_INPUT_CLASSIFICATION.D3D11_INPUT_PER_VERTEX_DATA },
				new D3D11_INPUT_ELEMENT_DESC { SemanticName = "COLOR", AlignedByteOffset = 16, SemanticIndex = 0, Format = DXGI_FORMAT.DXGI_FORMAT_R32G32B32A32_FLOAT, InstanceDataStepRate = 0, InputSlot = 0, InputSlotClass = D3D11_INPUT_CLASSIFICATION.D3D11_INPUT_PER_VERTEX_DATA }
			};

			ID3DBlob inputSignature;
			ShaderCompiler.D3DGetInputSignatureBlob(vertexShaderBytecode.GetBufferPointer(), vertexShaderBytecode.GetBufferSize(), out inputSignature);
			ID3D11InputLayout inputLayout;
			device.CreateInputLayout(inputElements, inputElements.Length, inputSignature.GetBufferPointer(), inputSignature.GetBufferSize(), out inputLayout);

			ByteBuffer vertexData = new ByteBuffer(3 * 32);
			vertexData.Write(0 * Vector4.SizeInBytes, new Vector4(0.0f, 0.5f, 0.5f, 1.0f));
			vertexData.Write(1 * Vector4.SizeInBytes, new Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			vertexData.Write(2 * Vector4.SizeInBytes, new Vector4(0.5f, -0.5f, 0.5f, 1.0f));
			vertexData.Write(3 * Vector4.SizeInBytes, new Vector4(0.0f, 1.0f, 0.0f, 1.0f));
			vertexData.Write(4 * Vector4.SizeInBytes, new Vector4(-0.5f, -0.5f, 0.5f, 1.0f));
			vertexData.Write(5 * Vector4.SizeInBytes, new Vector4(0.0f, 0.0f, 1.0f, 1.0f));

			D3D11_BUFFER_DESC vertexBufferDescription = new D3D11_BUFFER_DESC
			{
				BindFlags = 1,//vertex buffer
				ByteWidth = 3 * 32,
				CPUAccessFlags = 0,
				MiscFlags = 0,
				Usage = D3D11_USAGE.D3D11_USAGE_DEFAULT,
				StructureByteStride = 0
			};
			ID3D11Buffer vertexBuffer;
			D3D11_SUBRESOURCE_DATA srd = new D3D11_SUBRESOURCE_DATA
			{
				pSysMem = vertexData.Pin(),
				SysMemPitch = 0,
				SysMemSlicePitch = 0
			};
			device.CreateBuffer(vertexBufferDescription, srd, out vertexBuffer);
			vertexData.Unpin();

			RenderLoop loop = new RenderLoop();
			ID3D11DeviceContext context = null;
			device.GetImmediateContext(out context);

			ID3D11VertexShader vertexShader;
			ID3D11PixelShader pixelShader;
			device.CreateVertexShader(vertexShaderBytecode.GetBufferPointer(), vertexShaderBytecode.GetBufferSize(), null, out vertexShader);
			device.CreatePixelShader(pixelShaderBytecode.GetBufferPointer(), pixelShaderBytecode.GetBufferSize(), null, out pixelShader);
			context.IASetInputLayout(inputLayout);
			context.VSSetShader(vertexShader, null, 0);
			context.PSSetShader(pixelShader, null, 0);
			context.IASetPrimitiveTopology(4);//triangle list
			context.IASetVertexBuffers(0, 1, new ID3D11Buffer[] { vertexBuffer }, new int[] { 32 }, new int[] { 0 });
			context.OMSetRenderTargets( 1, new ID3D11RenderTargetView[] { view }, IntPtr.Zero);

			D3D11_VIEWPORT vp = new D3D11_VIEWPORT {
				Height = form.ClientSize.Height,
				Width = form.ClientSize.Width,
				TopLeftX = 0,
				TopLeftY = 0,
				MinDepth = 0.0f,
				MaxDepth = 1.0f
			};

			context.RSSetViewports( 1, new D3D11_VIEWPORT [] { vp });

			loop.Run(form, () =>
			{
				var clearColor = new SlimDX.Color4 { R = 0.0f, G = 0.0f, B = 0.0f, A = 1.0f };
				context.ClearRenderTargetView(view, clearColor);
				context.Draw(3, 0);
				swapChain.Present(0, 0);
			});

			view.ReleaseReference();
			backbuffer.ReleaseReference();
			swapChain.ReleaseReference();
			device.ReleaseReference();
			adapter.ReleaseReference();
			factory.ReleaseReference();
		}
	}
}
